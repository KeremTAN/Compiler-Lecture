#include "Front-End/Scanning/Token.hpp"

Token::Token(){};

Token::TokenKind    Token::getKind() const { return m_kind; }
llvm::StringRef     Token::getText() const { return m_text; }

bool Token::is(TokenKind tokenKind) const { return m_kind==tokenKind; }
bool Token::isOneOf(TokenKind tokenKind1, TokenKind tokenKind2) const { return is(tokenKind1) || is(tokenKind2); }
