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

// g++ example.cpp -o example.exe -L"./build" -lmcpixel

//#define MCPIXEL_THROW
#include "include/mcpixel/mcpixel.h"

#include <iostream>
#include <string>

void log_callback(int level, std::string message) {
    std::cout << mcpixel::formatter::format("[{}] {}", mcpixel::level::type_names[level], message) << "\n";
}

int main() {
    mcpixel::Logger::SetCallback(log_callback);
    mcpixel::Logger::Log(0, "in logger");

    std::string username;
    std::cin >> username;

    mcpixel::HypixelApi hypixelApi("api-key-here");
    std::cout << hypixelApi.GetKeyInfo().str() << "\n\n";

    mcpixel::HypixelPlayer player(hypixelApi, username);

    std::cout << "Created hypixel player" << std::endl;

    std::cout << "Username: " << player.GetUsername() << "\n"
              << "UUID: " << player.GetUuid() << "\n"
              << "Invalid: " << player.IsInvalid() << " Nicked: " << player.IsNicked() << "\n"
              << "Partially Invalid: " << player.IsPartiallyInvalid() << " YtOrStaffNicked: " << player.IsYtOrStaffNicked() << "\n";

    // std::cout << player.GetJsonData().dump(4);

    return 0;
}
