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

#include "yal/frontend/passes/decl/errorspassdecl.h"

#include "yal/error/errorreporter.h"
#include "yal/error/errorprinter.h"
#include "yal/frontend/ast/declbase.h"
#include "yal/frontend/module.h"
#include "yal/frontend/parser/stdeclfunction.h"
#include "yal/frontend/parser/stdeclstruct.h"
#include "yal/frontend/parser/stexprliterals.h"
#include "yal/frontend/passes/passes.h"
#include "yal/frontend/types/type.h"
#include "yal/frontend/types/typefunction.h"
#include "yal/frontend/types/typestruct.h"
#include "yal/util/format.h"

namespace yal::frontend {

    const ErrorCode  ErrorDuplicateTypeDecl::kCode =
            MakeErrorCode(static_cast<uint16_t>(PassTypeCode::Decl), 1);

    ErrorDuplicateTypeDecl::ErrorDuplicateTypeDecl(const Module& module,
                                                   const Type& newType,
                                                   const Type& oldType):
        Error(kCode),
        m_module(module),
        m_newType(newType),
        m_oldType(oldType) {

    }

    StringRef
    ErrorDuplicateTypeDecl::getErrorName() const {
        return "Duplicate Type Declaration";
    }

    void
    ErrorDuplicateTypeDecl::printDetail(ErrorPrinter &printer) const {
        FormatAppend(printer.getFormater(),
                     "Can not re-declare '%', type previously declared here:\n",
                     m_newType.getIdentifier());
        const SourceInfo& oldSrcInfo = getSourceInfoFromType(m_oldType);

        auto srcHandle = m_module.getSourceHandle();
        SourceItem* item = printer.getSourceManager().getItem(srcHandle);
        printer.printSourceInfo(printer.getFormater(),* item, oldSrcInfo);
    };

    const SourceInfo&
    ErrorDuplicateTypeDecl::getSourceInfo() const {
        return getSourceInfoFromType(m_newType);
    }

    const SourceInfo&
    ErrorDuplicateTypeDecl::getSourceInfoFromType(const Type& type) const {
        static const SourceInfo kNoSourceInfo;
        const TypeFunction* typeFunction = dyn_cast<TypeFunction>(&type);
        if (typeFunction != nullptr) {
            return typeFunction->getSTDecl()->getSourceInfo();
        }

        const TypeStruct* typeStruct = dyn_cast<TypeStruct>(&type);
        if (typeStruct != nullptr) {
            return typeStruct->getSTDecl().getSourceInfo();
        }

        return kNoSourceInfo;
    }

    // ErrorUndefinedTypeRef ------------------------------------------------

    const ErrorCode  ErrorUndefinedTypeRef::kCode =
            MakeErrorCode(static_cast<uint16_t>(PassTypeCode::Decl), 2);

    ErrorUndefinedTypeRef::ErrorUndefinedTypeRef(const StringRef& typeName,
                                                 const SourceInfo& info):
        Error(kCode),
        m_typeName(typeName),
        m_srcInfo(info) {

    }

    StringRef
    ErrorUndefinedTypeRef::getErrorName() const {
        return "Undefined Type Reference";
    }

    void
    ErrorUndefinedTypeRef::printDetail(ErrorPrinter &printer) const {
        FormatAppend(printer.getFormater(),
                     "Reference to undefined type '%'\n", m_typeName);
    };

    const SourceInfo&
    ErrorUndefinedTypeRef::getSourceInfo() const {
        return m_srcInfo;
    }


    // ErrorDuplicateSymbol --------------------------------------------------

    const ErrorCode  ErrorDuplicateSymbol::kCode =
            MakeErrorCode(static_cast<uint16_t>(PassTypeCode::Decl), 3);


    ErrorDuplicateSymbol:: ErrorDuplicateSymbol(const StringRef& sym1,
                                                const SourceInfo& sym1SrcInfo,
                                                const StringRef& sym2,
                                                const SourceInfo& sym2SrcInfo):
        Error(kCode),
        m_sym1(sym1),
        m_sym1SrcInfo(sym1SrcInfo),
        m_sym2(sym2),
        m_sym2SrcInfo(sym2SrcInfo){

    }

