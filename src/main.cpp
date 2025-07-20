#include "compilador.h"
#include <iostream>
#include <filesystem>
int main() {
    Compilador compilador;
    compilador.compilar("samples/herrero.npc");
    return 0;
}

