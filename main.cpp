#include "ProjectLexer.h"

int main (int argc, char *argv[])
{
    if( argc !=2){
        std::cerr << "Usage: " << argv[0] << " <input file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if(!input.is_open()){
        std::cerr<<"No se puede abrir "<<argv[1]<<"\n";
        return 1;
    }

    ProjectLexer project_lexer(input);

    Token tk = project_lexer.getNextToken();

    while(tk!= Token::Eof){
        std::cout<<"Token: " << ProjectLexer::tokenToString(tk) << ", Lexema: " << project_lexer.getText() <<"\n";
        tk = project_lexer.getNextToken();
    }
}