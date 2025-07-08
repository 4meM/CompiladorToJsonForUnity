#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
using namespace std;
// Enumeracion de tipos de tokens
enum TokenType {
    TOKEN_NPC,
    TOKEN_DECIR,
    TOKEN_SI,
    TOKEN_SINO,
    TOKEN_JUGADOR,
    TOKEN_TIENE,
    TOKEN_VAR,        // Nueva palabra clave para variables
    TOKEN_STRING,
    TOKEN_EQUALS,
    TOKEN_IDENT,
    TOKEN_CADENA,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_DOT,
    TOKEN_COLON,
    TOKEN_SEMICOLON,
    TOKEN_EOF,
    TOKEN_UNKNOWN
};

#endif
