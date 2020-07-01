#include "parser.h"

void Parser::parse()
{
    //std::cout<<"Parse\n";
    curr_token = lexer.getNextSymbol();
    //std::cout<<lexer.SymbolToString(curr_token)<<"\n";
    while(curr_token != Symbol::Eof)
    {
        if(curr_token == Symbol::NewLine){
            curr_token = lexer.getNextSymbol();
        }else{
            stmt_list();
        }
    }
}

void Parser::stmt_list()
{
    switch (curr_token)
    {
        case Symbol::KwDef:
        {
            curr_token = lexer.getNextSymbol();
            fun_decl();
            break;
        }
        case Symbol::Ident:
        {
            curr_token = lexer.getNextSymbol();
            switch(curr_token)
            {
                case Symbol::EQUAL:
                {
                    curr_token = lexer.getNextSymbol();
                    assign();
                    break;
                }
                case Symbol::OPEN_PARENTHESIS:
                {
                    curr_token = lexer.getNextSymbol();
                    func();
                    break;
                }
                case Symbol::OPEN_BRACKET:
                {
                    curr_token = lexer.getNextSymbol();
                    array();
                    break;
                }
                default:
                {
                    std::cerr<<"UNexpected token: "<<lexer.SymbolToString(curr_token)<<"\n"; 
                    break;
                }
            }
        }
        case Symbol::KwPrint:
        {
            curr_token = lexer.getNextSymbol();
            print();
            break;
        }
        case Symbol::KwFor:
        {
            curr_token = lexer.getNextSymbol();
            for_stmt();
            break;
        }
        case Symbol::KwIf:
        {
            curr_token = lexer.getNextSymbol();
            if_stmt();
            break;
        }
        case Symbol::KwWhile:
        {
            curr_token = lexer.getNextSymbol();
            while_stmt();
            break;
        }
        case Symbol::KwReturn:
        {
            curr_token = lexer.getNextSymbol();
            return_stmt();
            break;
        }
        
        default:
        {
            std::cerr<<"UNexpected token: "<<lexer.SymbolToString(curr_token)<<"\n"; 
            break;
        }
    }
}


void Parser::fun_decl()
{
    if(curr_token == Symbol::Ident)
    {
        curr_token = lexer.getNextSymbol();
        if(curr_token == Symbol::OPEN_PARENTHESIS){
            curr_token = lexer.getNextSymbol();
            arg_list();
            if(curr_token == Symbol::CLOSE_PARENTHESIS){
                curr_token = lexer.getNextSymbol();
                if(curr_token == Symbol::COLON){
                    curr_token = lexer.getNextSymbol();
                    if(curr_token == Symbol::Indent){
                        curr_token = lexer.getNextSymbol();
                        stmt_list();
                        if(curr_token == Symbol::Dedent){
                            curr_token = lexer.getNextSymbol();
                        }else{
                            expectedToken(Symbol::Dedent, curr_token);    
                        }
                    }else{
                        expectedToken(Symbol::Indent, curr_token);
                    }
                }else{
                    std::cerr<<"Expected token Colon, found: "<<lexer.SymbolToString(curr_token)<<"\n";     
                }
            }else{
                std::cerr<<"Expected token Close Parenthesis, found: "<<lexer.SymbolToString(curr_token)<<"\n"; 
            }
        }
        else
        {
            std::cerr<<"Expected token Open Parenthesis, found: "<<lexer.SymbolToString(curr_token)<<"\n"; 
        }
    }
    else
    {
        std::cerr<<"Expected token Ident, found: "<<lexer.SymbolToString(curr_token)<<"\n"; 
    }
    
}

void Parser::arg_list()
{
    expr();
    while(curr_token == Symbol::COMMA){
        curr_token = lexer.getNextSymbol();
        expr();
    }
}

// void Parser::assign(){
//     //std::cout<<"Assign\n";
//     std::string text = lexer.getText();
//     curr_token = lexer.getNextSymbol();
//     if(curr_token == Symbol::EQUAL){
//         curr_token = lexer.getNextSymbol();
//         auto node1 = expr();
//         // int value = expr();
//         // auto i = value_map.emplace(ident,value);
//         // if(!i.second){
//         //     i.first->second = value;
//         // }
//         std::cout<<"Assign expr kind: "<<AST::kindToString(node1->getKind())<<"\n";
//         return std::make_shared<AST::Assign>(text,node1);
//     }else{
//         std::cerr<<"Expected token Equal but found "<<lexer.SymbolToString(curr_token)<<"\n";
//         throw std::exception();
//     }
// }

