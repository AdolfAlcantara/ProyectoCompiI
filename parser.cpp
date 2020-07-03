#include "parser.h"

void Parser::parse()
{
    //std::cout<<"Parse\n";
    curr_token = lexer.getNextSymbol();
    //std::cout<<lexer.SymbolToString(curr_token)<<"\n";
    while(curr_token != Symbol::Eof)
    {
        std::cout<<"Token: "<<lexer.SymbolToString(curr_token)<<"\n";
        if(curr_token == Symbol::NewLine){
            curr_token = lexer.getNextSymbol();
        }else{
            stmt_list();
        }
    }
    std::cout<<"Good parsing\n";
}

void Parser::stmt_list()
{
    while(curr_token == Symbol::KwDef ||
          curr_token == Symbol::Ident ||
          curr_token == Symbol::KwPrint ||
          curr_token == Symbol::KwFor ||
          curr_token == Symbol::KwIf ||
          curr_token == Symbol::KwWhile ||
          curr_token == Symbol::KwReturn){
        std::cout<<"Token: "<<lexer.SymbolToString(curr_token)<<"\n";
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
                std::cout<<"Token: "<<lexer.SymbolToString(curr_token)<<"\n";
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
                break;
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
    std::cout<<"Token: "<<lexer.SymbolToString(curr_token)<<"\n";
    while(curr_token == Symbol::COMMA){
        curr_token = lexer.getNextSymbol();
        expr();
    }
}

void Parser::assign()
{
    std::cout<<"Token: "<<lexer.SymbolToString(curr_token)<<"\n";
    expr();
    if(curr_token == Symbol::NewLine)
    {
        curr_token = lexer.getNextSymbol();
    }
}

void Parser::func()
{
    arg_list();
    if(curr_token == Symbol::CLOSE_PARENTHESIS){
        curr_token = lexer.getNextSymbol();
    }else{
        expectedToken(Symbol::CLOSE_PARENTHESIS,curr_token);
    }

    if(curr_token == Symbol::NewLine)
    {
        curr_token = lexer.getNextSymbol();
    }
}

void Parser::array()
{
    expr();
    if(curr_token == Symbol::CLOSE_BRACKET){
        curr_token = lexer.getNextSymbol();
        if(curr_token == Symbol::EQUAL){
            curr_token = lexer.getNextSymbol();
            assign();
        }else{
            expectedToken(Symbol::EQUAL, curr_token);
        }
    }else{
        expectedToken(Symbol::CLOSE_BRACKET, curr_token);
    }
}

void Parser::print()
{
    std::cout<<"Token: "<<lexer.SymbolToString(curr_token)<<"\n";
    if(curr_token == Symbol::String){
        curr_token = lexer.getNextSymbol();
    }else{
        expr();
    }

    std::cout<<"Token: "<<lexer.SymbolToString(curr_token)<<"\n";
    if(curr_token == Symbol::COMMA){
        curr_token = lexer.getNextSymbol();
        expr();
    }

    std::cout<<"Token: "<<lexer.SymbolToString(curr_token)<<"\n";
    while(curr_token == Symbol::COMMA){
        curr_token = lexer.getNextSymbol();
        std::cout<<"Token: "<<lexer.SymbolToString(curr_token)<<"\n";
        if(curr_token == Symbol::String){
            curr_token = lexer.getNextSymbol();
            if(curr_token == Symbol::COMMA){
                curr_token = lexer.getNextSymbol();
                expr();
            }else{
                expectedToken(Symbol::COMMA, curr_token);
            }
        }else{
            expectedToken(Symbol::String, curr_token);
        }
    }

    if(curr_token == Symbol::NewLine){
        curr_token = lexer.getNextSymbol();
    }
}

void Parser::for_stmt()
{
    std::cout<<"Token: "<<lexer.SymbolToString(curr_token)<<"\n";
    if(curr_token == Symbol::Ident){
        curr_token = lexer.getNextSymbol();
        if(curr_token == Symbol::KwIn){
            curr_token = lexer.getNextSymbol();
            if(curr_token == Symbol::Ident){
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
                            expectedToken(Symbol::COLON, curr_token);
                        }
                    }else{
                        expectedToken(Symbol::CLOSE_PARENTHESIS, curr_token);
                    }
                }else{
                    expectedToken(Symbol::OPEN_PARENTHESIS, curr_token);
                }
            }else{
                expectedToken(Symbol::Ident, curr_token);
            }
        }else{
            expectedToken(Symbol::KwIn, curr_token);
        }
    }else{
        expectedToken(Symbol::Ident, curr_token);
    }
}

