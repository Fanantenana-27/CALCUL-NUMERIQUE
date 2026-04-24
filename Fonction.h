#include <string>

class Fonction
{
    private:
        std::string fonction ;
    public:
        Fonction(/* args */);
        void setFonction(std::string chaine);
        float f(float x);
        float lim(float a);
        float df(float x);
        float dichotomie(float a , float b);
        float newton(float a , float b);
        ~Fonction();
};
