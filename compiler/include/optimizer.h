// start of optimization header:: To be added and studied later...

#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "ir.h"
#include "ast.h"
#include<vector>
#include<unordered_set>

// Optimizations ?
bool isConstantExpression(const std::shared_ptr<ASTNode>& node);
int evaluateConstantExpression(const std::shared_ptr<ASTNode>& node);
void optimizeIR(std:: vector<IRInstruction>& instructions);

#endif


// end of optimization header:: to be modified later..