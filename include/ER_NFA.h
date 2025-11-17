#ifndef ER_NFA_H
#define ER_NFA_H
#include <string>
#include "NFA.h"
#include "AnalizLexico.h"
#include <memory>
class ER_NFA{
    private:
        std::string ExprRegular;
        int ContarEdo = 0;
    public:
        NFA result;
        AnalizLexico L;
    public:
        //Constructor
        ER_NFA(std::string sigma, AFD AutFD);
        //Establece la expresion regular
        void SetExpresion(std::string sigma);
        //Destructor
        virtual ~ER_NFA();
        ////////PROCESO DE EVALUACION//////////
        bool F(std::shared_ptr<NFA> f_ap);
        bool Cp(std::shared_ptr<NFA> f_ap);
        bool C(std::shared_ptr<NFA> f_ap);
        bool Tp(std::shared_ptr<NFA> f_ap);
        bool T(std::shared_ptr<NFA> f_ap);
        bool Ep(std::shared_ptr<NFA> f_ap);
        bool E(std::shared_ptr<NFA> f_ap);
        bool IniConversion();
        ///////////////////////////////////////

};

#endif // ER_NFA_H
