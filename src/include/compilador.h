#ifndef COMPILADOR_H
#define COMPILADOR_H

#include <string>
#include <vector>
#include "analizadorLex.h"
#include "analizadorSint.h"
#include "token.h"

class Compilador {
public:
    Compilador(string codigoFuente);
    bool analizar();
    vector<Token> getTokens();

private:
    std::string codigoFuente;
    std::vector<Token> tokens;
};

#endif