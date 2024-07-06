#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include "Nodo.h"
#include "Transaccion.h"
#include "Cliente.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Realiza una búsqueda recursiva en el árbol binario.
Nodo* busquedaRec(Nodo* &raiz, int datoABuscar)
{
    if(!raiz) {return nullptr;}
    
    if(raiz->datos->id == datoABuscar) {return raiz;}

    if(raiz->datos->id > datoABuscar){return busquedaRec(raiz->izquierda,datoABuscar);}

    return busquedaRec(raiz->derecha,datoABuscar);
}

// Recorre el árbol binario en orden (in-order) de forma recursiva.
void inOrdenRecursivo(Nodo* &raiz)
{
    if(raiz == nullptr){
        return;
    }
    
    inOrdenRecursivo(raiz->izquierda);
    cout<<raiz->datos->id<<endl;
    inOrdenRecursivo(raiz->derecha);
}

// Genera un ID aleatorio único para una transacción.
int crearIDRandom(Nodo* &raiz)
{   
    bool existe = false;
    int idRandom = 0;
    do
    {
        srand(time(0));

        int minId = 10000;
        int maxId = 99999;

        idRandom = minId + rand() % ((maxId + 1) - minId);


        Nodo* encontrado = busquedaRec(raiz, idRandom);
        
        if(encontrado != nullptr)
        {
            existe = true;
        }
        
    }while(existe != false);

    return idRandom;
}

// Verifica si un RUT específico existe en la cola de clientes.
bool datoExiste(string rutSelect, queue<Cliente*> clientes)
{
    while(!clientes.empty())
    {
        if(clientes.front()->rut == rutSelect)
        {
            return true;
        }
        clientes.pop();
    }
    return false;
}

// Verifica si un ID específico existe en una cola de transacciones.
bool idExiste(int id, queue<Transaccion*> listaSus)
{
    queue<Transaccion*> aux = listaSus;
    while(!aux.empty())
    {
        if(aux.front()->id == id)
        {
            return true;
        }
        aux.pop();
    }
    return false;
}

