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

#include "yal/ast/typecontext.h"
#include "yal/ast/typebuiltin.h"
namespace yal{

    TypeContext::TypeContext() {

        {
            auto type = std::make_unique<TypeBuiltin>(TypeBuiltin::DataType::Boolean);
            m_typeBool = type.get();
            m_types.insert(std::make_pair(type->getNameWithModulePrefix(),
                                          std::move(type)));
        }

        {
            auto type = std::make_unique<TypeBuiltin>(TypeBuiltin::DataType::Int8);
            m_typeI8 = type.get();
            m_types.insert(std::make_pair(type->getNameWithModulePrefix(),
                                          std::move(type)));
        }

        {
            auto type = std::make_unique<TypeBuiltin>(TypeBuiltin::DataType::UInt8);
            m_typeU8 = type.get();
            m_types.insert(std::make_pair(type->getNameWithModulePrefix(),
                                          std::move(type)));
        }

        {
            auto type = std::make_unique<TypeBuiltin>(TypeBuiltin::DataType::Int16);
            m_typeI16 = type.get();
            m_types.insert(std::make_pair(type->getNameWithModulePrefix(),
                                          std::move(type)));
        }

        {
            auto type = std::make_unique<TypeBuiltin>(TypeBuiltin::DataType::UInt16);
            m_typeU16 = type.get();
            m_types.insert(std::make_pair(type->getNameWithModulePrefix(),
                                          std::move(type)));
        }

        {
            auto type = std::make_unique<TypeBuiltin>(TypeBuiltin::DataType::Int32);
            m_typeI32 = type.get();
            m_types.insert(std::make_pair(type->getNameWithModulePrefix(),
                                          std::move(type)));
        }

        {
            auto type = std::make_unique<TypeBuiltin>(TypeBuiltin::DataType::UInt32);
            m_typeU32 = type.get();
            m_types.insert(std::make_pair(type->getNameWithModulePrefix(),
                                          std::move(type)));
        }
        {
            auto type = std::make_unique<TypeBuiltin>(TypeBuiltin::DataType::Int64);
            m_typeI64 = type.get();
            m_types.insert(std::make_pair(type->getNameWithModulePrefix(),
                                          std::move(type)));
        }

        {
            auto type = std::make_unique<TypeBuiltin>(TypeBuiltin::DataType::UInt64);
            m_typeU64 = type.get();
            m_types.insert(std::make_pair(type->getNameWithModulePrefix(),
                                          std::move(type)));
        }

        {
            auto type = std::make_unique<TypeBuiltin>(TypeBuiltin::DataType::Float);
            m_typeFloat = type.get();
            m_types.insert(std::make_pair(type->getNameWithModulePrefix(),
                                          std::move(type)));
        }

        {
            auto type = std::make_unique<TypeBuiltin>(TypeBuiltin::DataType::Double);
            m_typeDouble = type.get();
            m_types.insert(std::make_pair(type->getNameWithModulePrefix(),
                                          std::move(type)));
        }

    }

    bool
    TypeContext::hasType(const Type* type) const {
        YAL_ASSERT(type != nullptr);
        const auto it = m_types.find(type->getNameWithModulePrefix());
        return it != m_types.end();
    }

    void
    TypeContext::addType(std::unique_ptr<Type>&& type) {
        YAL_ASSERT(!hasType(type.get()));
        m_types.insert(std::make_pair(type->getNameWithModulePrefix(),
                                      std::move(type)));
    }

    const Type*
    TypeContext::getByName(const char* name) const {
        const auto it = m_types.find(name);
        if(it != m_types.end()) {
            return it->second.get();
        } else {
            return nullptr;
        }
    }

}
