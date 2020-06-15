#include "ProjectLexer.h"
#include "ggrammar.h"

enum class State {
    Start_q0,
    Start_q2,
    Start_q3,
    Start_q4,
    Start_q5,
    decimal_q0,
    decimal_q1,
    Identifier_q0,
    Identifier_q1,
    Identifier_q2,
    Delimeter_q0,
    Relational_q0,
    Arimetical_q0,
    Arimetical_q3,
    Comments_q0,
    Comments_q1,
    string_q0,
    string_q1,
    string_q3,
};

Symbol ProjectLexer::checkIndent(const std::string& str){
    int _spaces = str.length();
    std::cout<<"spaces entrando:" << _spaces << "\n";
    std::cout<<"pila de espacios:" << spaces.size() << "\n";
    for(int x = 0; x<spaces.size(); x++){
        std::cout<<"pos:"<<x<<", text:"<<spaces[x] << "\n";
    }

    if(_spaces > spaces.back()){
        spaces.push_back(_spaces);
        std::cout<<"Push:" << _spaces << "\n\n";
        return Symbol::Indent;
    }else if(_spaces < spaces.back()){
            while(_spaces != spaces.back()){
                indentSymbols.push_back(Symbol::Dedent);
                std::cout<<"Pop:" << spaces.back() << "\n\n";
                spaces.pop_back();
            }
            std::cout<<"indentSymbols size: "<< indentSymbols.size() << "\n";
            Symbol temp = indentSymbols.back();
            temp = indentSymbols.back();
            indentSymbols.pop_back();
            return temp;
    }else{
        return Symbol::NewLine;
    }
}



Symbol ProjectLexer::findKeyword(const std::string& str){
    if(str == "print"){
        return Symbol::KwPrint;
    }else if(str == "for"){
        return Symbol::KwFor;
    }else if(str == "in"){
        return Symbol::KwIn;
    }else if(str == "if"){
        return Symbol::KwIf;
    }else if(str == "else"){
        return Symbol::KwElse;
    }else if(str == "while"){
        return Symbol::KwWhile;
    }else if(str == "input"){
        return Symbol::KwInput;
    }else if(str == "def"){
        return Symbol::KwDef;
    }else if(str == "return"){
        return Symbol::KwReturn;
    }else{
        return Symbol::Ident;
    }
}

