#pragma once 
#include <iostream>
#include <queue>
#include <vector>
#include "Nodo.h"
#include "Transaccion.h"

using namespace std;

class Cliente
{
    public:
        string rut;
        queue<Transaccion*> listaSospechosa;

        Cliente(string);
        ~Cliente();
        void cargarClientes(queue<Cliente*>&, Nodo*);
        bool buscarRut(queue<Cliente*>, string);
        bool confirmarTransferenciaSospechosa(Cliente*&, Transaccion*);
        void agregarSospecha(Transaccion*);
        queue<Transaccion*> getListaSospechosa();
};