#include "NFA.h"
#include "ClaseEstado.h"
#include "ClaseTransicion.h"


// TODO: Update the implementations based on the udpated method names in the header file

//---FUNCIONES AUXILIARES---

//Verifica que el id del estado se encuentre en el vector
bool ContieneEdo(std::vector<Estado> Edo,int EdoDestino){
    int tam = (int) Edo.size();

    for(int i=0; i<tam; i++){
        if(EdoDestino == Edo.at(i).get_IdEstado()){
            return true;
        }//if
    }//for
    return false;
}

//Regresa el estado por ID, que se encuentra dentro del vector
Estado DameEdo_byID (std::vector<Estado> Edo,int EdoID){
    int tam = (int) Edo.size();
    for(int i=0; i<tam;i++){
        if(Edo.at(i).get_IdEstado() == EdoID){
            return Edo.at(i);
        }//if
    }//for
    Estado e = Estado();
    e = e.Estado_null();
    return e;
}

//Regresa el indice en donde se encuentra el estado dentro de un conjunto
int DameIEdo_byID (std::vector<Estado> Edo,int EdoID){
    int tam = (int) Edo.size();
    for(int i=0; i<tam;i++){
        if(Edo.at(i).get_IdEstado() == EdoID){
            return i;
        }//if
    }//for
    return -1;
}

//Verifica si el simbolo ya esta en el alfabeto
bool ContieneSimb (std::vector<char> Alf,char simb){
    int tam = (int) Alf.size();
    if(Alf.empty()){
        return false;
    }

    for(int i=0;i<tam;i++){
        if(Alf.at(i) == simb)
            return true;
    }//for
    return false;
}

//Regresa la union de los conuntos de estados
std::vector<Estado> Unir_ConjEdos(std::vector<Estado> Conj1,std::vector<Estado> Conj2){
    int tam_ = (int) Conj2.size();
    for(int i=0;i<tam_;i++){
        Conj1.push_back(Conj2.at(i));
    }//for
    return Conj1;
}

//Regresa la union de los alfabetos
std::vector<char> Unir_ConjAlf(std::vector<char> Conj1,std::vector<char> Conj2){
    int tam_ = (int) Conj2.size();
    for(int i=0;i<tam_;i++){
        if(!ContieneSimb(Conj1,Conj2.at(i))){
            Conj1.push_back(Conj2.at(i));
        }//if
    }//for
    return Conj1;
}
/////////////////////////////////
//Metodos propios de la clase

//Constructor del NFA
NFA::NFA(){
    IdNFA = 0;
    EdoIni = -1;//posible error
    EdoNFA.clear();
    EdoAcept.clear();
    Alfabeto.clear();
    SeAgregoNFAUnionLexico = false; //sin informaci�n por el momento
    //ctor
}

//Crea un NFA basico para un simbolo
NFA NFA :: createBasic (char simb, int Cont){
    NFA temp = NFA();
    int Origen=Cont,Destino = Cont+1;
    Estado e1, e2;
    e1 = Estado();
    e1.set_IdEstado(Origen);
    e2 = Estado();
    e2.set_IdEstado(Destino);

    Transicion t = Transicion(simb,Origen,Destino);
    Transicion t2 = Transicion();
    Contador=Destino+1;
    e1.set_Trans(t);
    e2.set_EdoAcept(true);
    e2.set_Trans(t2);
    temp.Alfabeto.push_back(simb);
    temp.EdoIni = e1.get_IdEstado();
    temp.EdoNFA.push_back(e1);
    temp.EdoNFA.push_back(e2);
    temp.EdoAcept.push_back(e2);
    temp.Contador = Destino+1;
    SeAgregoNFAUnionLexico = false; //sin informaci�n por el momento
    return temp;
}

