/*
 *  Copyright 2018 by Leander Beernaert (lbb-dev@pm.me)
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

#include "yal/yal.h"
#include "yal/util/stringref.h"

#include <unordered_map>
#include <optional>

namespace yal {

    class StringPool {
    public:
        StringPool() = default;
        YAL_NO_COPY_CLASS(StringPool);

        StringRef getOrCreate(const StringRef string);

        std::optional<StringRef> get(const StringRef string) const;

    protected:
        using StringMap = std::unordered_map<StringRef, std::string>;
        StringMap m_map;
    };

}