#include "InterfaceSerial.h"

// Baseado em http://playground.arduino.cc/Interfacing/CPPWindows

// Parametros da placa
#define BAUD_RATE CBR_9600
#define BYTE_SIZE 8
#define STOP_BITS ONESTOPBIT
#define PARITY NOPARITY

#define WAIT_TIME 500

#include "InterfaceSerial.h"
#include <iostream>
void InterfaceSerial::inicializar() {
 this->nomes[0] = "T1";
 this->nomes[1] = "T2";
}
double InterfaceSerial::getValor(string canal) {
 int valoresT1[] = {10, 20, 30, 40};
 int valoresT2[] = {10, 15, 20, 25};
 if (canal == "T1") return valoresT1[numeroDeChamadas];
 return valoresT2[numeroDeChamadas];
}
bool InterfaceSerial::atualizar() {
 numeroDeChamadas++;
 return true;
}
string* InterfaceSerial::getNomeDosCanais() {
 return nomes;
}
int InterfaceSerial::getQuantidadeDeCanais() {
 return 2;
}

InterfaceSerial::InterfaceSerial(string canal){
}
