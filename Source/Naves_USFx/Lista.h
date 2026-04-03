#pragma once

// Estructura del Nodo genérico
template <typename T>
class NodoLista {
public:
    T Dato;
    NodoLista<T>* Siguiente;

    NodoLista(T dato) {
        Dato = dato;
        Siguiente = nullptr;
    }
};

// Contenedor Lista
template <typename T>
class Lista {
private:
    NodoLista<T>* Cabeza;
    int Tamano;

public:
    Lista() {
        Cabeza = nullptr;
        Tamano = 0;
    }

    ~Lista() {
        Vaciar();
    }

    // Insertar un elemento al final de la lista
    void InsertarFinal(T elemento) {
        NodoLista<T>* nuevoNodo = new NodoLista<T>(elemento);

        // Evaluamos el estado de la lista con if-else
        if (Cabeza == nullptr) {
            // CONDICIÓN IF: La lista está vacía, el nuevo nodo es el inicio
            Cabeza = nuevoNodo;
        } else {
            // CONDICIÓN ELSE: La lista ya tiene elementos, recorremos hasta el final
            NodoLista<T>* actual = Cabeza;
            while (actual->Siguiente != nullptr) {
                actual = actual->Siguiente;
            }
            actual->Siguiente = nuevoNodo;
        }
        Tamano++;
    }

    // Obtener un elemento por su índice
    T Obtener(int indice) {
        if (indice < 0 || indice >= Tamano) {
            return nullptr;
        } else {
            NodoLista<T>* actual = Cabeza;
            for (int i = 0; i < indice; i++) {
                actual = actual->Siguiente;
            }
            return actual->Dato;
        }
    }

    int ObtenerTamano() const {
        return Tamano;
    }

    void Vaciar() {
        NodoLista<T>* actual = Cabeza;
        while (actual != nullptr) {
            NodoLista<T>* siguiente = actual->Siguiente;
            delete actual;
            actual = siguiente;
        }
        Cabeza = nullptr;
        Tamano = 0;
    }
};