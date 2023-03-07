#ifndef TOIRVISITOR_HPP
#define TOIRVISITOR_HPP

#include <llvm/ADT/StringMap.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/raw_ostream.h>
#include "Front-End/Parsing/AST.hpp"
#include "Front-End/Parsing/WithDecl.hpp"
#include "Front-End/Parsing/Factor.hpp"
#include "Front-End/Parsing/BinaryOp.hpp"

using namespace llvm;

class ToIRVisitor : public ASTVisitor
{
public:
    ToIRVisitor(Module* Module);
    ~ToIRVisitor();
    void         run(AST* Tree);
    virtual void visit(WithDecl& Node)  override;
    virtual void visit(Factor& Node)    override;
    virtual void visit(BinaryOp& Node)  override;

private:
    Module*     m_Module;
    IRBuilder<> m_Builder;
    Type*       m_VoidTy;
    Type*       m_Int32Ty;
    Type*       m_Int8PtrType;
    Type*       m_Int8PtrPtrType;
    Constant*   m_Int32Zero;
    Value*      m_Value;
    StringMap<Value*> m_nameMap;
};


#endif