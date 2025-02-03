// for the code generation phase:

#ifndef CODEGEN_H
#define CODEGEN_H

#include "ir.h"
#include <unordered_set>

class CodeGenerator {
    public:
    void generate(const std::vector<IRInstruction>& instructions);
};

#endif

// end of codegen file