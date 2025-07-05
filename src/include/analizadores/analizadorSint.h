#ifndef ANALIZADOR_SINT_H
#define ANALIZADOR_SINT_H

#include "analizadorLex.h"
#include "contenedores/ast.h"


// Analizador sintactico para construir el AST
class Parser {
public:
    Parser(Lexer& lexer);
    AST parsearPrograma();

private:
    Lexer& lexer;
    Token tokenActual;

    void avanzarToken();
    void error(const string& mensaje);

    NPC parsearNPC();
    vector<Accion> parsearListaAcciones();
    Accion parsearAccion();
    Accion parsearCondicional();
    vector<Accion> parsearSino();
    string parsearCondicion();
};

#endif
