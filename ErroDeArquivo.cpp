#include "ErroDeArquivo.h"

ErroDeArquivo::ErroDeArquivo(string mensagem) : logic_error(mensagem) {
    //ctor
}

ErroDeArquivo::~ErroDeArquivo() {
    //dtor
}
