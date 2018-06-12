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

#include "yal/frontend/parser/stexprvarref.h"
#include "yal/frontend/parser/syntaxtreevisitor.h"

namespace yal::frontend {

    STExprVarRef::STExprVarRef(const STIdentifier* identifier):
        STExpression(SyntaxTreeType::STExprVarRef),
        m_varRef(identifier) {

    }

    void
    STExprVarRef::acceptVisitor(SyntaxTreeVisitor& visitor) const {
        visitor.visit(*this);
    }

    // -----------------------------------------------------------------------

    STExprStructVarRef::STExprStructVarRef(const STExpression *expression,
                                           const STIdentifier* identitifer):
        STExpression(SyntaxTreeType::STExprStructVarRef),
        m_expr(expression),
        m_varRef(identitifer) {

    }

    void
    STExprStructVarRef::acceptVisitor(SyntaxTreeVisitor& visitor) const {
        visitor.visit(*this);
    }

}