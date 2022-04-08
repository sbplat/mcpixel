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

#ifndef MCPIXEL_LOGGER_H
#define MCPIXEL_LOGGER_H

#include "format.h"

#include <functional>
#include <string>

namespace mcpixel {

namespace level {

enum type : int { TRACE, DEBUG, INFO, WARN, ERROR, CRITICAL };

const std::string type_names[6] = {"trace", "debug", "info", "warn", "error", "critical"};

}  // namespace level

namespace Logger {

static std::function<void(int, std::string)> callback_;

void SetCallback(const std::function<void(int, std::string)> callback);
std::function<void(int, std::string)> GetCallback();

void LogRawMessage(const int level, const std::string message);

template<typename ...Args>
void Log(const int level, const std::string format_string, Args&&... args) {
    return LogRawMessage(level, formatter::format(format_string, std::forward<Args>(args)...));
}

template<typename ...Args>
void Log(const int level, const char* format_string, Args&&... args) {
    return Log(level, std::string(format_string), std::forward<Args>(args)...);
}

} // Logger

}  // namespace mcpixel

#endif  // MCPIXEL_LOGGER_H
