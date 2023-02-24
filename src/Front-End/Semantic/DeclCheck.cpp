#include "DeclCheck.hpp"

DeclCheck::DeclCheck()
    :m_HasError(false) {}

bool DeclCheck::hasError(){ return m_HasError; }

void DeclCheck::visit(Factor& Node) {
    if(Node.getKind() == Factor::Ident){
        if(m_Scope.find(Node.getVal()) == m_Scope.end())
            error(Not, Node.getVal());
    }
}

void DeclCheck::visit(BinaryOp& Node) {
    if(Node.getLeft())
        Node.getLeft()->accept(*this);
    else m_HasError = true;

    if(Node.getRight())
        Node.getRight()->accept(*this);
    else m_HasError = true;
}

void DeclCheck::visit(WithDecl& Node) {
    for(auto Itr = Node.begin(), End = Node.end(); Itr!=End; ++Itr){
        if(!m_Scope.insert(*Itr).second){
            error(Twice, *Itr);
        }

        if(Node.getExpr())
            Node.getExpr()->accept(*this);
        else m_HasError = true;
    }
}

void DeclCheck::error(ErrorType ET, llvm::StringRef V) {
    llvm::errs() << "Variable " << V << " "
                 << (ET!=Not ? "already" : "not")
                 << " declared\n";
    m_HasError = true;
}