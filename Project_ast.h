#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

namespace AST
{

    class Node;

    using SymbolTable = std::unordered_map<std::string,int>;
    using NodePtr = std::shared_ptr<Node>;

    enum class Kind
    {
        Sequence,
        Func,
        Assign,
        Print,
        Plus,
        Minus,
        Sameas,
        LoE,
        LT,
        GoE,
        GT,
        Diff,
        Mult,
        Div,
        Mod,
        Exp,
        Ident,
        Function,
        Array,
        Number,
        ArrayDef,
        Input,
    };

    class Node
    {
        public:
            virtual ~Node() {}
            virtual Kind getKind() const= 0;
    };

    class Sequence: public Node
    {
        public:
            Sequence(std::vector<NodePtr> stmts): stmts(stmts){}

            Kind getKind() const override {return Kind::Sequence;}

            std::vector<NodePtr> getStmts(){return stmts;}

        private:
            std::vector<NodePtr> stmts;
    };

    class Print: public Node
    {
        public:
            Print(std::vector<NodePtr> exprs):exprs(exprs){}

            Kind getKind() const override {return Kind::Print;}

            std::vector<NodePtr> getExprs(){return exprs;}

        private:
            std::vector<NodePtr> exprs;
    };

    class Plus: public Node
    {
        public:
        Plus(NodePtr expr1, NodePtr expr2):expr1(expr1),expr2(expr2){}

        Kind getKind() const override {return Kind::Plus;}

        NodePtr getExpr1(){return expr1;}
        NodePtr getExpr2(){return expr2;}

        private:
            NodePtr expr1;
            NodePtr expr2;
    };

    class Minus: public Node
    {
        public:
        Minus(NodePtr expr1, NodePtr expr2):expr1(expr1),expr2(expr2){}

        Kind getKind() const override {return Kind::Minus;}

        NodePtr getExpr1(){return expr1;}
        NodePtr getExpr2(){return expr2;}

        private:
            NodePtr expr1;
            NodePtr expr2;
    };

    class Sameas: public Node
    {
        public:
        Sameas(NodePtr expr1, NodePtr expr2):expr1(expr1),expr2(expr2){}

        Kind getKind() const override {return Kind::Sameas;}

        NodePtr getExpr1(){return expr1;}
        NodePtr getExpr2(){return expr2;}

        private:
            NodePtr expr1;
            NodePtr expr2;
    };

    class LoE: public Node
    {
        public:
        LoE(NodePtr expr1, NodePtr expr2):expr1(expr1),expr2(expr2){}

        Kind getKind() const override {return Kind::LoE;}

        NodePtr getExpr1(){return expr1;}
        NodePtr getExpr2(){return expr2;}

        private:
            NodePtr expr1;
            NodePtr expr2;
    };

    class LT: public Node
    {
        public:
        LT(NodePtr expr1, NodePtr expr2):expr1(expr1),expr2(expr2){}

        Kind getKind() const override {return Kind::LT;}

        NodePtr getExpr1(){return expr1;}
        NodePtr getExpr2(){return expr2;}

        private:
            NodePtr expr1;
            NodePtr expr2;
    };

    class GoE: public Node
    {
        public:
        GoE(NodePtr expr1, NodePtr expr2):expr1(expr1),expr2(expr2){}

        Kind getKind() const override {return Kind::GoE;}

        NodePtr getExpr1(){return expr1;}
        NodePtr getExpr2(){return expr2;}

        private:
            NodePtr expr1;
            NodePtr expr2;
    };

    class GT: public Node
    {
        public:
        GT(NodePtr expr1, NodePtr expr2):expr1(expr1),expr2(expr2){}

        Kind getKind() const override {return Kind::GT;}

        NodePtr getExpr1(){return expr1;}
        NodePtr getExpr2(){return expr2;}

        private:
            NodePtr expr1;
            NodePtr expr2;
    };

    class Diff: public Node
    {
        public:
        Diff(NodePtr expr1, NodePtr expr2):expr1(expr1),expr2(expr2){}

        Kind getKind() const override {return Kind::Diff;}

        NodePtr getExpr1(){return expr1;}
        NodePtr getExpr2(){return expr2;}

        private:
            NodePtr expr1;
            NodePtr expr2;
    };

    class Mult: public Node
    {
        public:
        Mult(NodePtr expr1, NodePtr expr2):expr1(expr1),expr2(expr2){}

        Kind getKind() const override {return Kind::Mult;}

        NodePtr getExpr1(){return expr1;}
        NodePtr getExpr2(){return expr2;}

        private:
            NodePtr expr1;
            NodePtr expr2;
    };

    class Div: public Node
    {
        public:
        Div(NodePtr expr1, NodePtr expr2):expr1(expr1),expr2(expr2){}

        Kind getKind() const override {return Kind::Div;}

        NodePtr getExpr1(){return expr1;}
        NodePtr getExpr2(){return expr2;}

        private:
            NodePtr expr1;
            NodePtr expr2;
    };

    class Mod: public Node
    {
        public:
        Mod(NodePtr expr1, NodePtr expr2):expr1(expr1),expr2(expr2){}

        Kind getKind() const override {return Kind::Mod;}

        NodePtr getExpr1(){return expr1;}
        NodePtr getExpr2(){return expr2;}

        private:
            NodePtr expr1;
            NodePtr expr2;
    };

    class Exp: public Node
    {
        public:
        Exp(NodePtr expr1, NodePtr expr2):expr1(expr1),expr2(expr2){}

        Kind getKind() const override {return Kind::Exp;}

        NodePtr getExpr1(){return expr1;}
        NodePtr getExpr2(){return expr2;}

        private:
            NodePtr expr1;
            NodePtr expr2;
    };

    class Ident: public Node
    {
        public:
            Ident(std::string text):text(text){}

            Kind getKind() const override {return Kind::Ident;}

            std::string getText(){return text;}

        private:
            std::string text;
    };

    class Array: public Node
    {
        public:
            Array(std::string text, NodePtr expr):text(text),expr(expr){}

            Kind getKind() const override {return Kind::Array;}

            std::string getText(){return text;}
            NodePtr getExpr(){return expr;}

        private:
            std::string text;
            NodePtr expr;
    };

    class Func: public Node
    {
        public:
            Func(std::string text, std::vector<NodePtr> args):text(text),args(args){}

            Kind getKind() const override {return Kind::Array;}

            std::string getText(){return text;}
            std::vector<NodePtr> getExpr(){return args;}

        private:
            std::string text;
            std::vector<NodePtr> args ;
    };

    class Number: public Node
    {
        public:
        Number(int value):value(value){}

        Kind getKind() const override {return Kind::Number;}

        int getValue(){return value;}

        private:
        int value;
    };

    class ArrayDef: public Node
    {
        public:
            ArrayDef(std::vector<int> items):items(items){}

            Kind getKind() const override {return Kind::ArrayDef;}

            std::vector<int> getItems(){return items;}
        
        private:
            std::vector<int> items;

    };

    class Input: public Node
    {
        public:
            Input(std::string text, std::string input):text(text),input(input){}

            Kind getKind() const override {return Kind::Input;}

            std::string getText(){return text;}
            std::string getInput(){return input;}
        
        private:
            std::string input;
            std::string text;

    };

    std::string toString(const NodePtr& node);

}