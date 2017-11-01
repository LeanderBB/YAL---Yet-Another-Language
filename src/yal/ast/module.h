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

#include "yal/io/sourcemanager.h"
#include "yal/ast/astcontext.h"
#include "yal/ast/typecontext.h"
#include <string>

namespace yal {
    class ModuleManager;
    class Module {
    public:
        typedef uint32_t Id;

        Module(const char* name,
               ModuleManager &manager,
               const SourceManager::Handle handle,
               const Id id);

        YAL_MOVE_ONLY_CLASS(Module);

        const char* getName() const {
            return m_name.c_str();
        }

        SourceManager::Handle getSourceHandle() const {
            return m_sourceHandle;
        }

        ASTContext& getASTContext() {
            return m_astContext;
        }

        const DeclModule* getRootASTNode() const {
            return m_rootNode;
        }

        DeclModule* getRootNode() {
            return m_rootNode;
        }

        void setRootNode(DeclModule* node){
            m_rootNode = node;
        }

        Id getId() const {
            return m_id;
        }

        ModuleManager& getManager() {
            const Module* cthis = this;
            return const_cast<ModuleManager&>(cthis->getManager());
        }

        const ModuleManager& getManager() const {
            return m_manager;
        }

        TypeContext& getTypeContext() {
            const Module* cthis = this;
            return const_cast<TypeContext&>(cthis->getTypeContext());
        }

        const TypeContext& getTypeContext() const {
            return m_typeContext;
        }

    private:
        const Id m_id;
        const SourceManager::Handle m_sourceHandle;
        ModuleManager& m_manager;
        const std::string m_name;
        ASTContext m_astContext;
        TypeContext m_typeContext;
        DeclModule* m_rootNode;
    };
}