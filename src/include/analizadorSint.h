#ifndef ANALIZADOR_SINT_H
#define ANALIZADOR_SINT_H

#include <string>
#include <vector>
#include "token.h"
#include "arbolSint.h"
#include <iostream>
using namespace std;

class AnalizadorSint {
private:
    vector<Token> tokens;
    int pos;
    Token actual();
    void avanzar();
    bool coincidir(string tipo);
    
    Nodo* instrucciones();
    Nodo* bloque();
    Nodo* decir();
    Nodo* expresion();
    Nodo* expresionLiteral();
    Nodo* expresionBooleana();
    Nodo* expresionLlamada();
    Nodo* condicionSi();
    Nodo* npc();

public:
    AnalizadorSint(vector<Token> tokens);
    void imprimirArbol(Nodo* nodo);
    Nodo* analizar();
    void imprimirArbol(Nodo *nodo, int nivel);
};

#endif