#ifndef AST_HPP
#define AST_HPP

#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/StringRef.h>
#include "ASTVisitor.hpp"

class AST {
public:
    virtual ~AST() {}
    virtual void accept(ASTVisitor& V) = 0;
    virtual void print ()=0;
};

#endif

