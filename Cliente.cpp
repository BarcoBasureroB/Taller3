#include <iostream>
#include <queue>
#include <vector>
#include "Cliente.h"
#include "Transaccion.h"

using namespace std;

Cliente::Cliente(string Rut, vector<Transaccion*> &listaSospechosa)
{
    this -> rut = rut;
    this -> listaSospechosa = listaSospechosa;
}

Cliente::~Cliente(){}