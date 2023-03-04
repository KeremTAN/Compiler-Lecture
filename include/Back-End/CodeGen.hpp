#ifndef CODEGEN_HPP
#define CODEGEN_HPP

#include "Front-End/Parsing/AST.hpp"
#include "ToIRVisitor.hpp"

class CodeGen {
public:
void compile(AST* Tree);
};

#endif