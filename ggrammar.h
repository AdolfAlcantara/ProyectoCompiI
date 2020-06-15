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
    print_a = 7,
    expr = 8,
    print_p = 9,
    term = 10,
    expr_p = 11,
    prod = 12,
    term_p = 13,
    factor = 14,
    prod_p = 15,
    func = 16,
    Eof = 17,
    NewLine = 18,
    KwPrint = 19,
    String = 20,
    COMMA = 21,
    Ident = 22,
    EQUAL = 23,
    PLUS = 24,
    MINUS = 25,
    ASTERISK = 26,
    FORWARD_SLASH = 27,
    PERCENT = 28,
    Exp = 29,
    Number = 30,
    OPEN_PARENTHESIS = 31,
    CLOSE_PARENTHESIS = 32,
    KwInput = 33,
    Epsilon = 34,
    KwFor = 35,
    KwIn = 36,
    KwIf = 37,
    KwElse = 38,
    KwWhile = 39,
    KwDef = 40,
    KwReturn = 41,
    Indent = 42,
    Dedent = 43
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
    if (index < 17) return index;
    else return (index - 17);
}

static inline bool isTerminal(Symbol s) {
    return static_cast<unsigned>(s) >= 17;
}

const Rule& getEntry(Symbol non_term, Symbol term);

#endif
