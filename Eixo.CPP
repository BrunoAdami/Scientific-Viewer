#include "Eixo.h"
#include <stdexcept>

Eixo::Eixo(string titulo, double minimo, double maximo, bool orientacaoHorizontal) {
    if(minimo >= maximo)
        throw new runtime_error ("O minimo eh maior ou igual ao maximo!");
    else{
        this->minimo = minimo;
        this->maximo = maximo;
        this->titulo = titulo;
        this->orientacaoHorizontal = orientacaoHorizontal;
    }
}

Eixo::~Eixo(){
    //dtor
}

string Eixo::getTitulo(){
    return titulo;
}

double Eixo::getMinimo(){
    return minimo;
}

double Eixo::getMaximo(){
    return maximo;
}

bool Eixo::temOrientacaoHorizontal(){
    return orientacaoHorizontal;
}
