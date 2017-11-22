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

#include "yal/ast/declvar.h"
#include "yal/ast/nodecontainer.h"

namespace yal {

    class DeclParamVar : public DeclVar{
    public:
        DeclParamVar(Module& module,
                     StringRef name,
                     const RefType* varType);
    };





    class DeclParamVarContainer :
            public NodeContainer<DeclParamVar*,AstType::DeclParamVarContainer> {
        using BaseType = NodeContainer<DeclParamVar*,AstType::DeclParamVarContainer>;
    public:

        DeclParamVarContainer(Module& module);

        DeclParamVarContainer(Module& module,
                              ContainerType&& params);

        void addDeclParam(DeclParamVar* decl);

    };

    inline AstType get_typeid(const DeclParamVarContainer& container) {
        return container.getAstType();
    }
}