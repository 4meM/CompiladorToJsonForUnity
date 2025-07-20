#include "analizadores/analizadorSint.h"
#include <iostream>

Parser::Parser(Lexer& lexer) : lexer(lexer) {
    avanzarToken();
}

void Parser::avanzarToken() {
    tokenActual = lexer.obtenerSiguienteToken();
}

void Parser::error(const string& mensaje) {
    cerr << "Error sintactico: " << mensaje << "\n"
              << "Se encontro el token: '" << tokenActual.valor << "' (tipo: " << tokenActual.tipo << ")\n"
              << "Posicion: linea " << tokenActual.linea << ", columna " << tokenActual.columna << "\n"
              << "Posiblemente escribiste algo no valido en este lugar.\n";
    exit(1);
}

AST Parser::parsearPrograma() {
    AST ast;
    while (tokenActual.tipo == TOKEN_NPC) {
        ast.npcs.push_back(parsearNPC());
    }
    return ast;
}

NPC Parser::parsearNPC() {
    avanzarToken(); // NPC
    if (tokenActual.tipo != TOKEN_IDENT) {
        error("Se esperaba un identificador despues de 'NPC'");
    }
    string nombre = tokenActual.valor;
    avanzarToken(); // IDENT
    if (tokenActual.tipo != TOKEN_LBRACE) {
        error("Se esperaba '{'");
    }
    avanzarToken(); // {
    
    // Parsear variables del NPC
    vector<Variable> variables;
    while (tokenActual.tipo == TOKEN_VAR) {
        variables.push_back(parsearVariable());
    }
    
    vector<Accion> acciones = parsearListaAcciones(variables);
    if (tokenActual.tipo != TOKEN_RBRACE) {
        error("Se esperaba '}'");
    }
    avanzarToken(); // }
    return {nombre, variables, acciones};
}

vector<Accion> Parser::parsearListaAcciones(const vector<Variable>& variables) {
    vector<Accion> acciones;
    while (tokenActual.tipo == TOKEN_DECIR || tokenActual.tipo == TOKEN_SI) {
        acciones.push_back(parsearAccion(variables));
    }
    return acciones;
}

Accion Parser::parsearAccion(const vector<Variable>& variables) {
    if (tokenActual.tipo == TOKEN_DECIR) {
        avanzarToken(); // decir
        if (tokenActual.tipo != TOKEN_COLON) {
            error("Se esperaba ':'");
        }
        avanzarToken(); // :
        if (tokenActual.tipo != TOKEN_CADENA) {
            error("Se esperaba cadena");
        }
        string texto = tokenActual.valor; 
        avanzarToken(); // cadena
        if (tokenActual.tipo != TOKEN_SEMICOLON) {
            error("Se esperaba ';'");
        }
        avanzarToken(); // ;
        return {"decir", texto};
    } else if (tokenActual.tipo == TOKEN_SI) {
        return parsearCondicional(variables);
    } else {
        error("Accion invalida");
        return {};
    }
}

Accion Parser::parsearCondicional(const vector<Variable>& variables) {
    avanzarToken(); // si
    if (tokenActual.tipo != TOKEN_LPAREN) {
        error("Se esperaba '('");
    }
    avanzarToken(); // (
    string condicion = parsearCondicion();
    if (tokenActual.tipo != TOKEN_RPAREN) {
        error("Se esperaba ')'");
    }
    avanzarToken(); // )
    if (tokenActual.tipo != TOKEN_LBRACE) {
        error("Se esperaba '{'");
    }
    avanzarToken(); // {
    vector<Accion> accionesSi = parsearListaAcciones(variables);
    if (tokenActual.tipo != TOKEN_RBRACE) {
        error("Se esperaba '}'");
    }
    avanzarToken(); // }
    vector<Accion> accionesSino = parsearSino(variables);
    return {"si", "", accionesSi, accionesSino, condicion};
}

vector<Accion> Parser::parsearSino(const vector<Variable>& variables) {
    if (tokenActual.tipo == TOKEN_SINO) {
        avanzarToken(); // sino
        if (tokenActual.tipo != TOKEN_LBRACE) {
            error("Se esperaba '{'");
        }
        avanzarToken(); // {
        vector<Accion> acciones = parsearListaAcciones(variables);
        if (tokenActual.tipo != TOKEN_RBRACE) {
            error("Se esperaba '}'");
        }
        avanzarToken(); // }
        return acciones;
    }
    return {};
}

string Parser::parsearCondicion() {
    if (tokenActual.tipo != TOKEN_JUGADOR) {
        error("Se esperaba 'jugador'");
    }
    avanzarToken(); // jugador
    if (tokenActual.tipo != TOKEN_DOT) {
        error("Se esperaba '.'");
    }
    avanzarToken(); // .
    if (tokenActual.tipo != TOKEN_TIENE) {
        error("Se esperaba 'tiene'");
    }
    avanzarToken(); // tiene
    if (tokenActual.tipo != TOKEN_LPAREN) {
        error("Se esperaba '('");
    }
    avanzarToken(); // (
    if (tokenActual.tipo != TOKEN_CADENA) {
        error("Se esperaba cadena");
    }
    string texto = tokenActual.valor;
    avanzarToken(); // cadena
    if (tokenActual.tipo != TOKEN_RPAREN) {
        error("Se esperaba ')'");
    }
    avanzarToken(); // )
    return texto;
}

// Manejar variables string
Variable Parser::parsearVariable() {
    avanzarToken(); // var
    
    if (tokenActual.tipo != TOKEN_STRING) {
        error("Se esperaba 'string' (solo variables string por ahora)");
    }
    avanzarToken(); // string
    
    if (tokenActual.tipo != TOKEN_IDENT) {
        error("Se esperaba nombre de variable");
    }
    string nombre = tokenActual.valor;
    avanzarToken(); // nombre
    
    if (tokenActual.tipo != TOKEN_EQUALS) {
        error("Se esperaba '='");
    }
    avanzarToken(); // =
    
    if (tokenActual.tipo != TOKEN_CADENA) {
        error("Se esperaba una cadena de texto para la variable string");
    }
    string valor = tokenActual.valor;
    avanzarToken(); // cadena
    
    if (tokenActual.tipo != TOKEN_SEMICOLON) {
        error("Se esperaba ';'");
    }
    avanzarToken(); // ;
    
    return {nombre, TIPO_STRING, valor};
}

string Parser::parsearTextoConVariables(const vector<Variable>& variables) {
    string texto = tokenActual.valor;
    
    // Reemplazar variables en el texto (formato: {nombreVariable})
    for (const auto& var : variables) {
        string placeholder = "{" + var.nombre + "}";
        size_t pos = texto.find(placeholder);
        while (pos != string::npos) {
            texto.replace(pos, placeholder.length(), var.valor);
            pos = texto.find(placeholder, pos + var.valor.length());
        }
    }
    
    return texto;
}
