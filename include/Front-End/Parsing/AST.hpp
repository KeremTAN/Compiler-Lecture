#ifndef AST_HPP
#define AST_HPP

#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/StringRef.h>

class AST;
class Expr;
class Factor;
class BinaryOp;
class WithDecl;

class ASTVisitor {
public:
    virtual void visit(AST&) {};
    virtual void visit(Expr&) {};
    virtual void visit(Factor&) = 0;
    virtual void visit(BinaryOp&) = 0;
    virtual void visit(WithDecl&) = 0;
};

class AST {
public:
    virtual ~AST() {}
    virtual void accept(ASTVisitor& V) = 0;
};

#endif

