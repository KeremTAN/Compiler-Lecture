#ifndef PARSER_HPP
#define PARSER_HPP
#include "AST.hpp"
#include "Expr.hpp"
#include "lexer.hpp"
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