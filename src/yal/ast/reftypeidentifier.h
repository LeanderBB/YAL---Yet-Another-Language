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

#include "yal/ast/reftype.h"
#include "yal/util/stringref.h"
namespace yal{

    class RefTypeIdentifier : public RefType
    {
    public:
        RefTypeIdentifier(Module& module,
                          const StringRef identifier,
                          const Qualifier qualifier);

        RefTypeIdentifier(Module& module,
                          const StringRef identifier);

        StringRef getIdentifier() const {
            return m_identifier;
        }

    protected:
        StringRef m_identifier;
    };

}