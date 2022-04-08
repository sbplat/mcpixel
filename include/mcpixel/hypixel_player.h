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

#ifndef MCPIXEL_HYPIXEL_PLAYER_H
#define MCPIXEL_HYPIXEL_PLAYER_H

#include "minecraft_player.h"
#include "hypixel_api.h"

#include <nlohmann/json.hpp>

#include <string>

namespace mcpixel {

namespace json = nlohmann;

class HypixelPlayer: public MinecraftPlayer {
  public:
    HypixelPlayer(HypixelApi &hypixel_api, const std::string username);
    ~HypixelPlayer();

    bool IsNicked();
    bool IsYtOrStaffNicked();

    json::json GetJsonData() const;

    std::string GetDisplayName();
    std::string GetRank();

  private:
    json::json data_;
    std::string display_name_, rank_;
};

} // mcpixel

#endif // MCPIXEL_HYPIXEL_PLAYER_H
