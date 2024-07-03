#include <iostream>
#include <queue>
#include <vector>
#include "Transaccion.h"
#include "Cliente.h"

using namespace std;

Transaccion* busquedaRec(Transaccion* &raiz, int datoABuscar)
{
    if(!raiz)
    {
        return nullptr;
    }

    if(raiz->id == datoABuscar)
    {
        return raiz;
    }

    if(raiz->id > datoABuscar)
    {
        return busquedaRec(raiz->hijoIzq,datoABuscar);
    }
    return busquedaRec(raiz->hijoDer,datoABuscar);
}

void inOrdenRecursivo(Transaccion* &raiz)
{
    if(raiz == nullptr){
        return;
    }
    
    inOrdenRecursivo(raiz->hijoIzq);
    cout<<raiz->id<<"";
    inOrdenRecursivo(raiz->hijoDer);
}

int crearIDRandom(Transaccion* &raiz)
{   
    bool existe = false;
    int id;
    do
    {
        //proceso de crear número random

        Transaccion* encontrado = busquedaRec(raiz, id);
        if(encontrado != nullptr)
        {
            existe = true;
        }
        
    }while(existe != false);

    return id;
}

bool datoExiste(string rutSelect, vector<Cliente*> &clientes)
{
    for(int i = 0; i < clientes.size(); i++)
    {
        if(clientes[i]->rut == rutSelect)
        {
            return true;
        }
    }
    return false;
}

bool idExiste(int id, vector<Transaccion*> listaSus)
{
    for(int i = 0; i < listaSus.size(); i++)
    {
        if(listaSus[i]->id == id)
        {
            return true;
        }
    }
    return false;
}

void transaccionesSospechosas(vector<Cliente*> &clientes)
{
    string rutSelect;

    do{

        cout<<"RUT de los clientes: "<<endl;

        for(int i = 0; i < clientes.size(); i++)
        {
            cout<<clientes[i]->rut<<endl;
        }
        cout<<"Ingrese RUT a revisar: "<<endl;
        cin>>rutSelect;
        if(!datoExiste(rutSelect, clientes))
        {
            cout<<"RUT no encontrado. Ingrese un RUT en el sistema."<<endl;
        }
    }while(!datoExiste(rutSelect, clientes));

    Cliente* clientAux;

    for(int i = 0; i < clientes.size(); i++)
    {
        if(clientes[i]->rut == rutSelect)
        {
            clientAux = clientes[i];
        }
    }

    int idAux;
    vector<Transaccion*> listaSus = clientAux->listaSospechosa;

    if(listaSus.size() != 0)
    {
        do
        {
            cout<<"IDs de Transferencias sospechosas: "<<endl;
            for(int i = 0; i < listaSus.size(); i++)
            {
                cout<<listaSus[i]->id<<" | Fecha: "<<listaSus[i]->fecha<<"| Hora: "<<listaSus[i]->hora<<endl;
            }

            cout<<"Ingrese ID de Transacción a revisar: "<<endl;
            cin>>idAux;

            if(!idExiste(idAux, listaSus))
            {
                cout<<"ID no encontrado. Ingrese un ID en el sistema. "<<endl;
            }

        }while(!idExiste(idAux, listaSus));

        for(int i = 0; i < listaSus.size(); i++)
        {
            if(idAux == listaSus[i]->id)
            {
                cout<<"Rut de Origen: "<<listaSus[i]->rutOrigen<<endl;
                cout<<"Rut de Destino: "<<listaSus[i]->rutFinal<<endl;
                cout<<"Monto Transferido: "<<listaSus[i]->monto<<endl;
                cout<<"Ubicación de Origen de transferencia: "<<listaSus[i]->ubicacion<<endl;
                cout<<"Fecha de transferencia: "<<listaSus[i]->fecha<<endl;
                cout<<"Hora de transferencia: "<<listaSus[i]->hora<<endl;
            }
        }
    }
    else
    {
        cout<<"No existe actividad sospechosa en este RUT."<<endl;
    }
}

void crearTransaccion(Transaccion* &raiz)
{
    int id = crearIDRandom(raiz);
    string rutOrigen, rutDestino, ubicacion;
    int monto, fecha, hora;
    cout<<"Ingrese los siguientes datos: "<<endl;
    cout<<"RUT de origen: "<<endl;
    cin>>rutOrigen;

    cout<<"RUT de destino: "<<endl;
    cin>>rutDestino;

    cout<<"Monto recibido (Ej: 100000):"<<endl;
    cin>>monto;

    cout<<"Ubicación de Transferencia: "<<endl;
    cin>>ubicacion;

    cout<<"Fecha de Transacción: "<<endl;
    cin>>fecha;

    cout<<"Hora de Transacción (Ej:): "<<endl;
    cin>>hora;
}

void revisarTransacciones(Transaccion* &raiz)
{
    int opcion;

    do{
        cout<<"IDs en el sistema:"<<endl;
        inOrdenRecursivo(raiz);

        int IDBuscar;
        cout<<"Ingresa el ID de Transacción:"<<endl;
        cin>>IDBuscar;

        Transaccion* encontrada = busquedaRec(raiz, IDBuscar);

        if(encontrada != nullptr)
        {
            cout<<"Datos de Transacción:"<<endl;
            cout<<"ID: "<<encontrada->id<<endl;
            cout<<"RUT de origen: "<<encontrada->rutOrigen<<endl;
            cout<<"RUT de destino: "<<encontrada->rutFinal<<endl;
            cout<<"Monto recibido: "<<encontrada->monto<<endl;
            cout<<"Ubicación de Transferencia: "<<encontrada->ubicacion<<endl;
            cout<<"Fecha de Transacción: "<<encontrada->fecha<<endl;
            cout<<"Hora de Transacción: "<<encontrada->hora<<endl;
        
        }
        else
        {
            cout<<"El Id ingresado no es correcto."<<endl;
        }
        
        do
        {
            cout<<"¿Desea finalizar la revisión de Tranferencias?( 1)Si  2)No ): "<<endl;
            cin>>opcion;
            switch(opcion)
            {
                case 1:
                    cout<<"Volviendo al Menú..."<<endl;
                    break;
                case 2:
                    cout<<" "<<endl;
                    break;
                default:
                    cout << "Opción no válida. Por favor, ingrese una opción válida.\n";
        
            }
        }while(opcion != 1 && opcion != 2);

    }while(opcion != 1);
}

int menu(Transaccion* &raiz, vector<Cliente*> &clientes)
{
    int opcion;

    do {
        cout << "\n|--- Menú ---|\n";
        cout << "1. Ingresar transacción al sistema.\n";
        cout << "2. Registro de Transacciones.\n";
        cout << "3. Transacciones Sospechosas.\n";
        cout << "4. Salir\n";
        cout << "Ingrese una opción(Ejemplo: 1): ";
        cin >> opcion;
        cout<<endl;
        switch(opcion) {
            case 1:
                crearTransaccion(raiz);
                break;
            case 2:
                revisarTransacciones(raiz);
                break;
            case 3:
                transaccionesSospechosas(clientes);
                break;
            case 4:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción no válida. Por favor, ingrese una opción válida.\n";
        }
    } while(opcion != 4);
}

int main()
{
    
}
