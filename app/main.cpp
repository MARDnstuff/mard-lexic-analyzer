#include <iostream>
#include <memory>
#include "State.h"
#include "Transition.h"
#include "NFA.h"
// #include "ClaseAFD.h"
// #include "AnalizLexico.h"
// #include "EvaluadorExp1.h"
// #include "ER_NFA.h"
// #include "DescRecGram_Gram.h"
// #include "AnalizadorLL1.h"
#include <vector>
#include <list>

using namespace std;
State Edo_byID(vector<State> Edo, int EdoID);
void Ver_Alfabeto(vector<char> Alf);
void Ver_ConjAcept(vector<State> Conj);

// pruebas paso por referencia
void modifica(shared_ptr<float> prueba)
{
    *prueba += 1;
    return;
}

void modifica2(shared_ptr<float> prueba)
{
    modifica(prueba);
    *prueba += 5;

    return;
}

int main()
{

    cout << "Hello world" << endl;

    // AnalizadorLL1 e = AnalizadorLL1("E -> T Ep; Ep -> mas T Ep| menos T Ep |epsilon; T -> F Tp; Tp -> prod F Tp | div F Tp | epsilon; F -> parI E parD | num;");
    // e.CrearTablaLL1();
    // //cout<<e.column<<endl;

    // for(int i=0; i<e.row; i++){
    //     for(int j=0; j<e.column; j++){
    //       cout<<e.TablaLL1[i][j]<<" ";
    //     }//for
    //     cout<<endl;
    // }//for
    // //incializar el tama�o de Vt3
    // e.Vt3 = new int[e.column];
    // int token;
    // for(int i=0; i<e.column; i++){
    //     cout<<"Introduce el Token para:"<<e.Vt[i].Simbolo<<" -->";
    //     cin>>token;
    //     e.Vt3[i] = token;
    //     cout<<e.Vt3[i]<<endl;
    // }

    // /*
    //     e.NFA_UnionEspecial(a1,20,a10.Contador); // +
    //     e.NFA_UnionEspecial(a2,30,a10.Contador); // -
    //     e.NFA_UnionEspecial(a3,40,a10.Contador); // *
    //     e.NFA_UnionEspecial(a4,50,a10.Contador); // /
    //     e.NFA_UnionEspecial(a5,60,a10.Contador); // (
    //     e.NFA_UnionEspecial(a6,70,a10.Contador); // )
    //     e.NFA_UnionEspecial(a10,10,a10.Contador); // num
    // */
    // e.SetLexico("AFDAritmeticas.txt");
    // e.LexGram.SetSigma("2.57*(12+16-8)/13-17)");

    // cout<<e.LexGram.yylex()<<" --> "<<e.LexGram.Lexema<<endl;
    // cout<<e.LexGram.yylex()<<" --> "<<e.LexGram.Lexema<<endl;
    // cout<<e.LexGram.yylex()<<" --> "<<e.LexGram.Lexema<<endl;
    // cout<<e.LexGram.yylex()<<" --> "<<e.LexGram.Lexema<<endl;
    // cout<<e.LexGram.yylex()<<" --> "<<e.LexGram.Lexema<<endl;
    // cout<<e.LexGram.yylex()<<" --> "<<e.LexGram.Lexema<<endl;
    // cout<<e.LexGram.yylex()<<" --> "<<e.LexGram.Lexema<<endl;
    // cout<<e.LexGram.yylex()<<" --> "<<e.LexGram.Lexema<<endl;
    // cout<<e.LexGram.yylex()<<" --> "<<e.LexGram.Lexema<<endl;
    // cout<<e.LexGram.yylex()<<" --> "<<e.LexGram.Lexema<<endl;
    // cout<<e.LexGram.yylex()<<" --> "<<e.LexGram.Lexema<<endl;
    // cout<<e.LexGram.yylex()<<" --> "<<e.LexGram.Lexema<<endl;
    // cout<<e.LexGram.yylex()<<" --> "<<e.LexGram.Lexema<<endl;
    // cout<<e.LexGram.yylex()<<" --> "<<e.LexGram.Lexema<<endl;

    // if(e.AnalizSintacLL1("2.57*(12+16-8)/(13-17)")){ //<-- Es el caso de erro resolverlo YYAAA
    //     cout<<"cadena correcta"<<endl;
    // }else{
    //     cout<<"cadena incorrecta"<<endl;
    // }
    // //  REVISAR ANALISIS LL1

    return 0;
}

