#ifndef GRAFICO_H
#define GRAFICO_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include "Ponto.h"
#include "Serie.h"
#include "SerieTemporal.h"
#include "Tela.h"
#include "Eixo.h"
#include "EixoDinamico.h"
#include "InterfaceSerial.h"

using namespace std;

class Grafico
{
    public:
        Grafico(Eixo* x, Eixo* y, vector<Serie*>* series);
        virtual ~Grafico();
        Eixo* getEixoX();
        Eixo* getEixoY();
        vector<Serie*>* getSeries();
        void desenhar();
    protected:
    private:
        Eixo* x;
        Eixo* y;
        vector<Serie*>* series;
};

#endif // GRAFICO_H
