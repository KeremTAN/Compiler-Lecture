#include "Sema.hpp"

Sema::Sema(){}

bool Sema::semantic(AST* Tree){
    if(!Tree)
        return false;
    DeclCheck Check;
    Tree->accept(Check);
    return Check.hasError();
}