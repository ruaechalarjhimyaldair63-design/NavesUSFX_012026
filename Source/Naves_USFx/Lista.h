#pragma once

/**
 * Lista enlazada simple (estructura de datos: nodos, enlaces, inserción, borrado).
 * Uso típico en este proyecto: Lista<AActor*> para el camino del escenario.
 */
template <typename T>
class NodoLista {
public:
	T Dato;
	NodoLista<T>* Siguiente;

	explicit NodoLista(T dato)
		: Dato(dato)
		, Siguiente(nullptr)
	{
	}
};

template <typename T>
class Lista {
private:
	NodoLista<T>* Cabeza;
	int Tamano;

	void CopiarDesde(const Lista& Otra)
	{
		NodoLista<T>* Actual = Otra.Cabeza;
		while (Actual != nullptr)
		{
			InsertarFinal(Actual->Dato);
			Actual = Actual->Siguiente;
		}
	}

public:
	Lista()
		: Cabeza(nullptr)
		, Tamano(0)
	{
	}

	/** Copia profunda de la lista (mismos valores en el mismo orden). */
	Lista(const Lista& Otra)
		: Cabeza(nullptr)
		, Tamano(0)
	{
		CopiarDesde(Otra);
	}

	Lista& operator=(const Lista& Otra)
	{
		if (this != &Otra)
		{
			Vaciar();
			CopiarDesde(Otra);
		}
		return *this;
	}

	~Lista()
	{
		Vaciar();
	}

	void InsertarInicio(T Elemento)
	{
		NodoLista<T>* NuevoNodo = new NodoLista<T>(Elemento);
		NuevoNodo->Siguiente = Cabeza;
		Cabeza = NuevoNodo;
		Tamano++;
	}

	void InsertarFinal(T Elemento)
	{
		NodoLista<T>* NuevoNodo = new NodoLista<T>(Elemento);

		if (Cabeza == nullptr)
		{
			Cabeza = NuevoNodo;
		}
		else
		{
			NodoLista<T>* Actual = Cabeza;
			while (Actual->Siguiente != nullptr)
			{
				Actual = Actual->Siguiente;
			}
			Actual->Siguiente = NuevoNodo;
		}
		Tamano++;
	}

	/** Índice válido [0, Tamano). Si no es válido, devuelve valor por defecto de T. */
	T Obtener(int Indice) const
	{
		if (Indice < 0 || Indice >= Tamano)
		{
			return T();
		}
		NodoLista<T>* Actual = Cabeza;
		for (int i = 0; i < Indice; i++)
		{
			Actual = Actual->Siguiente;
		}
		return Actual->Dato;
	}

	bool IntentarObtener(int Indice, T& Salida) const
	{
		if (Indice < 0 || Indice >= Tamano)
		{
			return false;
		}
		NodoLista<T>* Actual = Cabeza;
		for (int i = 0; i < Indice; i++)
		{
			Actual = Actual->Siguiente;
		}
		Salida = Actual->Dato;
		return true;
	}

	int ObtenerTamano() const { return Tamano; }

	bool EsVacia() const { return Cabeza == nullptr; }

	/**
	 * Elimina el nodo en Indice. Los actores UObjects no se destruyen aquí;
	 * solo se quita el puntero de la lista.
	 */
	bool EliminarEn(int Indice)
	{
		if (Indice < 0 || Indice >= Tamano)
		{
			return false;
		}

		if (Indice == 0)
		{
			NodoLista<T>* Viejo = Cabeza;
			Cabeza = Cabeza->Siguiente;
			delete Viejo;
			Tamano--;
			return true;
		}

		NodoLista<T>* Anterior = Cabeza;
		for (int i = 0; i < Indice - 1; i++)
		{
			Anterior = Anterior->Siguiente;
		}
		NodoLista<T>* Viejo = Anterior->Siguiente;
		Anterior->Siguiente = Viejo->Siguiente;
		delete Viejo;
		Tamano--;
		return true;
	}

	void Vaciar()
	{
		NodoLista<T>* Actual = Cabeza;
		while (Actual != nullptr)
		{
			NodoLista<T>* Siguiente = Actual->Siguiente;
			delete Actual;
			Actual = Siguiente;
		}
		Cabeza = nullptr;
		Tamano = 0;
	}
};
