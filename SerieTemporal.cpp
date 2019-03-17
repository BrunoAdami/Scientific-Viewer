#include "SerieTemporal.h"

SerieTemporal::SerieTemporal(string nome, string nomeDoCanalY): Serie(nome, "Tempo", nomeDoCanalY)
{
    //ctor
}

SerieTemporal::~SerieTemporal()
{
    //dtor
}

void SerieTemporal::adicionar(double valor){ //POLIMORFISMO 1
    tempo++;
    Ponto *p = new Ponto(tempo, valor);
    Serie::pontos->push_back(p);
}
