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
#include "mcpixel/minecraft_api.h"

namespace mcpixel {

namespace MinecraftApi {

std::future<cpr::Response> GetMojang(const std::string username) {
    Logger::Log(MCPIXEL_LOG_DEBUG, "Getting uuid through Mojang with username={}.", username);

    return cpr::GetAsync(cpr::Url{kMojangUrl + username});
}

std::future<cpr::Response> GetPlayerDb(const std::string username) {
    Logger::Log(MCPIXEL_LOG_DEBUG, "Getting uuid through PlayerDB with username={}.", username);

    return cpr::GetAsync(cpr::Url{kPlayerDbUrl + username});
}

} // MinecraftApi

} // mcpixel
