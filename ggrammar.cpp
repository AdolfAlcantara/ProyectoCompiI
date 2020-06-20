#include <vector>
#include <functional>
#include "ggrammar.h"

Rule none;
static Rule rules[] = {
    /*0*/ {Symbol::single_input, {Symbol::stmt_list, Symbol::Eof, }},
    /*1*/ {Symbol::single_input, {Symbol::NewLine, Symbol::stmt_list, Symbol::Eof, }},
    /*2*/ {Symbol::stmt_list, {Symbol::stmt, Symbol::stmt_list_p, }},
    /*3*/ {Symbol::stmt_list_p, {Symbol::stmt, Symbol::stmt_list_p, }},
    /*4*/ {Symbol::stmt_list_p, {Symbol::Epsilon, }},
    /*5*/ {Symbol::stmt, {Symbol::assign, Symbol::stmt_end_nl, }},
    /*6*/ {Symbol::stmt, {Symbol::print, Symbol::stmt_end_nl, }},
    /*7*/ {Symbol::stmt, {Symbol::for_st, Symbol::Dedent, }},
    /*8*/ {Symbol::stmt_end_nl, {Symbol::NewLine, }},
    /*9*/ {Symbol::stmt_end_nl, {Symbol::Epsilon, }},
    /*10*/ {Symbol::for_st, {Symbol::KwFor, Symbol::Ident, Symbol::KwIn, Symbol::Ident, Symbol::for_opt, }},
    /*11*/ {Symbol::for_opt, {Symbol::OPEN_PARENTHESIS, Symbol::arg_list, Symbol::CLOSE_PARENTHESIS, Symbol::COLON, Symbol::Indent, Symbol::stmt_list, }},
    /*12*/ {Symbol::arg_list, {Symbol::arg, Symbol::arg_list_p, }},
    /*13*/ {Symbol::arg_list_p, {Symbol::COMMA, Symbol::arg, Symbol::arg_list_p, }},
    /*14*/ {Symbol::arg_list_p, {Symbol::Epsilon, }},
    /*15*/ {Symbol::arg, {Symbol::Ident, }},
    /*16*/ {Symbol::arg, {Symbol::Number, }},
    /*17*/ {Symbol::arg, {Symbol::Epsilon, }},
    /*18*/ {Symbol::print, {Symbol::KwPrint, Symbol::String, Symbol::print_a, }},
    /*19*/ {Symbol::print_a, {Symbol::COMMA, Symbol::expr, Symbol::print_p, }},
    /*20*/ {Symbol::print_a, {Symbol::Epsilon, }},
    /*21*/ {Symbol::print_p, {Symbol::COMMA, Symbol::String, Symbol::COMMA, Symbol::expr, Symbol::print_p, }},
    /*22*/ {Symbol::print_p, {Symbol::Epsilon, }},
    /*23*/ {Symbol::assign, {Symbol::Ident, Symbol::EQUAL, Symbol::expr, }},
    /*24*/ {Symbol::expr, {Symbol::term, Symbol::expr_p, }},
    /*25*/ {Symbol::expr_p, {Symbol::PLUS, Symbol::term, Symbol::expr_p, }},
    /*26*/ {Symbol::expr_p, {Symbol::MINUS, Symbol::term, Symbol::expr_p, }},
    /*27*/ {Symbol::expr_p, {Symbol::Epsilon, }},
    /*28*/ {Symbol::term, {Symbol::prod, Symbol::term_p, }},
    /*29*/ {Symbol::term_p, {Symbol::ASTERISK, Symbol::prod, Symbol::term_p, }},
    /*30*/ {Symbol::term_p, {Symbol::FORWARD_SLASH, Symbol::prod, Symbol::term_p, }},
    /*31*/ {Symbol::term_p, {Symbol::Epsilon, }},
    /*32*/ {Symbol::prod, {Symbol::factor, Symbol::prod_p, }},
    /*33*/ {Symbol::prod_p, {Symbol::PERCENT, Symbol::factor, Symbol::prod_p, }},
    /*34*/ {Symbol::prod_p, {Symbol::Exp, Symbol::factor, Symbol::prod_p, }},
    /*35*/ {Symbol::prod_p, {Symbol::Epsilon, }},
    /*36*/ {Symbol::factor, {Symbol::Ident, }},
    /*37*/ {Symbol::factor, {Symbol::Number, }},
    /*38*/ {Symbol::factor, {Symbol::OPEN_PARENTHESIS, Symbol::expr, Symbol::CLOSE_PARENTHESIS, }},
    /*39*/ {Symbol::factor, {Symbol::func, }},
    /*40*/ {Symbol::func, {Symbol::KwInput, Symbol::OPEN_PARENTHESIS, Symbol::String, Symbol::CLOSE_PARENTHESIS, }},
};

