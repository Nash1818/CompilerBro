// implementing the Abstract Syntax tree here....

#ifndef AST_H
#define AST_H

#include<memory>
#include<vector>
#include<string>
#include<unordered_map>

// enum class
enum class ASTNodeType{
    IDENTIFIER,
    NUMBER,
    BINARY_OPERATION,
    ASSIGNMENT,
    IF_STATEMENT,
    WHILE_STATEMENT,
    FOR_STATEMENT,
    PARALLEL_FOR_STATEMENT,
    FUNCTION_CALL,
    FUNCTION_DEFINITION,
    BLOCK,
    RETURN_STATEMENT,
    ARRAY_DECLARATION,
    ARRAY_ACCESS,
    STRUCT_DECLARATION,
    STRUCT_FIELD_ACCESS
};

// Base AST Node:
struct ASTNode{
    ASTNodeType type;
    virtual ~ASTNode() = default;
};

// Identifier Node:
struct IdentifierNode : public ASTNode{
    std::string name;
    explicit IdentifierNode(const std::string& name) : name(name) {
        type = ASTNodeType::IDENTIFIER;
    }
};

// Number Node:
struct NumberNode : public ASTNode{
    int value;
    explicit NumberNode(int value) : value(value) {
        type = ASTNodeType::NUMBER;
    }
};

// Binary Operation Node:
struct BinaryOperationNode : public ASTNode{
    std::string op;
    std::shared_ptr<ASTNode> left;
    std::shared_ptr<ASTNode> right;

    BinaryOperationNode(const std::string &op, std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right)
    : op(op), left(std::move(left)), right(std::move(right)) {
        type = ASTNodeType::BINARY_OPERATION;
    }
};

// Block Node:
struct BlockNode : public ASTNode{
    std::vector<std::shared_ptr<ASTNode>> statements;

    BlockNode() {
        type = ASTNodeType::BLOCK;
    }
};

// Function definition node:
struct FunctionDefinitionNode : public ASTNode{
    std::string name;
    std::vector<std::pair<std::string, std::string>> parameters; // (type, name)
    std::shared_ptr<BlockNode> body;

    FunctionDefinitionNode(const std::string& name, std::vector<std::pair<std::string, std::string>> parameters,
    std::shared_ptr<BlockNode> body) : name(name), parameters(std::move(parameters)), body(std::move(body)) {
        type = ASTNodeType::FUNCTION_DEFINITION;
    }
};

// Function Call Node:
struct FunctionCallNode: public ASTNode {
    std:: string functionName;
    std::vector<std::shared_ptr<ASTNode>> arguments;

    FunctionCallNode(const std::string& functionName, std::vector<std::shared_ptr<ASTNode>> arguments)
    : functionName(functionName), arguments(std::move(arguments)) {
        type = ASTNodeType::FUNCTION_CALL;
    }
};

// Return Statement Node:
struct ReturnStatementNode : public ASTNode {
    std::shared_ptr<ASTNode> expression;

    explicit ReturnStatementNode(std:: shared_ptr<ASTNode> expression) 
    : expression(std::move(expression)) {
        type = ASTNodeType::RETURN_STATEMENT;
    }
};

// Array Declaration Node:
struct ArrayDeclarationNode : public ASTNode {
    std::string name;
    int size;

    ArrayDeclarationNode(const std::string& name, int size) : name(name), size(size) {
        type = ASTNodeType::ARRAY_DECLARATION;
    }
};

// Array Access Node:
struct ArrayAccessNode : public ASTNode {
    std::string arrayName;
    std::shared_ptr<ASTNode> index;

    ArrayAccessNode(const std::string& arrayName, std::shared_ptr<ASTNode> index)
    : arrayName(arrayName), index(std::move(index)) {
        type = ASTNodeType::ARRAY_ACCESS;
    }
};

// Struct Declaration Node:
struct StructNode : public ASTNode{
    std::string name;
    std::unordered_map<std::string, std::string> fields; // field name is type

    StructNode(const std::string& name, std::unordered_map<std::string, std::string> fields)
    : name(name), fields(std::move(fields)) {
        type = ASTNodeType::STRUCT_DECLARATION;
    }
};

// Struct Field Access Node:
struct StructFieldAccessNode : public ASTNode {
    std:: string structName;
    std::string fieldName;

    StructFieldAccessNode(const std::string& structName, const std::string& fieldName)
    : structName(structName), fieldName(fieldName) {
        type = ASTNodeType::STRUCT_FIELD_ACCESS;
    } 
};

#endif

// end of implementation of header file