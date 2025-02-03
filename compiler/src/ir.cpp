// IR cpp file for compilation:

#include "ir.h"

// Generate IR from AST:
std::vector<IRInstruction> IRGenerator::generate(const std::shared_ptr<ASTNode>& node) {
    std::vector<IRInstruction> instructions;
    generateNode(node, instructions);
    return instructions;
}

// Generate IR for different AST Nodes:
void IRGenerator::generateNode(const std::shared_ptr<ASTNode>& node, std::vector<IRInstruction>& instructions) {
    switch (node->type) {
        case ASTNodeType::ARRAY_DECLARATION:
            generateArrayDeclaration(std::dynamic_pointer_cast<ArrayDeclarationNode>(node), instructions);
            break;
        case ASTNodeType::ARRAY_ACCESS:
            generateArrayAccess(std::dynamic_pointer_cast<ArrayAccessNode>(node), instructions);
            break;
        case ASTNodeType::STRUCT_DECLARATION:
            generateStructDeclaration(std::dynamic_pointer_cast<StructNode>(node), instructions);
            break;
        case ASTNodeType::STRUCT_FIELD_ACCESS:
            generateStructFieldAccess(std::dynamic_pointer_cast<StructFieldAccessNode>(node), instructions);
            break;
        default:
            throw std::runtime_error("Unsupported AST type in IR");
    }
}

// Generate IR for array declaration:
void IRGenerator::generateArrayDeclaration(const std::shared_ptr<ArrayDeclarationNode>& node, std::vector<IRInstruction>& instructions){
    instructions.push_back({"ALLOC_ARRAY", node->name, std::to_string(node->size), ""});
}

// Generate IR for array access:
void IRGenerator::generateArrayAccess(const std::shared_ptr<ArrayAccessNode>& node, std::vector<IRInstruction>& instructions){
    std::string index = generateExpression(node->index, instructions);
    std::string tempVar = "t" + std::to_string(instructions.size());
    instructions.push_back({"LOAD_ARRAY", node->arrayName, index, tempVar});
}

// Generate IR for struct declaration:
void IRGenerator::generateStructDeclaration(const std::shared_ptr<StructNode>& node, std::vector<IRInstruction>& instructions){
    instructions.push_back({"ALLOC_STRUCT", node->name, "", ""});
}

// Generate IR for struct field access:
void IRGenerator::generateStructFieldAccess(const std::shared_ptr<StructFieldAccessNode>& node, std::vector<IRInstruction>& instructions) {
    std::string tempVar = "t" + std::to_string(instructions.size());
    instructions.push_back({"LOAD_FIELD", node->structName, node->fieldName, tempVar});
}

// Generate IR for expressions:
std::string IRGenerator::generateExpression(const std::shared_ptr<ASTNode>& node, std::vector<IRInstruction>& instructions){
    if (node->type == ASTNodeType::NUMBER) {
        auto numberNode = std::dynamic_pointer_cast<NumberNode>(node);
        return std::to_string(numberNode->value);
    }
    throw std::runtime_error("Unsupported expression in IR generation");
}