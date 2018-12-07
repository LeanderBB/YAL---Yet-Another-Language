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

#include "yal/error/error.h"

namespace yal::frontend {

    class ErrorFrontend : public Error
    {
    public:

        virtual ~ErrorFrontend() {}

        void print(ErrorPrinter& printer) const override final;

    protected:

        ErrorFrontend(const ErrorCode code);

        virtual void printDetail(ErrorPrinter& printer) const = 0;

        virtual const SourceInfo& getSourceInfo() const = 0;
    };

}