    StringRef
    ErrorDuplicateSymbol::getErrorName() const {
        return "Duplicate Symbol";
    }

    void
    ErrorDuplicateSymbol::printDetail(ErrorPrinter &printer) const {
        FormatAppend(printer.getFormater(),
                     "Duplicate symbol '%', previously declared here:\n",
                     m_sym1);
        SourceItem* item = printer.getSourceManager().getItem(m_sym2SrcInfo.handle);
        printer.printSourceInfo(printer.getFormater(),* item, m_sym2SrcInfo);
    };

    const SourceInfo&
    ErrorDuplicateSymbol::getSourceInfo() const {
        return m_sym1SrcInfo;
    }

    // ErrorUndefinedSymbol --------------------------------------------------

    const ErrorCode  ErrorUndefinedSymbol::kCode =
            MakeErrorCode(static_cast<uint16_t>(PassTypeCode::Decl), 4);


    ErrorUndefinedSymbol:: ErrorUndefinedSymbol(const StringRef& sym,
                                                const SourceInfo& symSrcInfo):
        Error(kCode),
        m_sym(sym),
        m_symSrcInfo(symSrcInfo){

    }

    StringRef
    ErrorUndefinedSymbol::getErrorName() const {
        return "Undefined  Symbol";
    }

    void
    ErrorUndefinedSymbol::printDetail(ErrorPrinter &printer) const {
        FormatAppend(printer.getFormater(),
                     "Undefined symbol '%' in current scope.\n",
                     m_sym);
    };

    const SourceInfo&
    ErrorUndefinedSymbol::getSourceInfo() const {
        return m_symSrcInfo;
    }

    // ErrorFnOnNonTargetType ------------------------------------------------

    const ErrorCode  ErrorFnOnNonTargetType::kCode =
            MakeErrorCode(static_cast<uint16_t>(PassTypeCode::Decl), 5);


    ErrorFnOnNonTargetType:: ErrorFnOnNonTargetType(const StringRef& sym,
                                                    const SourceInfo& symSrcInfo,
                                                    const Type* type):
        Error(kCode),
        m_fnName(sym),
        m_fnSrcInfo(symSrcInfo),
        m_targetType(type) {

    }

    StringRef
    ErrorFnOnNonTargetType::getErrorName() const {
        return "Invalid function target type";
    }

    void
    ErrorFnOnNonTargetType::printDetail(ErrorPrinter &printer) const {
        FormatAppend(printer.getFormater(),
                     "Can not target type '%' with function '%' as type is non-targetable.\n",
                     m_targetType->getIdentifier(), m_fnName);
        SourceInfoOpt typeSrcInfo = m_targetType->getSourceInfo();
        if (typeSrcInfo.has_value()){
            FormatAppend(printer.getFormater(),
                         "Type '%' declared here:\n",
                         m_targetType->getIdentifier());
            SourceItem* item = printer.getSourceManager().getItem(typeSrcInfo->handle);
            printer.printSourceInfo(printer.getFormater(),* item, *typeSrcInfo);
        }
    };

    const SourceInfo&
    ErrorFnOnNonTargetType::getSourceInfo() const {
        return m_fnSrcInfo;
    }

    // ErrorSymNotDeclVar --------------------------------------------------

    const ErrorCode  ErrorSymNotDeclVar::kCode =
            MakeErrorCode(static_cast<uint16_t>(PassTypeCode::Decl), 6);


    ErrorSymNotDeclVar:: ErrorSymNotDeclVar(const StringRef& sym,
                                            const SourceInfo& symSrcInfo,
                                            const DeclBase& decl):
        Error(kCode),
        m_symName(sym),
        m_symSrcInfo(symSrcInfo),
        m_decl(decl) {
    }

    StringRef
    ErrorSymNotDeclVar::getErrorName() const {
        return "Referenced symbol is not a variable";
    }

    void
    ErrorSymNotDeclVar::printDetail(ErrorPrinter &printer) const {
        FormatAppend(printer.getFormater(),
                     "Expected symbol '%' to be of type variable.\n",
                     m_symName);
        FormatAppend(printer.getFormater(),
                     "'%' is defined here:\n",
                     m_symName);

        SourceItem* item = printer.getSourceManager()
                .getItem(m_decl.getSourceInfo().handle);
        if (item != nullptr) {
            printer.printSourceInfo(printer.getFormater(),
                                    *item,
                                    m_decl.getSourceInfo());
        }
    };

