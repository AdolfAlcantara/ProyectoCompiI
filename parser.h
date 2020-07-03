#include "ProjectLexer.h"
#include "ggrammar.h"

#include <unordered_map>

class Parser
{
    public:
    Parser(ProjectLexer lexer):lexer(lexer){}
    void parse();

    void SyntaxError(Symbol tk){
        std::cerr<<"Found out error with token:"<< lexer.SymbolToString(tk) << "\n";
    }

    void expectedToken(Symbol expected, Symbol found){
        std::cerr<<"Expected token "<<lexer.SymbolToString(expected)<<", found: "<<lexer.SymbolToString(found)<<"\n";         
        throw std::exception();
    }
    
    void printMap();
    private:
        void stmt_list();
        void arg_list();
        void fun_decl();
        void func();
        void array();
        void for_stmt();
        void if_stmt();
        void if_opt();
        void elif_stmt();
        void else_stmt();
        void while_stmt();
        void return_stmt();
        void expr();
        void print();
        void assign();
        void prod();
        void term();
        void factor();

    private:
    Symbol curr_token;
    ProjectLexer lexer;
    std::unordered_map<std::string,int> value_map;
    // std::vector<AST::NodePtr> nodes;
};