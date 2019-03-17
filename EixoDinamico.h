#ifndef EIXODINAMICO_H
#define EIXODINAMICO_H

#include <iostream>
#include <list>
#include "Tela.h"
#include "SerieTemporal.h"
#include "Serie.h"
#include "Ponto.h"
#include "InterfaceSerial.h"
#include "Grafico.h"
#include "Eixo.h"
#include <stdexcept>

using namespace std;

class EixoDinamico : public Eixo
{
    public:
        EixoDinamico(string titulo, double minimoPadrao, double maximoPadrao, list<Serie*>* series, bool orientacaoHorizontal);
        virtual ~EixoDinamico();
    protected:
    private:
        double minimoPadrao, maximoPadrao;
        Serie* base;
        bool orientacaoHorizontal;
        list<Serie*>* series;
};

#endif // EIXODINAMICO_H
