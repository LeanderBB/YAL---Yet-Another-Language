#ifndef __YAL_ASTNODE_H__
#define __YAL_ASTNODE_H__

#include "yal/yal.h"
#include "yal/enums.h"
#include "yal/util/stl_utils.h"
#include "yal/ast/astnodevisitor.h"
#include "yal/util/errorhandler.h"

namespace yal
{
class SymbolTable;

class AstBaseNode
{
public:
    AstBaseNode(const SourceLocationInfo& loc);

    AstBaseNode(const AstBaseNode&) = delete;

    AstBaseNode& operator=(const AstBaseNode&) = delete;

    virtual ~AstBaseNode(){}

    virtual void accept(AstNodeVisitor& visitor) = 0;

    virtual AstType nodeType() const = 0;

    virtual const char* nodeTypeStr() const = 0;

    const SourceLocationInfo& locationInfo() const
    {
        return _loc;
    }

    SymbolTable* symbolTable() const
    {
        return _pSymTable;
    }

    void setSymbolTable(SymbolTable* pSymTable)
    {
        _pSymTable = pSymTable;
    }

    ConstantType typeInfo() const
    {
        return _typeInfo;
    }

    void setTypeInfo(const ConstantType type)
    {
        _typeInfo = type;
    }
protected:
    const SourceLocationInfo _loc;
    ConstantType _typeInfo;
    SymbolTable* _pSymTable = nullptr;
};


typedef YALVector<yal::AstBaseNode*> AstBaseNodeVec_t;

#define YAL_AST_NODE_ACCEPT_HDR(type) \
    static const yal::AstType NodeType;\
    \
    inline virtual void accept(yal::AstNodeVisitor& visitor) override \
    { \
        visitor.visit(*this); \
    } \
    inline virtual yal::AstType nodeType() const override \
    { \
        return YAL_AST_NODE_TYPE(type); \
    } \
    inline virtual const char* nodeTypeStr() const override\
    {\
        return #type; \
    }

#define YAL_AST_NODE_ACCEPT_IMP(type) \
const yal::AstType type::NodeType = YAL_AST_NODE_TYPE(type);

template<class Sym>
inline bool ast_typeof(const AstBaseNode* pNode)
{
    return pNode->nodeType() == Sym::NodeType;
}

template<class Sym>
inline Sym* ast_cast(AstBaseNode* pNode)
{
    return (ast_typeof<Sym>(pNode)) ? static_cast<Sym*>(pNode) : nullptr;
}



class StatementNode : public AstBaseNode
{
public:
    StatementNode(const SourceLocationInfo& loc):
        AstBaseNode(loc)
    {
    }

    virtual ~StatementNode() {}
};

typedef YALVector<yal::StatementNode*> StatementNodeVec_t;


class ExpressionNode : public StatementNode
{
public:
    ExpressionNode(const SourceLocationInfo& loc):
        StatementNode(loc)
    {
    }

    virtual ~ExpressionNode() {}
};

typedef YALVector<yal::ExpressionNode*> ExpressionNodeVec_t;


class ExpressionList: public AstBaseNode
{
public:
    ExpressionList(const SourceLocationInfo& loc);

    ExpressionList(const SourceLocationInfo& loc,
                      ExpressionNodeVec_t&& list);

    virtual ~ExpressionList();

public:
    ExpressionNodeVec_t expressions;
};

}

#endif
