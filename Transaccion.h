#pragma once 
#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Transaccion
{
    public:
        string rutOrigen;
        string rutFinal;
        int monto;
        string ubicacion;
        string fecha;
        string hora;
        int id;
        string sospechosa;
        Transaccion(int, string, string, int, string, string, string);
        ~Transaccion();
        Transaccion* subirTransacciones(string);
        void actualizarDatosTransacciones(string);
        void setSospechosa(string);
        int getMonto();
        string getFecha();
        string datosTransaccion();
};