const Rule& getEntry(Symbol non_term, Symbol term)
{
    switch (non_term) {
        case Symbol::single_input:
            switch (term) {
                case Symbol::KwFor:
                case Symbol::Ident:
                case Symbol::KwPrint:
                    return rules[0];
                case Symbol::NewLine:
                    return rules[1];
            }
            break;
        case Symbol::stmt_list:
            switch (term) {
                case Symbol::KwFor:
                case Symbol::Ident:
                case Symbol::KwPrint:
                    return rules[2];
            }
            break;
        case Symbol::stmt:
            switch (term) {
                case Symbol::Ident:
                    return rules[5];
                case Symbol::KwPrint:
                    return rules[6];
                case Symbol::KwFor:
                    return rules[7];
            }
            break;
        case Symbol::stmt_list_p:
            switch (term) {
                case Symbol::KwFor:
                case Symbol::Ident:
                case Symbol::KwPrint:
                    return rules[3];
                case Symbol::Eof:
                case Symbol::Dedent:
                    return rules[4];
            }
            break;
        case Symbol::assign:
            switch (term) {
                case Symbol::Ident:
                    return rules[23];
            }
            break;
        case Symbol::stmt_end_nl:
            switch (term) {
                case Symbol::NewLine:
                    return rules[8];
                case Symbol::Eof:
                case Symbol::Dedent:
                case Symbol::KwFor:
                case Symbol::Ident:
                case Symbol::KwPrint:
                    return rules[9];
            }
            break;
        case Symbol::print:
            switch (term) {
                case Symbol::KwPrint:
                    return rules[18];
            }
            break;
        case Symbol::for_st:
            switch (term) {
                case Symbol::KwFor:
                    return rules[10];
            }
            break;
        case Symbol::for_opt:
            switch (term) {
                case Symbol::OPEN_PARENTHESIS:
                    return rules[11];
            }
            break;
        case Symbol::arg_list:
            switch (term) {
                case Symbol::Ident:
                case Symbol::CLOSE_PARENTHESIS:
                case Symbol::COMMA:
                case Symbol::Number:
                    return rules[12];
            }
            break;
        case Symbol::arg:
            switch (term) {
                case Symbol::Ident:
                    return rules[15];
                case Symbol::Number:
                    return rules[16];
                case Symbol::CLOSE_PARENTHESIS:
                case Symbol::COMMA:
                    return rules[17];
            }
            break;
        case Symbol::arg_list_p:
            switch (term) {
                case Symbol::COMMA:
                    return rules[13];
                case Symbol::CLOSE_PARENTHESIS:
                    return rules[14];
            }
            break;
        case Symbol::print_a:
            switch (term) {
                case Symbol::COMMA:
                    return rules[19];
                case Symbol::Eof:
                case Symbol::NewLine:
                case Symbol::Dedent:
                case Symbol::KwFor:
                case Symbol::Ident:
                case Symbol::KwPrint:
                    return rules[20];
            }
            break;
        case Symbol::expr:
            switch (term) {
                case Symbol::Ident:
                case Symbol::OPEN_PARENTHESIS:
                case Symbol::Number:
                case Symbol::KwInput:
                    return rules[24];
            }
            break;
        case Symbol::print_p:
            switch (term) {
                case Symbol::COMMA:
                    return rules[21];
                case Symbol::Eof:
                case Symbol::NewLine:
                case Symbol::Dedent:
                case Symbol::KwFor:
                case Symbol::Ident:
                case Symbol::KwPrint:
                    return rules[22];
            }
            break;
        case Symbol::term:
            switch (term) {
                case Symbol::Ident:
                case Symbol::OPEN_PARENTHESIS:
                case Symbol::Number:
                case Symbol::KwInput:
                    return rules[28];
            }
            break;
        case Symbol::expr_p:
            switch (term) {
                case Symbol::PLUS:
                    return rules[25];
                case Symbol::MINUS:
                    return rules[26];
                case Symbol::Eof:
                case Symbol::NewLine:
                case Symbol::Dedent:
                case Symbol::KwFor:
                case Symbol::Ident:
                case Symbol::CLOSE_PARENTHESIS:
                case Symbol::COMMA:
                case Symbol::KwPrint:
                    return rules[27];
            }
            break;
        case Symbol::prod:
            switch (term) {
                case Symbol::Ident:
                case Symbol::OPEN_PARENTHESIS:
                case Symbol::Number:
                case Symbol::KwInput:
                    return rules[32];
            }
            break;
        case Symbol::term_p:
            switch (term) {
                case Symbol::ASTERISK:
                    return rules[29];
                case Symbol::FORWARD_SLASH:
                    return rules[30];
                case Symbol::Eof:
                case Symbol::NewLine:
                case Symbol::Dedent:
                case Symbol::KwFor:
                case Symbol::Ident:
                case Symbol::CLOSE_PARENTHESIS:
                case Symbol::COMMA:
                case Symbol::KwPrint:
                case Symbol::PLUS:
                case Symbol::MINUS:
                    return rules[31];
            }
            break;
        case Symbol::factor:
            switch (term) {
                case Symbol::Ident:
                    return rules[36];
                case Symbol::Number:
                    return rules[37];
                case Symbol::OPEN_PARENTHESIS:
                    return rules[38];
                case Symbol::KwInput:
                    return rules[39];
            }
            break;
        case Symbol::prod_p:
            switch (term) {
                case Symbol::PERCENT:
                    return rules[33];
                case Symbol::Exp:
                    return rules[34];
                case Symbol::Eof:
                case Symbol::NewLine:
                case Symbol::Dedent:
                case Symbol::KwFor:
                case Symbol::Ident:
                case Symbol::CLOSE_PARENTHESIS:
                case Symbol::COMMA:
                case Symbol::KwPrint:
                case Symbol::PLUS:
                case Symbol::MINUS:
                case Symbol::ASTERISK:
                case Symbol::FORWARD_SLASH:
                    return rules[35];
            }
            break;
        case Symbol::func:
            switch (term) {
                case Symbol::KwInput:
                    return rules[40];
            }
            break;
    }

    return none;
}
