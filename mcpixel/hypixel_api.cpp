/*
MIT License

Copyright (c) 2022 sbplat

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "mcpixel/common.h"
#include "mcpixel/hypixel_api.h"

#include <sstream>

namespace mcpixel {

HypixelApi::HypixelApi() {
}

HypixelApi::HypixelApi(const std::string key) {
    TestAndSetKey(key);
}

HypixelApi::~HypixelApi() {
}

bool HypixelApi::TestAndSetKey(const std::string key) {
    Logger::Log(MCPIXEL_LOG_DEBUG, "Testing Hypixel API key.");

    cpr::Response response = cpr::Get(kKeyUrl, cpr::Parameters{{"key", key}});
    json::json data;

    try {
        data = json::json::parse(response.text);

    } catch (const json::json::parse_error &e) {
        Logger::Log(MCPIXEL_LOG_WARN, "Could not parse Hypixel API JSON response (url={}, status code={}).\nException: {}", response.url,
                    response.status_code, e.what());
        Logger::Log(MCPIXEL_LOG_TRACE, "Response text: {}", response.text);
        Logger::Log(MCPIXEL_LOG_WARN, "Hypixel API key is invalid!");
        return false;
    }

    if (data["success"]) {
        key_info_.valid = true;
        key_info_.key = data["record"]["key"];
        key_info_.owner_uuid = data["record"]["owner"];
        key_info_.limit = data["record"].value("limit", 0);
        key_info_.total_queries = data["record"].value("totalQueries", 0);

        Logger::Log(MCPIXEL_LOG_DEBUG, "Hypixel API key is valid. {}", key_info_.str());

        return true;

    } else {
        Logger::Log(MCPIXEL_LOG_WARN, "Hypixel API key is invalid!");
        return false;
    }
}

std::string HypixelApi::GetKey() {
    return key_info_.key;
}

HypixelApi::KeyInfo HypixelApi::GetKeyInfo() {
    return key_info_;
}

#ifdef BUILD_HYPIXEL_API_GET_PLAYER_DATA
#undef BUILD_HYPIXEL_API_GET_PLAYER_DATA
#endif
#define BUILD_HYPIXEL_API_GET_PLAYER_DATA(NAME, QUERY, VAR_NAME, URL)                                          \
    std::future<json::json> HypixelApi::Get##NAME(const std::string QUERY) {                                   \
        Logger::Log(MCPIXEL_LOG_DEBUG, "Getting Hypixel " #NAME " information with " #VAR_NAME "={}.", QUERY); \
                                                                                                               \
        if (!key_info_.valid) {                                                                                \
            Logger::Log(MCPIXEL_LOG_ERROR, "HypixelApi::Get" #NAME " was called with an invalid api key!");    \
            MCPIXEL_THROW(std::runtime_error("Invalid Hypixel API key"));                                      \
        }                                                                                                      \
                                                                                                               \
        return cpr::GetCallback([](cpr::Response response) { return json::json::parse(response.text); }, URL,  \
                                cpr::Parameters{{"key", HypixelApi::GetKey()}, {#QUERY, QUERY}});              \
    }

BUILD_HYPIXEL_API_GET_PLAYER_DATA(Player, uuid, uuid, kPlayerUrl)
BUILD_HYPIXEL_API_GET_PLAYER_DATA(Friends, uuid, uuid, kFriendsUrl)
BUILD_HYPIXEL_API_GET_PLAYER_DATA(RecentGames, uuid, uuid, kRecentGamesUrl)
BUILD_HYPIXEL_API_GET_PLAYER_DATA(Status, uuid, uuid, kStatusUrl)
BUILD_HYPIXEL_API_GET_PLAYER_DATA(GuildById, id, id, kGuildUrl)
BUILD_HYPIXEL_API_GET_PLAYER_DATA(GuildByPlayerUuid, player, uuid, kGuildUrl)
BUILD_HYPIXEL_API_GET_PLAYER_DATA(GuildByName, name, name, kGuildUrl)

#undef BUILD_HYPIXEL_API_GET_PLAYER_DATA

#ifdef BUILD_HYPIXEL_API_GET_PLAYER_DATA_RAW
#undef BUILD_HYPIXEL_API_GET_PLAYER_DATA_RAW
#endif
#define BUILD_HYPIXEL_API_GET_PLAYER_DATA_RAW(NAME, QUERY, VAR_NAME, URL)                                      \
    std::future<std::string> HypixelApi::Get##NAME##Raw(const std::string QUERY) {                             \
        Logger::Log(MCPIXEL_LOG_DEBUG, "Getting Hypixel " #NAME " information with " #VAR_NAME "={}.", QUERY); \
                                                                                                               \
        if (!key_info_.valid) {                                                                                \
            Logger::Log(MCPIXEL_LOG_ERROR, "HypixelApi::Get" #NAME " was called with an invalid api key!");    \
            MCPIXEL_THROW(std::runtime_error("Invalid Hypixel API key"));                                      \
        }                                                                                                      \
                                                                                                               \
        return cpr::GetCallback([](cpr::Response response) { return response.text; }, URL,                     \
                                cpr::Parameters{{"key", HypixelApi::GetKey()}, {#QUERY, QUERY}});              \
    }

BUILD_HYPIXEL_API_GET_PLAYER_DATA_RAW(Player, uuid, uuid, kPlayerUrl)
BUILD_HYPIXEL_API_GET_PLAYER_DATA_RAW(Friends, uuid, uuid, kFriendsUrl)
BUILD_HYPIXEL_API_GET_PLAYER_DATA_RAW(RecentGames, uuid, uuid, kRecentGamesUrl)
BUILD_HYPIXEL_API_GET_PLAYER_DATA_RAW(Status, uuid, uuid, kStatusUrl)
BUILD_HYPIXEL_API_GET_PLAYER_DATA_RAW(GuildById, id, id, kGuildUrl)
BUILD_HYPIXEL_API_GET_PLAYER_DATA_RAW(GuildByPlayerUuid, player, uuid, kGuildUrl)
BUILD_HYPIXEL_API_GET_PLAYER_DATA_RAW(GuildByName, name, name, kGuildUrl)

#undef BUILD_HYPIXEL_API_GET_PLAYER_DATA_RAW

std::string HypixelApi::KeyInfo::str() {
    std::stringstream ss;
    ss << "{valid: " << valid << ", key: " << key + ", owner_uuid: " << owner_uuid + ", limit: " << limit + ", total_queries: " << total_queries << "}";
    return ss.str();
}

std::ostream &operator<<(std::ostream &os, HypixelApi::KeyInfo &key_info) {
    os << key_info.str();
    return os;
}

}  // namespace mcpixel