// E -> T Ep; Ep -> mas T Ep| menos T Ep |epsilon; T -> F Tp; Tp -> prod F Tp | div F Tp | epsilon; F -> parI E parD | num;
State Edo_byID(vector<State> Edo, int EdoID)
{
    int tam = (int)Edo.size();
    for (int i = 0; i < tam; i++)
    {
        if (Edo.at(i).getStateId() == EdoID)
        {
            return Edo.at(i);
        } // if
    } // for
    State e = State();
    e.setStateId(-1);
    return e;
}

void Ver_Alfabeto(vector<char> Alf)
{
    int tam = (int)Alf.size();
    cout << "Alfabeto={";
    for (int i = 0; i < tam; i++)
    {
        cout << Alf.at(i) << ",";
    } // for
    cout << "}" << endl;
    return;
}

void Ver_ConjAcept(vector<State> Conj)
{
    int tam = (int)Conj.size();
    cout << "Estados de Aceptacion ={";
    for (int i = 0; i < tam; i++)
    {
        cout << Conj.at(i).getStateId() << "(" << Conj.at(i).getToken() << "), ";
    } // for
    cout << "}" << endl;
    return;
}
// Pruebas
/*
NFA automata = NFA();
NFA a1;
a1 = automata.createBasic('a','c',0);

NFA automata2 = NFA();
NFA a2;
a2 = automata2.createBasic('d','f',a1.get_Contador());

a1 = a1.NFA_Union(a2);
a1 = a1.NFA_CerrKleene();


NFA automata3 = NFA();
NFA a3;
a3 = automata3.createBasic('g','i',a1.get_Contador());

a3 = a3.NFA_CerrPOS();

NFA automata4 = NFA();
NFA a4;
a4 = automata4.createBasic('w','y',a3.get_Contador());




NFA e =NFA();
e.NFA_UnionEspecial(a1,10,a4.Contador);
e.NFA_UnionEspecial(a3,20,a4.Contador);
e.NFA_UnionEspecial(a4,30,a4.Contador);

AFD nuevo = AFD();
nuevo = nuevo.Conv_NFAaAFD(e);

Ver_Alfabeto(nuevo.Alfabeto);
vector<ConIj> temp;
temp = nuevo.get_EdoNFA();
nuevo.Crea_TablaAFD();

if(!nuevo.Guarda_TablaAFD("pruebaAFD")){
    cout<<"No se puedo guardar la tabla del AFD"<<endl;
}

AFD f1 = AFD();

f1.Carga_TablaAFD("pruebaAFD.txt");*/

