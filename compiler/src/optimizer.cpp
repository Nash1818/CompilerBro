// start of optimization functions implemented in CPP:

#include "optimizer.h"

// constant expression:
bool isConstantExpression(const std::shared_ptr<ASTNode>& node) {
    return node->type == ASTNodeType::NUMBER;
}

// evaluations:
int evaluateConstantExpression(const std::shared_ptr<ASTNode>& node) {
    if(node->type == ASTNodeType::NUMBER) {
        return std::dynamic_pointer_cast<NumberNode>(node)->value;
    }
    throw std::runtime_error("Non-constant expression; can't evaluate");
}

// Optimization by Dead Code elimination:
void optimizeIR(std::vector<IRInstruction>& instructions) {
    std::unordered_set<std::string> usedVars;

    // identify variables that are used...
    for (const auto& inst:instructions) {
        if(!inst.result.empty()) {
            usedVars.insert(inst.result);
        }
    }

    std::vector<IRInstruction> optimizedinstructions;
    for (const auto& inst : instructions){
        if(usedVars.find(inst.arg1) != usedVars.end() || usedVars.find(inst.arg2) != usedVars.end()) {
            std::cout << inst.op << " " << inst.arg1 << " " << inst.arg2 << " -> " << inst.result << "\n";
        }
    }

    instructions = optimizedinstructions;

}