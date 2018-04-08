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
#pragma once

#include "yal/parser/syntaxtree.h"

namespace yal {
    class STStatement;

    class STDeclParam {
    public:

        STDeclParam(const STIdentifier* name,
                    const STQualType* type);

        const STIdentifier* getName() const {
            return m_name;
        }

        const STQualType* getType() const {
            return m_type;
        }

        const SourceInfo getSourceInfo() const {
            return m_sourceInfo;
        }

        void setSourceInfo(const SourceInfo& sourceInfo);

    protected:
        const STIdentifier* m_name;
        const STQualType* m_type;
        SourceInfo m_sourceInfo;
    };


    class STDeclFunction final : public STDecl {
    public:
        using Body = std::vector<const STStatement*>;
        using Params = std::vector<const STDeclParam*>;

        STDeclFunction(const STIdentifier* functionName,
                       const STType* functionTarget,
                       const STQualType* returnType,
                       const Params* params,
                       const Body* statements);

        const STIdentifier* getFunctionName() const {
            return m_functionName;
        }

        const STType* getFunctionTarget() const{
            return m_functionTarget;
        }

        const STQualType* getReturnType() const {
            return m_returnType;
        }

        const Body* getBody() const {
            return m_body;
        }

        const Params* getParams() const {
            return m_params;
        }

        void acceptVisitor(SyntaxTreeVisitor& visitor) const override final;

    protected:
        const STIdentifier* m_functionName;
        const STType* m_functionTarget;
        const STQualType* m_returnType;
        const Params* m_params;
        const Body* m_body;
    };

}
