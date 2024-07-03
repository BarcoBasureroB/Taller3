#pragma once 
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Transaccion
{
    public:
        string rutOrigen;
        string rutFinal;
        int monto;
        string ubicacion;
        string fecha;
        int hora;
        int id;
        Transaccion* hijoIzq;
        Transaccion* hijoDer;
        Transaccion(int, string, string, int, string, string, int);
        ~Transaccion();
};

