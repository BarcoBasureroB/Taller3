#include "Nodo.h"
using namespace std;

Nodo::Nodo(Transaccion* datos) 
{
    this->derecha = nullptr;
    this->izquierda = nullptr;
    this->datos = datos;
    this->alturaNodo = 1;
}

Nodo::~Nodo(){}

int Nodo::altura(Nodo* N) 
{
    if (N) {return N->alturaNodo;}

    else {return 0;}
}

int Nodo::max(int a, int b) {
    if (a > b) {return a;}

    else {return b;}
}

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

Nodo* Nodo::rotacionIzquierdaDerecha(Nodo* z) 
{
    z->izquierda = rotacionIzquierda(z->izquierda);
    return rotacionDerecha(z);
}

Nodo* Nodo::rotacionDerechaIzquierda(Nodo* z) 
{
    z->derecha = rotacionDerecha(z->derecha);
    return rotacionIzquierda(z);
}

int Nodo::obtenerBalance(Nodo* N)
{
    if (N) {return altura(N->izquierda) - altura(N->derecha);} 
    
    else {return 0;}
}

Nodo* Nodo::insertar(Nodo* nodo, Transaccion* datos) 
{
    if (!nodo) {return new Nodo(datos);}

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
void Nodo::vaciarAVL(Nodo*& raiz) 
{
    if (!raiz)
        return;

    vaciarAVL(raiz->izquierda);
    vaciarAVL(raiz->derecha);

    delete raiz;
    raiz = nullptr;
}
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