void Parser::if_stmt()
{
    std::cout<<"Token: "<<lexer.SymbolToString(curr_token)<<"\n";
    expr();
    std::cout<<"Token: "<<lexer.SymbolToString(curr_token)<<"\n";
    if(curr_token == Symbol::COLON){
        curr_token = lexer.getNextSymbol();
        if(curr_token == Symbol::Indent){
            curr_token = lexer.getNextSymbol();
            stmt_list();
            if_opt();
        }else{
            expectedToken(Symbol::Indent, curr_token);
        }
    }else{
        expectedToken(Symbol::COLON, curr_token);
    }
}

void Parser::if_opt()
{
    std::cout<<"Token: "<<lexer.SymbolToString(curr_token)<<"\n";
    if(curr_token == Symbol::Eof){
        return;
    }else if(curr_token == Symbol::Dedent){
        curr_token = lexer.getNextSymbol();
        if(curr_token == Symbol::KwElif){
            curr_token = lexer.getNextSymbol();
            elif_stmt();
        }else if(curr_token == Symbol::KwElse){
            curr_token = lexer.getNextSymbol();
            else_stmt();
        }else{
            return;
        }
    }else{
        expectedToken(Symbol::Dedent,curr_token);
        expectedToken(Symbol::Eof,curr_token);
    }
}

void Parser::else_stmt()
{
    if(curr_token == Symbol::COLON){
        curr_token = lexer.getNextSymbol();
        if(curr_token == Symbol::Indent){
            curr_token = lexer.getNextSymbol();
            stmt_list();
            if(curr_token == Symbol::Eof){
                return;
            }else if(curr_token == Symbol::Dedent){
                curr_token = lexer.getNextSymbol();
            }else{
                expectedToken(Symbol::Dedent,curr_token);
                expectedToken(Symbol::Eof,curr_token);
            }
        }else{
            expectedToken(Symbol::Indent,curr_token);
        }
    }else{
        expectedToken(Symbol::COLON,curr_token);
    }
}

void Parser::elif_stmt()
{
    expr();
    if(curr_token == Symbol::COLON){
        curr_token = lexer.getNextSymbol();
        if(curr_token == Symbol::Indent){
            curr_token = lexer.getNextSymbol();
            stmt_list();
            if_opt();
        }else{
            expectedToken(Symbol::Indent, curr_token);
        }
    }else{
        expectedToken(Symbol::COLON, curr_token);
    }
}

void Parser::expr()
{
    std::cout<<"Token: "<<lexer.SymbolToString(curr_token)<<"\n";
    term();
    std::cout<<"Token: "<<lexer.SymbolToString(curr_token)<<"\n";
    while(curr_token == Symbol::PLUS ||
          curr_token == Symbol::MINUS ||
          curr_token == Symbol::Sameas ||
          curr_token == Symbol::LessOrEqual ||
          curr_token == Symbol::LessThan ||
          curr_token == Symbol::GreaterOrEqual ||
          curr_token == Symbol::GreaterThan ||
          curr_token == Symbol::Different
    ){
        switch (curr_token)
        {
            case Symbol::PLUS:
            {
                curr_token = lexer.getNextSymbol();
                break;
            }
            case Symbol::MINUS:
            {
                curr_token = lexer.getNextSymbol();
                break;
            }
            case Symbol::Sameas:
            {
                curr_token = lexer.getNextSymbol();
                break;
            }
            case Symbol::LessOrEqual:
            {
                curr_token = lexer.getNextSymbol();
                break;
            }
            case Symbol::LessThan:
            {
                curr_token = lexer.getNextSymbol();
                break;
            }
            case Symbol::GreaterOrEqual:
            {
                curr_token = lexer.getNextSymbol();
                break;
            }
            case Symbol::GreaterThan:
            {
                curr_token = lexer.getNextSymbol();
                break;
            }
            case Symbol::Different:
            {
                curr_token = lexer.getNextSymbol();
                break;
            }
            default:
            {
                std::cerr<<"Unexpected token: "<<lexer.SymbolToString(curr_token)<<"\n";
                throw std::exception();
                break;
            }
        }
        term();
    }
}

void Parser::term()
{
    std::cout<<"Token: "<<lexer.SymbolToString(curr_token)<<"\n";
    prod();
    std::cout<<"Token: "<<lexer.SymbolToString(curr_token)<<"\n";
    while(curr_token == Symbol::ASTERISK || curr_token == Symbol::FORWARD_SLASH){
        if(curr_token == Symbol::ASTERISK){
            curr_token = lexer.getNextSymbol();
        }else{
            curr_token = lexer.getNextSymbol();
        }
        prod();
    }
}

