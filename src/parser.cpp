#include "parser.hpp"

AST* Parser::parse() {
    AST* Res = parseCalc();
    expect(Token::eof);
    return Res;
}

AST* Parser::parseCalc(){
    Expr* E;
    llvm::SmallVector<llvm::StringRef, 8> Vars;
    if (expect(Token::ident))
        goto _error;
    Vars.push_back(m_Tok.getText());
    advance();

    while (m_Tok.is(Token::comma)){
        advance();
        if (expect(Token::ident))
            goto _error;
        Vars.push_back(m_Tok.getText());
        advance();
    }

    if(consume(Token::colon))
        goto _error;
        
    E = parseExpr();

/*
    if(Vars.empty()) return E;
    else return new WithDecl(Vars, E);
*/
_error:
while (!m_Tok.is(Token::eof))
    advance();
return nullptr;
}

void Parser::error(){
    llvm::errs()<<"Unexpected: " << m_Tok.getText() <<'\n';
    m_HasError = true;
}

void Parser::advance() { m_Lex.next(m_Tok); }

bool Parser::expect(Token::TokenKind Kind) {
    if(m_Tok.getKind()!=Kind) {
        error();
        return true;
    }
        return false;
}

bool Parser::consume(Token::TokenKind Kind){
    if(expect(Kind))
        return true;
    advance();
    return false;
}