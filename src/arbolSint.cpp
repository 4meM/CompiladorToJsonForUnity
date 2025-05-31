#include "include/arbolSint.h"
#include <iostream>
using namespace std;

Nodo::Nodo(string etiqueta, string tipoToken, string valor) {
    this->etiqueta = etiqueta;
    this->tipoToken = tipoToken;
    this->valor = valor;
}

void Nodo::agregarHijo(Nodo* hijo) {
    hijos.push_back(hijo);
}

Nodo::~Nodo() {
    for (Nodo* hijo : hijos) {
        delete hijo;
    }
    hijos.clear();
}

ArbolSintactico::ArbolSintactico() {
    raiz = nullptr;
}

void ArbolSintactico::setNodoRaiz(Nodo* nodo) {
    raiz = nodo;
}

void ArbolSintactico::imprimir() {
    imprimirNodo(raiz, 0);
}

void ArbolSintactico::imprimirNodo(Nodo* nodo, int nivel) {
    if (nodo == nullptr) return;

    for (int i = 0; i < nivel; i++) cout << "  ";
    cout << nodo->etiqueta;

    if (!nodo->tipoToken.empty()) {
        cout << " [" << nodo->tipoToken;
        if (!nodo->valor.empty()) {
            cout << ": " << nodo->valor;
        }
        cout << "]";
    }

    cout << endl;

    for (Nodo* hijo : nodo->hijos) {
        imprimirNodo(hijo, nivel + 1);
    }
}
