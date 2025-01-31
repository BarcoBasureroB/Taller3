#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <climits>
#include "Cliente.h"
#include "Nodo.h"

using namespace std;

Cliente::Cliente(string rut) 
{
    this -> rut = rut;
    this->listaSospechosa.push(nullptr);
    this->listaTransac.push(nullptr);
}

// Destructor de la clase Cliente.
Cliente::~Cliente(){}

// Método para agregar una transacción sospechosa a la lista de sospechas del cliente.
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

// Método para agregar una transacción a la lista de transacciones del cliente.
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

// Función que evalúa si una transacción es sospechosa en función del tiempo y la ubicación. (Si es mayor a $1000000 es sospechosa, si ocurre un el mismo lugar y suma más de $1000000 en menos de una hora es sospechosa, y si suma más de $1000000 en 2 horas y ocurre en lugares distintos, también es sospechosa).
Transaccion* sospechaTiempo(queue<Transaccion*>& transacciones, Transaccion*& datos, int hora, int minutos)
{
    Transaccion* sus = nullptr;
    queue<Transaccion*> aux;
    while(!transacciones.empty())
    { 
        if(transacciones.front()->fecha == datos->fecha)
        {
            string horaAux, minutosAux;
            stringstream datosSeparar(transacciones.front()->hora);
            getline(datosSeparar, horaAux, ':');
            getline(datosSeparar, minutosAux, ':');
            if(transacciones.front()->ubicacion == datos->ubicacion)
            {
                if((transacciones.front()->monto + datos->monto) >= 1000000)
                {
                    if(stoi(horaAux) == hora && minutos > stoi(minutosAux))
                    {
                        datos->setSospechosa("Transacciones en corto periodo de tiempo");
                        sus = datos;
                    }
                    else if(stoi(horaAux) == hora && minutos < stoi(minutosAux))
                    {
                        transacciones.front()->setSospechosa("Transacciones en corto periodo de tiempo");
                        sus = transacciones.front();
                    }
                    else if(stoi(horaAux) == hora-1 && stoi(minutosAux) > minutos)
                    {
                        datos->setSospechosa("Transacciones en corto periodo de tiempo");
                        sus = datos;
                    }
                    else if(hora == stoi(horaAux)-1 && minutos > stoi(minutosAux))
                    {
                        transacciones.front()->setSospechosa("Transacciones en corto periodo de tiempo");
                        sus = transacciones.front();
                    }
                    
                }
            }
            else
            {
                if((transacciones.front()->monto + datos->monto) >= 1000000)
                {
                    if(stoi(horaAux) == hora && minutos > stoi(minutosAux))
                    {
                        datos->setSospechosa("Transacciones en corto periodo de tiempo");
                        sus = datos;
                    }
                    else if(stoi(horaAux) == hora && minutos < stoi(minutosAux))
                    {
                        transacciones.front()->setSospechosa("Transacciones en corto periodo de tiempo");
                        sus = transacciones.front();
                    }
                    else if(stoi(horaAux) == hora-2 && stoi(minutosAux) > minutos)
                    {
                        datos->setSospechosa("Transacciones en corto periodo de tiempo");
                        sus = datos;
                    }
                    else if(hora == stoi(horaAux)-2 && minutos > stoi(minutosAux))
                    {
                        transacciones.front()->setSospechosa("Transacciones en corto periodo de tiempo");
                        sus = transacciones.front();
                    }
                    
                }
            }
        }
        aux.push(transacciones.front());
        transacciones.pop();
    }
    while(!aux.empty())
    {
        transacciones.push(aux.front());
        aux.pop();
    }
    return sus;
}

