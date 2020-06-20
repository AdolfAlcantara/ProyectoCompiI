#include "ProjectParser.h"
#include "ggrammar.cpp"

bool ProjectParser::parse()
{
    data_pile.push_back(Symbol::single_input);
    curr_symbol = lexer.getNextSymbol();

    while(!data_pile.empty()){
        firstElement = data_pile.back();
        std::cout<<"Terminal: "<<lexer.SymbolToString(curr_symbol)<<"\n";
        std::cout<<"NoNTerminal: "<<lexer.SymbolToString(firstElement)<<"\n"; 
        PrintPile();
        if(isTerminal(firstElement)){
            if(firstElement == Symbol::Epsilon){
                data_pile.pop_back();
            }else if(firstElement == curr_symbol){
                data_pile.pop_back();
                curr_symbol = lexer.getNextSymbol();
            }else{
                std::cerr<<"Found Nonterminal "<<lexer.SymbolToString(firstElement)<<"\n";
                std::cerr<<"Found terminal "<<lexer.SymbolToString(curr_symbol)<<"\n";
                std::cerr<<"Expected token: "<< lexer.SymbolToString(firstElement) <<" but expected token: "<<lexer.SymbolToString(curr_symbol)<<"\n";
                std::cerr<<"Bad Parse\n";
                throw std::exception();
            }
        }else{
            const Rule& prod = getEntry(firstElement,curr_symbol);
            if(prod.isEmpty()){
                std::cout<<"Error, produccion vacia\n";
                std::cerr<<"Expected token: "<< lexer.SymbolToString(firstElement) <<" but expected token: "<<lexer.SymbolToString(curr_symbol)<<"\n";
                std::cerr<<"Bad Parse\n";
                throw std::exception();
            }
            data_pile.pop_back();
            for(int i=prod.rhs.size()-1; i>=0 ;i--){ 
                data_pile.push_back(prod.rhs.at(i));
            }
            
        }
    }
    std::cout<<"Parseo exitoso\n";
    return true;
}

void ProjectParser::PrintPile(){

    std::cout<<"Pile\n";
    for(int i =0; i < data_pile.size();i++){
        std::cout<<lexer.SymbolToString(data_pile.at(i))<<"\n";
    }
    std::cout<<"--------------\n";
}