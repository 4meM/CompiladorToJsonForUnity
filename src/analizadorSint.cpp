#include "include/analizadorSint.h"
#include "analizadorSint.h"

AnalizadorSint::AnalizadorSint(vector<Token> tokens) {
    this->tokens = tokens;
    this->pos = 0;
}

Token AnalizadorSint::actual() {
    if (pos >= tokens.size()) {
        return {"EOF", ""};
    }
    return tokens[pos];
}

void AnalizadorSint::avanzar(){
    if(pos < tokens.size()){
        pos++;
    }
}

bool AnalizadorSint::coincidir(string tipo){
    Token actualToken = this->actual();
    if(actualToken.tipo == tipo){
        this->avanzar();
        return true;
    }
    return false;
}

Nodo* AnalizadorSint::instrucciones(){
    Token tokAct = actual();
    if(tokAct.tipo == "DECIR") return decir();
    if(tokAct.tipo == "SI") return condicionSi();
    if(tokAct.tipo == "NPC") return npc();
    return nullptr;
}

Nodo* AnalizadorSint::bloque(){
    
    if(!coincidir("LLAVE_ABRE")) return nullptr;

    Nodo* nodoBloque = new Nodo("BLOQUE");
    Nodo* nodoLLaveAbre = new Nodo("","LLAVE_ABRE","{");
    nodoBloque->agregarHijo(nodoLLaveAbre);
    while(actual().tipo != "LLAVE_CIERRA" && actual().tipo != "EOF"){
        Nodo* instruccion = instrucciones();
        if(!instruccion){
            delete nodoBloque;
            return nullptr;
        }
        nodoBloque->agregarHijo(instruccion);
    }
    if(!coincidir("LLAVE_CIERRA")){
        delete nodoBloque;
        return nullptr;
    };
    Nodo* nodoLLaveCierra = new Nodo("","LLAVE_CIERRA","}");
    nodoBloque->agregarHijo(nodoLLaveCierra);
    return nodoBloque;
}
Nodo* AnalizadorSint::decir(){
    if(!coincidir("DECIR")) return nullptr;
    if(!coincidir("DOS_PUNTOS")) return nullptr;
    Token actualToken = this->actual();
    if(!coincidir("CADENA")) return nullptr;

    Nodo* nodoDecir = new Nodo("DECIR");
    nodoDecir->agregarHijo(new Nodo("", actualToken.tipo, actualToken.valor));


    if(!coincidir("PUNTO_Y_COMA")){
        delete nodoDecir;
        return nullptr;
    }
    return nodoDecir;
}
Nodo* AnalizadorSint::expresion() {
    int posInicial = this->pos;

    Nodo* lit = expresionLiteral();
    if(lit) return lit;
    this -> pos = posInicial;

    Nodo* boolExpr = expresionBooleana();
    if(boolExpr) return boolExpr;
    this->pos = posInicial;

    Nodo* llamada = expresionLlamada();
    if(llamada) return llamada;
    this->pos = posInicial;

    return nullptr;
}


Nodo* AnalizadorSint::expresionLiteral() {
    Token actualToken = this->actual();
    if(actualToken.tipo == "CADENA" || actualToken.tipo == "NUMERO"){
        avanzar();
        return new Nodo("EXPRESION_LITERAL", actualToken.tipo, actualToken.valor);
    }
    return nullptr;
}

Nodo* AnalizadorSint::expresionBooleana() {
    Token actualToken = this->actual();
    if (actualToken.tipo == "VERDADERO" || actualToken.tipo == "FALSO") {
        avanzar();
        return new Nodo("BOOLEANO", actualToken.tipo, actualToken.valor);
    }
    return nullptr;
}

Nodo* AnalizadorSint::expresionLlamada() {
    int posInicial = this->pos;

    Token objeto = actual();
    if (!coincidir("JUGADOR")) return nullptr;

    if (!coincidir("PUNTO")) {
        this->pos = posInicial;
        return nullptr;
    }

    Token funcion = actual();
    if (!coincidir("TIENE")) {
        this->pos = posInicial;
        return nullptr;
    }

    if (!coincidir("PAR_ABRE")) {
        this->pos = posInicial;
        return nullptr;
    }

    Nodo* llamada = new Nodo("LLAMADA");
    llamada->agregarHijo(new Nodo("", "JUGADOR", objeto.valor));
    llamada->agregarHijo(new Nodo("", "TIENE", funcion.valor));

    Nodo* param = expresion();
    if (!param) {
        delete llamada;
        this->pos = posInicial;
        return nullptr;
    }
    llamada->agregarHijo(param);

    if (!coincidir("PAR_CIERRA")) {
        delete llamada;
        this->pos = posInicial;
        return nullptr;
    }

    return llamada;
}


Nodo* AnalizadorSint::condicionSi(){
    int posInicial = this->pos;
    if(!coincidir("SI")) return nullptr;

    if(!coincidir("PAR_ABRE")){ this->pos = posInicial; return nullptr;}

    Nodo* nodoSi = new Nodo("SI");
    Nodo* expr = expresion();
    if(!expr){
        delete nodoSi;
        this->pos = posInicial;
        return nullptr;
    }
    nodoSi->agregarHijo(expr);

    if(!coincidir("PAR_CIERRA")){
        delete nodoSi;
        this->pos = posInicial;
        return nullptr;
    }
    Nodo* bloqueSi = bloque();
    if(!bloqueSi){
        delete nodoSi;
        this->pos = posInicial;
        return nullptr;
    }
    nodoSi->agregarHijo(bloqueSi);

    if(coincidir("SINO")){
        Nodo* bloqueSino = bloque();
        if(!bloqueSino){
            delete nodoSi;
            this->pos = posInicial;
            return nullptr;
        }
        nodoSi->agregarHijo(bloqueSino);
    }    
    return nodoSi;
}

Nodo* AnalizadorSint::npc() {
    int posInicial = this->pos;
    if (!coincidir("NPC")) return nullptr;
    Token id = actual();
    if (!coincidir("ID")) return nullptr;
    Nodo* nodoNpc = new Nodo("NPC");
    nodoNpc->agregarHijo(new Nodo("", id.tipo, id.valor));
    Nodo* bloqueNpc = bloque();
    if(!bloqueNpc) {
        delete nodoNpc;
        this->pos = posInicial;
        return nullptr;
    }
    nodoNpc->agregarHijo(bloqueNpc);
    return nodoNpc;
}

Nodo* AnalizadorSint::analizar() {
    Nodo* nodoRaiz = new Nodo("INICIO");
    while (actual().tipo != "EOF") {
        Nodo* instr = instrucciones();
        if (!instr) {
            delete nodoRaiz;
            return nullptr;
        }
        nodoRaiz->agregarHijo(instr);
    }
    return nodoRaiz;
}

void AnalizadorSint::imprimirArbol(Nodo* nodo, int nivel){
    if (!nodo) return;

    for (int i = 0; i < nivel; i++) {
        cout << "  ";
    }

    cout << nodo->tipoToken;
    if (!nodo->valor.empty()) {
        cout << " (" << nodo->valor << ")";
    }
    cout << endl;

    for (Nodo* hijo : nodo->hijos) {
        imprimirArbol(hijo, nivel + 1);
    }
}

