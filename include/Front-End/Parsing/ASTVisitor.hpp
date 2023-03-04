#ifndef ASTVISITOR_HPP
#define ASTVISITOR_HPP

#include "Front-End/Parsing/AST.hpp"
#include "Front-End/Parsing/Expr.hpp"
#include "Front-End/Parsing/BinaryOp.hpp"
#include "Front-End/Parsing/Factor.hpp"
#include "Front-End/Parsing/WithDecl.hpp"

class ASTVisitor {
public:
    virtual void visit(AST&) {};
    virtual void visit(Expr&) {};
    virtual void visit(Factor&) = 0;
    virtual void visit(BinaryOp&) = 0;
    virtual void visit(WithDecl&) = 0;
};

#endif