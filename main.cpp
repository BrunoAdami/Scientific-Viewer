#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <stdexcept>
#include <stdlib.h>

#include "Eixo.h"
#include "EixoDinamico.h"
#include "EixoEstatico.h"
#include "ErroDeArquivo.h"
#include "Grafico.h"
#include "InterfaceSerial.h"
#include "PersistenciaDeSerie.h"
#include "Ponto.h"
#include "Serie.h"
#include "SerieTemporal.h"
#include "Tela.h"



#define COMM "\\\\.\\COM3"

using namespace std;

int main(){
    Grafico *g1;
    Eixo *eixoX, *eixoY; //eixos utilizados no grafico
    list<Serie*>* seriesList = new list<Serie*>; //lista de series usada para passar para o eixo dinamico
    vector<Serie*>* series = new vector<Serie*>; //vector de series usado para armazenar as series carregadas e criadas e plota-las no grafico
    string arquivo, //salva o nome do arquivo de persistencia
    nomeDaSerie, //nome da serie criada pelo usuario (passada pela interface serial)
    nomeDaSerieParaSalvar;

    int quantidade, canalX, canalY, serieCarregada, serieParaSalvar;

    string tipoEixoX, tipoEixoY, nomeEixoX, nomeEixoY;
    double minimoEixoX, maximoEixoX, minimoEixoY, maximoEixoY;
    string novaSerie = "s"; //condicao para criar nova serie
    string carregarArquivo = "s"; //condicao para carregar arquivo
    string salvarSerie; //condicao para salvar serie
    string *nomesDosCanais;
    string testeVazio; //utilizado para verificar se o arquivo esta vazio

    InterfaceSerial* is = new InterfaceSerial(COMM);

    PersistenciaDeSerie *pS;

    try{
        is->inicializar();
    }catch(runtime_error *r){
        cout << r->what() << endl;
        exit(1);
    }


    cout << "Informe o nome do arquivo de dados: ";
    cin >> arquivo;
    nomesDosCanais = is->getNomeDosCanais();

    while (novaSerie == "s") {
        cout << "Informe o nome da serie: ";
        cin >> nomeDaSerie;

        cout << "Escolha o canal X: " << endl;
        for (int i = -1; i < is->getQuantidadeDeCanais(); i++){//imprime os canais disponíveis para X
            if (i >= 0)
                cout << i+1 << ")" << nomesDosCanais[i] << endl;
            else
                cout << i+1 << ")" << "Tempo" << endl;
        }

        cin >> canalX;


        cout << "Escolha o canal Y:" << endl;

        for (int i = 0; i < is->getQuantidadeDeCanais(); i++){ //imprime os canais disponiveis para Y
            cout << i+1 << ")" << nomesDosCanais[i] << endl;
        }

        cin >> canalY;




        cout << "Adicionar uma outra serie (s/n): ";
        cin >> novaSerie;


        if(canalX == 0) series->push_back(new SerieTemporal(nomeDaSerie, nomesDosCanais[canalY - 1])); //armazena series no vector
        else if(canalY <= is->getQuantidadeDeCanais() && canalY > 0 &&
                canalX <= is->getQuantidadeDeCanais() && canalX > 0 )
            series->push_back(new SerieNormal(nomeDaSerie, nomesDosCanais[canalX - 1], nomesDosCanais[canalY - 1]));

    }

    if(novaSerie == "n"){
        cout << "Obter quantos pontos? ";
        cin >> quantidade;
        cout << "Obtendo os pontos" << endl;
        cout << "Deseja carregar alguma serie (s/n): ";
        cin >> carregarArquivo;
    }

    for(int i = 0; i < series->size(); i++){
        if(series->at(i)->getNomeDoCanalX() == "Tempo"){

            for(int j = 0; j < quantidade; j++){ //adiciona os pontos a serie temporal criada
                try{
                    is->atualizar();
                    dynamic_cast <SerieTemporal*>(series->at(i))->adicionar(is->getValor(series->at(i)->getNomeDoCanalY()));
                }catch(runtime_error *r2){
                    cout << r2->what() << endl;
                    exit(1); //termina o programa apos jogar a excecao
                }catch(logic_error *l2){
                    cout << l2->what() << endl;
                    exit(1);
                }

            }
        }
        else {

            for(int j = 0; j < quantidade; j++){ //adiciona os pontos a serie normal criada
                try{is->atualizar();
                dynamic_cast<SerieNormal*>(series->at(i))->adicionar(is->getValor(series->at(i)->getNomeDoCanalX()),
                 is->getValor(series->at(i)->getNomeDoCanalY()));
                }catch(runtime_error *r3){
                    cout << r3->what() << endl;
                    exit(1);
                }catch(logic_error *l3){
                    cout << l3->what() << endl;
                    exit(1);
                }
            }
        }
    }

    if(carregarArquivo == "s"){
        ifstream ler;
        ler.open(arquivo);
        ler >> testeVazio;
        if (ler.eof()){ //testa se o arquivo esta vazio
            carregarArquivo = "n";
            cout << "Sem series salvas" << endl;
        }

    }

    while(carregarArquivo == "s"){
        try {
            ifstream input;
            input.open(arquivo);
            if(input.good()){
                pS = new PersistenciaDeSerie(arquivo);
                for(int i = 0; i < pS->getNomes()->size() && carregarArquivo == "s"; i++){ //imprime as series do arquivo
                    cout << i+1 << ") " << pS->getNomes()->at(i) << endl;

                }
                cout << "Escolha a serie para carregar: ";
                cin >> serieCarregada;
                cout << "Deseja carregar outra serie? (s/n): ";
                cin >> carregarArquivo;
                series->push_back(pS->obter(pS->getNomes()->at(serieCarregada - 1)));
                input.close();
            }

        } catch (ErroDeArquivo *e) {
            cout << e->what() << endl;
            exit(1);
        }

    }

    for (int k = 0; k < series->size(); k++)
            seriesList->push_back(series->at(k)); //

    if (carregarArquivo == "n") {

        cout << "O eixo X e' estatico ou dinamico (e/d): ";
        cin >> tipoEixoX;



        if (tipoEixoX == "e"){
            cout << "Informe o titulo: ";
            cin >> nomeEixoX;

            cout << "Valor minimo: ";
            cin >> minimoEixoX;

            cout << "Valor maximo: ";
            cin >> maximoEixoX;
            try{
                eixoX = new EixoEstatico(nomeEixoX, minimoEixoX, maximoEixoX, true);
            }catch(runtime_error *r){
                cout << r->what() << endl;
                exit(1);
            }
        }

        else if (tipoEixoX == "d"){
            cout << "Informe o titulo: ";
            cin >> nomeEixoX;

            cout << "Valor minimo padrao: ";
            cin >> minimoEixoX;

            cout << "Valor maximo padrao: ";
            cin >> maximoEixoX;

            try{
                eixoX = new EixoDinamico(nomeEixoX, minimoEixoX, maximoEixoX, seriesList, true);
            }catch( runtime_error *e){
                cout << e->what() << endl;
                exit(1);
            }catch (logic_error *l){
                cout << l->what() << endl;
                exit(1);
            }
        }

        cout << "O eixo Y e' estatico ou dinamico (e/d): ";
        cin >> tipoEixoY;



        if (tipoEixoY == "e") {
            cout << "Informe o titulo: ";
            cin >> nomeEixoY;

            cout << "Valor minimo: ";
            cin >> minimoEixoY;

            cout << "Valor maximo: ";
            cin >> maximoEixoY;

            try{
                eixoY = new EixoEstatico(nomeEixoY, minimoEixoY, maximoEixoY, false);
            }
            catch (runtime_error *r){
                cout << r->what() << endl;
                exit(1);
            }
        }

        else if(tipoEixoY == "d") {
            cout << "Informe o titulo: ";
            cin >> nomeEixoY;

            cout << "Valor minimo padrao: ";  /// quando os eixos sao dinamicos esta dando erro
            cin >> minimoEixoY;

            cout << "Valor maximo padrao: ";
            cin >> maximoEixoY;

            try{
                eixoY = new EixoDinamico(nomeEixoY, minimoEixoY, maximoEixoY, seriesList, false);
            }catch(runtime_error *e){
                cout << e->what() << endl;
                exit(1);
            }catch(logic_error *l){
                cout << l->what() << endl;
                exit(1);
            }
        }




        try{
            g1 = new Grafico(eixoX, eixoY, series);
        }catch (logic_error *l){
            cout << l->what() << endl;
            exit(1);
        }

        g1->desenhar();

        cout << "Deseja salvar alguma serie? (s/n) ";
        cin >> salvarSerie;

        if (salvarSerie == "s"){
            try{
                pS = new PersistenciaDeSerie(arquivo);
            }catch(ErroDeArquivo *e3){
                cout << e3->what() << endl;
                exit(1);
            }
        }

        while (salvarSerie == "s"){
            for (int w = 0; w < series->size(); w++){
                cout << w + 1 << ") " << series->at(w)->getNome() << endl;
            }

            cout << "Escolha a serie para salvar: ";
            cin >> serieParaSalvar;
            cout << "Salvar a serie com qual nome: ";
            cin >> nomeDaSerieParaSalvar;

            try{
                pS->inserir(nomeDaSerieParaSalvar, series->at(serieParaSalvar - 1)); //salva a serie no arquivo
            }catch(ErroDeArquivo *e){
                cout << e->what() << endl;
                exit(1);
            }

            cout << "Deseja salvar outra serie (s/n) ";
            cin >> salvarSerie;

        }
    }
    return 0;
}
