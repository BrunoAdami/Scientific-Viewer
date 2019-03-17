#ifndef INTERFACESERIAL_H
#define INTERFACESERIAL_H
#include <string>
using namespace std;
class InterfaceSerial {
public:
 void inicializar();
 InterfaceSerial(string canal);
 double getValor (string canal);
 bool atualizar();
 string* getNomeDosCanais();
 int getQuantidadeDeCanais();
private:
 int numeroDeChamadas = -1;
 string nomes[2];
};
#endif

