#include "Fonction.h"
#include <iostream>

int main()
{
    float a , b;
    std::string fonction;
    Fonction f = Fonction();
    std::cout << "Entrez une fonction pôlunome : ";
    std::cin >> fonction;
    std :: cout << "Entrez les bornes a et b  de l'interval [a,b] : \na = ";
    std::cin >> a;
    std::cout << "b = ";
    std::cin >> b;
    f.setFonction(fonction);
    f.f(-1);
    f.newton(a,b);
    f.dichotomie(a,b);
    f.lim(0);
    f.df(3);
    return(0);
}
