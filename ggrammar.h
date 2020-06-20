#ifndef __GGRAMMAR_H__
#define __GGRAMMAR_H__

#include <vector>

enum class Symbol: unsigned {
    single_input = 0,
    stmt_list = 1,
    stmt = 2,
    stmt_list_p = 3,
    assign = 4,
    stmt_end_nl = 5,
    print = 6,
    for_st = 7,
    for_opt = 8,
    arg_list = 9,
    arg = 10,
    arg_list_p = 11,
    print_a = 12,
    expr = 13,
    print_p = 14,
    term = 15,
    expr_p = 16,
    prod = 17,
    term_p = 18,
    factor = 19,
    prod_p = 20,
    func = 21,
    Eof = 22,
    NewLine = 23,
    Dedent = 24,
    KwFor = 25,
    Ident = 26,
    KwIn = 27,
    OPEN_PARENTHESIS = 28,
    CLOSE_PARENTHESIS = 29,
    COLON = 30,
    Indent = 31,
    COMMA = 32,
    Number = 33,
    KwPrint = 34,
    String = 35,
    EQUAL = 36,
    PLUS = 37,
    MINUS = 38,
    ASTERISK = 39,
    FORWARD_SLASH = 40,
    PERCENT = 41,
    Exp = 42,
    KwInput = 43,
    Epsilon = 44,
    KwIf = 45,
    KwElse = 46,
    KwWhile = 47,
    KwDef = 48,
    KwReturn = 49
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
    if (index < 22) return index;
    else return (index - 22);
}

static inline bool isTerminal(Symbol s) {
    return static_cast<unsigned>(s) >= 22;
}

const Rule& getEntry(Symbol non_term, Symbol term);

#endif