// Aritmeticas
/*
NFA automata = NFA();
NFA a1;
a1 = automata.createBasic('+','+',0);

NFA automata2 = NFA();
NFA a2;
a2 = automata2.createBasic('-','-',a1.get_Contador());

NFA automata3 = NFA();
NFA a3;
a3 = automata3.createBasic('*','*',a2.get_Contador());

NFA automata4 = NFA();
NFA a4;
a4 = automata4.createBasic('/','/',a3.get_Contador());

NFA automata5 = NFA();
NFA a5;
a5 = automata5.createBasic('(','(',a4.get_Contador());

NFA automata6 = NFA();
NFA a6;
a6 = automata6.createBasic(')',')',a5.get_Contador());

NFA automata7 = NFA();
NFA a7;
a7 = automata7.createBasic('0','9',a6.get_Contador());
a7 = a7.NFA_CerrPOS();



NFA automata8 = NFA();
NFA a8;
a8 = automata8.createBasic('.','.',a7.get_Contador());

a7 = a7.NFA_Conca(a8);



NFA automata9 = NFA();
NFA a9;
a9 = automata9.createBasic('0','9',a7.get_Contador());
a9 = a9.NFA_CerrPOS();

a7 = a7.NFA_Conca(a9);

NFA automata10 = NFA();
NFA a10;
a10 = automata10.createBasic('0','9',a7.get_Contador());
a10 = a10.NFA_CerrPOS();
a10 = a10.NFA_Union(a7);


NFA e =NFA();
e.NFA_UnionEspecial(a1,20,a10.Contador); // +
e.NFA_UnionEspecial(a2,30,a10.Contador); // -
e.NFA_UnionEspecial(a3,40,a10.Contador); // *
e.NFA_UnionEspecial(a4,50,a10.Contador); // /
e.NFA_UnionEspecial(a5,60,a10.Contador); // (
e.NFA_UnionEspecial(a6,70,a10.Contador); // )
e.NFA_UnionEspecial(a10,10,a10.Contador); // num

AFD nuevo = AFD();
nuevo = nuevo.Conv_NFAaAFD(e);
nuevo.Crea_TablaAFD();
nuevo.Guarda_TablaAFD("AFDAritmeticas");*/

