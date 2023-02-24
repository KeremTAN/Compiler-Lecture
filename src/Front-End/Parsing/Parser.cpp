#include "Front-End/Parsing/Parser.hpp"

AST* Parser::parse() {
    AST* Res = parseCalc();
    expect(Token::eof);
    return Res;
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

    if(Vars.empty()) return E;
    else return new WithDecl(Vars, E);

_error:
    while (!m_Tok.is(Token::eof))
        advance();
    return nullptr;
}

Expr* Parser::parseExpr(){
    Expr* Left = parseTerm();
    while (m_Tok.isOneOf(Token::plus, Token::minus)) {
        BinaryOp::Operator Op = m_Tok.is(Token::plus) ? BinaryOp::Plus : BinaryOp::Minus;
        advance();
        Expr* Right = parseTerm();
        Left = new BinaryOp(Op, Left, Right);
    }
    return Left;
}

Expr* Parser::parseTerm() {
    Expr* Left = parseFactor();
    while (m_Tok.isOneOf(Token::star, Token::slash)) {
        BinaryOp::Operator Op = m_Tok.is(Token::star) ? BinaryOp::Mul : BinaryOp::Div;
        advance();
        Expr* Right = parseTerm();
        Left = new BinaryOp(Op, Left, Right);
    }
    return Left;
}

Expr* Parser::parseFactor(){
    Expr* Res = nullptr;
    switch ((m_Tok.getKind()))
    {
    case Token::number:
        Res = new Factor(Factor::Number, m_Tok.getText());
        advance();
        break;
    
    case Token::ident:
        Res = new Factor(Factor::Ident, m_Tok.getText());
        advance();
        break;

    case Token::l_paren:
        advance();
        Res = parseExpr();
        if(!consume(Token::r_paren))
            break;     
    default:
        if(!Res)
            error();
        break;
    }

    while(!m_Tok.isOneOf(Token::r_paren, Token::star, Token::plus, Token::minus, Token::eof))
        advance();
    
    return Res;
}