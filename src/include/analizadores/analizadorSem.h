#ifndef ANALIZADOR_SEM_H
#define ANALIZADOR_SEM_H

#include "contenedores/ast.h"
#include <set>
// Analizador semantico para validar la estructura
class AnalizadorSemantico {
public:
    void analizar(const AST& ast);
private:
    void analizarNPC(const NPC& npc);
    void analizarAccion(const Accion& accion, const std::set<string>& variablesDefinidas);
    void validarVariablesEnTexto(const string& texto, const std::set<string>& variablesDefinidas);
    std::set<string> extraerVariablesDeTexto(const string& texto);
};

#endif

