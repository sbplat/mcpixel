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

#ifndef MCPIXEL_COMMON_H
#define MCPIXEL_COMMON_H

#include "logger.h"

#ifndef MCPIXEL_THROW
#define MCPIXEL_THROW(exception) throw (exception)
#endif // MCPIXEL_THROW

#define MCPIXEL_LOG_TRACE 0
#define MCPIXEL_LOG_DEBUG 1
#define MCPIXEL_LOG_INFO 2
#define MCPIXEL_LOG_WARN 3
#define MCPIXEL_LOG_ERROR 4
#define MCPIXEL_LOG_CRITICAL 5

#endif // MCPIXEL_COMMON_H
