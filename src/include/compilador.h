#ifndef COMPILADOR_H
#define COMPILADOR_H

#include "analizadores/analizadorLex.h"
#include "analizadores/analizadorSint.h"
#include "analizadores/analizadorSem.h"
#include "generdorJson.h"
// Union de todos los analizadores y generador JSON
class Compilador {
public:
    void compilar(const string& fuente);

private:
    string extraerNombreBase(const string& ruta);
};

#endif
