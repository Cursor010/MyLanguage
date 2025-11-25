#include <iostream>
#include "lexer.h"
#include "utils.h"

int main(int argc, char* argv[]) {
    try {
        Lexer lexer;

        std::string tokensFile = "tokens.txt";
        std::string codeFile = "code.txt";
        std::string outputFile = "output_tokens.txt";

        if (argc >= 2) codeFile = argv[1];
        if (argc >= 3) tokensFile = argv[2];
        if (argc >= 4) outputFile = argv[3];

        std::cout << "Loading tokens from: " << tokensFile << std::endl;
        if (!lexer.loadTokensFromFile(tokensFile)) {
            std::cerr << "Failed to load tokens file!" << std::endl;
            return 1;
        }

        std::cout << "Reading code from: " << codeFile << std::endl;
        std::string code = readCodeFromFile(codeFile);
        std::cout << "Code to analyze:\n" << code << "\n" << std::endl;

        auto tokens = lexer.tokenize(code);

        std::cout << "Writing tokens to: " << outputFile << std::endl;
        writeTokensToFile(tokens, lexer, outputFile);

        printTokens(tokens, lexer);

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}