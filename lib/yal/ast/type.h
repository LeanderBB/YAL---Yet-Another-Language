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
#include "yal/ast/identifier.h"
#include "yal/util/stringref.h"
#include "yal/util/cast.h"
#include "yal/util/formattypes.h"
#include <unordered_map>

namespace yal {

    class TypeRegistry;
    class Module;
    class DeclBase;
    class TypeDecl;

    class Type {
        friend class TypeContext;
    public:
        enum class Kind {
#define YAL_AST_TYPE(type) type,
#include "yal/ast/typelist.def"
#undef YAL_AST_TYPE
        };

        Type(const Kind kind);

        Type(const Module*,
             const Kind kind,
             const Identifier& identifier);

        virtual ~Type();

        YAL_NO_COPY_CLASS(Type);

        bool isFunction() const;
        bool isTypeFunction() const;
        bool isBuilitin() const;
        bool isStruct() const;
        bool isAlias() const;
        bool isWeakAlias() const;
        bool isStrongAlias() const;

        bool isModuleDependent() const;
        bool isExternalType() const;
        bool isModuleType() const;
        bool isTriviallyCopiable() const;
        bool isFunctionTargetable() const;

        uint32_t getSizeBytes() const {
            return m_sizeBytes;
        }

        const Identifier& getIdentifier() const {
            return m_identifier;
        }

        const Module* getModule() const {
            return m_module;
        }

        const TypeDecl* getFunctionWithIdentifier(const Identifier& id) const;

        const TypeDecl* getFunctionWithName(const StringRef name) const;

        Kind getKind() const {
            return m_kind;
        }

        uint64_t getTypeId() const {
            return m_typeId;
        }

        bool isCastableTo(const Type* other) const;

   protected:
        virtual bool isCastableToDetail(const Type*) const {
            return false;
        }

    protected:

        void addFunction(TypeDecl* function);

    protected:
        using FunctionMap = std::unordered_map<StringRef,TypeDecl*>;
        uint64_t m_typeId;
        const Module* m_module;
        const Kind m_kind;
        uint32_t m_sizeBytes = 0;
        Identifier m_identifier;
        FunctionMap m_typeFunctions;
        unsigned m_moduleDependent:1;
        unsigned m_moduleExternal:1;
        unsigned m_moduleType:1;
        unsigned m_defined:1;
        unsigned m_trivialCopy:1;
        unsigned m_functionTargetable:1;
        unsigned m_function:1;
        unsigned m_typefunction:1;
        unsigned m_struct:1;
    };

    template <>
    struct cast_typeid<Type> {
        typedef Type::Kind type;
    };

    inline Type::Kind get_typeid(const Type& type) {
        return type.getKind();
    }

#define YAL_AST_TYPE(TYPE) \
    class TYPE;\
    template<> struct cast_typeid< TYPE >{typedef Type::Kind type;}; \
    template<> constexpr cast_typeid< TYPE >::type get_typeid< TYPE >() {return Type::Kind::TYPE ;}
#include "yal/ast/typelist.def"
#undef YAL_AST_TYPE

    inline size_t FormatType(FormatTypeArgs& loc,
                             const Type& value) {
       return FormatType(loc, value.getIdentifier());
    }


    class Qualifier {
    public:        
        Qualifier();

        void setMutable();
        void setImmutable();
        void setReference();
        void setPointer();

        bool isMutable() const;
        bool isImmutable() const;
        bool isReference() const;
        bool isPointer() const;

    private:
        unsigned m_mutable:1;
        unsigned m_reference:1;
        unsigned m_pointer:1;
    };

    inline size_t FormatType(FormatTypeArgs& loc,
                             const Qualifier& value) {
        size_t bytesWritten = 0;
        FormatTypeArgs localArg = loc;
        if (value.isMutable()) {
            bytesWritten += FormatType(localArg, "mut");
            localArg = FormatTypeArgsAdvance(localArg, bytesWritten);
        }

        if (value.isReference()) {
            bytesWritten += FormatType(localArg, "&");
            localArg = FormatTypeArgsAdvance(localArg, bytesWritten);
        }
        return bytesWritten;
    }

    class QualType {
    public:

        static QualType Create(const Qualifier& qualifier,
                               const Type* type);

        bool isValid() const {
            return  m_type != nullptr;
        }

        const Qualifier& getQualifier() const {
            return m_qualifier;
        }

        const Type* getType() const {
            return m_type;
        }
    private:
        Qualifier m_qualifier;
        const Type* m_type = nullptr;
    };

    inline size_t FormatType(FormatTypeArgs& loc,
                             const QualType& value) {
        const size_t bytesWritten = FormatType(loc, value.getQualifier());
        loc.ptr += bytesWritten;
        loc.length -= bytesWritten;
        return bytesWritten + FormatType(loc, *value.getType());
    }
}
