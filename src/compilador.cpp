#include "compilador.h"
#include <sstream>
#include <fstream>
#include <filesystem>

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

    // Extraer el nombre base del archivo (sin extensión)
    string nombreBase = extraerNombreBase(fuente);
    string archivoSalida = "Plantilla-Unity-NPC/Resources/" + nombreBase + ".json";

    GeneradorJson::generar(ast, archivoSalida);

    cout << "Compilacion completada correctamente.\n";
    cout << "Archivo generado: " << archivoSalida << "\n";
}

string Compilador::extraerNombreBase(const string& ruta) {
    //Encontrar la ultima barra de la ruta 
    size_t ultimaBarra = ruta.find_last_of("/\\");
    string nombreArchivo = (ultimaBarra == string::npos) ? ruta : ruta.substr(ultimaBarra + 1);
    
    // Quitar el (.npc)
    size_t ultimoPunto = nombreArchivo.find_last_of('.');
    return (ultimoPunto == string::npos) ? nombreArchivo : nombreArchivo.substr(0, ultimoPunto);
}