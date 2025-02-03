// implementation of header file for intermediate code generation phase:

#ifndef IR_H
#define IR_H

#include "ast.h"
#include <string>
#include <iostream>
#include <vector>
#include<memory>
#include<unordered_set>

// IR instruction struct:
struct IRInstruction{
    std::string op;
    std::string arg1;
    std::string arg2;
    std::string result;

    void print() const {
        std::cout<<op<<" "<< arg1 << " " << arg2 << " -> " <<result <<"\n";
    }
};

// IR generator Class:
class IRGenerator {
    public:
    std::vector<IRInstruction> generate(const std::shared_ptr<ASTNode>& node);

    private:
    void generateNode(const std::shared_ptr<ASTNode>& node, std::vector<IRInstruction>& instructions);
    void generateArrayDeclaration(const std::shared_ptr<ArrayDeclarationNode>& node, std::vector<IRInstruction>& instructions);
    void generateArrayAccess(const std::shared_ptr<ArrayAccessNode>& node, std::vector<IRInstruction>& instructions);
    void generateStructDeclaration(const std::shared_ptr<StructNode>& node, std::vector<IRInstruction>& instructions);
    void generateStructFieldAccess(const std::shared_ptr<StructFieldAccessNode>& node, std::vector<IRInstruction>& instructions);
    std::string generateExpression(const std::shared_ptr<ASTNode>& node, std::vector<IRInstruction>& instructions);
};



#endif