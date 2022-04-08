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

#ifndef MCPIXEL_HYPIXEL_API_H
#define MCPIXEL_HYPIXEL_API_H

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <future>
#include <ostream>
#include <string>

namespace mcpixel {

namespace json = nlohmann;

class HypixelApi {
  public:
    struct KeyInfo {
        bool valid = false;
        std::string key,
            owner_uuid;
        int limit = 0, total_queries = 0;

        std::string str();
    };

    HypixelApi();
    HypixelApi(const std::string key);
    ~HypixelApi();

    bool TestAndSetKey(const std::string key);
    std::string GetKey();
    KeyInfo GetKeyInfo();

    std::future<json::json> GetPlayer(const std::string uuid);
    std::future<json::json> GetFriends(const std::string uuid);
    std::future<json::json> GetRecentGames(const std::string uuid);
    std::future<json::json> GetStatus(const std::string uuid);
    std::future<json::json> GetGuildById(const std::string uuid);
    std::future<json::json> GetGuildByPlayerUuid(const std::string uuid);
    std::future<json::json> GetGuildByName(const std::string uuid);

    std::future<std::string> GetPlayerRaw(const std::string uuid);
    std::future<std::string> GetFriendsRaw(const std::string uuid);
    std::future<std::string> GetRecentGamesRaw(const std::string uuid);
    std::future<std::string> GetStatusRaw(const std::string uuid);
    std::future<std::string> GetGuildByIdRaw(const std::string uuid);
    std::future<std::string> GetGuildByPlayerUuidRaw(const std::string uuid);
    std::future<std::string> GetGuildByNameRaw(const std::string uuid);

  private:
    const cpr::Url kKeyUrl{"https://api.hypixel.net/key"},
          kPlayerUrl{"https://api.hypixel.net/player"},
          kFriendsUrl{"https://api.hypixel.net/friends"},
          kRecentGamesUrl{"https://api.hypixel.net/recentgames"},
          kStatusUrl{"https://api.hypixel.net/status"},
          kGuildUrl{"https://api.hypixel.net/guild"};
    KeyInfo key_info_ = {};
};

std::ostream& operator<<(std::ostream &os, HypixelApi::KeyInfo &key_info);

} // mcpixel

#endif // MCPIXEL_HYPIXEL_API_H
