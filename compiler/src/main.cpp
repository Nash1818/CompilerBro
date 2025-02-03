#include "lexer.h"
#include "parser.h"
#include "ir.h"
#include "optimizer.h"
#include "codegen.h"
#include<fstream>
#include<sstream>

// My extension for this compiler is ".bro"
bool hasExtension(const std::string& filename, const std::string& extension) {
    return filename.size() >= extension.size() && 
    filename.compare(filename.size() - extension.size(), extension.size(), extension) == 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <source_file.bro> " << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    // has to have correct extension...
    if (!hasExtension(filename, ".bro")) {
        std::cerr << "Incorrect extension : should be in form .bro\n";
        return 1;
    }

    // reading the source file now:
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file " << filename << std::endl;
        return 1;
    }

    // Creating a buffer for file reading...
    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string sourceCode = buffer.str();
    file.close();

    // Tokenization with token and lexer:
    Lexer lexer(sourceCode);
    auto tokens = lexer.tokenize();
    std::cout << "Tokens:\n";
    for (const auto& token : tokens) {
        token.print(); // cout does not work in buffer in ostring;
    }

    // Parsing using parser files:
    // To implement: Parser... (Done v2)
    Parser parser(tokens);
    auto ast = parser.parse();

    // IR generation:
    IRGenerator irGen;
    auto ir = irGen.generate(ast);

    // Optimizations:
    optimizeIR(ir);

    // CodeGeneration:
    CodeGenerator codeGen;
    std::cout << "\nGenerated Optimized Code is as follows:\n";
    codeGen.generate(ir);

    return 0;
}