Symbol ProjectLexer::getNextSymbol()
{
    text = "";
    //std::cout<<"indentSymbols size: "<< indentSymbols.size() << "\n";
    if(indentSymbols.size() > 0){
        Symbol temp = indentSymbols.back();
        indentSymbols.pop_back();
        return temp;
    }

        State state = State::Start_q0;
    int ch = getNextChar();

    while (true) {
        switch (state) {
            // Start
            case State::Start_q0:
                if (ch == EOF) {
                    text += ch;
                    return Symbol::Eof;
                }
                else if ((ch == ' ') || (ch == '\t')) {
                    state = State::Start_q0;
                    ch = getNextChar();
                }
                else if (ch == '\n') {
                    state = State::Start_q2;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'decimal
                    state = State::decimal_q0;
                }
                break;
            case State::Start_q2:
                if (ch == '\n') {
                    state = State::Start_q2;
                    ch = getNextChar();
                }
                else if ((ch == '\t') || (ch == ' ')) {
                    text += ch;
                    state = State::Start_q3;
                    ch = getNextChar();
                }
                else if (ch == '#') {
                    state = State::Start_q5;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return checkIndent(text);
                }
                break;
            case State::Start_q3:
                if (ch == '#') {
                    state = State::Start_q5;
                    ch = getNextChar();
                }
                else if ((ch == ' ') || (ch == '\t')) {
                    text += ch;
                    state = State::Start_q3;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return checkIndent(text);
                }
                break;
            case State::Start_q5:
                text="";
                if (ch == '\n') {
                    state = State::Start_q0;
                    ch = getNextChar();
                }
                else {
                    state = State::Start_q5;
                    ch = getNextChar();
                }
                break;
            // decimal
            case State::decimal_q0:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::decimal_q1;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'Identifier
                    state = State::Identifier_q0;
                }
                break;
            case State::decimal_q1:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::decimal_q1;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Symbol::Number;
                }
                break;
            // Identifier
            case State::Identifier_q0:
                if ((ch == '_') || ((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z'))) {
                    text += ch;
                    state = State::Identifier_q1;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'Delimeter
                    state = State::Delimeter_q0;
                }
                break;
            case State::Identifier_q1:
                if (((ch >= '0') && (ch <= '9')) || ((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')) || (ch == '_')) {
                    text += ch;
                    state = State::Identifier_q1;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return findKeyword(text);
                }
                break;
            // Delimeter
            case State::Delimeter_q0:
                if (ch == '(') {
                    text += ch;
                    return Symbol::OPEN_PARENTHESIS;
                }
                else if (ch == ')') {
                    text += ch;
                    return Symbol::CLOSE_PARENTHESIS;
                }
                else if (ch == ',') {
                    text += ch;
                    return Symbol::COMMA;
                }
                else {
                    // Trying next automaton 'Relational
                    state = State::Relational_q0;
                }
                break;
            // Relational
            case State::Relational_q0:
                if (ch == '=') {
                    text += ch;
                    return Symbol::EQUAL;
                }
                else {
                    // Trying next automaton 'Arimetical
                    state = State::Arimetical_q0;
                }
                break;
            // Arimetical
            case State::Arimetical_q0:
                if (ch == '%') {
                    text += ch;
                    return Symbol::PERCENT;
                }
                else if (ch == '+') {
                    text += ch;
                    return Symbol::PLUS;
                }
                else if (ch == '/') {
                    text += ch;
                    return Symbol::FORWARD_SLASH;
                }
                else if (ch == '-') {
                    text += ch;
                    return Symbol::MINUS;
                }
                else if (ch == '*') {
                    text += ch;
                    state = State::Arimetical_q3;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'Comments
                    state = State::Comments_q0;
                }
                break;
            case State::Arimetical_q3:
                if (ch == '*') {
                    text += ch;
                    return Symbol::Exp;
                }
                else {
                    ungetChar(ch);
                    return Symbol::ASTERISK;
                }
                break;
            // Comments
            case State::Comments_q0:
                if (ch == '#') {
                    state = State::Comments_q1;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'string
                    state = State::string_q0;
                }
                break;
            case State::Comments_q1:
                if (ch == '\n') {
                    state = State::Start_q0;
                    ch = getNextChar();
                }
                else {
                    state = State::Comments_q1;
                    ch = getNextChar();
                }
                break;
            // string
            case State::string_q0:
                if (ch == '"') {
                    text += ch;
                    state = State::string_q1;
                    ch = getNextChar();
                }
                else if (ch == '\'') {
                    text += ch;
                    state = State::string_q3;
                    ch = getNextChar();
                }
                else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::Start_q0;
                }
                break;
            case State::string_q1:
                if (ch == '"') {
                    text += ch;
                    return Symbol::String;
                }
                else {
                    text += ch;
                    state = State::string_q1;
                    ch = getNextChar();
                }
                break;
            case State::string_q3:
                if (ch == '\'') {
                    text += ch;
                    return Symbol::String;
                }
                else {
                    text += ch;
                    state = State::string_q3;
                    ch = getNextChar();
                }
                break;
        }
    }

}

const char *ProjectLexer::SymbolToString(Symbol tk)
{
        switch (tk) {
        case Symbol::single_input: return "single_input";
        case Symbol::stmt_list: return "stmt_list";
        case Symbol::stmt: return "stmt";
        case Symbol::stmt_list_p: return "stmt_list_p";
        case Symbol::stmt_p: return "stmt_p";
        case Symbol::print: return "print";
        case Symbol::expr: return "expr";
        case Symbol::print_p: return "print_p";
        case Symbol::term: return "term";
        case Symbol::expr_p: return "expr_p";
        case Symbol::prod: return "prod";
        case Symbol::term_p: return "term_p";
        case Symbol::factor: return "factor";
        case Symbol::prod_p: return "prod_p";
        case Symbol::func: return "func";
        case Symbol::Eof: return "Eof";
        case Symbol::assign: return "assign";
        case Symbol::String: return "String";
        case Symbol::Exp: return "Exp";
        case Symbol::FORWARD_SLASH: return "FORWARD_SLASH";
        case Symbol::Number: return "Number";
        case Symbol::ASTERISK: return "ASTERISK";
        case Symbol::COMMA: return "COMMA";
        case Symbol::OPEN_PARENTHESIS: return "OPEN_PARENTHESIS";
        case Symbol::PLUS: return "PLUS";
        case Symbol::CLOSE_PARENTHESIS: return "CLOSE_PARENTHESIS";
        case Symbol::MINUS: return "MINUS";
        case Symbol::PERCENT: return "PERCENT";
        case Symbol::Ident: return "Identifier";
        case Symbol::EQUAL: return "Equal";
        case Symbol::KwInput: return "Input";
        case Symbol::KwPrint: return "Print";
        case Symbol::Epsilon: return "Epsilon";
        case Symbol::KwFor: return "For";
        case Symbol::KwIn: return "In";
        case Symbol::KwIf: return "If";
        case Symbol::KwElse: return "Else";
        case Symbol::Indent: return "Indent";
        case Symbol::Dedent: return "Dedent";
        case Symbol::NewLine: return "NewLine";
        case Symbol::KwWhile: return "While";
        case Symbol::KwDef: return "Def";
        case Symbol::KwReturn: return "Return";
        default: return "Unknown";
    }
}