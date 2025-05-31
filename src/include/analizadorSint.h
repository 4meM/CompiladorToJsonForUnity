#ifndef ANALIZADOR_SINT_H
#define ANALIZADOR_SINT_H

#include <string>
#include <vector>
#include <map>
#include "token.h"
#include "arbolSint.h"
using namespace std;

class AnalizadorSint {
private:
    vector<Token> tokens;
    int pos;
    Token actual();
    void avanzar();
    bool coincidir(string tipo);
    
    bool instrucciones();
    bool bloque();
    bool decir();
    bool expresion();
    bool expresionLiteral();
    bool expresionBooleana();
    bool expresionLlamada();
    bool condicionSi();
    bool npc();

public:
    AnalizadorSint(vector<Token> tokens);

    Nodo* analizar();
};

#endif