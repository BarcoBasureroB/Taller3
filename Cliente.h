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
        queue<Transaccion*> listaSospechosa;
        vector<Transaccion*> listaTransac;

        Cliente(string,vector<Transaccion*>&,queue<Transaccion*>&);
        ~Cliente();
};