#ifndef __PROJECTLEXER_H__
#define __PROJECTLEXER_H__

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "tokens.h"

class ProjectLexer
{
public:
    ProjectLexer(std::istream& input): input(input){spaces.push_back(0);}
    std::string getText() {return text;}
    int getNextChar() {return input.get();}
    void ungetChar(int ch) { input.unget();}

    void reportError(int ch){
        std::cerr << "Error: caracter invalido: '"<<ch<<"'\n";
    }

    void startSpacesStack(){
        spaces.push_back(0);
    }

    Token getNextToken();
    Token findKeyword(const std::string& str);
    Token checkIndent(const std::string& str);
    static const char* tokenToString(Token tk);


private:
    std::string text;
    std::istream& input;
    std::vector<int> spaces;
    std::vector<Token> indentTokens;
    
};

#endif