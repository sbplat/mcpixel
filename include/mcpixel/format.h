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

#ifndef MCPIXEL_FORMAT_H
#define MCPIXEL_FORMAT_H

#include <sstream>
#include <string>
#include <vector>

namespace mcpixel {

namespace formatter {

inline void unpack(std::vector<std::string> &unpacked_args) {
    // Do nothing
}

template <typename Arg>
inline void unpack(std::vector<std::string> &unpacked_args, Arg arg) {
    std::stringstream buffer;
    buffer << arg;
    unpacked_args.push_back(buffer.str());
}

template <typename Arg, typename... Args>
inline void unpack(std::vector<std::string> &unpacked_args, Arg arg, Args &&...args) {
    std::stringstream buffer;
    buffer << arg;
    unpacked_args.push_back(buffer.str());
    unpack(unpacked_args, std::forward<Args>(args)...);
}

template <typename... Args>
std::string format(std::string format_string, Args &&...args) {
    std::vector<std::string> unpacked_args;
    unpack(unpacked_args, std::forward<Args>(args)...);

    std::stringstream ss;
    int current_arg = 0;

    std::string::iterator it = format_string.begin();
    bool in_bracket = false;

    while (it < format_string.end()) {
        if (in_bracket) {
            if (*it == '}') {
                in_bracket = false;
            }

        } else if (*it == '{') {
            in_bracket = true;
            ss << unpacked_args.at(current_arg++);

        } else {
            ss << *it;
        }

        ++it;
    }

    return ss.str();
}

}  // namespace formatter

}  // namespace mcpixel

#endif  // MCPIXEL_FORMAT_H