//Crea un NFA Basico para un rango de caracteres
NFA NFA :: NFA_Basico (char simb1,char simb2,int Cont){
    NFA temp = NFA();
    int Origen=Cont,Destino = Cont+1;
    Estado e1, e2;
    e1 = Estado();
    e1.set_IdEstado(Origen);
    e2 = Estado();
    e2.set_IdEstado(Destino);
    int s1 = (int) simb1,s2 = (int) simb2;
    while(s1<=s2 ){
        char s = (char) s1;
        Transicion t = Transicion(s,Origen,Destino);
        Transicion t2 = Transicion();
        e1.set_Trans(t);
        //e2.set_Trans(t2);
        s1++;
    }//for

    Contador=Destino+1;
    e2.set_EdoAcept(true);
    int m = simb1,n = simb2;
    while(m<=n){
        char s = m;
        temp.Alfabeto.push_back(s);
        m++;
    }

    temp.EdoIni = e1.get_IdEstado();
    temp.EdoNFA.push_back(e1);
    temp.EdoNFA.push_back(e2);
    temp.EdoAcept.push_back(e2);
    temp.Contador = Destino+1;
    SeAgregoNFAUnionLexico = false; //sin informaci�n por el momento
    return temp;

}

//Union de dos NFA
NFA NFA :: NFA_Union (NFA automata){
    int Origen;
    if(automata.get_Contador() > Contador){
        Origen = automata.get_Contador();
    }else{
        Origen= Contador;
    }
    int Destino=Origen+1;
    Estado e1,e2;
    e1 = Estado();
    e1.set_IdEstado(Origen);
    e2 = Estado();
    e2.set_IdEstado(Destino);
    //Estas transiciones le pertencen a e1
    Transicion t1 = Transicion(EPSILON,Origen,EdoIni);
    Transicion t2 = Transicion(EPSILON,Origen,automata.EdoIni);
    e1.set_Trans(t1);
    e1.set_Trans(t2);

    int tam = (int) EdoNFA.size();
    for(int i=0;i<tam;i++){
        if(EdoNFA.at(i).is_EdoAcept()){
            Transicion t = Transicion(EPSILON,EdoNFA.at(i).get_IdEstado(),e2.get_IdEstado());
            EdoNFA.at(i).set_EdoAcept(false);
            EdoNFA.at(i).set_Trans(t);
        }//if

    }//for

    int tam2 =(int) automata.EdoNFA.size();
    for(int i=0;i<tam2;i++){
        if(automata.EdoNFA.at(i).is_EdoAcept()){
            Transicion t_ = Transicion(EPSILON,automata.EdoNFA.at(i).get_IdEstado(),e2.get_IdEstado());
            automata.EdoNFA.at(i).set_EdoAcept(false);
            automata.EdoNFA.at(i).set_Trans(t_);
        }//if

    }//for
Contador=Destino+1;
    //actulizamos informacion para el automata resultante
    EdoAcept.clear();
    automata.EdoAcept.clear();
    EdoIni = e1.get_IdEstado();
    e2.set_EdoAcept(true);
    EdoAcept.push_back(e2);


    //Union de los estados de los dos automatas
    int n = (int) automata.EdoNFA.size();
        for (int i=0;i<n;i++){
            EdoNFA.push_back(automata.EdoNFA.at(i));
            //Transicion m = Transicion();
        }//for
    //Unions de los alfabetos de los automatas
    int p = (int) automata.Alfabeto.size();
    for(int i=0;i<p;i++){
        if(!ContieneSimb(Alfabeto,automata.Alfabeto.at(i))){
            Alfabeto.push_back(automata.Alfabeto.at(i));
        }
    }//for

    EdoNFA.push_back(e1);
    EdoNFA.push_back(e2);


    return *this;

}

