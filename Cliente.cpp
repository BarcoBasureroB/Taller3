#include <iostream>
#include <queue>
#include <vector>
#include "Cliente.h"
#include "Transaccion.h"

using namespace std;

Cliente::Cliente(string Rut, vector<Transaccion*> &listaTransac, queue<Transaccion*> &listaSospechosa)
{
    this -> rut = rut;
    this -> listaTransac = listaTransac;
    this -> listaSospechosa = listaSospechosa;
}

Cliente::~Cliente(){}