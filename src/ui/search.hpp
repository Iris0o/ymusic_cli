//
// Created by Iris0 on 06.06.2026.
//

#ifndef YMUSIC_CLI_SEARCH_HPP
#define YMUSIC_CLI_SEARCH_HPP

#include <cpr/cpr.h>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>
#include <vector>
#include "../models/schemas.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/util/ref.hpp"

namespace ui {
using namespace ftxui;
using json = nlohmann::json;

void SearchScreen(const std::string& token) {
    // --- общее состояние ---
    std::string search_query;
    std::vector<Track> results;
    std::vector<std::string> entries;  // строки для Menu, синхронны с results
    int selected = 0;
    bool loading = false;
    std::string error_msg;

    auto screen = ScreenInteractive::TerminalOutput();

    // --- компоненты (создаются один раз) ---
    Component input = Input(&search_query, "Введите запрос...");

    MenuOption menu_option = MenuOption::Vertical();
    Component menu = Menu(&entries, &selected, menu_option);

    // Enter в поле ввода → HTTP-запрос в фоне
    input |= CatchEvent([&](const Event& event) {
        if (event == Event::Return && !loading && !search_query.empty()) {
            loading = true;
            results.clear();
            entries.clear();
            error_msg.clear();
            selected = 0;

            std::string query_copy = search_query;
            std::thread([&, query_copy]() {
                auto res = cpr::Get(
                    cpr::Url{"https://api.music.yandex.net/search"},
                    cpr::Parameters{
                        {"text", query_copy}, {"page", "0"}, {"type", "all"}},
                    cpr::Header{{"Authorization", "OAuth " + token},
                                {"User-Agent", "MusicApp/1.0"}});

                screen.Post([&, res = std::move(res)]() {
                    loading = false;
                    if (res.error) {
                        error_msg = "Ошибка сети: " + res.error.message;
                        return;
                    }
                    if (res.status_code != 200) {
                        error_msg = "HTTP " + std::to_string(res.status_code);
                        return;
                    }
                    try {
                        SearchResponse response;
                        from_json(json::parse(res.text), response);
                        results = response.result.tracks.value_or({}).results;

                        for (const auto& track : results) {
                            std::string artist =
                                track.artists.empty()
                                    ? "неизвестен"
                                    : track.artists.front().name;
                            entries.push_back(
                                track.title + " — " + artist + " [" +
                                std::to_string(track.durationMs / 1000) + "с]");
                        }
                    } catch (const std::exception& e) {
                        error_msg = std::string("Ошибка парсинга: ") + e.what();
                    }
                });
            }).detach();

            return true;
        }
        return false;
    });

    // Container: Tab переключает фокус между input и menu
    auto container = Container::Vertical({input, menu});

    auto renderer = Renderer(container, [&] {
        Elements rows;
        rows.push_back(hbox(text("Поиск: "), input->Render()) | border);

        if (loading) {
            rows.push_back(text(" Загрузка...") | dim);
        } else if (!error_msg.empty()) {
            rows.push_back(text(" " + error_msg) | color(Color::Red));
        } else if (!entries.empty()) {
            rows.push_back(menu->Render() | frame | flex);
        }

        return vbox(rows);
    });

    screen.Loop(renderer);
}

}  // namespace ui

#endif  // YMUSIC_CLI_SEARCH_HPP
