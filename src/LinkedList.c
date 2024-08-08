#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"

/*
FUNCIONES ESTATICAS EN PARADIGMA FUNCIONAL

-Las variables dentro de funciones estaticas no se borran cuando termina la funcion. Se almacenan
 en el mismo lugar que se almacenan las variables globales

-El scope es si o si el archivo donde se define.

*/
// pongo aca el prototipo de las funciones para que solo puedan ser usadas aca; serian como private.
static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);



/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	if (this != NULL && (nodeIndex > -1 && nodeIndex < this->size)) // entre 0 y len-1
	{
		Node* aux = this->pFirstNode;
		int i;
		i = 0;
		while (i < nodeIndex)
		{
			aux = aux->pNextNode;
			i++;
		}
		return aux;
	}
	else {return NULL;}
}



/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex, void* pElement)
{
    int returnAux = -1;

    if (this != NULL && nodeIndex > -1 && nodeIndex <= this->size)
    {
    	Node* nodoNuevo = (Node*)malloc(sizeof(Node));
    	if (nodoNuevo != NULL)
    	{
    		nodoNuevo->pNextNode = NULL;
			nodoNuevo->pElement = pElement;

    		if (this->size == 0){this->pFirstNode = nodoNuevo;}
			else
			{
				Node* nodoViejo = getNode(this, nodeIndex-1); // encuentro el nodo inmediato anterior al nuevo
				if (nodoViejo != NULL){nodoViejo->pNextNode = nodoNuevo;}
			}
			returnAux = 0;
    	}
    }
    return returnAux;
}



/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= (LinkedList*)malloc(sizeof(LinkedList));
    this->size = 0;
    this->pFirstNode = NULL;
    return this;
}



/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if (this != NULL) {returnAux = (*this).size;}
    return returnAux;
}



/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux;
    returnAux = addNode(this, this->size, pElement); // si size es 0, se agregara en el nodo1. Si es 1, en el nodo2 y asi...
	if (returnAux != -1) {(*this).size ++;}
    return returnAux;
}



