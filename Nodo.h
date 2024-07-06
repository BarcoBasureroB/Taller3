#pragma once
#include <iostream>
#include "Transaccion.h"
using namespace std;

class Nodo 
{
    public:
        Transaccion* datos;
        Nodo* izquierda;
        Nodo* derecha;
        int alturaNodo;
        ~Nodo();
        Nodo(Transaccion*);
        int altura(Nodo* N);
        int max(int a, int b);
        Nodo* rotacionDerecha(Nodo* y);
        Nodo* rotacionIzquierda(Nodo* x);
        Nodo* rotacionIzquierdaDerecha(Nodo* z);
        Nodo* rotacionDerechaIzquierda(Nodo* z);
        int obtenerBalance(Nodo* N);
        Nodo* insertar(Nodo* nodo, Transaccion* datos);
        string datosTransferencia();
};