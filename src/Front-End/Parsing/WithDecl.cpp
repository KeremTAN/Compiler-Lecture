#include "WithDecl.hpp"

WithDecl::WithDecl(llvm::SmallVector<llvm::StringRef, 8> Vars, Expr* Expr)
    : m_Vars(Vars), m_Expr(Expr) {}

VarVector::const_iterator WithDecl::begin() { return m_Vars.begin(); }
    
VarVector::const_iterator WithDecl::end() { return m_Vars.end(); };

Expr* WithDecl::getExpr() { return m_Expr; }

void WithDecl::accept(ASTVisitor& V) { V.visit(*this); }