/*
 *  Copyright 2017 by Leander Beernaert (leanderbb@gmail.com)
 *
 *  This file is part of YAL.
 *
 *  YAL is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3
 *  of the License, or (at your option) any later version.
 *
 *  YAL is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with YAL. If not, see <http://www.gnu.org/licenses/>.
 */
#include "yal/util/log.h"
#include "yal/io/bytestream.h"
#include <cstdio>
#include <cstring>
#include <algorithm>
namespace yal{
    Log::Log(ByteStream& stream):
        m_buffer(),
        m_out(stream),
        m_error(stream),
        m_multiLine(false){

    }

    Log::Log(ByteStream& out,
             ByteStream& error):
        m_buffer(),
        m_out(out),
        m_error(error) {

    }

    Log::MultiLineScope::MultiLineScope(Log& log):
        m_log(log) {
        m_log.m_multiLine = true;
    }

    Log::MultiLineScope::~MultiLineScope() {
        m_log.m_multiLine = false;
    }

    void
    Log::message(const char* format, ...) {
        static const char* tag= "[Info] ";
        static const size_t tagLen = ::strlen(tag);
        ::va_list args;
        ::va_start(args, format);
        const size_t size = formatWithTag(tag, tagLen, format, args);
        ::va_end(args);

        if (size >0) {
            m_out.write(m_buffer, size);
        }
    }

    void
    Log::warning(const char* format, ...) {
        static const char* tag= "[Warning] ";
        static const size_t tagLen = ::strlen(tag);
        ::va_list args;
        ::va_start(args, format);
        const size_t size = formatWithTag(tag, tagLen, format, args);
        ::va_end(args);

        if (size >0) {
            m_out.write(m_buffer, size);
        }
    }

    void
    Log::error(const char* format, ...) {
        static const char* tag= "[Error] ";
        static const size_t tagLen = ::strlen(tag);
        ::va_list args;
        ::va_start(args, format);
        const size_t size = formatWithTag(tag, tagLen, format, args);
        ::va_end(args);

        if (size >0) {
            m_error.write(m_buffer, size);
        }
    }

    void
    Log::debug(const char* format, ...) {
        static const char* tag= "[Debug] ";
        static const size_t tagLen = ::strlen(tag);
        ::va_list args;
        ::va_start(args, format);
        const size_t size = formatWithTag(tag, tagLen, format, args);
        ::va_end(args);

        if (size >0) {
            m_out.write(m_buffer, size);
        }
    }

    size_t
    Log::formatWithTag(const char* tag,
                       const size_t tagLen,
                       const char* format,
                       ::va_list args){

        const char* logTag = (m_multiLine ? "--- " : tag);
        const int bytesWrittenTag =  std::snprintf(m_buffer,
                                                   kInternalBufferSizBytes,
                                                   "%*s",
                                                   static_cast<int>(tagLen),
                                                   logTag);
        YAL_ASSERT(bytesWrittenTag >0
                   && static_cast<size_t>(bytesWrittenTag)<= strlen(tag));

        const int bytesWrittenFormat = std::vsnprintf(m_buffer + bytesWrittenTag,
                                                      static_cast<size_t>(static_cast<int>(kInternalBufferSizBytes) - bytesWrittenTag),
                                                      format,
                                                      args);
        YAL_ASSERT(bytesWrittenFormat >= 0);

        return std::min(static_cast<size_t>(bytesWrittenTag)
                        + static_cast<size_t>(bytesWrittenFormat),
                        static_cast<size_t>(kInternalBufferSizBytes));
    }

}