#include "yal/ast/variableaccessnode.h"

namespace yal
{

YAL_AST_NODE_ACCEPT_IMP(VariableAccessNode)

VariableAccessNode::VariableAccessNode(const SourceLocationInfo& loc,
                                       const char* variableName):
    ExpressionNode(loc),
    _variableName(variableName)
{

}

}
