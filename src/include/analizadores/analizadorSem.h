#ifndef ANALIZADOR_SEM_H
#define ANALIZADOR_SEM_H

#include "contenedores/ast.h"
// Analizador semantico para validar la estructura
class AnalizadorSemantico {
public:
    void analizar(const AST& ast);
private:
    void analizarNPC(const NPC& npc);
    void analizarAccion(const Accion& accion);
};

#endif

