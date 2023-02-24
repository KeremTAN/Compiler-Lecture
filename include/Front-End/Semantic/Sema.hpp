#ifndef SEMA_HPP
#define SEMA_HPP

#include "AST.hpp"
#include "Lexer.hpp"
#include "DeclCheck.hpp"

class Sema {
public:
    Sema();
    bool semantic(AST* Tree);
};
#endif