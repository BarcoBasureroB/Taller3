#include <iostream>
#include <queue>
#include <vector>
#include "Transaccion.h"

using namespace std;


void crearTransaccion(vector<Transaccion*> &transacciones)
{

}

void RevisarTransacciones(vector<Transaccion*> &transacciones)
{

}

int menu(vector<Transaccion*> &transacciones)
{
    int opcion;

    do {
        cout << "\n|--- Menú ---|\n";
        cout << "1. Realizar Transacción.\n";
        cout << "2. Registro de Transacción.\n";
        cout << "3. Transacciones Sospechosas.\n";
        cout << "4. Salir\n";
        cout << "Ingrese una opción(Ejemplo: 1): ";
        cin >> opcion;
        cout<<endl;
        switch(opcion) {
            case 1:
                crearTransaccion(transacciones);
                break;
            case 2:
                RevisarTransacciones(transacciones);
                break;
            case 3:
                
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