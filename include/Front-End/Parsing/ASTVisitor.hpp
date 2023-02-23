#ifndef ASTVISITOR_HPP
#define ASTVISITOR_HPP

#include "AST.hpp"
#include "Expr.hpp"
#include "BinaryOp.hpp"
#include "Factor.hpp"
#include "WithDecl.hpp"

class ASTVisitor {
public:
    virtual void visit(AST&) {};
    virtual void visit(Expr&) {};
    virtual void visit(Factor&) = 0;
    virtual void visit(BinaryOp&) = 0;
    virtual void visit(WithDecl&) = 0;
};

#endif