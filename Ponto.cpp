#include "Ponto.h"

Ponto::Ponto(double x, double y): x(x), y(y) {

}

Ponto::~Ponto(){

}

double Ponto::getX(){
    return this->x;
}

double Ponto::getY(){
    return this->y;
}

void Ponto::imprimir(){
    cout << "(" << this->x << ", " << this->y << ")" << endl;
}

bool Ponto::eIgual(Ponto* outro){
    if ((-(1e-5) < (this->x - outro->x) && (this->x - outro->x) < (1e-5)) && (-(1e-5) < this->y - outro->y && this->y - outro->y < (1e-5))) //verifica se o modulo da diferença dos valores de x e dos valores de y dos pontos é menor que epslon
        return true;
    return false;
}

