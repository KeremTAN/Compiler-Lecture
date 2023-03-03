#ifndef TOIRVISITOR_HPP
#define TOIRVISITOR_HPP

#include <llvm/ADT/StringMap.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/raw_ostream.h>
#include "Front-End/Parsing/AST.hpp"

using namespace llvm;

class ToIRVisitor : public ASTVisitor
{
public:
    ToIRVisitor(Module* M);
    ~ToIRVisitor();
    void         run(AST* Tree);
    virtual void visit(WithDecl& Node)  override;
    virtual void visit(Factor& Node)    override;
    virtual void visit(BinaryOp& Node)  override;

private:
    Module*     M;
    IRBuilder<> Builder;
    Type*       VoidTy;
    Type*       Int32Ty;
    Type*       Int8PtrType;
    Type*       Int8PtrPtrType;
    Constant*   Int32Zero;
    Value*      V;
    StringMap<Value*> nameMap;
};


#endif