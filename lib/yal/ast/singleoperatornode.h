#ifndef __YAL_SINGLEOPERATORNODE_H__
#define __YAL_SINGLEOPERATORNODE_H__

#include "yal/ast/astbasenode.h"

namespace yal
{

class SingleOperatorNode : public ExpressionNode
{
public:
    YAL_AST_NODE_ACCEPT_HDR(SingleOperatorNode)

    SingleOperatorNode(const SourceLocationInfo& loc,
                  const OperatorType optype,
                  ExpressionNode* exp);

    virtual ~SingleOperatorNode();

    ExpressionNode* expression() const
    {
        return _pExpression;
    }

    OperatorType singleOperatorType() const
    {
        return _singleOperatorType;
    }

private:
    const OperatorType _singleOperatorType;
    ExpressionNode* _pExpression;
};

}

#endif
