#include "compilador.h"
#include <sstream>
#include <fstream>

void Compilador::compilar(const string& fuente) {
    ifstream archivo(fuente);
    if (!archivo) {
        cerr << "Error: No se pudo abrir el archivo.\n";
        return;
    }

    stringstream buffer;
    buffer << archivo.rdbuf();
    string contenido = buffer.str();

    Lexer lexer(contenido);
    Parser parser(lexer);
    AST ast = parser.parsearPrograma();

    AnalizadorSemantico semantico;
    semantico.analizar(ast);

    GeneradorJson::generar(ast, "npc.json");

    cout << "Compilacion completada correctamente.\n";
}