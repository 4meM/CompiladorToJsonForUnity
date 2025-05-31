#include "include/compilador.h"

Compilador::Compilador(string codigoFuente) {
    this->codigoFuente = codigoFuente;
}

bool Compilador::analizar() {
    AnalizadorLex lexer(codigoFuente);
    tokens = lexer.analizar();
    cout << "CODIGO ANALIZADO\n";
    lexer.imprimirTokens();
    AnalizadorSint parser(tokens);
    cout << "IMPRIMIR ARBOL\n";
    Nodo* arbol = parser.analizar();
    parser.imprimirArbol(arbol,0);
    if (arbol == nullptr) {
        return false;
    }

    delete arbol;
    return true;
}

vector<Token> Compilador::getTokens() {
    return tokens;
}