//Concatenaci�n de  dos NFA
NFA NFA :: NFA_Conca (NFA automata){
    std::vector<Transicion> t1;
    std::vector<Transicion> t2;
    int nuevoID = automata.EdoIni, viejoID = EdoAcept.at(0).get_IdEstado();
    int p = (int) EdoNFA.size(),cn;

   int n = (int) automata.EdoNFA.size();
    for(int i=0;i<n;i++){
        if(automata.EdoNFA.at(i).get_IdEstado() == automata.EdoIni){
            t1 = automata.EdoNFA.at(i).get_Trans();
            automata.EdoNFA.erase(automata.EdoNFA.begin()+i);
            break;
        }//if
    }//for


    int q = (int) t1.size();
    for(int i=0;i<p;i++){
        if(EdoNFA.at(i).is_EdoAcept()){
            EdoNFA.at(i).set_EdoAcept(false);
            EdoNFA.at(i).set_IdEstado(nuevoID);
           for(int j=0;j<q;j++){
                EdoNFA.at(i).set_Trans(t1.at(j));
            }//for
        }
    }//for

    EdoAcept.clear();
    EdoAcept.push_back(automata.EdoAcept.at(0));

    int lim = (int) automata.EdoNFA.size();
    for(int i=0;i<lim;i++){
        EdoNFA.push_back(automata.EdoNFA.at(i));
    }//for

    int llim = (int) EdoNFA.size();

    for(int i=0;i<llim;i++){
        cn = (int) EdoNFA.at(i).get_Trans().size();
        for(int j=0;j<cn;j++){
            if(EdoNFA.at(i).get_Trans().at(j).get_EdoDestino() == viejoID){
                EdoNFA.at(i).Trans1.at(j).set_EdoDestino(nuevoID);
            }
        }//for
    }//for

    //Union de los alfabetos
     p = (int) automata.Alfabeto.size();
    for(int i=0;i<p;i++){
        if(!ContieneSimb(Alfabeto,automata.Alfabeto.at(i))){
            Alfabeto.push_back(automata.Alfabeto.at(i));
        }
    }//for

    if(automata.get_Contador() > Contador){
        Contador=automata.Contador;
    }

    return *this;

}

//Cerradura positiva de un NFA
NFA NFA ::NFA_CerrPOS(){
    int Origen=Contador,Destino=Origen + 1;
    Estado e1,e2;
    e1 = Estado();//nuevo estado inicial
    e1.set_IdEstado(Origen);
    e2 = Estado();//nuevo estado final
    e2.set_IdEstado(Destino);


    int n = (int) EdoNFA.size();
    for(int i=0; i<n; i++){
        if(EdoNFA.at(i).is_EdoAcept()){
            Transicion t = Transicion(EPSILON,EdoNFA.at(i).get_IdEstado(),EdoIni);
            Transicion t1 = Transicion(EPSILON,EdoNFA.at(i).get_IdEstado(),Destino);
            EdoNFA.at(i).set_Trans(t);
            EdoNFA.at(i).set_EdoAcept(false);
            EdoNFA.at(i).set_Trans(t1);
            break;
        }//if
    }//for

    Transicion t2 = Transicion(EPSILON,e1.get_IdEstado(),EdoIni);
    e1.set_Trans(t2);

    EdoAcept.clear();
    e2.set_EdoAcept(true);
    EdoAcept.push_back(e2);

    EdoIni = e1.get_IdEstado();
    EdoNFA.push_back(e1);
    EdoNFA.push_back(e2);
    Contador=Destino + 1;
    if(!ContieneSimb(Alfabeto,EPSILON)){
        Alfabeto.push_back(EPSILON);
    }

    return *this;

}

//Cerradura de Kleene
NFA NFA :: NFA_CerrKleene(){
    int Origen=Contador,Destino=Origen + 1;
    Estado e1,e2;
    e1 = Estado();//nuevo estado inicial
    e1.set_IdEstado(Origen);
    e2 = Estado();//nuevo estado final
    e2.set_IdEstado(Destino);


    int n = (int) EdoNFA.size();
    for(int i=0; i<n; i++){
        if(EdoNFA.at(i).is_EdoAcept()){
            Transicion t = Transicion(EPSILON,EdoNFA.at(i).get_IdEstado(),EdoIni);
            Transicion t1 = Transicion(EPSILON,EdoNFA.at(i).get_IdEstado(),e2.get_IdEstado());
            EdoNFA.at(i).set_Trans(t);
            EdoNFA.at(i).set_EdoAcept(false);
            EdoNFA.at(i).set_Trans(t1);
            break;
        }//if
    }//for

    Transicion t2 = Transicion(EPSILON,e1.get_IdEstado(),EdoIni);
    Transicion t3 = Transicion(EPSILON,e1.get_IdEstado(),Destino);
    e1.set_Trans(t2);
    e1.set_Trans(t3);

    EdoAcept.clear();
    e2.set_EdoAcept(true);
    EdoAcept.push_back(e2);

    EdoIni = e1.get_IdEstado();
    EdoNFA.push_back(e1);
    EdoNFA.push_back(e2);
    Contador=Destino + 1;
    if(!ContieneSimb(Alfabeto,EPSILON)){
        Alfabeto.push_back(EPSILON);
    }
    return *this;
}

