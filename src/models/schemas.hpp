//
// Created by Iris0 on 06.06.2026.
//

#ifndef YMUSIC_CLI_SCHEMAS_HPP
#define YMUSIC_CLI_SCHEMAS_HPP

#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <variant>
#include <vector>

using json = nlohmann::json;

template <typename T>
static void get_opt(const json& j, const char* key, std::optional<T>& out) {
    if (j.contains(key) && !j.at(key).is_null()) {
        out = j.at(key).get<T>();
    }
}

template <typename T>
static void get_if(const json& j, const char* key, T& out) {
    if (j.contains(key) && !j.at(key).is_null()) {
        j.at(key).get_to(out);
    }
}

struct InvocationInfo {
    std::string hostname;
    std::string reqId;
    std::string execDurationMillis;
};

inline void from_json(const json& j, InvocationInfo& v) {
    get_if(j, "hostname", v.hostname);
    get_if(j, "req-id", v.reqId);
    get_if(j, "exec-duration-millis", v.execDurationMillis);
}

struct Cover {
    std::string type;
    std::string uri;
    std::optional<std::string> prefix;
};

inline void from_json(const json& j, Cover& v) {
    get_if(j, "type", v.type);
    get_if(j, "uri", v.uri);
    get_opt(j, "prefix", v.prefix);
}

struct Label {
    int id{};
    std::string name;
};

inline void from_json(const json& j, Label& v) {
    get_if(j, "id", v.id);
    get_if(j, "name", v.name);
}

struct ArtistCounts {
    int tracks{};
    int directAlbums{};
    int alsoAlbums{};
    int alsoTracks{};
};

inline void from_json(const json& j, ArtistCounts& v) {
    get_if(j, "tracks", v.tracks);
    get_if(j, "directAlbums", v.directAlbums);
    get_if(j, "alsoAlbums", v.alsoAlbums);
    get_if(j, "alsoTracks", v.alsoTracks);
}

struct ArtistRatings {
    int week{};
    int month{};
    int day{};
};

inline void from_json(const json& j, ArtistRatings& v) {
    get_if(j, "week", v.week);
    get_if(j, "month", v.month);
    get_if(j, "day", v.day);
}

struct ArtistLink {
    std::string title;
    std::string href;
    std::string type;
    std::optional<std::string> socialNetwork;
};

inline void from_json(const json& j, ArtistLink& v) {
    get_if(j, "title", v.title);
    get_if(j, "href", v.href);
    get_if(j, "type", v.type);
    get_opt(j, "socialNetwork", v.socialNetwork);
}

struct ArtistResult {
    int id{};
    std::string name;
    bool various{};
    bool composer{};
    std::optional<Cover> cover;
    std::optional<std::string> ogImage;
    std::vector<std::string> genres;
    std::optional<ArtistCounts> counts;
    bool available{};
    std::vector<std::string> disclaimers;
    std::optional<ArtistRatings> ratings;
    std::vector<ArtistLink> links;
    bool ticketsAvailable{};
    std::vector<std::string> regions;
};

inline void from_json(const json& j, ArtistResult& v) {
    get_if(j, "id", v.id);
    get_if(j, "name", v.name);
    get_if(j, "various", v.various);
    get_if(j, "composer", v.composer);
    get_opt(j, "cover", v.cover);
    get_opt(j, "ogImage", v.ogImage);
    get_if(j, "genres", v.genres);
    get_opt(j, "counts", v.counts);
    get_if(j, "available", v.available);
    get_if(j, "disclaimers", v.disclaimers);
    get_opt(j, "ratings", v.ratings);
    get_if(j, "links", v.links);
    get_if(j, "ticketsAvailable", v.ticketsAvailable);
    get_if(j, "regions", v.regions);
}

struct Major {
    int id{};
    std::string name;
};

inline void from_json(const json& j, Major& v) {
    get_if(j, "id", v.id);
    get_if(j, "name", v.name);
}

struct R128 {
    double i{};
    double tp{};
};

inline void from_json(const json& j, R128& v) {
    get_if(j, "i", v.i);
    get_if(j, "tp", v.tp);
}

struct Fade {
    double inStart{};
    double inStop{};
    double outStart{};
    double outStop{};
};

inline void from_json(const json& j, Fade& v) {
    get_if(j, "inStart", v.inStart);
    get_if(j, "inStop", v.inStop);
    get_if(j, "outStart", v.outStart);
    get_if(j, "outStop", v.outStop);
}