// Método para confirmar si una transacción es sospechosa basándose en varios criterios.
bool Cliente::confirmarTransferenciaSospechosa(Cliente* &cliente,Transaccion* datos)
{
    string hora, minutos;
    stringstream datosSeparar(datos->hora);
    getline(datosSeparar, hora, ':');
    getline(datosSeparar, minutos, ':');

    if(datos->monto >= 1000000)
    {
        datos->setSospechosa("Cantidad de Monto demasiado alta");
        cliente->agregarSospecha(datos);
    }
    else if(stoi(hora) < 2)
    {
        datos->setSospechosa("Hora de transacción poco habitual");
        cliente->agregarSospecha(datos);
    }
    else if(cliente->listaTransac.size() > 0 && cliente->listaTransac.front() != nullptr)
    {
        Transaccion* opcion = sospechaTiempo(cliente->listaTransac, datos, stoi(hora), stoi(minutos));
        if(opcion != nullptr)
        {
            cliente->agregarSospecha(opcion);
        }
    }
    cliente->setListaTransac(datos);
    return false;
}

// Función para comparar dos fechas.
// Devuelve verdadero si la primera fecha es menor o igual que la segunda.
bool compareDates(const string& date1, const string& date2) 
{
    return date1 <= date2;
}

// Método para ordenar una cola de transacciones en orden cronológico.
void Cliente::ordenarQueue(queue<Transaccion*>& transacciones) 
{
    int n = transacciones.size();
    for (int i = 0; i < n; ++i) 
    {
        int min_index = -1;
        Transaccion* min_value = new Transaccion(0,"","",0,"","9999-12-31","");
        int current_size = transacciones.size();

        for (int j = 0; j < current_size; ++j) 
        {
            Transaccion* curr = transacciones.front();
            transacciones.pop();
            if (compareDates(curr->fecha, min_value->fecha) && j <= (n - i - 1)) 
            {
                min_value = curr;
                min_index = j;
            }

            transacciones.push(curr);
        }

        for (int j = 0; j < current_size; ++j) 
        {
            Transaccion* curr = transacciones.front();
            transacciones.pop();

            if (!(curr->fecha == min_value->fecha && j == min_index)) 
            {
                transacciones.push(curr);
            }
        }

        transacciones.push(min_value);
    }
}

// Método para ordenar las colas de transacciones y sospechas de cada cliente.
void Cliente::explorarOrdenar(queue<Cliente*>& clientes)
{
    queue<Cliente*> aux;
    while(!clientes.empty())
    {
        ordenarQueue(clientes.front()->listaTransac);
        if(clientes.front()->listaSospechosa.front() != nullptr)
        {
            ordenarQueue(clientes.front()->listaSospechosa);
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

// Método para buscar transacciones de un cliente en un árbol y verificar si son sospechosas.
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

// Método para agregar una transacción a un cliente existente.
void Cliente::agregarTransaccionClienteExistente(queue<Cliente*>& clientes, Transaccion* transaccion, string rut)
{
    queue<Cliente*> aux;
    while(!clientes.empty())
    {
        if(clientes.front()->rut == rut)
        {
            confirmarTransferenciaSospechosa(clientes.front(),transaccion);
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

// Método para agregar transacciones de un árbol a todos los clientes en una cola.
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

// Método para cargar clientes desde un árbol a una pila.
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

// Método para agregar una transacción a un cliente específico en una cola de clientes.
void Cliente::agregarTransaccion(queue<Cliente*>& clientes, Transaccion* datos, string rut)
{
    queue<Cliente*> aux;

    while(!clientes.empty())
    {
        if(clientes.front()->rut == rut)
        {
            if(clientes.front()->listaTransac.front() == nullptr)
            {
                clientes.front()->listaTransac.pop();
                clientes.front()->listaTransac.push(datos);
            }
            else
            {
                clientes.front()->listaTransac.push(datos);
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

// Método para buscar si un RUT ya está presente en una cola de clientes.
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

// Método para obtener la lista de transacciones sospechosas del cliente.
queue<Transaccion*> Cliente::getListaSospechosa()
{
    return this->listaSospechosa;
}

// Función para vaciar una cola.
void Cliente::vaciarCola(queue<Cliente*>& clientes)
{
    while(!clientes.empty())
    {
        clientes.pop();
    }
}
