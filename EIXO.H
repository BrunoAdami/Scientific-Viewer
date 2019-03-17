#ifndef EIXO_H
#define EIXO_H
#include "Serie.H"
#include <list>
#include<stdexcept>


#include <iostream>

using namespace std;


class Eixo
{
    public:
        Eixo(string titulo, double minimo, double maximo, bool orientacaoHorizontal);
        virtual ~Eixo();
        virtual string getTitulo();
        virtual double getMinimo();
        virtual double getMaximo();
        virtual bool temOrientacaoHorizontal();
    protected:
        string titulo;
        double minimo, maximo;
        bool orientacaoHorizontal;
    private:
};

#endif // EIXO_H
