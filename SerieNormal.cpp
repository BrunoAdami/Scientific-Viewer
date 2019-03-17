#include "SerieNormal.h"

SerieNormal::SerieNormal(string nome, string nomeDoCanalX, string nomeDoCanalY): Serie(nome, nomeDoCanalX, nomeDoCanalY) {
    //ctor
}

SerieNormal::~SerieNormal() {
    //dtor
}

void SerieNormal::adicionar(double x, double y){
    Ponto *ponto = new Ponto(x, y);
    Serie::pontos->push_back(ponto);
}
