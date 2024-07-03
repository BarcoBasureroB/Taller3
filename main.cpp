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

void transaccionesSospechosas(vector<Cliente*> &clientes)
{


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
