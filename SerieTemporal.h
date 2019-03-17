#ifndef SERIETEMPORAL_H
#define SERIETEMPORAL_H

#include <iostream>
#include "Serie.h"
#include "Ponto.h"
#include <stdexcept>

using namespace std;

class SerieTemporal: public Serie{
    public:
        SerieTemporal(string nome, string nomeDoCanalY);
        virtual ~SerieTemporal();
        virtual void adicionar(double valor);
    protected:
        string nome;
        string nomeDoCanalY;
    private:
        int tempo = 0; //VARIAVEL SERA USADA PARA CONTAGEM DO TEMPO
};

#endif // SERIETEMPORAL_H
