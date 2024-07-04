#include <iostream>
#include <queue>
#include <vector>
#include "Cliente.h"
#include "Nodo.h"

using namespace std;

Cliente::Cliente(string rut) {this -> rut = rut;}

Cliente::~Cliente(){}

void Cliente::cargarClientes(queue<Cliente*>& clientes, Nodo* raiz)
{
    if(raiz == nullptr)
    {
        return;
    }
    
    cargarClientes(clientes, raiz->izquierda);
    if(buscarRut(clientes, raiz->datos->rutOrigen))
    {
        Cliente* nuevoCliente = new Cliente(raiz->datos->rutOrigen);
        clientes.push(nuevoCliente);
    }
    if(buscarRut(clientes, raiz->datos->rutFinal))
    {
        Cliente* nuevoCliente = new Cliente(raiz->datos->rutFinal);
        clientes.push(nuevoCliente);
    }

    cargarClientes(clientes, raiz->derecha);
}
bool Cliente::buscarRut(queue<Cliente*> clientes, string rut)
{
    if(clientes.empty())
    {
        return true;
    }

    queue<Cliente*>aux = clientes;
    
    while(!aux.empty())
    {
        string rutCliente = aux.front()->rut;
        if(rutCliente == rut)
        {
            return false;
        }
        aux.pop();
    }
    return true;
}