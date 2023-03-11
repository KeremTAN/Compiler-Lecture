#ifndef WITHDECL_HPP
#define WITHDECL_HPP

#include "Front-End/Parsing/AST.hpp"

using VarVector = llvm::SmallVector<llvm::StringRef, 8>;

class WithDecl : public AST{

public:
    WithDecl(llvm::SmallVector<llvm::StringRef, 8> Vars, Expr* E);
    VarVector::const_iterator begin();
    VarVector::const_iterator end();
    Expr* getExpr();
    virtual void accept(ASTVisitor& V) override;

private:
    VarVector m_Vars;
    Expr* m_Expr;
};
#endif