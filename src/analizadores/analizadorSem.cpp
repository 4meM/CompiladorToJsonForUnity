#include "analizadores/analizadorSem.h"
#include <iostream>
#include <cstdlib>

void AnalizadorSemantico::analizar(const AST& ast) {
    for (const auto& npc : ast.npcs) {
        analizarNPC(npc);
    }
}

void AnalizadorSemantico::analizarNPC(const NPC& npc) {
    if (npc.acciones.empty()) {
        cerr << "Error semantico: El NPC '" << npc.nombre << "' no tiene acciones.\n";
        exit(1);
    }
    for (const auto& accion : npc.acciones) {
        analizarAccion(accion);
    }
}

void AnalizadorSemantico::analizarAccion(const Accion& accion) {
    if (accion.tipo == "si") {
        if (accion.accionesSi.empty()) {
            cerr << "Error semantico: Bloque 'si' sin acciones.\n";
            exit(1);
        }
        for (const auto& acc : accion.accionesSi) {
            analizarAccion(acc);
        }
        for (const auto& acc : accion.accionesSino) {
            analizarAccion(acc);
        }
    }
}





