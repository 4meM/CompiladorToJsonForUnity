#include "analizadores/analizadorLex.h"
#include <cctype>
#include <iostream>

Lexer::Lexer(const string& entrada)
    : entrada(entrada), posicion(0), linea(1), columna(1) {}

char Lexer::caracterActual() const {
    if (posicion < entrada.size()) {
        return entrada[posicion];
    }
    return '\0';
}

char Lexer::avanzar() {
    char c = caracterActual();
    if (c == '\n') {
        linea++;
        columna = 1;
    } else {
        columna++;
    }
    posicion++;
    return c;
}

void Lexer::saltarEspacios() {
    while (isspace(caracterActual())) {
        avanzar();
    }
}

Token Lexer::reconocerIdentificadorOPalabraClave() {
    size_t inicio = posicion;
    while (isalnum(caracterActual()) || caracterActual() == '_') {
        avanzar();
    }
    string texto = entrada.substr(inicio, posicion - inicio);

    if (texto == "NPC") return {TOKEN_NPC, texto, linea, columna};
    if (texto == "decir") return {TOKEN_DECIR, texto, linea, columna};
    if (texto == "si") return {TOKEN_SI, texto, linea, columna};
    if (texto == "sino") return {TOKEN_SINO, texto, linea, columna};
    if (texto == "jugador") return {TOKEN_JUGADOR, texto, linea, columna};
    if (texto == "tiene") return {TOKEN_TIENE, texto, linea, columna};

    return {TOKEN_IDENT, texto, linea, columna};
}

Token Lexer::reconocerCadena() {
    avanzar(); // Saltar comilla inicial
    size_t inicio = posicion;
    while (caracterActual() != '"' && caracterActual() != '\0') {
        avanzar();
    }
    string texto = entrada.substr(inicio, posicion - inicio);
    if (caracterActual() == '"') {
        avanzar(); // Saltar comilla final
    }
    return {TOKEN_CADENA, texto, linea, columna};
}

Token Lexer::obtenerSiguienteToken() {
    saltarEspacios();

    char c = caracterActual();
    if (c == '\0') {
        return {TOKEN_EOF, "", linea, columna};
    }

    if (isalpha(c) || c == '_') {
        return reconocerIdentificadorOPalabraClave();
    }

    if (c == '"') {
        return reconocerCadena();
    }

    switch (c) {
        case '{': avanzar(); return {TOKEN_LBRACE, "{", linea, columna};
        case '}': avanzar(); return {TOKEN_RBRACE, "}", linea, columna};
        case '(': avanzar(); return {TOKEN_LPAREN, "(", linea, columna};
        case ')': avanzar(); return {TOKEN_RPAREN, ")", linea, columna};
        case '.': avanzar(); return {TOKEN_DOT, ".", linea, columna};
        case ':': avanzar(); return {TOKEN_COLON, ":", linea, columna};
        case ';': avanzar(); return {TOKEN_SEMICOLON, ";", linea, columna};
        default:
            cerr << "Error lexico: simbolo no reconocido '" << c 
                      << "' en linea " << linea << ", columna " << columna << ".\n";
            exit(1);
    }
}
