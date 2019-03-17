#include "Serie.h"
#ifndef SERIENORMAL_H
#define SERIENORMAL_H
#include <stdexcept>

class SerieNormal:public Serie {
public:
    SerieNormal(string nome, string nomeDoCanalX, string nomeDoCanalY);
    virtual ~SerieNormal();
    virtual void adicionar(double x, double y);
private:
    string nome;
    string nomeDoCanalX;
    string nomeDoCanalY;
};

#endif // SERIENORMAL_H