//Operacion opcional (?)
NFA NFA :: NFA_Opcional(){
    int Origen=Contador,Destino=Origen + 1;
    Estado e1,e2;
    e1 = Estado();//nuevo estado inicial
    e1.set_IdEstado(Origen);
    e2 = Estado();//nuevo estado final
    e2.set_IdEstado(Destino);


    int n = (int) EdoNFA.size();
    for(int i=0; i<n; i++){
        if(EdoNFA.at(i).is_EdoAcept()){
            Transicion t1 = Transicion(EPSILON,EdoNFA.at(i).get_IdEstado(),Destino);
            EdoNFA.at(i).set_EdoAcept(false);
            EdoNFA.at(i).set_Trans(t1);
            break;
        }//if
    }//for

    Transicion t2 = Transicion(EPSILON,e1.get_IdEstado(),EdoIni);
    Transicion t3 = Transicion(EPSILON,e1.get_IdEstado(),Destino);
    e1.set_Trans(t2);
    e1.set_Trans(t3);

    EdoAcept.clear();
    e2.set_EdoAcept(true);
    EdoAcept.push_back(e2);

    EdoIni = e1.get_IdEstado();
    EdoNFA.push_back(e1);
    EdoNFA.push_back(e2);
    Contador=Destino + 1;

    if(!ContieneSimb(Alfabeto,EPSILON)){
        Alfabeto.push_back(EPSILON);
    }

    return *this;
}

 //Regresa el conjunto de estados que son accesible desde "e" con EPSILON
std::vector<Estado> NFA:: CerraduraEpsilon(Estado e){
    std::vector<Estado> R;
    std::stack<Estado> S;

    Estado aux, Edo;
    S.push(e);
    int tam = (int) S.size(), tam_t;

    while(tam != 0){
        aux = S.top();
        S.pop();
        R.push_back(aux);
        tam_t = (int) aux.get_Trans().size();
        for(int i=0; i<tam_t;i++){
          if(aux.get_Trans().at(i).get_SimbInf() == EPSILON){
            if(!ContieneEdo(R,aux.get_Trans().at(i).get_EdoDestino())){
                    Estado p = Estado();
                    p = DameEdo_byID(EdoNFA,aux.get_Trans().at(i).get_EdoDestino());
                    if(p.get_IdEstado() != -1){
                        S.push(p);
                    }
            }//if
          }//if
        }//for
        tam = (int) S.size();
    }//while

    return R;

}

//Regresa el conjunto de estados que son accesibles desde cada uno
//de los estados e que estan en el vector con EPSILON
std::vector<Estado> NFA :: CerraduraEpsilon(std::vector<Estado> ConjEdos){
    int tam = (int) ConjEdos.size(),tam_;
    std::vector<Estado> temp;
    std::vector<Estado> temp2;
    std::vector<Estado> Cerradura;
    temp.clear();

    for(int i=0;i<tam;i++){
        tam_ = (int) CerraduraEpsilon(ConjEdos.at(i)).size();
        for(int j=0; j<tam_; j++){
            Cerradura.push_back(CerraduraEpsilon(ConjEdos.at(i)).at(j));
        }//for
    }//for

    return Cerradura;
}