    const SourceInfo&
    ErrorSymNotDeclVar::getSourceInfo() const {
        return m_symSrcInfo;
    }

    // ErrorInvalidIntLiteral --------------------------------------------------

    const ErrorCode  ErrorInvalidIntLiteral::kCode =
            MakeErrorCode(static_cast<uint16_t>(PassTypeCode::Decl), 7);


    ErrorInvalidIntLiteral:: ErrorInvalidIntLiteral(const STExprIntegerLiteral& expr):
        Error(kCode),
        m_expr(expr) {
    }

    StringRef
    ErrorInvalidIntLiteral::getErrorName() const {
        return "Invalid Integer Literal";
    }

    void
    ErrorInvalidIntLiteral::printDetail(ErrorPrinter &printer) const {
        FormatAppend(printer.getFormater(),
                     "Value of '%' is not a valid integer literal\n",
                     m_expr.getValue());
    };

    const SourceInfo&
    ErrorInvalidIntLiteral::getSourceInfo() const {
        return m_expr.getSourceInfo();
    }

    // ErrorInvalidFloatLiteral ----------------------------------------------

    const ErrorCode  ErrorInvalidFloatLiteral::kCode =
            MakeErrorCode(static_cast<uint16_t>(PassTypeCode::Decl), 8);


    ErrorInvalidFloatLiteral:: ErrorInvalidFloatLiteral(const STExprFloatLiteral& expr):
        Error(kCode),
        m_expr(expr) {
    }

    StringRef
    ErrorInvalidFloatLiteral::getErrorName() const {
        return "Invalid Float Literal";
    }

    void
    ErrorInvalidFloatLiteral::printDetail(ErrorPrinter &printer) const {
        FormatAppend(printer.getFormater(),
                     "Value of '%' is not a valid floating point literal\n",
                     m_expr.getValue());
    };

    const SourceInfo&
    ErrorInvalidFloatLiteral::getSourceInfo() const {
        return m_expr.getSourceInfo();
    }



    // ErrorTypeIsNotStruct -------------------------------------------------

    const ErrorCode ErrorTypeIsNotStruct::kCode =
            MakeErrorCode(static_cast<uint16_t>(PassTypeCode::Decl), 9);


    ErrorTypeIsNotStruct:: ErrorTypeIsNotStruct(const Type& type,
                                                const SourceInfo &srcInfo):
        Error(kCode),
        m_type(type),
        m_srcInfo(srcInfo) {
    }

    StringRef
    ErrorTypeIsNotStruct::getErrorName() const {
        return "Type is not a Struct";
    }

    void
    ErrorTypeIsNotStruct::printDetail(ErrorPrinter &printer) const {
        FormatAppend(printer.getFormater(),
                     "Type '%' used in the above context is not of type Struct\n",
                     m_type.getIdentifier().getName());
        SourceInfoOpt typeSrcInfo = m_type.getSourceInfo();
        if (typeSrcInfo.has_value()){
            FormatAppend(printer.getFormater(),
                         "Type '%' declared here:\n",
                         m_type.getIdentifier());
            SourceItem* item = printer.getSourceManager().getItem(typeSrcInfo->handle);
            printer.printSourceInfo(printer.getFormater(),* item, *typeSrcInfo);
        }
    };

    const SourceInfo&
    ErrorTypeIsNotStruct::getSourceInfo() const {
        return m_srcInfo;
    }

    // ErrorTypeIsNotFunction ------------------------------------------------

    const ErrorCode ErrorTypeIsNotFunction::kCode =
            MakeErrorCode(static_cast<uint16_t>(PassTypeCode::Decl), 10);


    ErrorTypeIsNotFunction:: ErrorTypeIsNotFunction(const Type& type,
                                                    const SourceInfo &srcInfo):
        Error(kCode),
        m_type(type) ,
        m_srcInfo(srcInfo) {
    }

    StringRef
    ErrorTypeIsNotFunction::getErrorName() const {
        return "Type is not a Function";
    }

