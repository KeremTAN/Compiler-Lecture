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

void ToIRVisitor::visit(WithDecl& Node){
    FunctionType*   ReadFty = FunctionType::get(m_Int32Ty, {m_Int8PtrType}, false);
    Function*       ReadFn  = Function::Create(ReadFty, GlobalValue::ExternalLinkage, "calc_read", m_Module);

    for(auto I = Node.begin(), E=Node.end(); I!=E; ++I){
        StringRef   Var = *I;
        Constant*   StrText = ConstantDataArray::getString(m_Module->getContext(), Var);
        GlobalVariable* Str = new GlobalVariable(
            *m_Module, StrText->getType(), true,
            GlobalValue::PrivateLinkage, StrText,
            Twine(Var).concat(".str"));

        Value* Ptr = m_Builder.CreateInBoundsGEP(Str->getType(), Str, {m_Int32Zero, m_Int32Zero}, "ptr");
        CallInst* Call = m_Builder.CreateCall(ReadFty, ReadFn, {Ptr});
        m_nameMap[Var] = Call;
    }
    Node.getExpr()->accept(*this);
}

void ToIRVisitor::visit(Factor& Node){
    if(Node.getKind() == Factor::Ident){
        m_Value = m_nameMap[Node.getVal()];
    }
    else {
        int intVal;
        Node.getVal().getAsInteger(10, intVal);
        m_Value = ConstantInt::get(m_Int32Ty, intVal, true);
    }
}

void ToIRVisitor::visit(BinaryOp& Node){
    Node.getLeft()->accept(*this);
    Value* Left = m_Value;
    Node.getRight()->accept(*this);
    Value* Right =m_Value;
    switch (Node.getOperator())
    {
    case BinaryOp::Plus:
        m_Value = m_Builder.CreateNSWAdd(Left, Right);
        break;

    case BinaryOp::Minus:
        m_Value = m_Builder.CreateNSWSub(Left, Right);
        break;
    
    case BinaryOp::Mul:
        m_Value = m_Builder.CreateNSWMul(Left, Right);
        break;
    
    case BinaryOp::Div:
        m_Value = m_Builder.CreateSDiv(Left, Right);
        break;
    }
}
