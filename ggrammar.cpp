#include <vector>
#include <functional>
#include "ggrammar.h"

Rule none;
static Rule rules[] = {
    /*0*/ {Symbol::single_input, {Symbol::stmt_list, Symbol::Eof, }},
    /*1*/ {Symbol::single_input, {Symbol::NewLine, Symbol::stmt_list, Symbol::Eof, }},
    /*2*/ {Symbol::stmt_list, {Symbol::stmt, Symbol::stmt_list_p, }},
    /*3*/ {Symbol::stmt_list, {Symbol::func_decl, Symbol::stmt_list_p, }},
    /*4*/ {Symbol::stmt_list_p, {Symbol::stmt, Symbol::stmt_list_p, }},
    /*5*/ {Symbol::stmt_list_p, {Symbol::func_decl, Symbol::stmt_list_p, }},
    /*6*/ {Symbol::stmt_list_p, {Symbol::Epsilon, }},
    /*7*/ {Symbol::func_decl, {Symbol::KwDef, Symbol::Ident, Symbol::OPEN_PARENTHESIS, Symbol::arg_list, Symbol::CLOSE_PARENTHESIS, Symbol::COLON, Symbol::Indent, Symbol::stmt_list, Symbol::Dedent, }},
    /*8*/ {Symbol::stmt, {Symbol::Ident, Symbol::stmt_p, }},
    /*9*/ {Symbol::stmt_p, {Symbol::assign, Symbol::stmt_end_nl, }},
    /*10*/ {Symbol::stmt_p, {Symbol::func, Symbol::stmt_end_nl, }},
    /*11*/ {Symbol::stmt_p, {Symbol::arr_st, Symbol::stmt_end_nl, }},
    /*12*/ {Symbol::stmt, {Symbol::print, Symbol::stmt_end_nl, }},
    /*13*/ {Symbol::stmt, {Symbol::for_st, Symbol::Dedent, }},
    /*14*/ {Symbol::stmt, {Symbol::if_st, }},
    /*15*/ {Symbol::stmt, {Symbol::while_st, }},
    /*16*/ {Symbol::stmt, {Symbol::return_st, Symbol::stmt_end_nl, }},
    /*17*/ {Symbol::stmt_end_nl, {Symbol::NewLine, }},
    /*18*/ {Symbol::stmt_end_nl, {Symbol::Epsilon, }},
    /*19*/ {Symbol::assign, {Symbol::EQUAL, Symbol::expr, }},
    /*20*/ {Symbol::func, {Symbol::OPEN_PARENTHESIS, Symbol::arg_list, Symbol::CLOSE_PARENTHESIS, }},
    /*21*/ {Symbol::arr_st, {Symbol::OPEN_BRACKET, Symbol::expr, Symbol::CLOSE_BRACKET, Symbol::EQUAL, Symbol::expr, }},
    /*22*/ {Symbol::return_st, {Symbol::KwReturn, Symbol::expr, }},
    /*23*/ {Symbol::while_st, {Symbol::KwWhile, Symbol::expr, Symbol::COLON, Symbol::Indent, Symbol::stmt_list, Symbol::while_opt, }},
    /*24*/ {Symbol::while_opt, {Symbol::Eof, }},
    /*25*/ {Symbol::while_opt, {Symbol::Dedent, }},
    /*26*/ {Symbol::if_st, {Symbol::KwIf, Symbol::expr, Symbol::COLON, Symbol::Indent, Symbol::stmt_list, Symbol::if_opt, }},
    /*27*/ {Symbol::if_opt, {Symbol::Eof, }},
    /*28*/ {Symbol::if_opt, {Symbol::Dedent, Symbol::if_opt_p, }},
    /*29*/ {Symbol::if_opt_p, {Symbol::Epsilon, }},
    /*30*/ {Symbol::if_opt_p, {Symbol::KwElse, Symbol::COLON, Symbol::Indent, Symbol::stmt_list, Symbol::if_opt_pp, }},
    /*31*/ {Symbol::if_opt_p, {Symbol::KwElif, Symbol::expr, Symbol::COLON, Symbol::Indent, Symbol::stmt_list, Symbol::if_opt, }},
    /*32*/ {Symbol::if_opt_pp, {Symbol::Eof, }},
    /*33*/ {Symbol::if_opt_pp, {Symbol::Dedent, }},
    /*34*/ {Symbol::for_st, {Symbol::KwFor, Symbol::Ident, Symbol::KwIn, Symbol::Ident, Symbol::for_opt, }},
    /*35*/ {Symbol::for_opt, {Symbol::OPEN_PARENTHESIS, Symbol::arg_list, Symbol::CLOSE_PARENTHESIS, Symbol::COLON, Symbol::Indent, Symbol::stmt_list, }},
    /*36*/ {Symbol::arg_list, {Symbol::arg, Symbol::arg_list_p, }},
    /*37*/ {Symbol::arg_list_p, {Symbol::COMMA, Symbol::arg, Symbol::arg_list_p, }},
    /*38*/ {Symbol::arg_list_p, {Symbol::Epsilon, }},
    /*39*/ {Symbol::arg, {Symbol::expr, }},
    /*40*/ {Symbol::print, {Symbol::KwPrint, Symbol::print_b, }},
    /*41*/ {Symbol::print_b, {Symbol::expr, Symbol::print_a, }},
    /*42*/ {Symbol::print_b, {Symbol::String, Symbol::print_a, }},
    /*43*/ {Symbol::print_a, {Symbol::COMMA, Symbol::expr, Symbol::print_p, }},
    /*44*/ {Symbol::print_a, {Symbol::Epsilon, }},
    /*45*/ {Symbol::print_p, {Symbol::COMMA, Symbol::String, Symbol::COMMA, Symbol::expr, Symbol::print_p, }},
    /*46*/ {Symbol::print_p, {Symbol::Epsilon, }},
    /*47*/ {Symbol::expr, {Symbol::term, Symbol::expr_p, }},
    /*48*/ {Symbol::expr_p, {Symbol::PLUS, Symbol::term, Symbol::expr_p, }},
    /*49*/ {Symbol::expr_p, {Symbol::MINUS, Symbol::term, Symbol::expr_p, }},
    /*50*/ {Symbol::expr_p, {Symbol::Sameas, Symbol::term, Symbol::expr_p, }},
    /*51*/ {Symbol::expr_p, {Symbol::LessOrEqual, Symbol::term, Symbol::expr_p, }},
    /*52*/ {Symbol::expr_p, {Symbol::LessThan, Symbol::term, Symbol::expr_p, }},
    /*53*/ {Symbol::expr_p, {Symbol::GreaterOrEqual, Symbol::term, Symbol::expr_p, }},
    /*54*/ {Symbol::expr_p, {Symbol::GreaterThan, Symbol::term, Symbol::expr_p, }},
    /*55*/ {Symbol::expr_p, {Symbol::Different, Symbol::term, Symbol::expr_p, }},
    /*56*/ {Symbol::expr_p, {Symbol::Epsilon, }},
    /*57*/ {Symbol::term, {Symbol::prod, Symbol::term_p, }},
    /*58*/ {Symbol::term_p, {Symbol::ASTERISK, Symbol::prod, Symbol::term_p, }},
    /*59*/ {Symbol::term_p, {Symbol::FORWARD_SLASH, Symbol::prod, Symbol::term_p, }},
    /*60*/ {Symbol::term_p, {Symbol::Epsilon, }},
    /*61*/ {Symbol::prod, {Symbol::factor, Symbol::prod_p, }},
    /*62*/ {Symbol::prod_p, {Symbol::PERCENT, Symbol::factor, Symbol::prod_p, }},
    /*63*/ {Symbol::prod_p, {Symbol::Exp, Symbol::factor, Symbol::prod_p, }},
    /*64*/ {Symbol::prod_p, {Symbol::Epsilon, }},
    /*65*/ {Symbol::factor, {Symbol::Ident, Symbol::factor_p, }},
    /*66*/ {Symbol::factor, {Symbol::Number, }},
    /*67*/ {Symbol::factor, {Symbol::OPEN_PARENTHESIS, Symbol::expr, Symbol::CLOSE_PARENTHESIS, }},
    /*68*/ {Symbol::factor, {Symbol::OPEN_BRACKET, Symbol::factor_pp, Symbol::CLOSE_BRACKET, }},
    /*69*/ {Symbol::factor, {Symbol::KwInput, Symbol::OPEN_PARENTHESIS, Symbol::String, Symbol::CLOSE_PARENTHESIS, }},
    /*70*/ {Symbol::factor_p, {Symbol::OPEN_PARENTHESIS, Symbol::arg_list, Symbol::CLOSE_PARENTHESIS, }},
    /*71*/ {Symbol::factor_p, {Symbol::OPEN_BRACKET, Symbol::expr, Symbol::CLOSE_BRACKET, }},
    /*72*/ {Symbol::factor_p, {Symbol::Epsilon, }},
    /*73*/ {Symbol::factor_pp, {Symbol::Number, Symbol::factor_ppp, }},
    /*74*/ {Symbol::factor_pp, {Symbol::Epsilon, }},
    /*75*/ {Symbol::factor_ppp, {Symbol::COMMA, Symbol::Number, Symbol::factor_ppp, }},
    /*76*/ {Symbol::factor_ppp, {Symbol::Epsilon, }},
};

