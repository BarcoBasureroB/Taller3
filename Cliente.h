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

        Cliente(string,vector<Transaccion*>&);
        ~Cliente();
};