void Parser::prod()
{
    std::cout<<"Token: "<<lexer.SymbolToString(curr_token)<<"\n";
    factor();
    std::cout<<"Token: "<<lexer.SymbolToString(curr_token)<<"\n";
    while(curr_token == Symbol::PERCENT || curr_token == Symbol::Exp)
    {
        if(curr_token == Symbol::PERCENT){
            curr_token = lexer.getNextSymbol();
        }else{
            curr_token = lexer.getNextSymbol();
        }
        factor();
    }
}

void Parser::factor()
{
    std::cout<<"Token: "<<lexer.SymbolToString(curr_token)<<"\n";
    if(curr_token == Symbol::Number){
        curr_token = lexer.getNextSymbol();

    }else if(curr_token == Symbol::Ident){
        curr_token = lexer.getNextSymbol();
        
        if(curr_token == Symbol::OPEN_PARENTHESIS){
            curr_token = lexer.getNextSymbol();
            arg_list();

            if(curr_token != Symbol::CLOSE_PARENTHESIS){
                expectedToken(Symbol::CLOSE_PARENTHESIS, curr_token);
            }else{
                curr_token = lexer.getNextSymbol();
            }
        
        }else if(curr_token == Symbol::OPEN_BRACKET){
            curr_token = lexer.getNextSymbol();
            expr();
            if(curr_token != Symbol::CLOSE_BRACKET){
                expectedToken(Symbol::CLOSE_BRACKET, curr_token);
            }else{
                curr_token = lexer.getNextSymbol();
            }
        }
    }else if(curr_token == Symbol::OPEN_PARENTHESIS){
        curr_token = lexer.getNextSymbol();
        expr();
        if(curr_token != Symbol::CLOSE_PARENTHESIS){
            expectedToken(Symbol::CLOSE_PARENTHESIS, curr_token);
        }else{
            curr_token = lexer.getNextSymbol();
        }
    }else if(curr_token == Symbol::OPEN_BRACKET){
        curr_token = lexer.getNextSymbol();
        if(curr_token == Symbol::Number){
            curr_token = lexer.getNextSymbol();
            while(curr_token == Symbol::COMMA){
                curr_token = lexer.getNextSymbol();
                if(curr_token == Symbol::Number){
                    curr_token = lexer.getNextSymbol();
                }else{
                    expectedToken(Symbol::Number,curr_token);
                }
            }
        }
        if(curr_token != Symbol::CLOSE_BRACKET){
            expectedToken(Symbol::CLOSE_BRACKET, curr_token);
        }else{
            curr_token = lexer.getNextSymbol();
        }
    }else if(curr_token == Symbol::KwInput){
        curr_token = lexer.getNextSymbol();
        if(curr_token == Symbol::OPEN_PARENTHESIS){
            curr_token = lexer.getNextSymbol();
            if(curr_token == Symbol::String){
                curr_token = lexer.getNextSymbol();
                if(curr_token == Symbol::CLOSE_PARENTHESIS){
                    curr_token = lexer.getNextSymbol();
                }else{
                    expectedToken(Symbol::CLOSE_PARENTHESIS, curr_token);
                }
            }else{
                expectedToken(Symbol::String, curr_token);
            }
        }else{
            expectedToken(Symbol::OPEN_PARENTHESIS, curr_token);
        }
    }else{
        std::cerr<<"Unexpected token: "<<lexer.SymbolToString(curr_token)<<"\n";
        throw std::exception();
    }

}

void Parser::while_stmt()
{
    expr();
    if(curr_token == Symbol::COLON){
        curr_token = lexer.getNextSymbol();
        if(curr_token == Symbol::Indent){
            curr_token = lexer.getNextSymbol();
            stmt_list();
            if(curr_token == Symbol::Eof){
                return;
            }else if(curr_token == Symbol::Dedent){
                curr_token = lexer.getNextSymbol();
            }else{
                std::cerr<<"Expected Dedent or Eof token, found "<<lexer.SymbolToString(curr_token)<<"\n";
            }
        }else{
            expectedToken(Symbol::Indent,curr_token);
        }
    }else{
        expectedToken(Symbol::COLON,curr_token);
    }
}

void Parser::return_stmt()
{
    expr();

    if(curr_token == Symbol::NewLine){
        curr_token = lexer.getNextSymbol();
    }
}