#pragma once 
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Transaccion
{
     private:
        string id;
        string rutOrigen;
        string rutFinal;
        int monto;
        string ubicacion;
        string fechaYHora;


    public:
        Transaccion(string, string, string, int, string, string);
        ~Transaccion();

};

