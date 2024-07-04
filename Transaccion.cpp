#include <iostream>
#include <queue>
#include <vector>
#include "Transaccion.h"

using namespace std;

Transaccion::Transaccion(int id, string rutOrigen, string rutFinal, int monto, string ubicacion, string fecha, string hora)
{
    this -> id = id;
    this -> rutOrigen = rutOrigen;
    this -> rutFinal = rutFinal;
    this -> monto = monto;
    this -> ubicacion = ubicacion;
    this -> fecha = fecha;
    this -> hora = hora;
    this -> sospechosa = "";
}

//Destructor de la clase Transaccion
Transaccion::~Transaccion(){}

Transaccion* Transaccion::subirTransacciones(string datosTransaccion)
{
    string id, cuentaOrigen, cuentaDestino, monto, ubicacion, fecha, hora;
    stringstream datosSeparar(datosTransaccion);

    getline(datosSeparar, id, ',');
    getline(datosSeparar, cuentaOrigen, ',');
    getline(datosSeparar, cuentaDestino, ',');
    getline(datosSeparar, monto, ',');
    getline(datosSeparar, ubicacion, ',');
    getline(datosSeparar, fecha, ',');
    getline(datosSeparar, hora, ',');

    Transaccion* nuevaTransaccion = new Transaccion(stoi(id), cuentaOrigen, cuentaDestino, stoi(monto), ubicacion, fecha, hora);
    return nuevaTransaccion;
}

void Transaccion::setSospechosa(string sospechosa)
{
    this->sospechosa = sospechosa;
}
