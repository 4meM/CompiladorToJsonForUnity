#include "include/analizadorSint.h"

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

bool AnalizadorSint::instrucciones(){
    Token tokAct = actual();
    if(tokAct.tipo == "DECIR") return decir();
    if(tokAct.tipo == "SI") return condicionSi();
    if(tokAct.tipo == "NPC") return npc();
    return false;
}

bool AnalizadorSint::bloque(){
    if(!coincidir("LLAVE_ABRE")) return false;
    while(actual().tipo != "LLAVE_CIERRA" && actual().tipo != "EOF"){
        if(!instrucciones()) return false; 
    }
    if(!coincidir("LLAVE_CIERRA")) return false;
    return true;
}
bool AnalizadorSint::decir(){
    if(!coincidir("DECIR")) return false;
    if(!coincidir("DOS_PUNTOS")) return false;
    if(!coincidir("CADENA")) return false;
    if(!coincidir("PUNTO_Y_COMA")) return false;
    return true;
}
bool AnalizadorSint::expresion() {
    int posInicial = this->pos;
    if(expresionLiteral()) return true;
    this -> pos = posInicial;
    if(expresionBooleana()) return true;
    this->pos = posInicial;
    if(expresionLlamada()) return true;
    this->pos = posInicial;
    return false;
}


bool AnalizadorSint::expresionLiteral() {
    Token actualToken = this->actual();
    return actualToken.tipo == "CADENA" || actualToken.tipo == "NUMERO";
}

bool AnalizadorSint::expresionBooleana() {
    Token actualToken = this->actual();
    return actualToken.tipo == "VERDADERO" || actualToken.tipo == "FALSO";
}

bool AnalizadorSint::expresionLlamada(){
    int posInicial = this->pos;
    if (actual().tipo == "ID") {
        avanzar();
        if (coincidir("PUNTO") && coincidir("ID") && coincidir("PAR_ABRE")) {
            if (expresion()) {
                return coincidir("PAR_CIERRA");
            }
        }
    }
    this->pos = posInicial;
    return false;
}

bool AnalizadorSint::condicionSi(){
    int posInicial = this->pos;
    if(!coincidir("SI")) return false;

    if(!coincidir("PAR_ABRE")){ this->pos = posInicial; return false;}

    if(!expresion()) { this->pos = posInicial; return false; }

    if(!coincidir("PAR_CIERRA")){ this->pos = posInicial; return false; }

    if(!bloque()){ this->pos = posInicial; return false;}

    if(coincidir("SINO")){

        if(!bloque()){ this->pos = posInicial; return false; }
    }    

    return true;
}

bool AnalizadorSint::npc() {
    if (!coincidir("NPC")) return false;
    if (!coincidir("ID")) return false;
    if (!bloque()) return false;
    return true;
}