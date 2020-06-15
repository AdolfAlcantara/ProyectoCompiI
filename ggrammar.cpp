#include <vector>
#include <functional>
#include "ggrammar.h"

Rule none;
static Rule rules[] = {
    /*0*/ {Symbol::single_input, {Symbol::stmt_list, }},
    /*1*/ {Symbol::stmt_list, {Symbol::stmt, Symbol::stmt_list_p, }},
    /*2*/ {Symbol::stmt_list_p, {Symbol::stmt, Symbol::stmt_list_p, }},
    /*3*/ {Symbol::stmt_list_p, {Symbol::Epsilon, }},
    /*4*/ {Symbol::stmt, {Symbol::NewLine, Symbol::stmt_p, }},
    /*5*/ {Symbol::stmt_p, {Symbol::assign, }},
    /*6*/ {Symbol::stmt_p, {Symbol::print, }},
    /*7*/ {Symbol::stmt_p, {Symbol::Epsilon, }},
    /*8*/ {Symbol::print, {Symbol::KwPrint, Symbol::String, Symbol::print_a, }},
    /*9*/ {Symbol::print_a, {Symbol::COMMA, Symbol::expr, Symbol::print_p, }},
    /*10*/ {Symbol::print_a, {Symbol::Epsilon, }},
    /*11*/ {Symbol::print_p, {Symbol::COMMA, Symbol::String, Symbol::COMMA, Symbol::expr, Symbol::print_p, }},
    /*12*/ {Symbol::print_p, {Symbol::Epsilon, }},
    /*13*/ {Symbol::assign, {Symbol::Ident, Symbol::EQUAL, Symbol::expr, }},
    /*14*/ {Symbol::expr, {Symbol::term, Symbol::expr_p, }},
    /*15*/ {Symbol::expr_p, {Symbol::PLUS, Symbol::term, Symbol::expr_p, }},
    /*16*/ {Symbol::expr_p, {Symbol::MINUS, Symbol::term, Symbol::expr_p, }},
    /*17*/ {Symbol::expr_p, {Symbol::Epsilon, }},
    /*18*/ {Symbol::term, {Symbol::prod, Symbol::term_p, }},
    /*19*/ {Symbol::term_p, {Symbol::ASTERISK, Symbol::prod, Symbol::term_p, }},
    /*20*/ {Symbol::term_p, {Symbol::FORWARD_SLASH, Symbol::prod, Symbol::term_p, }},
    /*21*/ {Symbol::term_p, {Symbol::Epsilon, }},
    /*22*/ {Symbol::prod, {Symbol::factor, Symbol::prod_p, }},
    /*23*/ {Symbol::prod_p, {Symbol::PERCENT, Symbol::factor, Symbol::prod_p, }},
    /*24*/ {Symbol::prod_p, {Symbol::Exp, Symbol::factor, Symbol::prod_p, }},
    /*25*/ {Symbol::prod_p, {Symbol::Epsilon, }},
    /*26*/ {Symbol::factor, {Symbol::Ident, }},
    /*27*/ {Symbol::factor, {Symbol::Number, }},
    /*28*/ {Symbol::factor, {Symbol::OPEN_PARENTHESIS, Symbol::expr, Symbol::CLOSE_PARENTHESIS, }},
    /*29*/ {Symbol::factor, {Symbol::func, }},
    /*30*/ {Symbol::func, {Symbol::KwInput, Symbol::OPEN_PARENTHESIS, Symbol::String, Symbol::CLOSE_PARENTHESIS, }},
};

const Rule& getEntry(Symbol non_term, Symbol term)
{
    switch (non_term) {
        case Symbol::single_input:
            switch (term) {
                case Symbol::NewLine:
                    return rules[0];
            }
            break;
        case Symbol::stmt_list:
            switch (term) {
                case Symbol::NewLine:
                    return rules[1];
            }
            break;
        case Symbol::stmt:
            switch (term) {
                case Symbol::NewLine:
                    return rules[4];
            }
            break;
        case Symbol::stmt_list_p:
            switch (term) {
                case Symbol::NewLine:
                    return rules[2];
                case Symbol::Eof:
                    return rules[3];
            }
            break;
        case Symbol::stmt_p:
            switch (term) {
                case Symbol::Ident:
                    return rules[5];
                case Symbol::KwPrint:
                    return rules[6];
                case Symbol::Eof:
                case Symbol::NewLine:
                    return rules[7];
            }
            break;
        case Symbol::assign:
            switch (term) {
                case Symbol::Ident:
                    return rules[13];
            }
            break;
        case Symbol::print:
            switch (term) {
                case Symbol::KwPrint:
                    return rules[8];
            }
            break;
        case Symbol::print_a:
            switch (term) {
                case Symbol::COMMA:
                    return rules[9];
                case Symbol::Eof:
                case Symbol::NewLine:
                    return rules[10];
            }
            break;
        case Symbol::expr:
            switch (term) {
                case Symbol::Ident:
                case Symbol::Number:
                case Symbol::OPEN_PARENTHESIS:
                case Symbol::KwInput:
                    return rules[14];
            }
            break;
        case Symbol::print_p:
            switch (term) {
                case Symbol::COMMA:
                    return rules[11];
                case Symbol::Eof:
                case Symbol::NewLine:
                    return rules[12];
            }
            break;
        case Symbol::term:
            switch (term) {
                case Symbol::Ident:
                case Symbol::Number:
                case Symbol::OPEN_PARENTHESIS:
                case Symbol::KwInput:
                    return rules[18];
            }
            break;
        case Symbol::expr_p:
            switch (term) {
                case Symbol::PLUS:
                    return rules[15];
                case Symbol::MINUS:
                    return rules[16];
                case Symbol::Eof:
                case Symbol::NewLine:
                case Symbol::COMMA:
                case Symbol::CLOSE_PARENTHESIS:
                    return rules[17];
            }
            break;
        case Symbol::prod:
            switch (term) {
                case Symbol::Ident:
                case Symbol::Number:
                case Symbol::OPEN_PARENTHESIS:
                case Symbol::KwInput:
                    return rules[22];
            }
            break;
        case Symbol::term_p:
            switch (term) {
                case Symbol::ASTERISK:
                    return rules[19];
                case Symbol::FORWARD_SLASH:
                    return rules[20];
                case Symbol::Eof:
                case Symbol::NewLine:
                case Symbol::COMMA:
                case Symbol::PLUS:
                case Symbol::MINUS:
                case Symbol::CLOSE_PARENTHESIS:
                    return rules[21];
            }
            break;
        case Symbol::factor:
            switch (term) {
                case Symbol::Ident:
                    return rules[26];
                case Symbol::Number:
                    return rules[27];
                case Symbol::OPEN_PARENTHESIS:
                    return rules[28];
                case Symbol::KwInput:
                    return rules[29];
            }
            break;
        case Symbol::prod_p:
            switch (term) {
                case Symbol::PERCENT:
                    return rules[23];
                case Symbol::Exp:
                    return rules[24];
                case Symbol::Eof:
                case Symbol::NewLine:
                case Symbol::COMMA:
                case Symbol::PLUS:
                case Symbol::MINUS:
                case Symbol::ASTERISK:
                case Symbol::FORWARD_SLASH:
                case Symbol::CLOSE_PARENTHESIS:
                    return rules[25];
            }
            break;
        case Symbol::func:
            switch (term) {
                case Symbol::KwInput:
                    return rules[30];
            }
            break;
    }

    return none;
}
