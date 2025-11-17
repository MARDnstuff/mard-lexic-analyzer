#include "ER_NFA.h"

//Constructor
ER_NFA::ER_NFA(std::string sigma, AFD AutFD){
    ExprRegular = sigma;
    L = AnalizLexico(ExprRegular,AutFD);
}

//Establece la expresion regular
void ER_NFA::SetExpresion(std::string sigma){
    ExprRegular = sigma;
    L.SetSigma(sigma);
}

//Destructor
ER_NFA::~ER_NFA(){
    //dtor
}

//////////PRCOESO DE EVALUACION///////////

bool ER_NFA:: F(std::shared_ptr<NFA> f_ap){
    int Token;
    char simbolo1, simbolo2;
    Token = L.yylex();
    switch(Token){
        case 60: { //PAR_IZQ
            if(E(f_ap)){
                Token = L.yylex();
                if(Token == 70){ //PAR_DER
                    return true;
                }//if
            }//if
            return false;
            break;
        }
        case 80: { //CORCHETE_IZQ
            Token = L.yylex();
            if(Token == 110){ //SIMBOLO
                simbolo1 = (L.Lexema[0] == '\\')?L.Lexema[1]: L.Lexema[0];
                Token = L.yylex();
                if(Token == 100){ //GUION
                    Token = L.yylex();
                    if(Token == 110){//SIMBOLO
                            simbolo2 = (L.Lexema[0] == '\\')?L.Lexema[1]: L.Lexema[0];
                            Token = L.yylex();
                            if(Token == 90){ //CORCHETE DERECHO
                                *f_ap = f_ap->createBasic(simbolo1,simbolo2,ContarEdo);
                                ContarEdo = f_ap->counter;
                                return true;
                            }

                    }//if
                }//if
            }//if
            return false;
            break;
        }
        case 110: { //SIMBOLO
            simbolo1 = (L.Lexema[0] == '\\')?L.Lexema[1]: L.Lexema[0];
            *f_ap = f_ap->createBasic(simbolo1,simbolo1,ContarEdo);
            ContarEdo = f_ap->counter;
            return true;
            break;
        }
    }//switch
    return false;
}

bool ER_NFA :: Cp(std::shared_ptr<NFA> f_ap){
    int Token;
    Token = L.yylex();
    switch(Token){
        case 30: { //CERRADURA POSITIVA
            *f_ap = f_ap->applyPositiveClosure();
            ContarEdo = f_ap->counter;
            if(Cp(f_ap)){
                return true;
            }//if
            return false;
            break;
        }
        case 40:{ //CERRADURA DE KLEEN
            *f_ap = f_ap->applyKleeneClosure();
            ContarEdo = f_ap->counter;
            if(Cp(f_ap)){
                return true;
            }//if
            return false;
            break;
        }
        case 50:{ // OPCIONAL
            *f_ap = f_ap->makeOptional();
            ContarEdo = f_ap->counter;
            if(Cp(f_ap)){
                return true;
            }//if
            return false;
            break;
        }
    }//switch
    L.UndoToken();
    return true;
}


bool ER_NFA :: C(std::shared_ptr<NFA> f_ap){
    if(F(f_ap)){
        if(Cp(f_ap)){
            return true;
        }//if
    }//if
    return false;
}

bool ER_NFA :: Tp(std::shared_ptr<NFA> f_ap){
    int Token;
    NFA f2 = NFA();
    std::shared_ptr<NFA> f2_ap(new NFA(f2));
    Token = L.yylex();
    if(Token == 20){//CONCATENACION
        if(C(f2_ap)){
            *f_ap = f_ap->makeConcat(*f2_ap);
            ContarEdo = f_ap->counter;
            if(Tp(f_ap)){
                return true;
            }//if
        }//if
        return false;
    }//if
    L.UndoToken();
    return true;

}

bool ER_NFA :: T(std::shared_ptr<NFA> f_ap){
    if(C(f_ap)){
        if(Tp(f_ap)){
            return true;
        }//if
    }//if
    return false;
}

bool ER_NFA:: Ep(std::shared_ptr<NFA> f_ap){
    int Token;
    NFA f2 = NFA();
    std::shared_ptr<NFA> f2_ap(new NFA(f2));
    Token = L.yylex();
    if(Token == 10){ //OR
        if(T(f2_ap)){
            *f_ap =f_ap->makeUnion(*f2_ap);
            ContarEdo = f_ap->counter;
            if(Ep(f_ap)){
                return true;
            }//if
        }//if
        return false;
    }//if
    L.UndoToken();
    return true;
}

bool ER_NFA :: E(std::shared_ptr<NFA> f_ap){
    if(T(f_ap)){
        if(Ep(f_ap)){
            return true;
        }//if
    }//if
    return false;
}

bool ER_NFA::IniConversion(){
    int Token;
    NFA f = NFA();
    std::shared_ptr<NFA> f_ap(new NFA(f));
    if(E(f_ap)){
        Token = L.yylex();
        if(Token == 0){
            result = *f_ap;
            return true;
        }//if
    }//if
    return false;
}
//////////////////////////////////////////
