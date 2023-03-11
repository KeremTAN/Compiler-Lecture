#include "Front-End/Parsing/BinaryOp.hpp"

BinaryOp::BinaryOp(Operator Op, Expr* Left, Expr* Right)
    :m_Operator(Op), m_Left(Left), m_Right(Right) {}

Expr* BinaryOp::getLeft() {return  m_Left; }

Expr* BinaryOp::getRight() { return m_Right; }

BinaryOp::Operator BinaryOp::getOperator() { return m_Operator; }

void BinaryOp::accept(ASTVisitor& V) { V.visit(*this); }