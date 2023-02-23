#include "Front-End/Parsing/Factor.hpp"

Factor::Factor(ValueKind Kind, llvm::StringRef Val)
:m_Kind(Kind), m_Val(Val) {}

Factor::ValueKind Factor::getKind(){
    return m_Kind;
}

llvm::StringRef Factor::getVal(){
    return m_Val;
}

void Factor::accept (ASTVisitor& V){ V.visit(*this);}