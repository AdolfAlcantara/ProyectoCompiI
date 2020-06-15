#include "ProjectLexer.h"

class ProjectParser {
    public:
    ProjectParser(ProjectLexer &lexer):lexer(lexer){}
    bool parse();

    void SyntaxError(Symbol tk){
        std::cerr<<"Unexpected Symbol found: " << lexer.SymbolToString(tk) << "\n";
    }

    void PrintPile();

    private:
    ProjectLexer& lexer;
    std::vector<Symbol> data_pile;
    Symbol curr_symbol;
    Symbol firstElement;
};