    void
    ErrorTypeIsNotFunction::printDetail(ErrorPrinter &printer) const {
        FormatAppend(printer.getFormater(),
                     "Type '%' used in the above context is not a Function\n",
                     m_type.getIdentifier().getName());
        SourceInfoOpt typeSrcInfo = m_type.getSourceInfo();
        if (typeSrcInfo.has_value()){
            FormatAppend(printer.getFormater(),
                         "Type '%' declared here:\n",
                         m_type.getIdentifier());
            SourceItem* item = printer.getSourceManager().getItem(typeSrcInfo->handle);
            printer.printSourceInfo(printer.getFormater(),* item, *typeSrcInfo);
        }
    };

    const SourceInfo&
    ErrorTypeIsNotFunction::getSourceInfo() const {
        return m_srcInfo;
    }

    // ErrorTypeIsNotTypeFunction --------------------------------------------

    const ErrorCode ErrorTypeIsNotTypeFunction::kCode =
            MakeErrorCode(static_cast<uint16_t>(PassTypeCode::Decl), 11);


    ErrorTypeIsNotTypeFunction:: ErrorTypeIsNotTypeFunction(const Type& type,
                                                            const SourceInfo &srcInfo):
        Error(kCode),
        m_type(type) ,
        m_srcInfo(srcInfo) {
        flagAsFatal();
    }

    StringRef
    ErrorTypeIsNotTypeFunction::getErrorName() const {
        return "Type is not a TypeFunction";
    }

    void
    ErrorTypeIsNotTypeFunction::printDetail(ErrorPrinter &printer) const {
        FormatAppend(printer.getFormater(),
                     "Type '%' used in the above context is not a TypeFunction\n",
                     m_type.getIdentifier().getName());
        SourceInfoOpt typeSrcInfo = m_type.getSourceInfo();
        if (typeSrcInfo.has_value()){
            FormatAppend(printer.getFormater(),
                         "Type '%' declared here:\n",
                         m_type.getIdentifier());
            SourceItem* item = printer.getSourceManager().getItem(typeSrcInfo->handle);
            printer.printSourceInfo(printer.getFormater(),* item, *typeSrcInfo);
        }
    };

    const SourceInfo&
    ErrorTypeIsNotTypeFunction::getSourceInfo() const {
        return m_srcInfo;
    }

    // ErrorFunctionOnTypeNotDefined -----------------------------------------

    const ErrorCode ErrorTypeFunctionUndefined::kCode =
            MakeErrorCode(static_cast<uint16_t>(PassTypeCode::Decl), 12);


    ErrorTypeFunctionUndefined:: ErrorTypeFunctionUndefined(const Type& type,
                                                            const STIdentifier& name):
        Error(kCode),
        m_type(type) ,
        m_sym(name.getString()),
        m_srcInfo(name.getSourceInfo()) {

        flagAsFatal();
    }

    StringRef
    ErrorTypeFunctionUndefined::getErrorName() const {
        return "Undefined Function on Type";
    }

    void
    ErrorTypeFunctionUndefined::printDetail(ErrorPrinter &printer) const {
        FormatAppend(printer.getFormater(),
                     "Function '%' in not defined on target Type '%'\n",
                     m_sym,
                     m_type.getIdentifier().getName());
    };

    const SourceInfo&
    ErrorTypeFunctionUndefined::getSourceInfo() const {
        return m_srcInfo;
    }

    // ErrorTypeFunctionIsNotStatic -------------------------------------------

    const ErrorCode ErrorTypeFunctionIsNotStatic::kCode =
            MakeErrorCode(static_cast<uint16_t>(PassTypeCode::Decl), 13);


    ErrorTypeFunctionIsNotStatic:: ErrorTypeFunctionIsNotStatic(const TypeFunction& type,
                                                                const SourceInfo &srcInfo):
        Error(kCode),
        m_type(type) ,
        m_srcInfo(srcInfo) {

         flagAsFatal();
    }

    StringRef
    ErrorTypeFunctionIsNotStatic::getErrorName() const {
        return "Function type is not static";
    }

