// writing dependency functions for codegen.h

#include "codegen.h"
#include<iostream>

void CodeGenerator::generate(const std::vector<IRInstruction>& instructions){
    // Generate code for each instruction in the vector
    std::unordered_set<std::string> usedVars;

    // variables used in computations:
    for (const auto&inst : instructions) {
        if (!inst.result.empty()) {
            usedVars.insert(inst.result);
        }
    }

    // Variables in instructions:
    // Basically optimization (Dead Code Elimination)
    for (const auto&inst : instructions) {
        if(usedVars.find(inst.arg1) != usedVars.end() || usedVars.find(inst.arg2) != usedVars.end()) {
            std::cout << inst.op << " " << inst.arg1 << " " << inst.arg2 << " -> " << inst.result << "\n";
        }
    }
}