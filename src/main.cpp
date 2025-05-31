#include <iostream>
#include <fstream>
#include <vector>
#include "include/compilador.h"
using namespace std;
int main() {
    ifstream archivo("../../samples/vendedor.npc");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo.\n";
        return 1;
    }
    cout << "Leyendo archivo...\n";
    return 0;
}

