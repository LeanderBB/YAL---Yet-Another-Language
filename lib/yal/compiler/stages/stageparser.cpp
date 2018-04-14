/*
 *  Copyright 2018 by Leander Beernaert (leanderbb@gmail.com)
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

#include "yal/compiler/stages/stageparser.h"
#include "yal/compiler/compiler.h"

namespace yal {

    StageParser::StageParser(Compiler& compiler,
                             SourceItem& item):
     m_lexer(item.getByteStream()),
     m_parser(m_lexer, compiler.getErrorReporter(), item){

    }

    bool
    StageParser::execute() {
        return m_parser.parse();
    }

    const frontend::STDeclModule*
    StageParser::getSyntaxTree() const {
        return m_parser.getDeclModule();
    }
}
