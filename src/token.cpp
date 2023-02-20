#include "token.hpp"

Token::TokenKind    Token::getKind() const { return m_kind; }
llvm::StringRef     Token::getText() const { return m_text; }

bool Token::is(TokenKind tokenKind) const { return m_kind==tokenKind; }
bool Token::isOneOf(TokenKind tokenKind1, TokenKind tokenKind2) const { return is(tokenKind1) || is(tokenKind2); }

template <typename... Ts>
bool Token::isOneOf(TokenKind tokenKind1, TokenKind tokenKind2, Ts... Ks) const { return is(tokenKind1) || isOneOf(tokenKind2, Ks...); }