#include "ClaseEstado.h"
#include <vector>

// TODO: Udpate names and add a better logging mechanism instead of using std::cout for debugging (spdlog)

// Constructor de un estado
Estado::Estado(){
    EdoAcept1 = false;
    Token1 = -1;
    //aumento -- revisar
    idEstado1 = ContadorIdEstado++;
    Trans1.clear();
    //ctor
}

//Constructor de un estado vacio
Estado Estado :: Estado_null(){
    Estado e = Estado();
    e.set_IdEstado(-1);
    return e;
}

// Regresa id del estado
int Estado:: get_IdEstado(){
    return idEstado1;
}

// Establece el id del estado
void Estado:: set_IdEstado(int id){
    idEstado1 = id;
    return;
}

// Regresa el valor True si es un estado de aceptaci�n
bool Estado:: is_EdoAcept(){
    return EdoAcept1;
}

// Establece el valor a True o False a un estado si es una estado de aceptaci�n
void Estado:: set_EdoAcept(bool value){
    EdoAcept1 = value;
    return;
}

// Regresa el valor del Token unico
int Estado:: get_Token (){
    return Token1;
}

// Establece el valor del Token (valor �nico)
void Estado:: set_Token(int value){
    Token1 = value;
    return;
}


// Establece el conjunto (o alguna Transition dentro del conjunto) de Transitiones
// Agrega a la lista
std::vector<Transition> Estado :: set_Trans (Transition value){
    Trans1.push_back(value);
    return Trans1;
}


Estado::~Estado(){
    //dtor
}