// void Parser::print(){
//     //std::cout<<"KwPrint\n";
//     // if(curr_token == Symbol::Ident){
//     //     //std::cout<<"Ident\n";
//     //     //std::cout<<lexer.getText()<<"\n";
//         // auto i = value_map.find(lexer.getText());
//         // if(i == value_map.end()){
//         //     std::cerr<<"Not value found for "<<lexer.getText()<<"\n";
//         //     throw std::exception();
//         // }
//         // //std::cout<<lexer.getText()<<" = "<<i->second<<"\n";
//         auto node = expr();
//         // curr_token = lexer.getNextSymbol();
//         return std::make_shared<AST::Print>(node);
//     // }else{
//     //     std::cerr<<"Expected token Ident but found "<<lexer.SymbolToString(curr_token)<<"\n";
//     //     throw std::exception();
//     // }
// }

// void Parser::expr(){
//     // int value=0;
//     //std::cout<<"Expr\n";
//     // value = term();
//     auto node1 = term();
//     //std::cout<<lexer.SymbolToString(curr_token)<<"\n";
//     while(curr_token == Symbol::PLUS || curr_token == Symbol::MINUS){
//         if(curr_token == Symbol::PLUS){
//             curr_token = lexer.getNextSymbol();
//             // value = value + term();
//             auto node2 = term();
//             return std::make_shared<AST::Plus>(node1,node2);
//         }else{
//             curr_token = lexer.getNextSymbol();
//             // value = value - term();
//             auto node2 = term();
//             return std::make_shared<AST::Minus>(node1,node2);
//         }
//     }
//     // return value;
//     return node1;
// }

// AST::NodePtr Parser::term(){
//     // int value=0;
//     //std::cout<<"term\n";
//     // value = factor();
//     auto node1 = factor();
//     //std::cout<<lexer.SymbolToString(curr_token)<<"\n";
//     while(curr_token == Symbol::ASTERISK || curr_token == Symbol::FORWARD_SLASH){
//         if(curr_token == Symbol::ASTERISK){
//             curr_token = lexer.getNextSymbol();
//             // value = value * factor();
//             auto node2 = factor();
//             std::cout<<"term expr1 kind: "<<AST::kindToString(node1->getKind())<<"\n";
//             std::cout<<"term expr2 kind: "<<AST::kindToString(node2->getKind())<<"\n";
//             return std::make_shared<AST::Mult>(node1,node2);
//         }else{
//             curr_token = lexer.getNextSymbol();
//             // value = value / factor();
//             auto node2 = factor();
//             return std::make_shared<AST::Div>(node1,node2);
//         }
//     }
//     return node1;
//     // return value;
// }

// AST::NodePtr Parser::factor(){
//     //std::cout<<"factor\n";
//     //std::cout<<lexer.SymbolToString(curr_token)<<"\n";
//     //std::cout<<lexer.getText()<<"\n";
//     // int value=0;
//     if(curr_token == Symbol::num){
//         // value = std::stoi(lexer.getText());
//         int value = std::stoi(lexer.getText());
//         curr_token = lexer.getNextSymbol();
//         return std::make_shared<AST::Numb>(value);
//     }else if(curr_token == Symbol::OPEN_PARENTHESIS){
//         curr_token = lexer.getNextSymbol();
//         auto node = expr();
//         // value = expr();
//         if(curr_token != Symbol::CLOSE_PARENTHESIS){
//             SyntaxError(curr_token);
//             throw std::exception();
//         }else{
//             curr_token = lexer.getNextSymbol();
//         }
//         return node;
//     }else if(curr_token == Symbol::Ident){
//         // auto i = value_map.find(lexer.getText());
//         // if(i == value_map.end()){
//         //     std::cerr<<"Not value found for "<<lexer.getText()<<"\n";
//         //     throw std::exception();
//         // }
//         auto text = lexer.getText();
//         curr_token = lexer.getNextSymbol();
//         return std::make_shared<AST::Ident>(text);
//         // value = i->second;
//     }else{
//         SyntaxError(curr_token);
//         throw std::exception();
//     }
//     // return value;
// }

// void Parser::printMap(){
//     for (auto& x: value_map)
//         std::cout << x.first << ": " << x.second << std::endl;
//     std::cout<<"-----------\n";
// }