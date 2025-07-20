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
    
    // Validar variables duplicadas y crear conjunto de variables definidas
    set<string> variablesDefinidas;
    for (const auto& variable : npc.variables) {
        // Verificar si la variable ya existe
        if (variablesDefinidas.find(variable.nombre) != variablesDefinidas.end()) {
            cerr << "Error semantico: Variable '" << variable.nombre << "' esta declarada mas de una vez en el NPC '" << npc.nombre << "'.\n";
            exit(1);
        }
        variablesDefinidas.insert(variable.nombre);
    }
    
    // Validar todas las acciones
    for (const auto& accion : npc.acciones) {
        analizarAccion(accion, variablesDefinidas);
    }
}

void AnalizadorSemantico::analizarAccion(const Accion& accion, const std::set<string>& variablesDefinidas) {
    if (accion.tipo == "decir") {
        validarVariablesEnTexto(accion.texto, variablesDefinidas);
    } else if (accion.tipo == "si") {
        if (accion.accionesSi.empty()) {
            cerr << "Error semantico: Bloque 'si' sin acciones.\n";
            exit(1);
        }
        for (const auto& acc : accion.accionesSi) {
            analizarAccion(acc, variablesDefinidas);
        }
        for (const auto& acc : accion.accionesSino) {
            analizarAccion(acc, variablesDefinidas);
        }
    }
}

void AnalizadorSemantico::validarVariablesEnTexto(const string& texto, const set<string>& variablesDefinidas) {
    set<string> variablesUsadas = extraerVariablesDeTexto(texto);
    
    for (const auto& variable : variablesUsadas) {
        if (variablesDefinidas.find(variable) == variablesDefinidas.end()) {
            cerr << "Error semantico: Variable '{" << variable << "}' no esta definida.\n";
            cerr << "Variables disponibles: ";
            for (const auto& var : variablesDefinidas) {
                cerr << "{" << var << "} ";
            }
            cerr << "\n";
            exit(1);
        }
    }
}

set<string> AnalizadorSemantico::extraerVariablesDeTexto(const string& texto) {
    set<string> variables;
    size_t pos = 0;
    
    while ((pos = texto.find('{', pos)) != string::npos) {
        size_t cierre = texto.find('}', pos);
        if (cierre != string::npos) {
            string nombreVariable = texto.substr(pos + 1, cierre - pos - 1);
            variables.insert(nombreVariable);
            pos = cierre + 1;
        } else {
            pos++;
        }
    }
    
    return variables;
}





