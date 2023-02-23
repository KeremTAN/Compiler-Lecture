#ifndef FACTOR_HPP
#define FACTOR_HPP

#include "Expr.hpp"

class Factor : public Expr {
public:
    enum ValueKind{ Ident, Number };
    Factor(ValueKind Kind, llvm::StringRef Val);
    ValueKind getKind();
    llvm::StringRef getVal();
    virtual void accept (ASTVisitor& V) override;
private:
    ValueKind       m_Kind;
    llvm::StringRef m_Val;
};

#endif