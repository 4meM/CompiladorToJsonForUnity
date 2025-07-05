#ifndef ANALIZADOR_LEX_H
#define ANALIZADOR_LEX_H

#include <string>
#include <iostream>
#include "contenedores/token.h"

// tipo, valor y ubicacion 
struct Token {
    TokenType tipo;
    string valor;
    int linea;
    int columna;
};

// Lexer: Generar tokens a partir de la entrada
class Lexer {
public:
    Lexer(const string& entrada);
    Token obtenerSiguienteToken();

private:
    string entrada;
    size_t posicion;
    int linea;
    int columna;

    void saltarEspacios();
    char caracterActual() const;
    char avanzar();
    Token reconocerIdentificadorOPalabraClave();
    Token reconocerCadena();
};


#endif
