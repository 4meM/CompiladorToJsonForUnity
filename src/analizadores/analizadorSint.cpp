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
    vector<Accion> acciones = parsearListaAcciones();
    if (tokenActual.tipo != TOKEN_RBRACE) {
        error("Se esperaba '}'");
    }
    avanzarToken(); // }
    return {nombre, acciones};
}

vector<Accion> Parser::parsearListaAcciones() {
    vector<Accion> acciones;
    while (tokenActual.tipo == TOKEN_DECIR || tokenActual.tipo == TOKEN_SI) {
        acciones.push_back(parsearAccion());
    }
    return acciones;
}

Accion Parser::parsearAccion() {
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
        return parsearCondicional();
    } else {
        error("Accion invalida");
        return {};
    }
}

Accion Parser::parsearCondicional() {
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
    vector<Accion> accionesSi = parsearListaAcciones();
    if (tokenActual.tipo != TOKEN_RBRACE) {
        error("Se esperaba '}'");
    }
    avanzarToken(); // }
    vector<Accion> accionesSino = parsearSino();
    return {"si", "", accionesSi, accionesSino, condicion};
}

vector<Accion> Parser::parsearSino() {
    if (tokenActual.tipo == TOKEN_SINO) {
        avanzarToken(); // sino
        if (tokenActual.tipo != TOKEN_LBRACE) {
            error("Se esperaba '{'");
        }
        avanzarToken(); // {
        vector<Accion> acciones = parsearListaAcciones();
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
