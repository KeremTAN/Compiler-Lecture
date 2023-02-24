#include "Sema.hpp"
#include <llvm/ADT/StringSet.h>
#include <llvm/Support/Error.h>

class DeclCheck : public ASTVisitor {
public:
    enum ErrorType { Twice, Not };
    DeclCheck();
    bool hasError();
    virtual void visit(Factor& Node) override;
    virtual void visit(BinaryOp& Node) override;
    virtual void visit(WithDecl& Node) override;

private:
    llvm::StringSet<> m_Scope;
    bool m_HasError;
    void error(ErrorType ET, llvm::StringRef V);
};