// Expresion Regular a NFA
// OR
/*NFA automata = NFA();
NFA a1;
a1 = automata.createBasic('|','|',0);
// CONC
NFA automata2 = NFA();
NFA a2;
a2 = automata2.createBasic('&','&',a1.Contador);
// CERR_POS
NFA automata3 = NFA();
NFA a3;
a3 = automata3.createBasic('+','+',a2.Contador);
// CERR_KLE
NFA automata4 = NFA();
NFA a4;
a4 = automata.createBasic('*','*',a3.Contador);
//OPC
NFA automata5 = NFA();
NFA a5;
a5 = automata5.createBasic('?','?',a4.Contador);
//PAR_I
NFA automata6 = NFA();
NFA a6;
a6 = automata6.createBasic('(','(',a5.Contador);
// PAR_D
NFA automata7 = NFA();
NFA a7;
a7 = automata7.createBasic(')',')',a6.Contador);
//CORCH_I
NFA automata8 = NFA();
NFA a8;
a8 = automata8.createBasic('[','[',a7.Contador);
//CORCH_D
NFA automata9 = NFA();
NFA a9;
a9 = automata9.createBasic(']',']',a8.Contador);
//GUION
NFA automata10 = NFA();
NFA a10;
a10 = automata10.createBasic('-','-',a9.Contador);
//SIMBOLO
//--> [a - z]
NFA automata11 = NFA();
NFA a11;
a11 = automata11.createBasic('a','z',a10.Contador);

//--> [A - Z]
NFA automata12 = NFA();
NFA a12;
a12 = automata12.createBasic('A','Z',a11.Contador);

// --> [0 - 9]
NFA automata13 = NFA();
NFA a13;
a13 = automata13.createBasic('0','9',a12.Contador);

// --> [A - z] | [a - z] | [0 - 9]
a13 = a13.NFA_Union(a11);
a13 = a13.NFA_Union(a12);

// --> |
NFA automata14 = NFA();
NFA a14;
a14 = automata14.createBasic('|','|',a13.Contador);

// --> &
NFA automata15 = NFA();
NFA a15;
a15 = automata15.createBasic('&','&',a14.Contador);
 // --> +
NFA automata16 = NFA();
NFA a16;
a16 = automata16.createBasic('+','+',a15.Contador);
// --> *
NFA automata17 = NFA();
NFA a17;
a17 = automata17.createBasic('*','*',a16.Contador);
 // --> ?
NFA automata18 = NFA();
NFA a18;
a18 = automata18.createBasic('?','?',a17.Contador);
 // --> (
NFA automata19 = NFA();
NFA a19;
a19 = automata19.createBasic('(','(',a18.Contador);
 // --> )
NFA automata20 = NFA();
NFA a20;
a20 = automata20.createBasic(')',')',a19.Contador);
 // --> [
NFA automata21 = NFA();
NFA a21;
a21 = automata21.createBasic('[','[',a20.Contador);
 // --> ]
NFA automata22 = NFA();
NFA a22;
a22 = automata22.createBasic(']',']',a21.Contador);
 // --> -
NFA automata23 = NFA();
NFA a23;
a23 = automata23.createBasic('-','-',a22.Contador);

// --> '\'
NFA automata24 = NFA();
NFA a24;
a24 = automata24.createBasic('\\','\\',a23.Contador);


// --> Concatenacion de simbolos
a24 = a24.NFA_Union(a14);
a24 = a24.NFA_Union(a15);
a24 = a24.NFA_Union(a16);
a24 = a24.NFA_Union(a17);
a24 = a24.NFA_Union(a18);
a24 = a24.NFA_Union(a19);
a24 = a24.NFA_Union(a20);
a24 = a24.NFA_Union(a21);
a24 = a24.NFA_Union(a22);
a24 = a24.NFA_Union(a23);

    // --> '\'
NFA automata25 = NFA();
NFA a25;
a25 = automata25.createBasic('\\','\\',a24.Contador);
a25 = a25.NFA_Conca(a24);

// Completo
a13 = a13.NFA_Union(a25);
// Diagonales invertidas
NFA automata26 = NFA();
NFA a26;
a26 = automata26.createBasic('\\','\\',a13.Contador);
//Union especial
NFA e =NFA();
e.NFA_UnionEspecial(a1,10,a13.Contador);
e.NFA_UnionEspecial(a2,20,a13.Contador);
e.NFA_UnionEspecial(a3,30,a13.Contador);
e.NFA_UnionEspecial(a4,40,a13.Contador);
e.NFA_UnionEspecial(a5,50,a13.Contador);
e.NFA_UnionEspecial(a6,60,a13.Contador);
e.NFA_UnionEspecial(a7,70,a13.Contador);
e.NFA_UnionEspecial(a8,80,a13.Contador);
e.NFA_UnionEspecial(a9,90,a13.Contador);
e.NFA_UnionEspecial(a10,100,a13.Contador);
e.NFA_UnionEspecial(a13,110,a13.Contador);
//e.NFA_UnionEspecial(a26,120,a13.Contador);
AFD nuevo = AFD();
nuevo = nuevo.Conv_NFAaAFD(e);
nuevo.Crea_TablaAFD();
nuevo.Guarda_TablaAFD("ER_NFA");

AFD  nuevo = AFD();
nuevo.Carga_TablaAFD("ER_NFA.txt");

ER_NFA e = ER_NFA("[a-z]|[A-Z]|[0-9]|((\\\\)&(\\||\\&|\\+|\\*|\\?|\\(|\\)|\\[|\\]|\\-|\\\\))",nuevo);

if(e.IniConversion()){
    cout<<"Automata creado por Expresion regular"<<endl;
    e.result.Mx_Adyacencia(e.result);
}else{
    cout<<"Expresion regular erronea"<<endl;
}*/

