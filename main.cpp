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
    cout<<raiz->id<<endl;
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

bool datoExiste(string rutSelect, queue<Cliente*> clientes)
{
    for(int i = 0; i < clientes.size(); i++)
    {
        if(clientes.front()->rut == rutSelect)
        {
            return true;
        }
        clientes.pop();
    }
    return false;
}

bool idExiste(int id, queue<Transaccion*> listaSus)
{
    for(int i = 0; i < listaSus.size(); i++)
    {
        if(listaSus.front()->id == id)
        {
            return true;
        }
        listaSus.pop();
    }
    return false;
}

void transaccionesSospechosas(queue<Cliente*> &clientes)
{
    string rutSelect;


    do{
        queue<Cliente*> aux = clientes;
        
        cout<<"RUT de los clientes: "<<endl;

        for(int i = 0; i < aux.size(); i++)
        {
            cout<<aux.front()->rut<<endl;
            aux.pop();
        }
        cout<<"Ingrese RUT a revisar: "<<endl;
        cin>>rutSelect;
        if(!datoExiste(rutSelect, clientes))
        {
            cout<<"RUT no encontrado. Ingrese un RUT en el sistema."<<endl;
        }
    }while(!datoExiste(rutSelect, clientes));

    Cliente* clientAux;

    queue<Cliente*> aux1 = clientes;

    for(int i = 0; i < clientes.size(); i++)
    {
        if(aux1.front()->rut == rutSelect)
        {
            clientAux = aux1.front();
            break;
        }
        aux1.pop();
    }

    int idAux;

    queue<Transaccion*> listaSus; 

    if(clientAux->listaSospechosa.size() != 0)
    {
        do
        {
            listaSus = clientAux->listaSospechosa;
            cout<<"IDs de Transferencias sospechosas: "<<endl;
            for(int i = 0; i < listaSus.size(); i++)
            {
                cout<<listaSus.front()->id<<" | Fecha: "<<listaSus.front()->fecha<<"| Hora: "<<listaSus.front()->hora<<endl;
                listaSus.pop();
            }

            cout<<"Ingrese ID de Transacción a revisar: "<<endl;
            cin>>idAux;

            if(!idExiste(idAux, listaSus))
            {
                cout<<"ID no encontrado. Ingrese un ID en el sistema. "<<endl;
            }

        }while(!idExiste(idAux, listaSus));

        listaSus = clientAux->listaSospechosa;
        
        for(int i = 0; i < listaSus.size(); i++)
        {
            if(idAux == listaSus.front()->id)
            {
                cout<<"Rut de Origen: "<<listaSus.front()->rutOrigen<<endl;
                cout<<"Rut de Destino: "<<listaSus.front()->rutFinal<<endl;
                cout<<"Monto Transferido: "<<listaSus.front()->monto<<endl;
                cout<<"Ubicación de Origen de transferencia: "<<listaSus.front()->ubicacion<<endl;
                cout<<"Fecha de transferencia: "<<listaSus.front()->fecha<<endl;
                cout<<"Hora de transferencia: "<<listaSus.front()->hora<<endl;
                cout<<"Motivo de sospecha: "<<listaSus.front()->sospechosa<<endl;
            }
            listaSus.pop();
        }
    }
    else
    {
        cout<<"No existe actividad sospechosa en este RUT."<<endl;
    }
}

void arbolDeDecision(queue<Cliente*> &clientes, Transaccion* &raiz)
{
    
    if(raiz == nullptr){
        return;
    }

    arbolDeDecision(clientes, raiz->hijoIzq);
    
    queue<Cliente*> aux;
    
    if(raiz->monto >= 1000000)
    {
        raiz->sospechosa = "Cantidad de Monto demasiado alta.";
        for(int i = 0; i < clientes.size() ;i++)
        {
            if(clientes.front()->rut == raiz->rutOrigen || clientes.front()->rut == raiz->rutFinal)
            {
                clientes.front()->listaSospechosa.push(raiz);
            }
            aux.push(clientes.front());
            clientes.pop();
        }
    }

    arbolDeDecision(clientes, raiz->hijoDer);
    
    clientes = aux;
}

void crearTransaccion(Transaccion* &raiz, queue<Cliente*> &clientes)
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

    //Se inserta Nodo al arbol

    arbolDeDecision(clientes, raiz);
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

int menu(Transaccion* &raiz, queue<Cliente*> &clientes)
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
                crearTransaccion(raiz, clientes);
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
    return 0;
}

int main()
{
    
}