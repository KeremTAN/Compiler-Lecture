#include "ToIRVisitor.hpp"

ToIRVisitor::ToIRVisitor(Module* Module)
    :m_Module(Module), m_Builder(Module->getContext())
{
    m_VoidTy            = Type::getVoidTy(m_Module->getContext());
    m_Int32Ty           = Type::getInt32Ty(m_Module->getContext());
    m_Int8PtrType       = Type::getInt8PtrTy(m_Module->getContext());
    m_Int8PtrPtrType    = m_Int8PtrType->getPointerTo();
    m_Int32Zero         = ConstantInt::get(m_Int32Ty, 0, true);
}

void ToIRVisitor::run(AST* Tree){
    FunctionType*   MainFty = FunctionType::get(m_Int32Ty, { m_Int32Ty, m_Int8PtrPtrType}, false);
    Function*       MainFn  = Function::Create(MainFty, GlobalValue::ExternalLinkage, "main", m_Module);
    BasicBlock*     BB      = BasicBlock::Create(m_Module->getContext(), "entry", MainFn);
    m_Builder.SetInsertPoint(BB);
    
    Tree->accept(*this);

    FunctionType*   CalcWriteFnTy   = FunctionType::get(m_VoidTy, {m_Int32Ty}, false);
    Function*       CalcWriteFn     = Function::Create(CalcWriteFnTy, GlobalValue::ExternalLinkage, "calc_write", m_Module);
    m_Builder.CreateCall(CalcWriteFnTy, CalcWriteFn, {m_Value});
    m_Builder.CreateRet(m_Int32Zero);
}

void ToIRVisitor::visit(WithDecl& Node){}
void ToIRVisitor::visit(Factor& Node){}
void ToIRVisitor::visit(BinaryOp& Node){}