    void
    ErrorTypeFunctionIsNotStatic::printDetail(ErrorPrinter &printer) const {
        FormatAppend(printer.getFormater(),
                     "Attempting to use function '%' as a static function call,"
                     " function is not static.\n",
                     m_type.getIdentifier());
        SourceInfoOpt typeSrcInfo = m_type.getSourceInfo();
        if (typeSrcInfo.has_value()){
            FormatAppend(printer.getFormater(),
                         "Type '%' declared here:\n",
                         m_type.getIdentifier());
            SourceItem* item = printer.getSourceManager().getItem(typeSrcInfo->handle);
            printer.printSourceInfo(printer.getFormater(),* item, *typeSrcInfo);
        }
    };

    const SourceInfo&
    ErrorTypeFunctionIsNotStatic::getSourceInfo() const {
        return m_srcInfo;
    }

    // ErrorInvalidUseOfSelf -----------------------------------------------

    const ErrorCode ErrorInvalidUseOfSelf::kCode =
            MakeErrorCode(static_cast<uint16_t>(PassTypeCode::Decl), 14);


    ErrorInvalidUseOfSelf:: ErrorInvalidUseOfSelf(const TypeFunction& type,
                                                  const SourceInfo &srcInfo):
        Error(kCode),
        m_type(type) ,
        m_srcInfo(srcInfo) {
    }

    StringRef
    ErrorInvalidUseOfSelf::getErrorName() const {
        return "Invalid use of self keyword";
    }

    void
    ErrorInvalidUseOfSelf::printDetail(ErrorPrinter &printer) const {
        FormatAppend(printer.getFormater(),
                     "Invalid use of 'self' in function %. Self can only be "
                     "use with non-static target functions.\n",
                     m_type.getIdentifier());
    };

    const SourceInfo&
    ErrorInvalidUseOfSelf::getSourceInfo() const {
        return m_srcInfo;
    }

    // ErrorInvalidUseOfSelf -----------------------------------------------

    const ErrorCode ErrorInvalidLocationForSelf::kCode =
            MakeErrorCode(static_cast<uint16_t>(PassTypeCode::Decl), 15);


    ErrorInvalidLocationForSelf:: ErrorInvalidLocationForSelf(const TypeFunction& type,
                                                              const SourceInfo &srcInfo):
        Error(kCode),
        m_type(type) ,
        m_srcInfo(srcInfo) {
    }

    StringRef
    ErrorInvalidLocationForSelf::getErrorName() const {
        return "Invalid location for self keyword";
    }

    void
    ErrorInvalidLocationForSelf::printDetail(ErrorPrinter &printer) const {
        FormatAppend(printer.getFormater(),
                     "Invalid location for 'self' in function %. Self can only be "
                     "used as the first parameter to a function.\n",
                     m_type.getIdentifier());
    };

    const SourceInfo&
    ErrorInvalidLocationForSelf::getSourceInfo() const {
        return m_srcInfo;
    }

    // ErrorUndefinedStructMember -------------------------------------------

    const ErrorCode  ErrorUndefinedStructMember::kCode =
            MakeErrorCode(static_cast<uint16_t>(PassTypeCode::Decl), 16);


    ErrorUndefinedStructMember::ErrorUndefinedStructMember(const TypeStruct& type,
                                                           const StringRef& sym,
                                                           const SourceInfo& symSrcInfo):
        Error(kCode),
        m_type(type),
        m_sym(sym),
        m_symSrcInfo(symSrcInfo){

    }

    ErrorUndefinedStructMember::ErrorUndefinedStructMember(const TypeStruct& type,
                                                           const STIdentifier& id):
        ErrorUndefinedStructMember(type, id.getString(), id.getSourceInfo()) {

    }

    StringRef
    ErrorUndefinedStructMember::getErrorName() const {
        return "Undefined Struct Member";
    }

    void
    ErrorUndefinedStructMember::printDetail(ErrorPrinter &printer) const {
        FormatAppend(printer.getFormater(),
                     "Struct '%' doesn't contain any member named '%'.\n",
                     m_type.getIdentifier(), m_sym);
    };

    const SourceInfo&
    ErrorUndefinedStructMember::getSourceInfo() const {
        return m_symSrcInfo;
    }
}
