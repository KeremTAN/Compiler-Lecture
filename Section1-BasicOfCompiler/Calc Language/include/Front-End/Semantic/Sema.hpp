#ifndef SEMA_HPP
#define SEMA_HPP

#include "Front-End/Parsing/AST.hpp"
#include "Front-End/Scanning/Lexer.hpp"
#include "Front-End/Semantic/DeclCheck.hpp"

class Sema {
public:
    Sema();
    bool semantic(AST* Tree);
};
#endif