const Rule& getEntry(Symbol non_term, Symbol term)
{
    switch (non_term) {
        case Symbol::single_input:
            switch (term) {
                case Symbol::KwDef:
                case Symbol::Ident:
                case Symbol::KwReturn:
                case Symbol::KwWhile:
                case Symbol::KwIf:
                case Symbol::KwFor:
                case Symbol::KwPrint:
                    return rules[0];
                case Symbol::NewLine:
                    return rules[1];
            }
            break;
        case Symbol::stmt_list:
            switch (term) {
                case Symbol::Ident:
                case Symbol::KwReturn:
                case Symbol::KwWhile:
                case Symbol::KwIf:
                case Symbol::KwFor:
                case Symbol::KwPrint:
                    return rules[2];
                case Symbol::KwDef:
                    return rules[3];
            }
            break;
        case Symbol::stmt:
            switch (term) {
                case Symbol::Ident:
                    return rules[8];
                case Symbol::KwPrint:
                    return rules[12];
                case Symbol::KwFor:
                    return rules[13];
                case Symbol::KwIf:
                    return rules[14];
                case Symbol::KwWhile:
                    return rules[15];
                case Symbol::KwReturn:
                    return rules[16];
            }
            break;
        case Symbol::stmt_list_p:
            switch (term) {
                case Symbol::Ident:
                case Symbol::KwReturn:
                case Symbol::KwWhile:
                case Symbol::KwIf:
                case Symbol::KwFor:
                case Symbol::KwPrint:
                    return rules[4];
                case Symbol::KwDef:
                    return rules[5];
                case Symbol::Eof:
                case Symbol::Dedent:
                    return rules[6];
            }
            break;
        case Symbol::func_decl:
            switch (term) {
                case Symbol::KwDef:
                    return rules[7];
            }
            break;
        case Symbol::arg_list:
            switch (term) {
                case Symbol::Ident:
                case Symbol::OPEN_PARENTHESIS:
                case Symbol::OPEN_BRACKET:
                case Symbol::Number:
                case Symbol::KwInput:
                    return rules[36];
            }
            break;
        case Symbol::stmt_p:
            switch (term) {
                case Symbol::EQUAL:
                    return rules[9];
                case Symbol::OPEN_PARENTHESIS:
                    return rules[10];
                case Symbol::OPEN_BRACKET:
                    return rules[11];
            }
            break;
        case Symbol::assign:
            switch (term) {
                case Symbol::EQUAL:
                    return rules[19];
            }
            break;
        case Symbol::stmt_end_nl:
            switch (term) {
                case Symbol::NewLine:
                    return rules[17];
                case Symbol::Eof:
                case Symbol::KwDef:
                case Symbol::Ident:
                case Symbol::Dedent:
                case Symbol::KwReturn:
                case Symbol::KwWhile:
                case Symbol::KwIf:
                case Symbol::KwFor:
                case Symbol::KwPrint:
                    return rules[18];
            }
            break;
        case Symbol::func:
            switch (term) {
                case Symbol::OPEN_PARENTHESIS:
                    return rules[20];
            }
            break;
        case Symbol::arr_st:
            switch (term) {
                case Symbol::OPEN_BRACKET:
                    return rules[21];
            }
            break;
        case Symbol::print:
            switch (term) {
                case Symbol::KwPrint:
                    return rules[40];
            }
            break;
        case Symbol::for_st:
            switch (term) {
                case Symbol::KwFor:
                    return rules[34];
            }
            break;
        case Symbol::if_st:
            switch (term) {
                case Symbol::KwIf:
                    return rules[26];
            }
            break;
        case Symbol::while_st:
            switch (term) {
                case Symbol::KwWhile:
                    return rules[23];
            }
            break;
        case Symbol::return_st:
            switch (term) {
                case Symbol::KwReturn:
                    return rules[22];
            }
            break;
        case Symbol::expr:
            switch (term) {
                case Symbol::Ident:
                case Symbol::OPEN_PARENTHESIS:
                case Symbol::OPEN_BRACKET:
                case Symbol::Number:
                case Symbol::KwInput:
                    return rules[47];
            }
            break;
        case Symbol::while_opt:
            switch (term) {
                case Symbol::Eof:
                    return rules[24];
                case Symbol::Dedent:
                    return rules[25];
            }
            break;
        case Symbol::if_opt:
            switch (term) {
                case Symbol::Eof:
                    return rules[27];
                case Symbol::Dedent:
                    return rules[28];
            }
            break;
        case Symbol::if_opt_p:
            switch (term) {
                case Symbol::Eof:
                case Symbol::KwDef:
                case Symbol::Ident:
                case Symbol::Dedent:
                case Symbol::KwReturn:
                case Symbol::KwWhile:
                case Symbol::KwIf:
                case Symbol::KwFor:
                case Symbol::KwPrint:
                    return rules[29];
                case Symbol::KwElse:
                    return rules[30];
                case Symbol::KwElif:
                    return rules[31];
            }
            break;
        case Symbol::if_opt_pp:
            switch (term) {
                case Symbol::Eof:
                    return rules[32];
                case Symbol::Dedent:
                    return rules[33];
            }
            break;
        case Symbol::for_opt:
            switch (term) {
                case Symbol::OPEN_PARENTHESIS:
                    return rules[35];
            }
            break;
        case Symbol::arg:
            switch (term) {
                case Symbol::Ident:
                case Symbol::OPEN_PARENTHESIS:
                case Symbol::OPEN_BRACKET:
                case Symbol::Number:
                case Symbol::KwInput:
                    return rules[39];
            }
            break;
        case Symbol::arg_list_p:
            switch (term) {
                case Symbol::COMMA:
                    return rules[37];
                case Symbol::CLOSE_PARENTHESIS:
                    return rules[38];
            }
            break;
        case Symbol::print_b:
            switch (term) {
                case Symbol::Ident:
                case Symbol::OPEN_PARENTHESIS:
                case Symbol::OPEN_BRACKET:
                case Symbol::Number:
                case Symbol::KwInput:
                    return rules[41];
                case Symbol::String:
                    return rules[42];
            }
            break;
        case Symbol::print_a:
            switch (term) {
                case Symbol::COMMA:
                    return rules[43];
                case Symbol::Eof:
                case Symbol::NewLine:
                case Symbol::KwDef:
                case Symbol::Ident:
                case Symbol::Dedent:
                case Symbol::KwReturn:
                case Symbol::KwWhile:
                case Symbol::KwIf:
                case Symbol::KwFor:
                case Symbol::KwPrint:
                    return rules[44];
            }
            break;
        case Symbol::print_p:
            switch (term) {
                case Symbol::COMMA:
                    return rules[45];
                case Symbol::Eof:
                case Symbol::NewLine:
                case Symbol::KwDef:
                case Symbol::Ident:
                case Symbol::Dedent:
                case Symbol::KwReturn:
                case Symbol::KwWhile:
                case Symbol::KwIf:
                case Symbol::KwFor:
                case Symbol::KwPrint:
                    return rules[46];
            }
            break;
        case Symbol::term:
            switch (term) {
                case Symbol::Ident:
                case Symbol::OPEN_PARENTHESIS:
                case Symbol::OPEN_BRACKET:
                case Symbol::Number:
                case Symbol::KwInput:
                    return rules[57];
            }
            break;
        case Symbol::expr_p:
            switch (term) {
                case Symbol::PLUS:
                    return rules[48];
                case Symbol::MINUS:
                    return rules[49];
                case Symbol::Sameas:
                    return rules[50];
                case Symbol::LessOrEqual:
                    return rules[51];
                case Symbol::LessThan:
                    return rules[52];
                case Symbol::GreaterOrEqual:
                    return rules[53];
                case Symbol::GreaterThan:
                    return rules[54];
                case Symbol::Different:
                    return rules[55];
                case Symbol::Eof:
                case Symbol::NewLine:
                case Symbol::KwDef:
                case Symbol::Ident:
                case Symbol::CLOSE_PARENTHESIS:
                case Symbol::COLON:
                case Symbol::Dedent:
                case Symbol::CLOSE_BRACKET:
                case Symbol::KwReturn:
                case Symbol::KwWhile:
                case Symbol::KwIf:
                case Symbol::KwFor:
                case Symbol::COMMA:
                case Symbol::KwPrint:
                    return rules[56];
            }
            break;
        case Symbol::prod:
            switch (term) {
                case Symbol::Ident:
                case Symbol::OPEN_PARENTHESIS:
                case Symbol::OPEN_BRACKET:
                case Symbol::Number:
                case Symbol::KwInput:
                    return rules[61];
            }
            break;
        case Symbol::term_p:
            switch (term) {
                case Symbol::ASTERISK:
                    return rules[58];
                case Symbol::FORWARD_SLASH:
                    return rules[59];
                case Symbol::Eof:
                case Symbol::NewLine:
                case Symbol::KwDef:
                case Symbol::Ident:
                case Symbol::CLOSE_PARENTHESIS:
                case Symbol::COLON:
                case Symbol::Dedent:
                case Symbol::CLOSE_BRACKET:
                case Symbol::KwReturn:
                case Symbol::KwWhile:
                case Symbol::KwIf:
                case Symbol::KwFor:
                case Symbol::COMMA:
                case Symbol::KwPrint:
                case Symbol::PLUS:
                case Symbol::MINUS:
                case Symbol::Sameas:
                case Symbol::LessOrEqual:
                case Symbol::LessThan:
                case Symbol::GreaterOrEqual:
                case Symbol::GreaterThan:
                case Symbol::Different:
                    return rules[60];
            }
            break;
        case Symbol::factor:
            switch (term) {
                case Symbol::Ident:
                    return rules[65];
                case Symbol::Number:
                    return rules[66];
                case Symbol::OPEN_PARENTHESIS:
                    return rules[67];
                case Symbol::OPEN_BRACKET:
                    return rules[68];
                case Symbol::KwInput:
                    return rules[69];
            }
            break;
        case Symbol::prod_p:
            switch (term) {
                case Symbol::PERCENT:
                    return rules[62];
                case Symbol::Exp:
                    return rules[63];
                case Symbol::Eof:
                case Symbol::NewLine:
                case Symbol::KwDef:
                case Symbol::Ident:
                case Symbol::CLOSE_PARENTHESIS:
                case Symbol::COLON:
                case Symbol::Dedent:
                case Symbol::CLOSE_BRACKET:
                case Symbol::KwReturn:
                case Symbol::KwWhile:
                case Symbol::KwIf:
                case Symbol::KwFor:
                case Symbol::COMMA:
                case Symbol::KwPrint:
                case Symbol::PLUS:
                case Symbol::MINUS:
                case Symbol::Sameas:
                case Symbol::LessOrEqual:
                case Symbol::LessThan:
                case Symbol::GreaterOrEqual:
                case Symbol::GreaterThan:
                case Symbol::Different:
                case Symbol::ASTERISK:
                case Symbol::FORWARD_SLASH:
                    return rules[64];
            }
            break;
        case Symbol::factor_p:
            switch (term) {
                case Symbol::OPEN_PARENTHESIS:
                    return rules[70];
                case Symbol::OPEN_BRACKET:
                    return rules[71];
                case Symbol::Eof:
                case Symbol::NewLine:
                case Symbol::KwDef:
                case Symbol::Ident:
                case Symbol::CLOSE_PARENTHESIS:
                case Symbol::COLON:
                case Symbol::Dedent:
                case Symbol::CLOSE_BRACKET:
                case Symbol::KwReturn:
                case Symbol::KwWhile:
                case Symbol::KwIf:
                case Symbol::KwFor:
                case Symbol::COMMA:
                case Symbol::KwPrint:
                case Symbol::PLUS:
                case Symbol::MINUS:
                case Symbol::Sameas:
                case Symbol::LessOrEqual:
                case Symbol::LessThan:
                case Symbol::GreaterOrEqual:
                case Symbol::GreaterThan:
                case Symbol::Different:
                case Symbol::ASTERISK:
                case Symbol::FORWARD_SLASH:
                case Symbol::PERCENT:
                case Symbol::Exp:
                    return rules[72];
            }
            break;
        case Symbol::factor_pp:
            switch (term) {
                case Symbol::Number:
                    return rules[73];
                case Symbol::CLOSE_BRACKET:
                    return rules[74];
            }
            break;
        case Symbol::factor_ppp:
            switch (term) {
                case Symbol::COMMA:
                    return rules[75];
                case Symbol::CLOSE_BRACKET:
                    return rules[76];
            }
            break;
    }

    return none;
}
