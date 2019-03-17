#ifndef PERSISTENCIADESERIE_H
#define PERSISTENCIADESERIE_H
#include "Serie.h"
#include "SerieNormal.h"
#include "SerieTemporal.h"
#include "Ponto.h"
#include "ErroDeArquivo.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;


class PersistenciaDeSerie
{
    public:
        PersistenciaDeSerie(string arquivo);
        virtual ~PersistenciaDeSerie();
        Serie* obter(string nome);
        vector<string>* getNomes();
        void inserir(string nome, Serie *s);

    protected:
        vector<Serie*> *seriesLidas;
        string arquivo;

    private:
};

#endif // PERSISTENCIADESERIE_H
