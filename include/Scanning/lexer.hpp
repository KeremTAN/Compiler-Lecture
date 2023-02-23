#ifndef LEXER_HPP
#define LEXER_HPP
#include "Scanning/token.hpp"

class Lexer{
public:
    Lexer(const llvm::StringRef& Buffer);
    void next(Token& token);

private:
    const char* m_BufferStart;
    const char* m_BufferPtr;
    void formToken(Token& Result, const char* TokEnd, Token::TokenKind Kind);
};

#endif