struct DerivedColors {
    std::string average;
    std::string waveText;
    std::string miniPlayer;
    std::string accent;
};

inline void from_json(const json& j, DerivedColors& v) {
    get_if(j, "average", v.average);
    get_if(j, "waveText", v.waveText);
    get_if(j, "miniPlayer", v.miniPlayer);
    get_if(j, "accent", v.accent);
}

struct LyricsInfo {
    bool hasAvailableSyncLyrics{};
    bool hasAvailableTextLyrics{};
};

inline void from_json(const json& j, LyricsInfo& v) {
    get_if(j, "hasAvailableSyncLyrics", v.hasAvailableSyncLyrics);
    get_if(j, "hasAvailableTextLyrics", v.hasAvailableTextLyrics);
}

struct TrackPosition {
    int volume{};
    int index{};
};

inline void from_json(const json& j, TrackPosition& v) {
    get_if(j, "volume", v.volume);
    get_if(j, "index", v.index);
}

struct Album {
    int id{};
    std::string title;
    std::string type;
    std::string metaType;
    std::optional<std::string> contentWarning;
    std::string coverUri;
    std::string ogImage;
    std::optional<std::string> genre;
    int trackCount{};
    int likesCount{};
    bool recent{};
    bool veryImportant{};
    std::vector<ArtistResult> artists;
    std::vector<Label> labels;
    bool available{};
    bool availableForPremiumUsers{};
    std::vector<std::string> availableForOptions;
    bool availableForMobile{};
    bool availablePartially{};
    std::vector<int> bests;
    std::vector<std::string> disclaimers;
    bool listeningFinished{};
    std::optional<TrackPosition> trackPosition;
    std::optional<std::string> storageDir;
    std::optional<std::vector<std::string>> regions;
    std::optional<std::vector<std::string>> availableRegions;
};

inline void from_json(const json& j, Album& v) {
    get_if(j, "id", v.id);
    get_if(j, "title", v.title);
    get_if(j, "type", v.type);
    get_if(j, "metaType", v.metaType);
    get_opt(j, "contentWarning", v.contentWarning);
    get_if(j, "coverUri", v.coverUri);
    get_if(j, "ogImage", v.ogImage);
    get_opt(j, "genre", v.genre);
    get_if(j, "trackCount", v.trackCount);
    get_if(j, "likesCount", v.likesCount);
    get_if(j, "recent", v.recent);
    get_if(j, "veryImportant", v.veryImportant);
    get_if(j, "artists", v.artists);
    if (j.contains("labels") && !j.at("labels").empty() &&
        j.at("labels")[0].is_object()) {
        j.at("labels").get_to(v.labels);
    }
    get_if(j, "available", v.available);
    get_if(j, "availableForPremiumUsers", v.availableForPremiumUsers);
    get_if(j, "availableForOptions", v.availableForOptions);
    get_if(j, "availableForMobile", v.availableForMobile);
    get_if(j, "availablePartially", v.availablePartially);
    get_if(j, "bests", v.bests);
    get_if(j, "disclaimers", v.disclaimers);
    get_if(j, "listeningFinished", v.listeningFinished);
    get_opt(j, "trackPosition", v.trackPosition);
    get_opt(j, "storageDir", v.storageDir);
    get_opt(j, "regions", v.regions);
    get_opt(j, "availableRegions", v.availableRegions);
}

struct Track {
    int id{};
    std::string realId;
    std::string title;
    std::optional<std::string> contentWarning;
    Major major;
    bool available{};
    bool availableForPremiumUsers{};
    bool availableFullWithoutPermission{};
    std::vector<std::string> availableForOptions;
    std::vector<std::string> disclaimers;
    std::string storageDir;
    int durationMs{};
    int fileSize{};
    R128 r128;
    Fade fade;
    int previewDurationMs{};
    std::vector<ArtistResult> artists;
    std::vector<Album> albums;
    std::string coverUri;
    std::optional<DerivedColors> derivedColors;
    std::string ogImage;
    bool lyricsAvailable{};
    std::string type;
    bool rememberPosition{};
    std::optional<std::string> shortDescription;
    std::optional<std::string> podcastEpisodeType;
    std::optional<std::string> pubDate;
    std::string trackSharingFlag;
    LyricsInfo lyricsInfo;
    std::string trackSource;
    bool availableAsRbt{};
    bool isExplicit{};
    std::vector<std::string> regions;
};

