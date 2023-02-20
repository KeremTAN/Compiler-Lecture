#ifndef LEXER_HPP
#define LEXER_HPP
#include <llvm/ADT/StringRef.h>
#include <llvm/Support/MemoryBuffer.h>

class Token {
    friend class Lexer;
public:
    enum TokenKind : unsigned short {
        eof, unknown, ident, number, command, colon, plus,
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