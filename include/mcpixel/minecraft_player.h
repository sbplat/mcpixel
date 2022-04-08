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

#ifndef MCPIXEL_MINECRAFT_PLAYER_H
#define MCPIXEL_MINECRAFT_PLAYER_H

#include "minecraft_api.h"

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <future>
#include <string>

namespace mcpixel {

namespace json = nlohmann;

class MinecraftPlayer {
  public:
    MinecraftPlayer(const std::string username);
    ~MinecraftPlayer();

    std::string GetUsername();
    std::string GetUuid();

    bool IsInvalid();
    bool IsPartiallyInvalid();

  private:
    json::json data;
    bool invalid_ = false, partially_invalid_ = false;
    std::string username_, uuid_;
};

} // mcpixel

#endif // MCPIXEL_MINECRAFT_PLAYER_H
