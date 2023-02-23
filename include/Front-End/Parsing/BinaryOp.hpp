#ifndef BINARYOP_HPP
#define BINARYOP_HPP

#include "Expr.hpp"

class BinaryOp : public Expr{

public:
    enum Operator {Plus, Minus, Mul, Div};
    BinaryOp(Operator Op, Expr* Left, Expr* Right);
    Expr* getLeft();
    Expr* getRight();
    Operator getOperator();
    virtual void accept(ASTVisitor& V) override;
    
private:
    Expr* m_Left;
    Expr* m_Right;
    Operator m_Operator;
};
#endif