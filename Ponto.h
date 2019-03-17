#include <iostream>
#ifndef PONTO_H
#define PONTO_H

using namespace std;

class Ponto {
public:
  Ponto(double x, double y);

  virtual ~Ponto();

  double getX();

  double getY();

  void imprimir();

  bool eIgual(Ponto* outro);

protected:
    double x, y;


};

#endif
