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
#include "mcpixel/minecraft_player.h"

namespace mcpixel {

MinecraftPlayer::MinecraftPlayer(const std::string username) {
    username_ = username;

    Logger::Log(MCPIXEL_LOG_DEBUG, "Getting UUID for player with username={}.", username);

    cpr::Response response = MinecraftApi::GetPlayerDb(username_).get();

    if (response.status_code == 200) {
        data = json::json::parse(response.text);

        username_ = data["data"]["player"]["username"];
        uuid_ = data["data"]["player"]["raw_id"];

        if (username != username_) {
            partially_invalid_ = true;

            Logger::Log(MCPIXEL_LOG_DEBUG, "Player with username={} has a partially invalid username.", username);
        }

        return;
    }

    response = MinecraftApi::GetMojang(username_).get();

    if (response.status_code == 200) {
        data = json::json::parse(response.text);

        username_ = data["name"];
        uuid_ = data["id"];

        if (username != username_) {
            partially_invalid_ = true;

            Logger::Log(MCPIXEL_LOG_DEBUG, "Player with username={} has a partially invalid username.", username);
        }

        return;
    }

    Logger::Log(MCPIXEL_LOG_DEBUG, "Player with username={} has an invalid username.", username);

    invalid_ = true;
}

MinecraftPlayer::~MinecraftPlayer() {

}

std::string MinecraftPlayer::GetUsername() {
    return username_;
}

std::string MinecraftPlayer::GetUuid() {
    return uuid_;
}

bool MinecraftPlayer::IsInvalid() {
    return invalid_;
}

bool MinecraftPlayer::IsPartiallyInvalid() {
    return partially_invalid_;
}

} // mcpixel
