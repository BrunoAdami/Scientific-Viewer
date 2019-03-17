#include "EixoDinamico.h"
#include <stdexcept>
#include "Eixo.h"

EixoDinamico::EixoDinamico(string titulo, double minimoPadrao, double maximoPadrao,
                            list<Serie*>* series, bool orientacaoHorizontal):Eixo(titulo, minimoPadrao, maximoPadrao, orientacaoHorizontal){
    if (minimoPadrao >= maximoPadrao)
        throw new runtime_error("Minimo padrao maior ou igual ao maximo padrao!");
    else if (series == NULL)
        throw new logic_error("Series nulas!");

    double maximo, minimo;
    list <Serie*>::iterator iter;  //iterator utilizado para percorrer a lista
    iter = series->begin(); //iterator no inicio da lista
    if (orientacaoHorizontal) {
        while ((*iter)->getPontos()->empty() && iter != series->end()) {
            iter++;
        }
        if (iter != series->end()) { //verifica se a lista nao acabou
            maximo = (*iter)->getPontos()->at(0)->getX(); //passa o primeiro valor para maximo
            minimo = (*iter)->getPontos()->at(0)->getX();

            while (iter != series->end()) {
                if (!(*iter)->getPontos()->empty()) {
                    for (int i = 1; i < (*iter)->getPontos()->size(); i++) { //compara todos os valores de x para os pontos pertencentes as series
                        if (maximo < (*iter)->getPontos()->at(i)->getX())
                            maximo = (*iter)->getPontos()->at(i)->getX();
                        if (minimo > (*iter)->getPontos()->at(i)->getX())
                            minimo = (*iter)->getPontos()->at(i)->getX();
                    }
                }
                iter++;
            }
            if (minimo - maximo < 1e-5 && minimo - maximo > -1e-5){
                this->minimo = minimoPadrao;
                this->maximo = maximoPadrao;
            }
        }
        else { //todas as series sao vazias
            this->minimo = minimoPadrao;
            this->maximo = maximoPadrao;
        }
    }
    else if (!orientacaoHorizontal) {
       while((*iter)->getPontos()->empty() && iter != series->end()) {
            iter++;
        }
        if (iter != series->end()) {
        maximo = (*iter)->getPontos()->at(0)->getY();
        minimo = (*iter)->getPontos()->at(0)->getY();

            while (iter != series->end()) {
                if (!(*iter)->getPontos()->empty()) {
                    for(int i = 1; i < (*iter)->getPontos()->size(); i++){
                        if(maximo < (*iter)->getPontos()->at(i)->getY())
                            maximo = (*iter)->getPontos()->at(i)->getY();
                        if(minimo > (*iter)->getPontos()->at(i)->getY())
                            minimo = (*iter)->getPontos()->at(i)->getY();
                    }
                }
                iter++;
            }
        }
         if (minimo - maximo < 1e-5 && minimo - maximo > -1e-5){
                this->minimo = minimoPadrao;
                this->maximo = maximoPadrao;
            }
        else { //todas as series sao vazias
            this->minimo = minimoPadrao;
            this->maximo = maximoPadrao;
        }
    }
}

EixoDinamico::~EixoDinamico() {
    delete base;
}
