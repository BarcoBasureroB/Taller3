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
        void setListaTransac(Transaccion*);
        void agregarTransacciones(queue<Cliente*>& clientes, Nodo* raiz);
        void buscarTransacciones(Cliente* & cliente, Nodo* raiz);
        void agregarTransaccionClienteExistente(queue<Cliente*>&, Transaccion*, string);
        void ordenarQueue(queue<Transaccion*>&);
        void explorarOrdenar(queue<Cliente*>&);
        void vaciarCola(queue<Cliente*>&);
};