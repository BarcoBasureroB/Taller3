#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include "Cliente.h"
#include "Nodo.h"

using namespace std;

Cliente::Cliente(string rut) 
{
    this -> rut = rut;
    this->listaSospechosa.push(nullptr);
}

Cliente::~Cliente(){}

void Cliente::agregarSospecha(Transaccion* datos)
{
    if(listaSospechosa.front() == nullptr)
    {
        this->listaSospechosa.pop();
        this->listaSospechosa.push(datos);
    }
    else
    {
        this->listaSospechosa.push(datos);
    }
}

bool Cliente::confirmarTransferenciaSospechosa(Cliente* &cliente,Transaccion* datos)
{
    if(datos->monto >= 1000000)
    {
        datos->setSospechosa("Cantidad de Monto demasiado alta");
        cliente->agregarSospecha(datos);
        return true;
    }
    return false;
}

void Cliente::cargarClientes(queue<Cliente*>& clientes, Nodo* raiz)
{
    stack<Nodo*> pila;
    
    Nodo* actual = raiz;
 
   
    while (!pila.empty() || actual != nullptr)
    {
        
        if (actual != nullptr)
        {
            pila.push(actual);
            actual = actual->izquierda;
        }
        else {
            
            actual = pila.top();

            if(buscarRut(clientes, actual->datos->rutOrigen))
            {
                Cliente* nuevoCliente = new Cliente(actual->datos->rutOrigen);
                confirmarTransferenciaSospechosa(nuevoCliente, actual->datos);
                clientes.push(nuevoCliente);
            }
            if(buscarRut(clientes, actual->datos->rutFinal))
            {
                Cliente* nuevoCliente = new Cliente(actual->datos->rutFinal);
                confirmarTransferenciaSospechosa(nuevoCliente, actual->datos);                                                                        
                clientes.push(nuevoCliente);
            }

            pila.pop();

 
            actual = actual->derecha;
        }
    }
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

queue<Transaccion*> Cliente::getListaSospechosa()
{
    return this->listaSospechosa;
}