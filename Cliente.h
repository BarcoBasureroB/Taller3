#pragma once 
#include <iostream>
#include <queue>
#include <vector>
#include "Transaccion.h"

using namespace std;

class Cliente
{
    public:
        string rut;
        vector<Transaccion*> listaSospechosa;
        vector<Transaccion*> listaTransac;

        Cliente(string,vector<Transaccion*>&,vector<Transaccion*>&);
        ~Cliente();
};