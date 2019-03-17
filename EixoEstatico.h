#ifndef EIXOESTATICO_H
#define EIXOESTATICO_H
#include "Eixo.h"
#include <stdexcept>
class EixoEstatico:public Eixo {
    public:
        EixoEstatico(string titulo, double minimo, double maximo, bool orientacaoHorizontal);
        virtual ~EixoEstatico();

    protected:

    private:
};

#endif // EIXOESTATICO_H