// Función para mostrar y revisar las transacciones sospechosas de un cliente.
void transaccionesSospechosas(queue<Cliente*> &clientes)
{
    string rutSelect;


    do{
        queue<Cliente*> aux = clientes;
        
        cout<<"RUT de los clientes: "<<endl;

        while(!aux.empty())
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

    Cliente* clientAux = nullptr;

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

    if(clientAux->getListaSospechosa().front() != nullptr)
    {
        do
        {
            listaSus = clientAux->getListaSospechosa();
            cout<<"IDs de Transferencias sospechosas: "<<endl;
            while(!listaSus.empty())
            {
                cout<<listaSus.front()->id<<" | Fecha: "<<listaSus.front()->fecha<<"| Hora: "<<listaSus.front()->hora<<endl;
                listaSus.pop();
            }

            cout<<"Ingrese ID de Transacción a revisar: "<<endl;
            cin>>idAux;

            if(!idExiste(idAux, clientAux->getListaSospechosa()))
            {
                cout<<"ID no encontrado. Ingrese un ID en el sistema. "<<endl;
            }

        }while(!idExiste(idAux, clientAux->getListaSospechosa()));

        listaSus = clientAux->getListaSospechosa();
        
        while(!listaSus.empty())
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

// Crea una nueva transacción y la agrega al árbol y a la cola de clientes.
void crearTransaccion(Nodo* &raiz, queue<Cliente*> &clientes)
{
    Cliente* aux2 = nullptr;
    Nodo* aux = nullptr;
    int id = crearIDRandom(raiz);
    string rutOrigen, rutDestino, ubicacion, fecha, hora;
    int monto;
    cout<<"Ingrese los siguientes datos: "<<endl;
    cout<<"RUT de origen: (Ej: 12345678-9)"<<endl;
    cin>>rutOrigen;

    cout<<"RUT de destino: (Ej: 12345678-9)"<<endl;
    cin>>rutDestino;

    cout<<"Monto recibido (Ej: 100000):"<<endl;
    cin>>monto;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout<<"Ubicación de Transferencia: "<<endl;
    getline(cin, ubicacion);

    cout<<"Fecha de Transacción: (Ej: 2024-07-03)"<<endl;
    cin>>fecha;

    cout<<"Hora de Transacción (Ej: 14:10): "<<endl;
    cin>>hora;

    Transaccion* nuevaTransaccion = new Transaccion(id, rutOrigen, rutDestino, monto, ubicacion, fecha, hora);

    raiz = aux->insertar(raiz, nuevaTransaccion);

    if(!aux2->buscarRut(clientes, nuevaTransaccion->rutFinal))
    {
        aux2->agregarTransaccionClienteExistente(clientes, nuevaTransaccion, nuevaTransaccion->rutFinal);
    }
    else
    {
        Cliente* nuevoCliente = new Cliente(nuevaTransaccion->rutFinal);
        clientes.push(nuevoCliente);
        aux2->agregarTransaccionClienteExistente(clientes, nuevaTransaccion, nuevaTransaccion->rutFinal);
    }
    if(!aux2->buscarRut(clientes, nuevaTransaccion->rutOrigen))
    {
        aux2->agregarTransaccionClienteExistente(clientes, nuevaTransaccion, nuevaTransaccion->rutOrigen);
    }
    else
    {
        Cliente* nuevoCliente = new Cliente(nuevaTransaccion->rutOrigen);
        clientes.push(nuevoCliente);
        aux2->agregarTransaccionClienteExistente(clientes, nuevaTransaccion, nuevaTransaccion->rutOrigen);
    }
}

// Permite revisar las transacciones en el árbol buscando por ID.
void revisarTransacciones(Nodo* &raiz)
{
    int opcion, opcion2;

    do{
        cout<<"IDs en el sistema:"<<endl;
        inOrdenRecursivo(raiz);

        int IDBuscar;
        cout<<"Ingresa el ID de Transacción:"<<endl;
        cin>>IDBuscar;

        Nodo* encontrada = busquedaRec(raiz, IDBuscar);

        if(encontrada != nullptr)
        {
            cout<<"Datos de Transacción:"<<endl;
            cout<<"ID: "<<encontrada->datos->id<<endl;
            cout<<"RUT de origen: "<<encontrada->datos->rutOrigen<<endl;
            cout<<"RUT de destino: "<<encontrada->datos->rutFinal<<endl;
            cout<<"Monto recibido: "<<encontrada->datos->monto<<endl;
            cout<<"Ubicación de Transferencia: "<<encontrada->datos->ubicacion<<endl;
            cout<<"Fecha de Transacción: "<<encontrada->datos->fecha<<endl;
            cout<<"Hora de Transacción: "<<encontrada->datos->hora<<endl;
        
        }
        else
        {
            cout<<"El Id ingresado no es correcto."<<endl;
        }
        
        do
        {
            cout<<"¿Desea finalizar la revisión de Tranferencias?( 1)Si  2)No ): "<<endl;
            cin>>opcion2;
            switch(opcion2)
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
        }while(opcion2 != 1 && opcion2 != 2);

    }while(opcion2 != 1);
}

// Menú principal del programa para realizar diferentes operaciones.
int menu(Nodo* &raiz, queue<Cliente*> &clientes)
{
    int opcion;
    
    do
    {
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

// Carga las transacciones desde un archivo de texto y las inserta en el árbol.
Nodo* cargarDatos()
{
    Nodo* aux1 = nullptr;
    Nodo* raiz = nullptr;
    Transaccion* aux2 = nullptr;

    string texto;
    
    ifstream datosTransaccion;

    datosTransaccion.open("Transferencias.txt", ios::in);

    if(datosTransaccion.fail())
    {
        cout<<"ERROR! no se pudo leer el archivo Transferencias."<<endl;
        exit(1);
    }
    while(getline(datosTransaccion, texto))
    {
        raiz = aux1->insertar(raiz, aux2->subirTransacciones(texto));
    }

    datosTransaccion.close();
    
    return raiz;
}

// Función para actualizar datos de las transacciones.
void actualizarDatos(Nodo* raiz, int cantidadNodos, int& saltosDeLinea, string& actualizacionTransferencias)
{
    if(raiz == nullptr)
    {
        return;
    }
    
    actualizarDatos(raiz->izquierda, cantidadNodos, saltosDeLinea, actualizacionTransferencias);
    saltosDeLinea++;
    if(saltosDeLinea < cantidadNodos)
    {
        actualizacionTransferencias += raiz->datos->datosTransaccion() + "\n";
    }
    else
    {
        actualizacionTransferencias += raiz->datos->datosTransaccion();
    }
    actualizarDatos(raiz->derecha, cantidadNodos, saltosDeLinea, actualizacionTransferencias);
}

// Función principal del programa.
int main()
{
    int cantidadNodos = 0, saltosDeLinea = 0;
    string actualizacion = "";
    Transaccion* auxActualizacion = nullptr;
    Cliente* auxCliente =nullptr;
    Nodo* auxNodo = nullptr;
    Nodo* raiz = nullptr;
    queue<Cliente*> clientes;
    raiz = cargarDatos();
    auxCliente->cargarClientes(clientes, raiz);
    auxCliente->agregarTransacciones(clientes, raiz);
    auxCliente->explorarOrdenar(clientes);
    menu(raiz, clientes);
    raiz->cantidadNodos(raiz, cantidadNodos);
    actualizarDatos(raiz, cantidadNodos, saltosDeLinea, actualizacion);
    auxActualizacion->actualizarDatosTransacciones(actualizacion);
    auxNodo->vaciarAVL(raiz);
    auxCliente->vaciarCola(clientes);
}