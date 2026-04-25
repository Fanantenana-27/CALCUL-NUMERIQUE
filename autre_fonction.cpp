#include <cmath>
#include <iostream>
#include <string>
#include <unistd.h>
#include "autre_fonction.h"

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
                reste=fonction.substr(i+3,fonction.size()-(i+3));
                resultat=valeur * resultat;
            }
            else
            {
                reste=fonction.substr(i+1,fonction.size()-(i+1));
                resultat=valeur * x;
            }
            sprintf(chaine,"%f%s",resultat,reste.c_str());
            fonction=chaine;
            i=0;
        }
    }
    resultat=std::stof(fonction);
    return(resultat);
}

float calcul_fonction(std::string fonction,float x)
{
    int i,j,ver;
    float resultat,a,b;
    char new_fonction[255];
    std::string reste,avant,apres;
    resultat=0;
    ver=0;
    for(i=0;i<fonction.size();i++)
    {
        if(fonction[i]=='*' || fonction[i]=='/' || fonction[i]=='+' || fonction[i]=='-')
        {
            avant=fonction.substr(0,i);
            for(j=i+1;j<fonction.size();j++)
            {
                if(fonction[j]=='*' || fonction[j]=='/' || fonction[j]=='+' || fonction[j]=='-')
                {
                    break;
                }
            }
            apres=fonction.substr(i+1,j-(i+1));
            reste=fonction.substr(j,fonction.size()-j);
            a=calcul(avant,x);
            b=calcul(apres,x);
            switch (fonction[i])
            {
                case '*':
                    resultat=a*b;
                    break;
                case '/':
                    resultat=a/b;
                    break;
                case '+':
                    resultat=a+b;
                    break;
                case '-':

                    resultat=a-b;
                    break;
                default:
                    break;
            }
            fonction=std::to_string(resultat)+ reste;
        }
    }
    resultat=calcul(fonction,x);
    return(resultat);
}

float calcul_entre_parenthese(std::string fonction,double x)
{
    int i,j,indice,compter_paranthese_ouvert;
    float resultat,fois;
    std::string entre_parenthese,avant_parenthese,apres_paranthese,tmp,chaine;
    for(i=0;i<fonction.size();i++)
    {
        if(fonction[i]=='(')
        {
            indice=0;
            compter_paranthese_ouvert=1;
            for(j=i+1;j<fonction.size();j++)
            {
                if(fonction[j]=='('){ compter_paranthese_ouvert++; }
                else if(fonction[j]==')') { compter_paranthese_ouvert--; }
                if(compter_paranthese_ouvert==0)
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
        }
    }
    resultat=calcul_fonction(fonction,x);
    return(resultat);
}

float _fonction(std::string fonction ,float x)
{
    float resultat;
    resultat=calcul_entre_parenthese(fonction,x);
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
