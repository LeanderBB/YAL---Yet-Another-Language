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
#pragma once

#include <string>
#include <iostream>
namespace yal {

    // Only Exists so that it can be used in the parser
    // since it's trivially constructable.
    struct StringRefPod
    {
        const char* str;
        size_t size;
    };

    class StringRef
    {
    public:
        StringRef() = default;

        ~StringRef() = default;

        StringRef(const char* str);

        StringRef(const char* str,
                  const size_t len);

        // Note: String must remain alive while this instance of StringRef
        // is alive
        StringRef(const std::string& str);

        StringRef(const StringRefPod& pod);

        StringRef(const StringRef& other) = default;
        StringRef(StringRef&& other);

        StringRef& operator=(const StringRef& other) = default;
        StringRef& operator=(StringRef&& other);
        StringRef& operator=(const StringRefPod& pod);

        size_t length() const;

        size_t size() const;

        bool operator == (const StringRef& other) const;
        bool operator != (const StringRef& other) const;

        bool operator == (const std::string& other) const;
        bool operator != (const std::string& other) const;

        bool operator == (const char* other) const;
        bool operator != (const char* other) const;

        char operator[](size_t i) const;

        const char* data() const {
            return m_str;
        }

        std::string toString() const;

        StringRefPod toStringRefPod() const;

    private:
        const char* m_str = nullptr;
        size_t m_size = 0;
    };
}

namespace std {
    template<> struct hash<yal::StringRef> {
        typedef yal::StringRef argument_type;
        typedef std::size_t result_type;
        result_type operator()(argument_type const& s) const noexcept
        {
            //TODO: Improve hashing function
            size_t result = 0;
            const size_t prime = 31;
            for (size_t i = 0; i < s.size(); ++i) {
                result = static_cast<size_t>(s[i]) + (result * prime);
            }
            return result;
        }
    };
}

inline std::ostream& operator<<(std::ostream &os, const yal::StringRef& strRef) {
    if (strRef.size() != 0) {
        os.write(strRef.data(), strRef.size());
    }
    return os;
}