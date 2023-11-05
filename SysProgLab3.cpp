#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

enum TokenType {
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_DIRECTIVE,
    TOKEN_COMMENT,
    TOKEN_KEYWORD,
    TOKEN_OPERATOR,
    TOKEN_DELIMITER,
    TOKEN_IDENTIFIER
};

struct Token {
    std::string lexeme;
    TokenType type;
};

std::vector<std::string> keywords = {"mov", "xchg", "push", "pop", "call"
                                      "add", "sub", "mul", "div", "inc", "dec", 
                                      "and", "or" , "xor", "not",
                                      "sar", "shr", "sal", "shl",
                                      "bt", "bts", "btr", "btc",
                                      "jmp", "jz", "jnz", "loop", "ret", "int",
                                      "movs", "cmps", "scas", "lods", "stos",
                                      "stc", "clc", "cmc", "cld", "std",
                                      "lds", "les", "lfs", "lgs", "lss" 
};

std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;
    int length = input.length();
    for (int i = 0; i < length; i++) {
        if (isalpha(input[i]) || input[i] == '_') {
            std::string lex = "";
            lex += input[i];
            i++;
            while (isalnum(input[i]) || input[i] == '_') {
                lex += input[i];
                i++;
            }
            Token t;
            if (std::find(keywords.begin(), keywords.end(), lex) != keywords.end()) {
                Token t;
                t.lexeme = lex;
                t.type = TOKEN_KEYWORD;
                tokens.push_back(t);
            }
            else {
                Token t;
                t.lexeme = lex;
                t.type = TOKEN_IDENTIFIER;
                tokens.push_back(t);
            }
            i--;
        }
        else if (std::isdigit(input[i]) || (input[i] == '-' && std::isdigit(input[i + 1]))) {
            std::string lex = "";
            lex += input[i];
            i++;
            while (isdigit(input[i])) {
                lex += input[i];
                i++;
            }
            Token t;
            t.lexeme = lex;
            t.type = TOKEN_NUMBER;
            tokens.push_back(t);
            i--;
        }
        else if (input[i] == ';') {
            std::string lex = "";
            lex += input[i];
            i++;
            while (input[i] != '\n') {
                lex += input[i];
                i++;
            }
            Token t;
            t.lexeme = lex;
            t.type = TOKEN_COMMENT;
            tokens.push_back(t);
            i--;
        }
        else if (input[i] == '.') {
            std::string lex = "";
            lex += input[i];
            i++;
            while (isalpha(input[i])) {
                lex += input[i];
                i++;
            }
            Token t;
            t.lexeme = lex;
            t.type = TOKEN_DIRECTIVE;
            tokens.push_back(t);
            i--;
        }
        else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '&' || input[i] == '|' || input[i] == '>' || input[i] == '<' || input[i] == '%' || input[i] == '!' || input[i] == '^') {
            std::string lex = "";
            lex += input[i];
            i++;
            while (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/'
                || input[i] == '&' || input[i] == '|' || input[i] == '>' || input[i] == '<'
                || input[i] == '%' || input[i] == '!' || input[i] == '^'){
                lex += input[i];
                i++;
            }
            Token t;
            t.lexeme = lex;
            t.type = TOKEN_OPERATOR;
            tokens.push_back(t);
            i--;
        }
        else if (input[i] == '\'') {
            std::string lex = "";
            lex += input[i];
            i++;
            while (input[i] != '\'') {
                lex += input[i];
                i++;
            }
            lex += '\'';
            Token t;
            t.lexeme = lex;
            t.type = TOKEN_STRING;
            tokens.push_back(t);
            i--;
        }
        else if (input[i] == ',' || input[i] == '(' || input[i] == ')' || input[i] == '[' || input[i] == ']' || input[i] == '{' || input[i] == '}' || input[i] == '<' || input[i] == '>'){
            std::string lex = "";
            lex += input[i];
            Token t;
            t.lexeme = lex;
            t.type = TOKEN_DELIMITER;
            tokens.push_back(t);
        }
    }
    return tokens;
}
    

int main() {
    std::string code = "mov ax, 5\n"
        "add bx, 2 + 10\n"
        "lavel: sub cx, 3 ; comment here\n"
        "jmp label\n"
        "pop Function\n"
        "ret";
    std::string lexemTypes[] = {"Number", "String", "Directive", "Comment", "Keyword", "Operator", "Delimiter", "Identifier"};
    std::vector<Token> tokens = tokenize(code);
    for (const Token& token : tokens) {
        std::cout << "<" << token.lexeme << ", " << lexemTypes[token.type] << ">" << std::endl;
    }
    return 0;
}