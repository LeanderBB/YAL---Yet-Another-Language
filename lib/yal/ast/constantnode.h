#ifndef __YAL_CONSTANTNODE_H__
#define __YAL_CONSTANTNODE_H__

#include "yal/ast/astbasenode.h"
#include "yal/util/constantvalue.h"

namespace yal
{

class ConstantNode : public ExpressionNode
{
public:
    YAL_AST_NODE_ACCEPT_HDR(ConstantNode)

    ConstantNode(const SourceLocationInfo& loc,
                 const ConstantValue& value);

    virtual ~ConstantNode();

    DataType constantType() const
    {
        return _constantValue.type();
    }

    const ConstantValue constantValue() const
    {
        return _constantValue;
    }


private:
    const ConstantValue _constantValue;

};

}
#endif