/** \brief Obtiene un puntero del elemento en el indice ingresado
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (void*) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* n = getNode(this, index);
    if (n != NULL)
    {
    	returnAux = n->pElement;
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
	Node* nodoModificar = getNode(this, index);
	if (nodoModificar != NULL)
	{
		nodoModificar->pElement = pElement;
		returnAux = 0;
	}

    return returnAux;
}



/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this, int index)
{
    int returnAux = -1;

    Node* nodoAnterior = NULL;
    Node* nodoEliminar = NULL;

    nodoEliminar = getNode(this, index);

    if (nodoEliminar != NULL)
    {
    	// al nodo anterior al que quiero eliminar le pongo como nodo siguiente el que el eliminado tenia.
    	if (index == 0)
    	{
    		this->pFirstNode = nodoEliminar->pNextNode;
    	}
    	else // si entra aca va a estar intentando borrar del 2do elemente para adelante
    	{
    		nodoAnterior = getNode(this, index-1);

			if (nodoAnterior != NULL)
			{
				nodoAnterior->pNextNode = nodoEliminar->pNextNode;
			}
    	}

    	free(nodoEliminar->pElement); // se borra pq ese puntero en teoria apunta a una dire de memo dinamica
    	free(nodoEliminar);
    	// free(nodoEliminar->pNextNode); // ESO NO TIENE SENTIDO BORRARLO PQ ES UN PUNTERO A OTRO NODO Y EL NODO
    									  // SIGUIENTE NO SE ELIMINA EN ESTE NODO
    	returnAux = 0;
    	this->size --;
    }

    return returnAux;
}



/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;

    if (this != NULL)
    {
    	int i;
    	i=0;
    	while (i<this->size) // this->size == 4 -> de 0 a 3 inclusive
    	{
    		ll_remove(this, i);
    		i++;
    	}

    	returnAux = 0;
    	this->size = 0;
    	this->pFirstNode = NULL;
    }

    return returnAux;
}



/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    returnAux = ll_clear(this);
    if (returnAux != -1)
    {
    	returnAux = 0;
    	free(this);
    }
    return returnAux;
}



/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if (this != NULL)
    {
    	Node* nodoActual;
    	int i;

    	i=0;

    	while (i < this->size)
    	{
    		nodoActual = getNode(this, i);
    		if (nodoActual != NULL)
    		{
    			if (nodoActual->pElement == pElement) // comparo los punteros.
    			{
    				returnAux = i;
    				break;
    			}
    		}
    		i++;
    	}
    }

    return returnAux;
}



/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if (this!=NULL)
    {
    	returnAux = 1; // no tiene elementos
    	if (this->size > 0) {returnAux = 0;} // si tiene elementos
    }
    return returnAux;
}



/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    if (this != NULL && pElement != NULL && (index>-1 && index<this->size))
    {
    	Node* nuevoNodo;
    	Node* nodoActual;
    	Node* nodoAnterior;

    	nodoActual = getNode(this, index);

    	nuevoNodo = (Node*)malloc(sizeof(Node));
		nuevoNodo->pElement = pElement;
		nuevoNodo->pNextNode = nodoActual;

    	if (index == 0)
    	{
    		this->pFirstNode = nuevoNodo;
    	}
    	else
    	{
    		nodoAnterior = getNode(this, index-1);
    		nodoAnterior->pNextNode = nuevoNodo;
    	}

    	returnAux = 0;
    	this->size ++;
    }
    return returnAux;
}



/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    if (this != NULL && (index>-1 && index<this->size))
    {
		Node* nodoEliminado = getNode(this, index);
		returnAux = nodoEliminado->pElement;

		ll_remove(this, index);
	 }
     return returnAux;
}



/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux;
    returnAux = ll_indexOf(this, pElement);

    if (returnAux > -1 && this != NULL)
    {
    	returnAux = 1;
    }
    else
    {
    	returnAux = 0;
    }
    return returnAux;
}



/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this, LinkedList* this2)
{
    int returnAux = -1;

    if (this != NULL && this2 != NULL)
    {
    	Node* nodoActual;
    	int i;

    	i=0;
    	returnAux = 1;

    	while (i < this2->size)
    	{
    		nodoActual = getNode(this2, i);
    		if (nodoActual == NULL || ll_contains(this, nodoActual->pElement) != 1)
    		{
				returnAux = 0;
				break;
    		}
    		i++;
    	}
    }
    return returnAux;
}



/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this, int from, int to)
{
    LinkedList* cloneLinkedList = NULL;

    if (this != NULL && (from > -1 && from <= this->size) && (to > -1 && to <= this->size))
    {
    	cloneLinkedList = ll_newLinkedList();

    	void* elemento;

        for (int i=from; i<to; i++)
        {
        	elemento = ll_get(this, i);

        	if (elemento != NULL) {ll_add(cloneLinkedList, elemento);}
        }
    }
    return cloneLinkedList;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneLinkedList = ll_subList(this, 0, this->size);
    return cloneLinkedList;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;

    if (this != NULL && pFunc != NULL)
    {
    	void* elementoAux;
    	void* elementoI;
    	void* elementoJ;
    	int retornoSwap;

    	for (int i=0; i<this->size-1; i++)
    	{
    		elementoI = ll_get(this, i);
    		for (int j=i+1; j<this->size; j++)
    		{
        		elementoJ = ll_get(this, j);

        		retornoSwap = pFunc(elementoI, elementoJ); // si a es mayor que b, pFunc retornará 1. Menor, -1. O igual.

        		if ((retornoSwap==1 && order==1) || (retornoSwap==-1 && order==0))
        		{
        			elementoAux = elementoI;
					ll_set(this, i, elementoJ); // tengo que cambiar en los nodos directamente pq si lo hago aca solo
					ll_set(this, j, elementoI); // estaria cambiando los punteros de las variables locales, no los de la linkedlist
        		}
    		}
    	}
    	returnAux = 0;
    }
    return returnAux;
}



/**
 * \fn int ll_map(LinkedList*, int(*)(void*))
 * \brief Recorre la linked list dada y utiliza la funcion dada en cada uno de los elementos
 * la cual esta destinada a modificar un campo deseado de un puntero a estructura
 *
 * \param this
 * \param pSet
 * \return 0 si fue exitoso, -1 si no lo fue
 */
int ll_map(LinkedList* this, int (*pSet)(void*))
{
	int retorno = -1;
	if (this != NULL && pSet != NULL)
	{
		Node* nodoActual;

		for (int i=0; i<this->size; i++)
		{
			nodoActual = getNode(this, i);
			if (nodoActual != NULL) {pSet(nodoActual->pElement);}
		}

		retorno = 0;
	}
	return retorno;
}



/**
 * \fn int ll_filter*(LinkedList*, int(*)(void*))
 * \brief Se recorrera una linked list y dependiendo del
 * resultado de la funcion dada si el objeto quedara en la
 * lista final, si es 0 el item permanecera y si es 1 el
 * item sera eliminado de la lista
 *
 * \param this
 * \param pCompare
 * \return -1 En caso de error, 0 En caso de que haya sido exitoso
 */
int ll_filter(LinkedList* this, int (*pCompare)(void*))
{
	int retorno = -1;
	if (this != NULL && pCompare != NULL)
	{
		Node* nodoActual;

		for (int i=0; i<this->size; i++)
		{
			nodoActual = getNode(this, i);
			if (nodoActual != NULL && pCompare(nodoActual->pElement) == 1)
			{
				ll_pop(this, i);
			}
		}
		retorno = 0;
	}
	return retorno;
}

