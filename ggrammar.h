#ifndef __GGRAMMAR_H__
#define __GGRAMMAR_H__

#include <vector>

enum class Symbol: unsigned {
    single_input = 0,
    stmt_list = 1,
    stmt = 2,
    stmt_list_p = 3,
    stmt_p = 4,
    assign = 5,
    print = 6,
    expr = 7,
    print_p = 8,
    term = 9,
    expr_p = 10,
    prod = 11,
    term_p = 12,
    factor = 13,
    prod_p = 14,
    func = 15,
    Eof = 16,
    NewLine = 17,
    KwPrint = 18,
    String = 19,
    COMMA = 20,
    Ident = 21,
    EQUAL = 22,
    PLUS = 23,
    MINUS = 24,
    ASTERISK = 25,
    FORWARD_SLASH = 26,
    PERCENT = 27,
    Exp = 28,
    Number = 29,
    OPEN_PARENTHESIS = 30,
    CLOSE_PARENTHESIS = 31,
    KwInput = 32,
    Epsilon = 33,
    KwFor = 34,
    KwIn = 35,
    KwIf = 36,
    KwElse = 37,
    KwWhile = 38,
    KwDef = 39,
    KwReturn = 40,
    Indent = 41,
    Dedent = 42
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
    if (index < 16) return index;
    else return (index - 16);
}

static inline bool isTerminal(Symbol s) {
    return static_cast<unsigned>(s) >= 16;
}

const Rule& getEntry(Symbol non_term, Symbol term);

#endif
