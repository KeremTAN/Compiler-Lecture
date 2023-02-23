#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <llvm/ADT/StringRef.h>
#include <llvm/Support/MemoryBuffer.h>

class Token {
public:
    Token();
    friend class Lexer;
    enum TokenKind : unsigned short {
        eof, unknown, ident, number, comma, colon, plus,
        minus, star, slash, l_paren, r_paren, KW_with
    };
    TokenKind       getKind() const;
    llvm::StringRef getText() const;
    bool            is(TokenKind tokenKind) const;
    bool            isOneOf(TokenKind tokenKind1, TokenKind tokenKind2) const;

    template <typename... Ts>
    bool            isOneOf(TokenKind tokenKind1, TokenKind tokenKind2, Ts... Ks) const;

private:
    TokenKind       m_kind;
    llvm::StringRef m_text; 
};
#endif