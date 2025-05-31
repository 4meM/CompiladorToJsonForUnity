#ifndef ANALIZADOR_LEX_H
#define ANALIZADOR_LEX_H

#include <string>
#include <vector>
#include <map>
#include "token.h"
using namespace std;



class AnalizadorLex {
public:
    AnalizadorLex(string texto);
    vector<Token> analizar();

private:
    map<string, string> palabrasReservadas = {
        {"NPC", "NPC"},
        {"decir", "DECIR"},
        {"si", "SI"},
        {"sino", "SINO"},
        {"vender", "VENDER"},
        {"jugador", "JUGADOR"},
        {"tiene", "TIENE"}
    };
    string texto;
    int pos;

    char actual();
    void avanzar();
    void omitirEspacios();
};

#endif
