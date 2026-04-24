#include "Fonction.h"

int main()
{
    Fonction f = Fonction();
    f.setFonction("3x^2-7");
    f.f(-1);
    f.newton(1,5);
    f.dichotomie(1,7);
    f.lim(0);
    f.df(3);
    return(0);
}