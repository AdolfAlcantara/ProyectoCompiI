#include "parser.cpp"

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
    Parser parser(project_lexer);

    // Symbol tk = project_lexer.getNextSymbol();

    // while(tk!= Symbol::Eof){
    //     std::cout<<"Symbol: " << ProjectLexer::SymbolToString(tk) << ", Lexema: " << project_lexer.getText() <<"\n";
    //     tk = project_lexer.getNextSymbol();
    // }
    try{
        parser.parse();
    }catch(error_t message){
        std::cerr<<"Ocurrio un error al parsear\n";
    }
}