#ifndef ARBOL_H
#define ARBOL_H

#include <string>
#include <vector>
#include "token.h"
using namespace std;

struct Nodo {
public:
    string etiqueta;             // Ej: "EXPRESION", "INSTRUCCION"
    string tipoToken;            // Ej: "NUMERO", "CADENA", "ID"
    string valor;                // Ej: "42", "hola", "x"
    vector<Nodo*> hijos;

    Nodo(string etiqueta, string tipoToken = "", string valor = "");
    void agregarHijo(Nodo* hijo);
};

class ArbolSintactico {
private:
    void imprimirNodo(Nodo* nodo, int nivel);
    Nodo* raiz;
public:
    ArbolSintactico();
    void setNodoRaiz(Nodo* nodo);
    void imprimir();
};
#endif

