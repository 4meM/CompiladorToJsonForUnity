#ifndef GENERADOR_JSON_H
#define GENERADOR_JSON_H

#include <string>
#include "contenedores/ast.h"
// GeneradorJson: Clase para generar el archivo JSON a partir del AST
class GeneradorJson {
public:
    static void generar(const AST& ast, const string& archivoSalida);
};

#endif