inline void from_json(const json& j, Track& v) {
    get_if(j, "id", v.id);
    get_if(j, "realId", v.realId);
    get_if(j, "title", v.title);
    get_opt(j, "contentWarning", v.contentWarning);
    get_if(j, "major", v.major);
    get_if(j, "available", v.available);
    get_if(j, "availableForPremiumUsers", v.availableForPremiumUsers);
    get_if(j, "availableFullWithoutPermission",
           v.availableFullWithoutPermission);
    get_if(j, "availableForOptions", v.availableForOptions);
    get_if(j, "disclaimers", v.disclaimers);
    get_if(j, "storageDir", v.storageDir);
    get_if(j, "durationMs", v.durationMs);
    get_if(j, "fileSize", v.fileSize);
    get_if(j, "r128", v.r128);
    get_if(j, "fade", v.fade);
    get_if(j, "previewDurationMs", v.previewDurationMs);
    get_if(j, "artists", v.artists);
    get_if(j, "albums", v.albums);
    get_if(j, "coverUri", v.coverUri);
    get_opt(j, "derivedColors", v.derivedColors);
    get_if(j, "ogImage", v.ogImage);
    get_if(j, "lyricsAvailable", v.lyricsAvailable);
    get_if(j, "type", v.type);
    get_if(j, "rememberPosition", v.rememberPosition);
    get_opt(j, "shortDescription", v.shortDescription);
    get_opt(j, "podcastEpisodeType", v.podcastEpisodeType);
    get_opt(j, "pubDate", v.pubDate);
    get_if(j, "trackSharingFlag", v.trackSharingFlag);
    get_if(j, "lyricsInfo", v.lyricsInfo);
    get_if(j, "trackSource", v.trackSource);
    get_if(j, "availableAsRbt", v.availableAsRbt);
    get_if(j, "explicit", v.isExplicit);
    get_if(j, "regions", v.regions);
}

struct TracksPage {
    int total{};
    int perPage{};
    int order{};
    std::vector<Track> results;
};

inline void from_json(const json& j, TracksPage& v) {
    get_if(j, "total", v.total);
    get_if(j, "perPage", v.perPage);
    get_if(j, "order", v.order);
    get_if(j, "results", v.results);
}

struct ArtistsPage {
    int total{};
    int perPage{};
    int order{};
    std::vector<ArtistResult> results;
};

inline void from_json(const json& j, ArtistsPage& v) {
    get_if(j, "total", v.total);
    get_if(j, "perPage", v.perPage);
    get_if(j, "order", v.order);
    get_if(j, "results", v.results);
}

struct AlbumsPage {
    int total{};
    int perPage{};
    int order{};
    std::vector<Album> results;
};

inline void from_json(const json& j, AlbumsPage& v) {
    get_if(j, "total", v.total);
    get_if(j, "perPage", v.perPage);
    get_if(j, "order", v.order);
    get_if(j, "results", v.results);
}

struct Best {
    std::string type;
    std::variant<ArtistResult, Track, Album> result;
};

inline void from_json(const json& j, Best& v) {
    get_if(j, "type", v.type);
    if (!j.contains("result")) {
        return;
    }
    if (v.type == "artist") {
        v.result = j.at("result").get<ArtistResult>();
    } else if (v.type == "track") {
        v.result = j.at("result").get<Track>();
    } else {
        v.result = j.at("result").get<Album>();
    }
}

struct SearchResult {
    bool misspellCorrected{};
    bool nocorrect{};
    std::string searchRequestId;
    std::string text;
    std::optional<Best> best;
    std::optional<TracksPage> tracks;
    std::optional<TracksPage> podcast_episodes;
    std::optional<ArtistsPage> artists;
    std::optional<AlbumsPage> albums;
};

inline void from_json(const json& j, SearchResult& v) {
    get_if(j, "misspellCorrected", v.misspellCorrected);
    get_if(j, "nocorrect", v.nocorrect);
    get_if(j, "searchRequestId", v.searchRequestId);
    get_if(j, "text", v.text);
    get_opt(j, "best", v.best);
    get_opt(j, "tracks", v.tracks);
    get_opt(j, "podcast_episodes", v.podcast_episodes);
    get_opt(j, "artists", v.artists);
    get_opt(j, "albums", v.albums);
}

struct SearchResponse {
    InvocationInfo invocationInfo;
    SearchResult result;
};

inline void from_json(const json& j, SearchResponse& v) {
    get_if(j, "invocationInfo", v.invocationInfo);
    get_if(j, "result", v.result);
}

#endif  // YMUSIC_CLI_SCHEMAS_HPP
