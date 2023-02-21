#include "lexer.hpp"

namespace charInfo {
    LLVM_READNONE inline bool isWhitespace(char c) {
        return c==' ' || c=='\t' || c=='\f' ||
            c=='\v' || c=='\r' || c=='\n';
    }
    LLVM_READNONE inline bool isDigit(char c){
        return c>= '0' && c<='9';
    }
    LLVM_READNONE inline bool isLetter(char c){
        return (c >='a' && c<='z') || (c>='A' && c<='Z');
    }
}

Lexer::Lexer(const llvm::StringRef& Buffer){
    m_BufferStart = Buffer.begin();
    m_BufferPtr = m_BufferStart;
}

void Lexer::next(Token& token){
    while(*m_BufferPtr && charInfo::isWhitespace(*m_BufferPtr))
        ++m_BufferPtr;

    if(!*m_BufferPtr){
        token.m_kind = Token::eof;
        return;
    }

    if(charInfo::isLetter(*m_BufferPtr)){
        const char* end = m_BufferPtr+1;
        while(charInfo::isLetter(*end))
            ++end;
        llvm::StringRef Name(m_BufferPtr, end-m_BufferPtr);
        Token::TokenKind kind = Name == "with" ? Token::KW_with : Token::ident;
        formToken(token, end, kind);
        return;
    }

    else if(charInfo::isDigit(*m_BufferPtr)){
        const char* end = m_BufferPtr + 1;
        while(charInfo::isDigit(*end))
            ++end;
        formToken(token, end, Token::number);
        return;
    }

    else {
        switch (*m_BufferPtr)
        {
        #define CASE(ch, tok) \
        case ch: formToken(token, m_BufferPtr + 1, tok); break;
        CASE('+', Token::plus);
        CASE('-', Token::minus);
        CASE('*', Token::star);
        CASE('/', Token::slash);
        CASE('(', Token::l_paren);  
        CASE(')', Token::r_paren); 
        CASE(',', Token::comma);
        #undef CASE
        default:
            formToken(token, m_BufferPtr+1, Token::unknown);
            break;
        }
        return;
    }  
}

void Lexer::formToken(Token& tok, const char* tokEnd, Token::TokenKind kind){
    tok.m_kind = kind;
    tok.m_text = llvm::StringRef(m_BufferPtr, tokEnd-m_BufferPtr);
    m_BufferPtr = tokEnd;
}