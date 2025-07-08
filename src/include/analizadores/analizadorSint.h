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
    vector<Accion> parsearListaAcciones(const vector<Variable>& variables);
    Accion parsearAccion(const vector<Variable>& variables);
    Accion parsearCondicional(const vector<Variable>& variables);
    vector<Accion> parsearSino(const vector<Variable>& variables);
    string parsearCondicion();
    // Metodos para variables string
    Variable parsearVariable();
    string parsearTextoConVariables(const vector<Variable>& variables);
};

#endif
