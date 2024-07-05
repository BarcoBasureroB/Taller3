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
    this->listaTransac.push(nullptr);
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

void Cliente::setListaTransac(Transaccion* datos)
{
    if(this->listaTransac.front() == nullptr)
    {
        this->listaTransac.pop();
        this->listaTransac.push(datos);
    }
    else
    {
        this->listaTransac.push(datos);
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
    cliente->setListaTransac(datos);
    // if(cliente->getListaTransac().size() > 1)
    // {
    //     queue<Transaccion*> aux;

    //     Transaccion* ultima = cliente->getListaTransac().front();
    //     cliente->getListaTransac().pop();
    //     Transaccion* penultima = cliente->getListaTransac().front();
    //     cliente->getListaTransac().pop();

    //     if(datos->ubicacion != ultima->ubicacion)
    //     {

    //     }
    //     else
    //     {

    //     } 
    // }

    return false;
}

void Cliente::buscarTransacciones(Cliente*& cliente, Nodo* raiz)
{
    if(raiz == nullptr)
    {
        return;
    }

    buscarTransacciones(cliente, raiz->izquierda);
    if(cliente->rut == raiz->datos->rutFinal || cliente->rut == raiz->datos->rutOrigen)
    {
        confirmarTransferenciaSospechosa(cliente, raiz->datos);
    }
    buscarTransacciones(cliente, raiz->derecha);
}

void Cliente::agregarTransacciones(queue<Cliente*>& clientes, Nodo* raiz)
{
    queue<Cliente*> aux;
    while(!clientes.empty())
    {
        buscarTransacciones(clientes.front(), raiz);
        aux.push(clientes.front());
        clientes.pop();
    }
    while(!aux.empty())
    {
        clientes.push(aux.front());
        aux.pop();
    }
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
        else 
        {
            actual = pila.top();

            if(buscarRut(clientes, actual->datos->rutOrigen))
            {
                Cliente* nuevoCliente = new Cliente(actual->datos->rutOrigen);
                clientes.push(nuevoCliente);
            }
            
            if(buscarRut(clientes, actual->datos->rutFinal))
            {
                Cliente* nuevoCliente = new Cliente(actual->datos->rutFinal);
                clientes.push(nuevoCliente);
            }

            pila.pop();

 
            actual = actual->derecha;
        }
    }
}

void Cliente::agregarTransaccion(queue<Cliente*>& clientes, Transaccion* datos, string rut)
{
    queue<Cliente*> aux;

    while(!clientes.empty())
    {
        if(clientes.front()->rut == rut)
        {
            if(clientes.front()->getListaTransac().front() == nullptr)
            {
                clientes.front()->getListaTransac().pop();
                clientes.front()->getListaTransac().push(datos);
            }
            else
            {
                clientes.front()->getListaTransac().push(datos);
            }
        }
        aux.push(clientes.front());
        clientes.pop();

    }

    while(!aux.empty())
    {
        clientes.push(aux.front());
        aux.pop();
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
queue<Transaccion*> Cliente::getListaTransac()
{
    return this->listaTransac;
}


