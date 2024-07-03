#include <iostream>
#include <queue>
#include <vector>
#include "Transaccion.h"

using namespace std;

Transaccion::Transaccion(int id, string rutOrigen, string rutFinal, int monto, string ubicacion, int fecha, int hora)
{

    this ->id = id;
    this ->rutOrigen = rutOrigen;
    this ->rutFinal = rutFinal;
    this ->monto = monto;
    this ->ubicacion = ubicacion;
    this ->fecha = fecha;
    this ->hora = hora;
    this->hijoIzq = nullptr;
    this->hijoDer = nullptr;

}

//Destructor de la clase Transaccion
Transaccion::~Transaccion(){}