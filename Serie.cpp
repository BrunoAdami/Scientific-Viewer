#include "Serie.h"

Serie::Serie(string nome, string nomeDoCanalX, string nomeDoCanalY): nome(nome), nomeDoCanalX(nomeDoCanalX), nomeDoCanalY(nomeDoCanalY) {
   pontos = new vector<Ponto*> ();
}

Serie::~Serie() {
    delete pontos;
}

string Serie::getNome(){
    return nome;
}

string Serie::getNomeDoCanalX(){
    return nomeDoCanalX;
}

string Serie::getNomeDoCanalY(){
    return nomeDoCanalY;
}

int Serie::getQuantidade(){
    return pontos->size();
}

bool Serie::estaVazia(){
    if (pontos->empty())
        return true;
    return false;
}

vector<Ponto*>* Serie::getPontos(){
    return pontos;
}

Ponto* Serie::getLimiteSuperior(){
    if (pontos->empty())
         throw new runtime_error("Serie vazia!");//runtime_error de serie vazia
    double maiorX = pontos->at (0)->getX(), maiorY = pontos->at (0)->getY();
    for(int i = 1; i < pontos->size(); i++){ //obtem os maiores valores para X e Y disponiveis na serie
        if (maiorX < pontos->at(i)->getX())
            maiorX = pontos->at(i)->getX();
        if(maiorY < pontos->at(i)->getY())
            maiorY = pontos->at(i)->getY();
    }
    Ponto *p = new Ponto(maiorX, maiorY); //cria um ponto para guardar o limite superior
    return p;
}

Ponto* Serie::getLimiteInferior(){
    if (pontos->empty())
        throw new runtime_error("Serie vazia!");//runtime_error de serie vazia
    double menorX = pontos->at (0)->getX(), menorY = pontos->at (0)->getY();
    for(int i = 1; i < pontos->size(); i++){ //obtem os menores valores para X e Y disponiveis na serie
        if (menorX > pontos->at(i)->getX())
            menorX = pontos->at(i)->getX();
        if (menorY > pontos->at(i)->getY())
            menorY = pontos->at(i)->getY();
    }
    Ponto *p = new Ponto(menorX, menorY); //cria um ponto para guardar o limite inferior
    return p;
}

Ponto* Serie::getPosicao(int posicao) {
    if (posicao >= pontos->size() || posicao < 0)
        throw new out_of_range("Posicao invalida!"); //posicao invalida
    return pontos->at(posicao);
}

void Serie::imprimir(){
    cout << "Serie " << nome << endl;
    for(int i = 0; i < pontos->size(); i++)
    cout << "(" << pontos->at(i)->getX() << ", " << pontos->at(i)->getY() << ")" << endl;
}
