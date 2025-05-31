#include <iostream>
#include <fstream>
#include <vector>
#include "include/compilador.h"
using namespace std;
int main() {
    cout << "Compilador de NPCs 1.0\n";
    ifstream archivo("../../samples/vendedor.npc");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo.\n";
        return 1;
    }
    cout << "Leyendo el archivo...\n";
    
    string codigoEnUnaLinea((istreambuf_iterator<char>(archivo)), istreambuf_iterator<char>());
    archivo.close();
    Compilador compilador(codigoEnUnaLinea);
    bool ans = compilador.analizar();
    (ans? cout << "EL CODIGO ES VALIDO\n" : cout << "EL CODIGO TIENE ERRORES\n");
    return 0;
}

