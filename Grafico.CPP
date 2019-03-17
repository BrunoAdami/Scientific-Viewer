#include "Grafico.h"

Grafico::Grafico(Eixo* x, Eixo* y, vector<Serie*>* series) {
    if(y->temOrientacaoHorizontal())
        throw new logic_error ("Os eixos nao tem a orientacao esperada! Y");
    if(!x->temOrientacaoHorizontal())
            throw new logic_error ("Eixo X");
    else if(series == NULL)
        throw new logic_error ("O vector series eh nulo!");
    else {
        this->x = x;
        this->y = y;
        this->series = series;
        }
}

Grafico::~Grafico(){
    delete x;
    delete y;
    delete series;
}

Eixo* Grafico::getEixoX(){
    return x;
}

Eixo* Grafico::getEixoY(){
    return y;
}

vector<Serie*>* Grafico::getSeries(){
    return series;
}

void Grafico::desenhar(){
   Tela *t = new Tela;
   t->setEixoX(x->getTitulo(), x->getMinimo(), x->getMaximo());
   t->setEixoY(y->getTitulo(), y->getMinimo(), y->getMaximo());
   for(int i = 0; i < series->size(); i++){ //plota os pontos do vector de series
        for(int j = 0; j < series->at(i)->getPontos()->size(); j++){
            t->plotar(series->at(i)->getNome(), series->at(i)->getPontos()->at(j)->getX(),
                      series->at(i)->getPontos()->at(j)->getY());
        }
   }
   t->mostrar();
   delete t;

}
