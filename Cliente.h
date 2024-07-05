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
        queue<Transaccion*> listaTransac;

        Cliente(string);
        ~Cliente();
        void cargarClientes(queue<Cliente*>&, Nodo*);
        bool buscarRut(queue<Cliente*>, string);
        bool confirmarTransferenciaSospechosa(Cliente*&, Transaccion*);
        void agregarSospecha(Transaccion*);
        void agregarTransaccion(queue<Cliente*>& , Transaccion* , string);
        queue<Transaccion*> getListaSospechosa();
        queue<Transaccion*> getListaTransac();
        
        void agregarTransacciones(queue<Cliente*>& clientes, Nodo* raiz);
};