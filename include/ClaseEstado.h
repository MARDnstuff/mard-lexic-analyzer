#ifndef CLASEESTADO_H
#define CLASEESTADO_H
#include <vector>
#include "Transition.h"

// TODO: Update class documentation and translate to English

class Estado{
    public:
        int ContadorIdEstado = 0; //contador para seguir la enumeracion secuencial
        //Conjunto de Transitiones del estado
        std::vector<Transition> Trans1;
    private:
        //Identificador del estado
        int idEstado1;
        //Verificador de Estado de aceptaci�n
        bool EdoAcept1;
        //Token para estados de aceptaci�n (n�mero �nico)
        int Token1;

    public:
        //Constructor de un estado
        Estado();
        //Constructor de un estado vacio
        Estado Estado_null();
        // Regresa id del estado
        int get_IdEstado();
        // Establece el id del estado
        void set_IdEstado(int id);
        // Regresa el valor True si es un estado de aceptaci�n
        bool is_EdoAcept();
        // Establece el valor a True o False a un estado si es una estado de aceptaci�n
        void set_EdoAcept(bool value);
        // Regresa el valor del Token unico
        int get_Token();
        // Establece el valor del Token (valor �nico)
        void set_Token(int value);
        // Regresa el conjunto de Transitiones asociadas al estado
        std::vector<Transition>  get_Trans (){
            return Trans1;
        }
        // Establece el conjunto (o alguna Transition dentro del conjunto) de Transitiones
        // Agrega a la lista
        std::vector<Transition> set_Trans (Transition value);

        virtual ~Estado();


};

#endif // CLASEESTADO_H
