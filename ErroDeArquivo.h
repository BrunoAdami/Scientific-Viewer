#include <iostream>
#include <stdexcept>
#ifndef ERRODEARQUIVO_H
#define ERRODEARQUIVO_H

using namespace std;

class ErroDeArquivo:public logic_error {
    public:
        ErroDeArquivo(string mensagem);
        virtual ~ErroDeArquivo();

    protected:

    private:
};

#endif // ERRODEARQUIVO_H
