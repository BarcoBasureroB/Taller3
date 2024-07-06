#include "Nodo.h"
using namespace std;

//Constructor de Nodo.
Nodo::Nodo(Transaccion* datos) 
{
    this->derecha = nullptr;
    this->izquierda = nullptr;
    this->datos = datos;
    this->alturaNodo = 1;
}

//Destructor de la clase Nodo.
Nodo::~Nodo(){}

// Método para obtener la altura de un nodo. Si el nodo es nulo, retorna 0.
int Nodo::altura(Nodo* N) 
{
    if (N) {return N->alturaNodo;}

    else {return 0;}
}

// Método para obtener el máximo de dos enteros.
int Nodo::max(int a, int b) {
    if (a > b) {return a;}

    else {return b;}
}

// Realiza una rotación a la derecha en el subárbol.
Nodo* Nodo::rotacionDerecha(Nodo* y)
{
    Nodo* x = y->izquierda;
    Nodo* T2 = x->derecha;

    x->derecha = y;
    y->izquierda = T2;

    y->alturaNodo = max(altura(y->izquierda), altura(y->derecha)) + 1;
    x->alturaNodo = max(altura(x->izquierda), altura(x->derecha)) + 1;

    return x;
}

// Realiza una rotación a la izquierda en el subárbol.
Nodo* Nodo::rotacionIzquierda(Nodo* x) 
{
    Nodo* y = x->derecha;
    Nodo* T2 = y->izquierda;

    y->izquierda = x;
    x->derecha = T2;

    x->alturaNodo = max(altura(x->izquierda), altura(x->derecha)) + 1;
    y->alturaNodo = max(altura(y->izquierda), altura(y->derecha)) + 1;

    return y;
}

// Realiza una rotación a la izquierda seguida de una rotación a la derecha.
Nodo* Nodo::rotacionIzquierdaDerecha(Nodo* z) 
{
    z->izquierda = rotacionIzquierda(z->izquierda);
    return rotacionDerecha(z);
}

// Realiza una rotación a la derecha seguida de una rotación a la izquierda.
Nodo* Nodo::rotacionDerechaIzquierda(Nodo* z) 
{
    z->derecha = rotacionDerecha(z->derecha);
    return rotacionIzquierda(z);
}

// Calcula el Factor de balanceo.
int Nodo::obtenerBalance(Nodo* N)
{
    if (N) {return altura(N->izquierda) - altura(N->derecha);} 
    
    else {return 0;}
}

// Inserta un nuevo nodo con los datos proporcionados.
Nodo* Nodo::insertar(Nodo* nodo, Transaccion* datos) 
{
    if (nodo == nullptr) {return new Nodo(datos);}

    if (datos->id < nodo->datos->id) {nodo->izquierda = insertar(nodo->izquierda, datos);}
    
    else if (datos->id > nodo->datos->id){nodo->derecha = insertar(nodo->derecha, datos);}

    else {return nodo;}
    nodo->alturaNodo = 1 + max(altura(nodo->izquierda), altura(nodo->derecha));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && datos->id < nodo->izquierda->datos->id) {return rotacionDerecha(nodo);}

    if (balance < -1 && datos->id > nodo->derecha->datos->id) {return rotacionIzquierda(nodo);}

    if (balance > 1 && datos->id > nodo->izquierda->datos->id) {return rotacionIzquierdaDerecha(nodo);}

    if (balance < -1 && datos->id < nodo->derecha->datos->id) {return rotacionDerechaIzquierda(nodo);}

    return nodo;
}

// Función para vaciar un árbol AVL liberando la memoria.
void Nodo::vaciarAVL(Nodo*& raiz) 
{
    if (!raiz)
        return;

    vaciarAVL(raiz->izquierda);
    vaciarAVL(raiz->derecha);

    delete raiz;
    raiz = nullptr;
}

// Calcula el número de nodos en el árbol.
void Nodo::cantidadNodos(Nodo* raiz, int& suma)
{
    if(raiz == nullptr)
    {
        return;
    }
    
    cantidadNodos(raiz->izquierda, suma);
    suma++;
    cantidadNodos(raiz->derecha, suma);
}
