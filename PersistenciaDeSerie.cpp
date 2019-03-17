#include "PersistenciaDeSerie.h"

PersistenciaDeSerie::PersistenciaDeSerie(string arquivo) { //ctor
    this->arquivo = arquivo;
    string nomeDaSerie;
    int numeroDePontos;
    int tipoDaSerie;
    string nomeDoCanalY, nomeDoCanalX;
    double coordenadaX, coordenadaY;
    this->seriesLidas = new vector<Serie*>;

    int numeroDeSeries = 0;

    ifstream input;
    input.open(arquivo);
    if(input.good()) input >> nomeDaSerie;

    if (!input.eof()){

        while (input.good()){//verifica se nao ocorreu eofbit (fim de arquivo) e se o arquivo existe (nao ocorreu failbit)

            if (!input && !input.eof())//verifica a atribuicao (!input = erro na atribuicao ou end of file)
                throw new ErroDeArquivo("Nome da Primeira Serie invalido.");
            if (!input.good() && !input.eof()) throw new ErroDeArquivo("Arquivo com apenas uma linha."); //fim de arquivo

            input >> tipoDaSerie;
            if (!input)//verifica a atribuicao (!input = erro na atribuicao ou end of file)
                throw new ErroDeArquivo("Tipo de serie nao suportado.");
            if (!input.good()) throw new ErroDeArquivo("Arquivo fora do formato esperado."); //fim de arquivo

            if (tipoDaSerie == 0){
                input >> numeroDePontos;
                if (!input || numeroDePontos < 0) throw new ErroDeArquivo("Numero de pontos nao suportado.");
                if (!input.good()) throw new ErroDeArquivo("Arquivo fora do formato esperado."); //fim de arquivo

                input >> nomeDoCanalY;
                if (!input) throw new ErroDeArquivo("Nome do Canal Y nao suportado.");
                if (!input.good() && numeroDePontos > 0) throw new ErroDeArquivo("Arquivo fora do formato esperado."); //fim de arquivo, mas se o numero de pontos for 0 ele pode acabar agora.

                seriesLidas->push_back(new SerieTemporal(nomeDaSerie, nomeDoCanalY));


                for (int i = 0; i < numeroDePontos; i++){//percorre as coordenadas dos pontos mais o nome do canal y
                    if (input.eof()) throw new ErroDeArquivo("Arquivo fora do formato esperado (pontos faltando).");//arquivo acaba antes do numero de coordenadas esperado
                    input >> coordenadaY;
                    if (!input && input.good()) throw new ErroDeArquivo("Coordenada y nao suportada.");
                    dynamic_cast <SerieTemporal*>(seriesLidas->at(numeroDeSeries))->adicionar(coordenadaY);
                }
                numeroDeSeries++;
            }
            else if (tipoDaSerie == 1){
                input >> numeroDePontos;
                if (!input || numeroDePontos < 0) throw new ErroDeArquivo("Numero de pontos nao suportado.");
                if (!input.good()) throw new ErroDeArquivo("Arquivo fora do formato esperado."); //fim de arquivo

                input >> nomeDoCanalX;
                if (!input) throw new ErroDeArquivo("Nome do Canal X nao suportado.");
                if (!input.good() && numeroDePontos > 0) throw new ErroDeArquivo("Arquivo fora do formato esperado."); //fim de arquivo, mas se o numero de pontos for 0 ele pode acabar agora.

                input >> nomeDoCanalY;
                if (!input) throw new ErroDeArquivo("Nome do Canal Y nao suportado.");
                if (!input.good() && numeroDePontos > 0) throw new ErroDeArquivo("Arquivo fora do formato esperado."); //fim de arquivo, mas se o numero de pontos for 0 ele pode acabar agora.

                seriesLidas->push_back(new SerieNormal(nomeDaSerie, nomeDoCanalX, nomeDoCanalY));


                for (int i = 0; i < numeroDePontos; i++){//percorre as coordenadas dos pontos
                    if (!input.good()) throw new ErroDeArquivo("Arquivo fora do formato esperado (coordenadas faltando).");//arquivo acaba antes do numero de coordenadas esperado
                    input >> coordenadaX;
                    if (!input && input.good()) throw new ErroDeArquivo("Coordenada x nao suportada.");

                    if (!input.good()) throw new ErroDeArquivo("Arquivo fora do formato esperado (coordenadas faltando).");//arquivo acaba antes do numero de coordenadas esperado
                    input >> coordenadaY;
                    if (!input && input.good()) throw new ErroDeArquivo("Coordenada y nao suportada.");

                    dynamic_cast <SerieNormal*>(seriesLidas->at (numeroDeSeries))->adicionar(coordenadaX, coordenadaY);
                }
                numeroDeSeries++;
            }
            else throw new ErroDeArquivo("Tipo de Serie nao suportado.");
        }

    }
    else if(input.fail())
            throw new ErroDeArquivo("Fora do formato");
}


PersistenciaDeSerie::~PersistenciaDeSerie() {
    delete seriesLidas;
}

Serie* PersistenciaDeSerie::obter(string nome) {
    for(int i = 0; i < seriesLidas->size(); i++) { //looping para retornar a serie com o nome dado
        if (seriesLidas->at (i)->getNome() == nome) return seriesLidas->at (i);
    }
    return NULL;
}

vector<string>* PersistenciaDeSerie::getNomes() {
    vector<string> *nomes = new vector<string>; //armazena os nomes das series presentes no arquivo
    for (int i = 0; i < seriesLidas->size(); i++){
        nomes->push_back (seriesLidas->at(i)->getNome());
    }
    return nomes;

}

void PersistenciaDeSerie::inserir(string nome, Serie* s) {
    for(int i = 0; i < seriesLidas->size(); i++){
        if (seriesLidas->at (i)->getNome() == nome) throw new ErroDeArquivo("Ja existe uma serie com esse nome.");
    }

    ofstream output;
    output.open(this->arquivo, ios_base::app);
    if (output.fail()) //erro de leitura, nao eh possivel escrever no arquivo
        throw new ErroDeArquivo("Nao eh possivel escrever no arquivo.");


    output << nome << endl;

    if (SerieTemporal *sT = dynamic_cast<SerieTemporal*>(s)){ //casting verifica se eh serie temporal
        output << "0" << endl;
        output << s->getQuantidade() << endl;
        output << s->getNomeDoCanalY() << endl;

        vector<Ponto*> *pontos = s->getPontos();
        for(int j = 0; j < s->getQuantidade(); j++) //looping para adicionar os valores de Y
            output << pontos->at(j)->getY() << endl;

    }
    else if (SerieNormal *sN = dynamic_cast<SerieNormal*>(s)){ //casting verifica se eh serie normal
         output << "1" << endl;
         output << s->getQuantidade() << endl;
         output << s->getNomeDoCanalX() << endl;
         output << s->getNomeDoCanalY() << endl;

         vector<Ponto*> *pontos = s->getPontos();
         for(int j = 0; j < s->getQuantidade(); j++){ //looping para adicionar os valores dos pontos da serie
            output<< pontos->at (j)->getX() << endl;
            output<< pontos->at (j)->getY() << endl;
         }
    }

    seriesLidas->push_back(s);
}
