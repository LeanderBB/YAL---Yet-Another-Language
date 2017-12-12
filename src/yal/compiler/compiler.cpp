/*
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

#include "yal/compiler/compiler.h"
#include "yal/util/log.h"
#include "yal/ast/modulemanager.h"
#include "yal/lexer/lexer.h"
#include "yal/parser/parser.h"
#include "yal/ast/astprinter.h"
#include "yal/compiler/cpassscopetyperesolve.h"

namespace yal {
    Compiler::Compiler(Log& log,
                       SourceManager& srcManager,
                       ModuleManager& moduleManager):
        m_log(log),
        m_srcManager(srcManager),
        m_moduleManager(moduleManager){

    }


    void
    Compiler::setFlags(const uint64_t flags) {
        m_flags = flags;
    }

    Module*
    Compiler::compile(const SourceManager::Handle source){
        yal::SourceItem* sourceItem = m_srcManager.getItem(source);
        if (sourceItem == nullptr) {
            m_log.error("Could not locate item from source handle.\n");
            return nullptr;
        }

        yal::Module* module =
                m_moduleManager.createNew(sourceItem->getPath(), source);
        if (module == nullptr) {
            m_log.error("Failed to create module with name '%'.\n",
                        sourceItem->getPath());
            return nullptr;
        }

        // Run Parsers
        {
            yal::Lexer lexer (sourceItem->getByteStream());
            yal::Parser parser(lexer, m_log, *module);

            yal::Parser::Result parseResult = parser.run();

            if (parseResult != yal::Parser::Result::Ok) {
                return nullptr;
            }
        }

        // type regestriation pass
        {
            yal::CPassScopeTypeResolve typeRegPass;
            const bool result = typeRegPass.run(m_log, *module, m_srcManager);
            if (!result) {
                return nullptr;
            }
        }

        return module;
    }
}
