#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;
// Estructuras para el AST (Abstract Syntax Tree)
struct Accion {
    string tipo; // "decir" o "si"
    string texto;
    vector<Accion> accionesSi;
    vector<Accion> accionesSino;
    string condicion;
};

struct NPC {
    string nombre;
    vector<Accion> acciones;
};

struct AST {
    vector<NPC> npcs;
};

#endif


