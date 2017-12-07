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

#include "yal/yal.h"
#include <vector>
#include "yal/util/allocatorstack.h"

namespace yal {
    class DeclModule;
    class DeclBase;
    class ASTContext {
    public:

        using DeclBaseList = std::vector<DeclBase*>;
        using DeclModuleList = std::vector<DeclModule*>;

        ASTContext();

        ~ASTContext();

        YAL_MOVE_ONLY_CLASS(ASTContext);

        void* allocate(const size_t size);

        void addDtor(void* ptr, void(*dtor)(void*));

        AllocatorStack& getAllocator() {
            return m_allocator;
        }

        void addNode(DeclBase* node);

        void addNode(DeclModule* node);

        DeclBaseList& getDeclNodes() {
            return m_declNodes;
        }

        const DeclBaseList& getDeclNodes() const{
            return m_declNodes;
        }

        DeclModuleList& getDeclModules() {
            return m_moduleNodes;
        }

        const DeclModuleList& getDeclModules() const {
            return m_moduleNodes;
        }

    private:
        using DtorList = std::vector<std::pair<void*,void(*)(void*)>>;
        AllocatorStack m_allocator;
        DeclBaseList m_declNodes;
        DeclModuleList m_moduleNodes;
        DtorList m_dtors;
    };
}
