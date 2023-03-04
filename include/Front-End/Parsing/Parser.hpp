#ifndef PARSER_HPP
#define PARSER_HPP
#include "Front-End/Parsing/AST.hpp"
#include "Front-End/Parsing/Expr.hpp"
#include "Front-End/Scanning/Lexer.hpp"
#include <llvm/Support/raw_ostream.h>

class Parser {
public:
    Parser(Lexer& Lex)
        :m_Lex(Lex), m_HasError(false)
    {}
    bool HasError();
    AST* parse();

private:
    Lexer& m_Lex;
    Token m_Tok;
    bool m_HasError;

    void error();
    void advance();
    bool expect(Token::TokenKind Kind);
    bool consume(Token::TokenKind Kind);

    AST* parseCalc();
    Expr* parseExpr();
    Expr* parseTerm();
    Expr* parseFactor();

};
#endif