//Regresa el cnjunto de estado a los que me puedo mover con el simbolo
std::vector<Estado> NFA :: Mover(std::vector<Estado> Edos,char simb){
    std::vector<Estado> C;
    std::vector<Transicion> t;
    Estado aux;
    C.clear();
    t.clear();

    int tam = (int) Edos.size(),tam_;
    for(int i=0; i<tam;i++){
        t = Edos.at(i).get_Trans();
        tam_ = (int) t.size();
        for(int j=0; j<tam_;j++){
            if(t.at(j).get_SimbInf()== simb){
               aux = DameEdo_byID(EdoNFA,t.at(j).get_EdoDestino());
               C.push_back(aux);
            }//if
        }//for
    }//for
    return C;

}

//Regresa el conjunto de estados obtenidos de la cerradura epsilon del conjunto de estados
//accesibles con un simbolo
std::vector<Estado> NFA :: Ir_A(std::vector<Estado> Edos,char simb){
     std::vector<Estado> C;
     C.clear();
     C = CerraduraEpsilon(Mover(Edos,simb));
     return C;
}

//Construye la union especial para los NFA, los va agregando uno a uno a this
//Se pretende que this sea nuevo
void NFA :: NFA_UnionEspecial (NFA f, int Token,int ContadorGlobal){
    Estado e;

    if(!SeAgregoNFAUnionLexico){
        e = Estado();
        e.set_IdEstado(ContadorGlobal);
        Transicion t = Transicion(EPSILON,ContadorGlobal,f.EdoIni);
        EdoNFA.clear();
        Alfabeto.clear();
        e.set_Trans(t);
        EdoIni = e.get_IdEstado();
        EdoNFA.push_back(e);
        SeAgregoNFAUnionLexico = true;

    }else{
        Transicion t = Transicion(EPSILON,EdoIni,f.EdoIni);
        int tam = (int) EdoNFA.size();
        for(int i=0; i<tam;i++){
            if(EdoNFA.at(i).get_IdEstado() == EdoIni){
                EdoNFA.at(i).set_Trans(t);
            }
        }//for
    }//if
    EdoNFA = Unir_ConjEdos(EdoNFA,f.EdoNFA);
    int iterador = DameIEdo_byID(EdoNFA,f.EdoAcept.at(0).get_IdEstado());
    EdoNFA.at(iterador).set_Token(Token);
    EdoAcept.push_back(EdoNFA.at(iterador));
    Alfabeto = Unir_ConjAlf(Alfabeto,f.Alfabeto);
    return;

}


//Muestra la matriz de adyacencia del NFA
void NFA :: Mx_Adyacencia(NFA automata){
int tam = (int) automata.EdoNFA.size();


    for(int i=0; i< tam ; i++){
        std::cout<<"ESTADO --> Q"<<automata.EdoNFA.at(i).get_IdEstado()<<"\n";
        int alf = (int) automata.EdoNFA.at(i).get_Trans().size();
        if(automata.EdoNFA.at(i).get_Trans().empty()){
            std::cout<<"SIN TRANCISION\n";
            std::cout<<"Estado de aceptacion: "<<automata.EdoNFA.at(i).is_EdoAcept()<<"\n";
            std::cout<<"Token: "<<automata.EdoNFA.at(i).get_Token()<<"\n";
        }else{
            for(int j=0; j<alf;j++){
                std::cout<<"TRANSICIONES\n";
                std::cout<<"De Q"<<automata.EdoNFA[i].get_IdEstado()<<" --> Q"<<automata.EdoNFA[i].get_Trans().at(j).get_EdoDestino()<<"\n";
                std::cout<<"Caracter necesario: "<<automata.EdoNFA.at(i).get_Trans().at(j).get_SimbInf()<<"\n";
                std::cout<<"Estado de aceptacion: "<<automata.EdoNFA.at(i).is_EdoAcept()<<"\n";
                std::cout<<"Token: "<<automata.EdoNFA.at(i).get_Token()<<"\n";
            }//for
        }//if
        std::cout<<"////////////////////////////////\n";
    }//for
}



//Regresa el contador del ultimo estado creado
int NFA :: get_Contador (){
    return Contador;
}

NFA::~NFA(){
    //dtor
}
