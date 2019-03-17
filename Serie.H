#ifndef SERIE_H
#define SERIE_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include "Ponto.h"

using namespace std;

class Serie {
public:
    Serie(string nome, string nomeDoCanalX, string nomeDoCanalY);
    virtual ~Serie() = 0;

    virtual string getNome();

    virtual string getNomeDoCanalX();

    virtual string getNomeDoCanalY();

    virtual int getQuantidade();

    virtual bool estaVazia();

    virtual vector<Ponto*>* getPontos();

    virtual Ponto* getLimiteSuperior();

    virtual Ponto* getLimiteInferior();

    virtual Ponto* getPosicao(int posicao);

    virtual void imprimir();

protected:
    string nome; //armazena o nome da serie
    string nomeDoCanalX;
    string nomeDoCanalY;
    vector<Ponto*>* pontos;

};

#endif // SERIE_H
