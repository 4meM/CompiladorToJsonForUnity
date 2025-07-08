#include "generdorJson.h"
#include <fstream>

static string indent(int nivel) {
    return string(nivel * 2, ' ');
}

static void escribirAccion(ofstream& out, const Accion& acc, int nivel) {
    out << indent(nivel) << "{\n";
    out << indent(nivel+1) << "\"tipo\": \"" << acc.tipo << "\",\n";
    if (acc.tipo == "decir") {
        out << indent(nivel+1) << "\"texto\": \"" << acc.texto << "\"\n";
    } else if (acc.tipo == "si") {
        out << indent(nivel+1) << "\"condicion\": \"" << acc.condicion << "\",\n";
        out << indent(nivel+1) << "\"accionesSi\": [\n";
        for (size_t i = 0; i < acc.accionesSi.size(); ++i) {
            escribirAccion(out, acc.accionesSi[i], nivel+2);
            if (i + 1 < acc.accionesSi.size()) out << ",\n";
        }
        out << "\n" << indent(nivel+1) << "],\n";
        out << indent(nivel+1) << "\"accionesSino\": [\n";
        for (size_t i = 0; i < acc.accionesSino.size(); ++i) {
            escribirAccion(out, acc.accionesSino[i], nivel+2);
            if (i + 1 < acc.accionesSino.size()) out << ",\n";
        }
        out << "\n" << indent(nivel+1) << "]\n";
    }
    out << indent(nivel) << "}";
}

void GeneradorJson::generar(const AST& ast, const string& archivoSalida) {
    ofstream out(archivoSalida);
    out << "{\n  \"npcs\": [\n";
    for (size_t i = 0; i < ast.npcs.size(); ++i) {
        const NPC& npc = ast.npcs[i];
        out << "    {\n";
        out << "      \"nombre\": \"" << npc.nombre << "\",\n";
        
        // Agregar variables al JSON (formato compatible con Unity)
        if (!npc.variables.empty()) {
            out << "      \"variables\": [\n";
            for (size_t v = 0; v < npc.variables.size(); ++v) {
                const Variable& var = npc.variables[v];
                out << "        {\n";
                out << "          \"nombre\": \"" << var.nombre << "\",\n";
                out << "          \"variable\": {\n";
                out << "            \"tipo\": \"string\",\n";  // Por ahora solo string
                out << "            \"valor\": \"" << var.valor << "\"\n";
                out << "          }\n";
                out << "        }";
                if (v + 1 < npc.variables.size()) out << ",";
                out << "\n";
            }
            out << "      ],\n";
        }
        
        out << "      \"acciones\": [\n";
        for (size_t j = 0; j < npc.acciones.size(); ++j) {
            escribirAccion(out, npc.acciones[j], 3);
            if (j + 1 < npc.acciones.size()) out << ",\n";
        }
        out << "\n      ]\n    }";
        if (i + 1 < ast.npcs.size()) out << ",";
        out << "\n";
    }
    out << "  ]\n}\n";
    out.close();
}
