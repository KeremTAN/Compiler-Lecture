#include "CodeGen.hpp"


void CodeGen::compile(AST* Tree){
    LLVMContext Ctx;
    Module* M = new Module("calc.expr", Ctx);
    ToIRVisitor ToIR(M);
    ToIR.run(Tree);
    M->print(outs(), nullptr);
}

