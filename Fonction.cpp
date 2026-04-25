#include "Fonction.h"
#include <cmath>
#include <iostream>
#include <string>
#include <unistd.h>
#include "autre_fonction.h"

Fonction::Fonction(){}

void Fonction::setFonction(std::string chaine)
{
    fonction=chaine;
}

float Fonction::f(float x)
{
    float resultat ;
    resultat=_fonction(fonction,x);
    return(resultat);
}

float Fonction::lim(float a)
{
    float l;
    l=_limite(fonction,a);
    return(l);
}

float Fonction::df(float x)
{
    float resultat ;
    std::string fonc;
    fonc= "(" + fonction + "-" + std::to_string(f(x)) + ")/(x-" + std::to_string(x) + ")" ;
    std::cout << fonc << std::endl; 
    resultat=_limite(fonc,x);
    return(resultat);
}



float Fonction::dichotomie(float a , float b)
{
    int compteur;
    float epsilon,milieu;
    epsilon=0.001;
    compteur=0;
    do 
    {
        milieu=(a+b)/2;
        if((f(a) * f(milieu)) <= 0 )
        {
            b=milieu;
        }
        else 
        {
            a=milieu;
        }
        compteur++;
    }
    while (fabs(b-a)>epsilon);
    std::cout << "Solution : " << milieu  <<"\nNombre d'itteration : " << compteur << std::endl;
    return(milieu);
} 

float Fonction::newton(float a , float b)
{
    int compteur;
    float xn1,xn,e;
    compteur=0;
    xn=a;
    e=0.001;
    do 
    {
        xn1=xn-(f(xn)/df(xn));
        if(fabs(xn1-xn)<e)
        {
            break;
        }
        xn=xn1;
        compteur++;
    }
    while(1);
    std::cout << "Solution : " << xn <<"\nNombre d'itteration : " << compteur << std::endl;
    return(xn);
}



Fonction::~Fonction(){}
