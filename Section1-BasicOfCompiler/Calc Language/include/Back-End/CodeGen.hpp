#ifndef CODEGEN_HPP
#define CODEGEN_HPP

#include "Front-End/Parsing/AST.hpp"
#include "Back-End/ToIRVisitor.hpp"

class CodeGen {
public:
void compile(AST* Tree);
};

#endif