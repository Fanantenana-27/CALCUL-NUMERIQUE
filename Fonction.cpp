#include "Fonction.h"
#include <cmath>
#include <iostream>
#include <string>
#include <unistd.h>

Fonction::Fonction(){}

void Fonction::setFonction(std::string chaine)
{
    fonction=chaine;
}

float calcul(std::string fonction,float x)
{
    std::cout << "Fonction _ calcul : " << fonction << std::endl; 
    int i;
    double puissance;
    float resultat,valeur;
    char chaine[255];
    std::string avant,reste;
    resultat=1;
    puissance=1;
    for (i=0;i<fonction.size();i++)
    {
        if(fonction[i]=='x')
        {
            
            avant=fonction.substr(0,i);
            valeur=std::stof(avant);
            if(valeur==0)
            {
                valeur=1;
            }
            if(i+1 < fonction.size() && fonction[i+1]=='^')
            {
                resultat=(float)pow(x,fonction[i+2]-'0');
                std::cout << x <<"^" << fonction[(i+2)]<<"= "<<resultat<< std::endl;
                reste=fonction.substr(i+3,fonction.size()-(i+3));
                resultat=valeur * resultat;
            }
            else
            {
                reste=fonction.substr(i+1,fonction.size()-(i+1));
                resultat=valeur * x;
                std::cout << "Avant : " << avant << "valeur : " << valeur << " x : " << x << " REsultata : "<< resultat<< std::endl;
            }
            //std::cout << "Fonction (calcul) --> reste : " << reste<< std::endl;
            sprintf(chaine,"%f%s",resultat,reste.c_str());
            fonction=chaine;
            i=0;
        }
       // std::cout << "Fonction (calcul) : " << fonction << " --> Resultat : " << resultat << std::endl;
    }
    resultat=std::stof(fonction);
    std::cout << "Resultat (calcul) : " << fonction << "==> Resultat final : " << resultat << std::endl;
    return(resultat);
}

float calcul_fonction(std::string fonction,float x)
{
    std::cout << "Fonction _ calcul_fonction : " << fonction << std::endl; 
    int i,j,ver;
    float resultat,a,b;
    char new_fonction[255];
    std::string reste,avant,apres;
    resultat=0;
    ver=0;
    for(i=0;i<fonction.size();i++)
    {
        avant=fonction.substr(0,i);
        for(j=i+1;j<fonction.size();j++)
        {
            if(fonction[j]=='+' || fonction[j]=='-')
            {
                break;
            }
        }
        apres=fonction.substr(i+1,j-i+1);
        reste=fonction.substr(j,fonction.size()-j);
        a=calcul(avant,x);
        b=calcul(apres,x);
        switch (fonction[i])
        {
            case '*':
                resultat=a+b;
                break;
            case '/':
                resultat=a+b;
                break;
            case '+':
                resultat=a+b;
                break;
            case '-':
                resultat=a+b;
                break;
            default:
                break;
        }
        fonction=std::to_string(resultat)+ reste;
        //std::cout << "Fonction (calcul_fonction) : " << fonction << " --> Resultat : " << resultat << std::endl;
    }
    resultat=calcul(fonction,x);
    std::cout << "Fonction (calcul_fonction) : " << fonction << " ==> Resultat finale : " << resultat << std::endl;
    return(resultat);
}

float calcul_entre_parenthese(std::string fonction,double x)
{
    std::cout << "Fonction _ entre_parenthese : " << fonction << std::endl; 
    int i,j,indice;
    float resultat,fois;
    std::string entre_parenthese,avant_parenthese,apres_paranthese,tmp,chaine;
    for(i=0;i<fonction.size();i++)
    {
        if(fonction[i]=='(')
        {
            indice=0;
            for (j=fonction.size();j>i;j--)
            {
                if(fonction[j]==')')
                {
                    indice=j;
                    break;
                }
            }
            avant_parenthese=fonction.substr(0,i);
            entre_parenthese = fonction.substr(i+1,indice-1-i);
            apres_paranthese=fonction.substr(indice+1,fonction.size()-indice+1);
            resultat=calcul_entre_parenthese(entre_parenthese,x);
            chaine=std::to_string(resultat);
            if(avant_parenthese.size()>0)
            {
                tmp=avant_parenthese.substr(0,avant_parenthese.size()-1);
                switch (avant_parenthese[avant_parenthese.size()-1])
                {
                    case '+':
                        chaine = tmp + '+' + std::to_string(resultat);
                        break;
                    case '-' :
                        chaine = tmp + '-' + std::to_string(resultat);
                        break;
                    case '/' :
                        chaine = tmp + '/' + std::to_string(resultat);
                        break;
                    case '*' :
                        chaine = tmp + '*' + std::to_string(resultat);
                        break;
                    default:
                        chaine = avant_parenthese + '*' + std::to_string(resultat);
                        break;
                }
            }
            if(apres_paranthese.size()>0)
            {
                tmp=apres_paranthese.substr(1,apres_paranthese.size()-1);
                switch (apres_paranthese[0])
                {
                case '+':
                    fonction= chaine + '+' + tmp;
                    break;
                case '-' :
                    fonction= chaine + '-' + tmp;              
                    break;
                case '/' :
                    fonction= chaine + '/' + tmp;               
                    break;
                case '*' :
                    fonction= chaine + '*' + tmp;                
                    break;
                default:
                    fonction= chaine + '*' + apres_paranthese;
                    break;
                }
            }
            fonction=chaine;
           // std::cout << "new fonction () : " << fonction << std::endl;
        }
        //std::cout << "Fonction (calcul_calcul_entre_parenthese) : " << fonction << " --> Resultat : " << resultat << std::endl;
    }
    resultat=calcul_fonction(fonction,x);
    //std::cout << fonction << "  :  " << resultat << std::endl; 
    std::cout << "Fonction calcul_entre_parenthese) : " << fonction << " ==> Resultat finale : " << resultat << std::endl;
    return(resultat);
}

float _fonction(std::string fonction ,float x)
{
    float resultat;
    resultat=calcul_entre_parenthese(fonction,x);
    std::cout << "RESULTAT : " << resultat << std::endl;
    return(resultat);
}

float _limite(std::string fonction ,float a)
{
    int i;
    float x,fx,milieu,epsilon,delta,l;
    delta=0.00001;
    epsilon=0.0001;
    x=0;
    while (fabs(x-a)>delta)
    {
        milieu=(x+a)/2;
        x=milieu;
    }
    fx=_fonction(fonction,milieu);
    if(fabs(x-a)<delta)
    {
        x=0;
        do
        {
            milieu=(x+a)/2;
            x=milieu;
            l=_fonction(fonction,x);
        }
        while (fabs(fx-l)>delta);
    }
    std::cout << "LIM(f(x)," << a << ")=" << l << std::endl;
    return(l);
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