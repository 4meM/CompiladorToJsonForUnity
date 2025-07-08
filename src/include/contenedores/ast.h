#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;


enum TipoVariable {
    TIPO_STRING
    // AÑADIR A FUTURO TIPO_INT, TIPO_BOOL, TIPO_FLOAT
};

struct Variable {
    string nombre;
    TipoVariable tipo;
    string valor;
};

// Estructuras para el AST (Abstract Syntax Tree)
struct Accion {
    string tipo; // "decir", "si"
    string texto;
    vector<Accion> accionesSi;
    vector<Accion> accionesSino;
    string condicion;
};

struct NPC {
    string nombre;
    vector<Variable> variables; // Variables string del NPC
    vector<Accion> acciones;
};

struct AST {
    vector<NPC> npcs;
};

#endif