/*
//Punto y coma (PC)
NFA automata = NFA();
NFA a1;
a1 = automata.createBasic(';',';',0);

// FLECHA
NFA automata2 = NFA();
NFA a2;
a2 = automata2.createBasic('-','-',a1.Contador);

NFA automata3 = NFA();
NFA a3;
a3 = automata3.createBasic('>','>',a2.Contador);

a2 = a2.NFA_Conca(a3);

// OR
NFA automata4 = NFA();
NFA a4;
a4 = automata4.createBasic('|','|',a2.Contador);

//SIMBOLO
NFA automata5 = NFA();
NFA a5;
a5 = automata5.createBasic('a','z',a4.Contador);

NFA automata6 = NFA();
NFA a6;
a6 = automata6.createBasic('A','Z',a5.Contador);

NFA automata7 = NFA();
NFA a7;
a7 = automata7.createBasic('0','9',a6.Contador);

NFA automata8 = NFA();
NFA a8;
a8 = automata8.createBasic('_','_',a7.Contador);

a8 = a8.NFA_Union(a5);
a8 = a8.NFA_Union(a6);
a8 = a8.NFA_Union(a7);
a8 = a8.NFA_CerrKleene();

NFA automata9 = NFA();
NFA a9;
a9 = automata9.createBasic('a','z',a8.Contador);

NFA automata10 = NFA();
NFA a10;
a10 = automata10.createBasic('A','Z',a9.Contador);

a10 = a10.NFA_Union(a9);
a10 = a10.NFA_Conca(a8);


NFA automata11 = NFA();
NFA a11;
a11 = automata10.createBasic(' ',' ',a11.Contador);

NFA e =NFA();
e.NFA_UnionEspecial(a11,2001,a11.Contador);
e.NFA_UnionEspecial(a1,10,a11.Contador);
e.NFA_UnionEspecial(a2,20,a11.Contador);
e.NFA_UnionEspecial(a4,30,a11.Contador);
e.NFA_UnionEspecial(a10,40,a11.Contador);

AFD nuevo = AFD();
nuevo = nuevo.Conv_NFAaAFD(e);
nuevo.Crea_TablaAFD();
nuevo.Guarda_TablaAFD("AFD_GramGram");*/

/*NOTA: falta agregar m�s simbolos para no tener problemas
agregacelos lo m�s pronto posible
Clase III - 18
Probar FIrst
*/

// Gamaticas de Gramaticas
/*AFD  nuevo = AFD();
nuevo.Carga_TablaAFD("AFD_GramGram.txt");

AnalizLexico l = AnalizLexico("E -> T Ep; Ep -> mas T Ep| epsilon;",nuevo);
cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
cout<<l.yylex()<<" -> "<<l.Lexema<<endl;*/

// Descenso recursivo mapeo de Gramatica
/*= DescRecGram_Gram("E -> T Ep; Ep -> mas T Ep| menos T Ep |epsilon; T -> F Tp; Tp -> prod F Tp | div F Tp | epsilon; F -> parI E parD | num;","AFD_GramGram.txt");

if(e.AnalizarGramatica()){
 cout<<"Expresion correcta"<<endl;
 e.IdentificarTerminales();
 cout<<"----Simbolos no terminales----"<<endl;
 int i=0;
 for(ClaseNodo s: e.Vn){
     cout<<"["<<i<<"] --> "<< s.Simbolo<< endl;
     i++;
 }//for
 cout<<"----------------------------"<<endl;

 cout<<"----Simbolos  terminales----"<<endl;
 int j=0;
 for(ClaseNodo n: e.Vt){
     cout<<"["<<j<<"] --> "<< n.Simbolo<< endl;
     j++;
 }//for
 cout<<"--------------------------"<<endl;

 cout<<"----Gramatica mapeada----"<<endl;
 i=0;
 for(int k=0; k<e.NumReglas ; k++){
         cout<<"Regla ["<<k<<"]:"<<e.ArrReglas[k].InfSimbolo.Simbolo<<endl;
     for(ClaseNodo p: e.ArrReglas[k].ListaLadoDerecho){
         cout<<"\t["<<i<<"] -->"<< p.Simbolo<<" -->EsTerminal: "<<p.Terminal<<"  ";
         i++;
     }
     cout<<endl;
 }//for
 cout<<"--------------------------"<<endl;
}else{
 cout<<"Expresion erronea"<<endl;
}

*/
