#include "include/analizadorLex.h"

AnalizadorLex::AnalizadorLex(string texto) {
    this->texto = texto;
    this->pos = 0;
}

char AnalizadorLex::actual() {
    if (pos >= texto.size()) {
        return '\0';
    }
    return texto[pos];
}

void AnalizadorLex::avanzar() {
    if (pos < texto.size()) {
        pos++;
    }
}

void AnalizadorLex::omitirEspacios() {
    while (actual() == ' ' || actual() == '\n' || actual() == '\t' || actual() == '\r') {
        avanzar();
    }
}

vector<Token> AnalizadorLex::analizar() {
    vector<Token> tokens;

    while (pos < texto.size()) {
        omitirEspacios();

        if ((actual() >= 'a' && actual() <= 'z') || (actual() >= 'A' && actual() <= 'Z')) {
            std::string palabra = "";

            while ((actual() >= 'a' && actual() <= 'z') || 
                   (actual() >= 'A' && actual() <= 'Z') ||
                   (actual() >= '0' && actual() <= '9') ||
                   actual() == '_') {
                palabra += actual();
                avanzar();
            }
            if(palabrasReservadas.find(palabra) != palabrasReservadas.end()){
                tokens.push_back({ palabrasReservadas[palabra], palabra });
            } else {
                tokens.push_back({ "ID", palabra });
            }
        }

        else if (actual() == '"') {
            avanzar();
            std::string textoCadena = "";

            while (actual() != '"' && actual() != '\0') {
                textoCadena += actual();
                avanzar();
            }

            avanzar();
            tokens.push_back({ "CADENA", textoCadena });
        }

        else {
            char c = actual();
            if(c == '\0') {
                break;
            }
            std::string valor(1, c);

            if (c == '{') tokens.push_back({ "LLAVE_ABRE", valor });
            else if (c == '}') tokens.push_back({ "LLAVE_CIERRA", valor });
            else if (c == '(') tokens.push_back({ "PAR_ABRE", valor });
            else if (c == ')') tokens.push_back({ "PAR_CIERRA", valor });
            else if (c == ':') tokens.push_back({ "DOS_PUNTOS", valor });
            else if (c == '.') tokens.push_back({ "PUNTO", valor});
            else if (c == ';') tokens.push_back({ "PUNTO_Y_COMA", valor });
            else tokens.push_back({ "DESCONOCIDO", valor });

            avanzar();
        }
    }
    this -> pos = 0;

    return tokens;
}

void AnalizadorLex::imprimirTokens(){
    vector<Token> forPrint = analizar();
    for(int i = 0; i < forPrint.size(); i++){
        cout << forPrint[i].tipo << " " << forPrint[i].valor << "\n";
    }
}