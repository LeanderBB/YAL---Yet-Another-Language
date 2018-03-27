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

#include "yal/parser/stexprcasts.h"
#include "yal/parser/syntaxtreevisitor.h"

namespace yal {

    STExprRangeCast::STExprRangeCast(const STIdentifier* targetType,
                                     const STStmtExpression* expr):
        SyntaxTree(SyntaxTreeType::STExprRangeCast),
        m_targetType(targetType),
        m_expr(expr) {

    }

    void
    STExprRangeCast::acceptVisitor(SyntaxTreeVisitor& visitor) const {
        visitor.visit(*this);
    }
}