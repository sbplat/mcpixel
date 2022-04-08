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
#include "mcpixel/hypixel_player.h"

namespace mcpixel {

HypixelPlayer::HypixelPlayer(HypixelApi &hypixel_api, const std::string username) : MinecraftPlayer(username) {
    if (!IsNicked()) {
        std::future<json::json> response = hypixel_api.GetPlayer(MinecraftPlayer::GetUuid());

        data_ = response.get();
    }
}

HypixelPlayer::~HypixelPlayer() {
}

bool HypixelPlayer::IsNicked() {
    return MinecraftPlayer::IsInvalid();
}

bool HypixelPlayer::IsYtOrStaffNicked() {
    return MinecraftPlayer::IsPartiallyInvalid();
}

json::json HypixelPlayer::GetJsonData() const {
    return data_;
}

std::string HypixelPlayer::GetDisplayName() {
    return display_name_;
}

std::string HypixelPlayer::GetRank() {
    return rank_;
}

}  // namespace mcpixel
