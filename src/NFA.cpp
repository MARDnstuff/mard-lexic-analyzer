#include "NFA.h"
#include "State.h"
#include "Transition.h"


// TODO: Add a better logging mechanism instead of using std::cout for debugging

//---FUNCIONES AUXILIARES---

//Verifica que el id del estado se encuentre en el vector
bool hasState(std::vector<State> Edo,int EdoDestino){
    int tam = (int) Edo.size();

    for(int i=0; i<tam; i++){
        if(EdoDestino == Edo.at(i).get_IdEstado()){
            return true;
        }//if
    }//for
    return false;
}

//Regresa el estado por ID, que se encuentra dentro del vector
State getStateById (std::vector<State> Edo,int EdoID){
    int tam = (int) Edo.size();
    for(int i=0; i<tam;i++){
        if(Edo.at(i).get_IdEstado() == EdoID){
            return Edo.at(i);
        }//if
    }//for
    State e = State();
    e = e.Estado_null();
    return e;
}

//Regresa el indice en donde se encuentra el estado dentro de un conjunto
int getIndexStateById (std::vector<State> Edo,int EdoID){
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
std::vector<State> Unir_ConjEdos(std::vector<State> Conj1,std::vector<State> Conj2){
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

// TODO: Update counting mechanism to ensure unique state IDs across multiple NFAs

NFA::NFA(char symbol, int initialCounter) {

    // Counter for states
    int source = initialCounter;
    int target = source + 1;

    State state1 = State(), state2 = State();
    counter = target++;

    state1.setStateId(source);
    state1.addTransition(Transition(symbol, source, target));

    state2.setStateId(target);
    state2.setAcceptanceState(true);

    alphabet.push_back(symbol);
    initialState = state1.getStateId();

    states.push_back(state1);
    states.push_back(state2);
    acceptanceStates.push_back(state2);
    counter = target + 1;
}


NFA::NFA(char firstSymbol, char lastSymbol, int initialCounter){
    
    // Counter for states
    int source = initialCounter;
    int target = initialCounter + 1;

    State e1, e2;
    e1 = State();
    e1.set_IdEstado(Origen);
    e2 = State();
    e2.set_IdEstado(Destino);
    int s1 = (int) firstSymbol,s2 = (int) lastSymbol;
    while(s1<=s2 ){
        char s = (char) s1;
        Transicion t = Transicion(s,Origen,Destino);
        Transicion t2 = Transicion();
        e1.set_Trans(t);
        //e2.set_Trans(t2);
        s1++;
    }//for

    counter=Destino+1;
    e2.set_EdoAcept(true);
    int m = firstSymbol,n = lastSymbol;
    while(m<=n){
        char s = m;
        temp.Alfabeto.push_back(s);
        m++;
    }

    temp.EdoIni = e1.get_IdEstado();
    temp.EdoNFA.push_back(e1);
    temp.EdoNFA.push_back(e2);
    temp.EdoAcept.push_back(e2);
    temp.counter = Destino+1;
    SeAgregoNFAUnionLexico = false; //sin informaci�n por el momento
    return temp;
}

//Union de dos NFA
NFA NFA :: makeUnion (NFA automaton){
    int Origen;
    if(automaton.getCounter() > counter){
        Origen = automaton.getCounter();
    }else{
        Origen= counter;
    }
    int Destino=Origen+1;
    State e1,e2;
    e1 = State();
    e1.set_IdEstado(Origen);
    e2 = State();
    e2.set_IdEstado(Destino);
    //Estas transiciones le pertencen a e1
    Transicion t1 = Transicion(EPSILON,Origen,EdoIni);
    Transicion t2 = Transicion(EPSILON,Origen,automaton.EdoIni);
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

    int tam2 =(int) automaton.EdoNFA.size();
    for(int i=0;i<tam2;i++){
        if(automaton.EdoNFA.at(i).is_EdoAcept()){
            Transicion t_ = Transicion(EPSILON,automaton.EdoNFA.at(i).get_IdEstado(),e2.get_IdEstado());
            automaton.EdoNFA.at(i).set_EdoAcept(false);
            automaton.EdoNFA.at(i).set_Trans(t_);
        }//if

    }//for
    counter=Destino+1;
    //actulizamos informacion para el automaton resultante
    EdoAcept.clear();
    automaton.EdoAcept.clear();
    EdoIni = e1.get_IdEstado();
    e2.set_EdoAcept(true);
    EdoAcept.push_back(e2);


    //Union de los estados de los dos automatons
    int n = (int) automaton.EdoNFA.size();
        for (int i=0;i<n;i++){
            EdoNFA.push_back(automaton.EdoNFA.at(i));
            //Transicion m = Transicion();
        }//for
    //Unions de los alfabetos de los automatons
    int p = (int) automaton.Alfabeto.size();
    for(int i=0;i<p;i++){
        if(!ContieneSimb(Alfabeto,automaton.Alfabeto.at(i))){
            Alfabeto.push_back(automaton.Alfabeto.at(i));
        }
    }//for

    EdoNFA.push_back(e1);
    EdoNFA.push_back(e2);


    return *this;

}

//Concatenaci�n de  dos NFA
NFA NFA :: makeConcat (NFA automaton){
    std::vector<Transicion> t1;
    std::vector<Transicion> t2;
    int nuevoID = automaton.EdoIni, viejoID = EdoAcept.at(0).get_IdEstado();
    int p = (int) EdoNFA.size(),cn;

   int n = (int) automaton.EdoNFA.size();
    for(int i=0;i<n;i++){
        if(automaton.EdoNFA.at(i).get_IdEstado() == automaton.EdoIni){
            t1 = automaton.EdoNFA.at(i).get_Trans();
            automaton.EdoNFA.erase(automaton.EdoNFA.begin()+i);
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
    EdoAcept.push_back(automaton.EdoAcept.at(0));

    int lim = (int) automaton.EdoNFA.size();
    for(int i=0;i<lim;i++){
        EdoNFA.push_back(automaton.EdoNFA.at(i));
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
     p = (int) automaton.Alfabeto.size();
    for(int i=0;i<p;i++){
        if(!ContieneSimb(Alfabeto,automaton.Alfabeto.at(i))){
            Alfabeto.push_back(automaton.Alfabeto.at(i));
        }
    }//for

    if(automaton.getCounter() > counter){
        counter=automaton.counter;
    }

    return *this;

}

//Cerradura positiva de un NFA
NFA NFA :: applyPositiveClosure(){
    int Origen=counter,Destino=Origen + 1;
    State e1,e2;
    e1 = State();//nuevo estado inicial
    e1.set_IdEstado(Origen);
    e2 = State();//nuevo estado final
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
    counter=Destino + 1;
    if(!ContieneSimb(Alfabeto,EPSILON)){
        Alfabeto.push_back(EPSILON);
    }

    return *this;

}

//Cerradura de Kleene
NFA NFA :: applyKleeneClosure(){
    int Origen=counter,Destino=Origen + 1;
    State e1,e2;
    e1 = State();//nuevo estado inicial
    e1.set_IdEstado(Origen);
    e2 = State();//nuevo estado final
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
    counter=Destino + 1;
    if(!ContieneSimb(Alfabeto,EPSILON)){
        Alfabeto.push_back(EPSILON);
    }
    return *this;
}

//Operacion opcional (?)
NFA NFA :: makeOptional(){
    int Origen=counter,Destino=Origen + 1;
    State e1,e2;
    e1 = State();//nuevo estado inicial
    e1.set_IdEstado(Origen);
    e2 = State();//nuevo estado final
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
    counter=Destino + 1;

    if(!ContieneSimb(Alfabeto,EPSILON)){
        Alfabeto.push_back(EPSILON);
    }

    return *this;
}

 //Regresa el conjunto de estados que son accesible desde "e" con EPSILON
std::vector<State> NFA:: computeEpsilonClosure(State state){
    std::vector<State> R;
    std::stack<State> S;

    State aux, Edo;
    S.push(state);
    int tam = (int) S.size(), tam_t;

    while(tam != 0){
        aux = S.top();
        S.pop();
        R.push_back(aux);
        tam_t = (int) aux.get_Trans().size();
        for(int i=0; i<tam_t;i++){
          if(aux.get_Trans().at(i).get_SimbInf() == EPSILON){
            if(!hasState(R,aux.get_Trans().at(i).get_EdoDestino())){
                    State p = State();
                    p = getStateById(EdoNFA,aux.get_Trans().at(i).get_EdoDestino());
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
std::vector<State> NFA :: computeEpsilonClosure(std::vector<State> states){
    int tam = (int) states.size(),tam_;
    std::vector<State> temp;
    std::vector<State> temp2;
    std::vector<State> Cerradura;
    temp.clear();

    for(int i=0;i<tam;i++){
        tam_ = (int) computeEpsilonClosure(states.at(i)).size();
        for(int j=0; j<tam_; j++){
            Cerradura.push_back(computeEpsilonClosure(states.at(i)).at(j));
        }//for
    }//for

    return Cerradura;
}

//Regresa el cnjunto de estado a los que me puedo mover con el simbolo
std::vector<State> NFA :: computeMove(std::vector<State> states,char symbol){
    std::vector<State> C;
    std::vector<Transicion> t;
    State aux;
    C.clear();
    t.clear();

    int tam = (int) states.size(),tam_;
    for(int i=0; i<tam;i++){
        t = states.at(i).get_Trans();
        tam_ = (int) t.size();
        for(int j=0; j<tam_;j++){
            if(t.at(j).get_SimbInf()== symbol){
               aux = getStateById(EdoNFA,t.at(j).get_EdoDestino());
               C.push_back(aux);
            }//if
        }//for
    }//for
    return C;
}

//Regresa el conjunto de estados obtenidos de la cerradura epsilon del conjunto de estados
//accesibles con un simbolo
std::vector<State> NFA :: computeGoto(std::vector<State> states,char symbol){
     std::vector<State> C;
     C.clear();
     C = computeEpsilonClosure(computeMove(states,symbol));
     return C;
}

//Construye la union especial para los NFA, los va agregando uno a uno a this
//Se pretende que this sea nuevo
void NFA ::buildSpecialUnion(NFA automaton, int token, int globalCounter){
    State e;

    if(!SeAgregoNFAUnionLexico){
        e = State();
        e.set_IdEstado(globalCounter);
        Transicion t = Transicion(EPSILON,globalCounter,automaton.EdoIni);
        EdoNFA.clear();
        Alfabeto.clear();
        e.set_Trans(t);
        EdoIni = e.get_IdEstado();
        EdoNFA.push_back(e);
        SeAgregoNFAUnionLexico = true;

    }else{
        Transicion t = Transicion(EPSILON,EdoIni,automaton.EdoIni);
        int tam = (int) EdoNFA.size();
        for(int i=0; i<tam;i++){
            if(EdoNFA.at(i).get_IdEstado() == EdoIni){
                EdoNFA.at(i).set_Trans(t);
            }
        }//for
    }//if
    EdoNFA = Unir_ConjEdos(EdoNFA,automaton.EdoNFA);
    int iterador = getIndexStateById(EdoNFA,automaton.EdoAcept.at(0).get_IdEstado());
    EdoNFA.at(iterador).set_Token(token);
    EdoAcept.push_back(EdoNFA.at(iterador));
    Alfabeto = Unir_ConjAlf(Alfabeto,automaton.Alfabeto);
    return;
}

//Muestra la matriz de adyacencia del NFA
void NFA :: showAdjacencyMatrix (NFA automaton){
int tam = (int) automaton.EdoNFA.size();


    for(int i=0; i< tam ; i++){
        std::cout<<"ESTADO --> Q"<<automaton.EdoNFA.at(i).get_IdEstado()<<"\n";
        int alf = (int) automaton.EdoNFA.at(i).get_Trans().size();
        if(automaton.EdoNFA.at(i).get_Trans().empty()){
            std::cout<<"SIN TRANCISION\n";
            std::cout<<"State de aceptacion: "<<automaton.EdoNFA.at(i).is_EdoAcept()<<"\n";
            std::cout<<"Token: "<<automaton.EdoNFA.at(i).get_Token()<<"\n";
        }else{
            for(int j=0; j<alf;j++){
                std::cout<<"TRANSICIONES\n";
                std::cout<<"De Q"<<automaton.EdoNFA[i].get_IdEstado()<<" --> Q"<<automaton.EdoNFA[i].get_Trans().at(j).get_EdoDestino()<<"\n";
                std::cout<<"Caracter necesario: "<<automaton.EdoNFA.at(i).get_Trans().at(j).get_SimbInf()<<"\n";
                std::cout<<"State de aceptacion: "<<automaton.EdoNFA.at(i).is_EdoAcept()<<"\n";
                std::cout<<"Token: "<<automaton.EdoNFA.at(i).get_Token()<<"\n";
            }//for
        }//if
        std::cout<<"////////////////////////////////\n";
    }//for
}



//Regresa el counter del ultimo estado creado
int NFA :: getCounter (){
    return counter;
}

NFA::~NFA(){
    //dtor
}
