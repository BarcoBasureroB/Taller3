#include <iostream>
#include <queue>
#include <vector>
#include "Transaccion.h"


Transaccion::Transaccion(string id, string rutOrigen, string rutFinal, int monto, string ubicacion, string fechaYHora)
{

    this ->id = id;
    this ->rutOrigen = rutOrigen;
    this ->rutFinal = rutFinal;
    this ->monto = monto;
    this ->ubicacion = ubicacion;
    this ->fechaYHora = fechaYHora;

}

//Destructor de la clase Transaccion
Transaccion::~Transaccion(){}