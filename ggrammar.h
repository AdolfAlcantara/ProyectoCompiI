#ifndef __GGRAMMAR_H__
#define __GGRAMMAR_H__

#include <vector>

enum class Symbol: unsigned {
    single_input = 0,
    stmt_list = 1,
    stmt = 2,
    stmt_list_p = 3,
    func_decl = 4,
    arg_list = 5,
    stmt_p = 6,
    assign = 7,
    stmt_end_nl = 8,
    func = 9,
    arr_st = 10,
    print = 11,
    for_st = 12,
    if_st = 13,
    while_st = 14,
    return_st = 15,
    expr = 16,
    while_opt = 17,
    if_opt = 18,
    if_opt_p = 19,
    if_opt_pp = 20,
    for_opt = 21,
    arg = 22,
    arg_list_p = 23,
    print_b = 24,
    print_a = 25,
    print_p = 26,
    term = 27,
    expr_p = 28,
    prod = 29,
    term_p = 30,
    factor = 31,
    prod_p = 32,
    factor_p = 33,
    factor_pp = 34,
    factor_ppp = 35,
    Eof = 36,
    NewLine = 37,
    KwDef = 38,
    Ident = 39,
    OPEN_PARENTHESIS = 40,
    CLOSE_PARENTHESIS = 41,
    COLON = 42,
    Indent = 43,
    Dedent = 44,
    EQUAL = 45,
    OPEN_BRACKET = 46,
    CLOSE_BRACKET = 47,
    KwReturn = 48,
    KwWhile = 49,
    KwIf = 50,
    KwElse = 51,
    KwElif = 52,
    KwFor = 53,
    KwIn = 54,
    COMMA = 55,
    KwPrint = 56,
    String = 57,
    PLUS = 58,
    MINUS = 59,
    Sameas = 60,
    LessOrEqual = 61,
    LessThan = 62,
    GreaterOrEqual = 63,
    GreaterThan = 64,
    Different = 65,
    ASTERISK = 66,
    FORWARD_SLASH = 67,
    PERCENT = 68,
    Exp = 69,
    Number = 70,
    KwInput = 71,
    Epsilon = 72
};

struct Rule {
    Rule() = default;
    Rule(const Rule&) = delete;

    Symbol lhs;
    std::vector<Symbol> rhs;
    bool isEmpty() const { return rhs.empty(); }
};

using RuleRef = std::reference_wrapper<Rule>;

static inline unsigned indexOf(Symbol s) {
    unsigned index = static_cast<unsigned>(s);
    if (index < 36) return index;
    else return (index - 36);
}

static inline bool isTerminal(Symbol s) {
    return static_cast<unsigned>(s) >= 36;
}

const Rule& getEntry(Symbol non_term, Symbol term);

#endif
