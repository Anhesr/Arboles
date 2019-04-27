#ifndef __ARBOLBINARIOORDENADO_HPP__
#define __ARBOLBINARIOORDENADOENLAZADO_HPP__

#include <iostream>
#include <cassert>
#include "arbolbinarioordenado.hpp"
#include "operadornodo.hpp"

using namespace std;
/*!
\brief Espacio de nombres para la asignatura Estructura de datos.
*/
namespace ed
{
	/*!\brief Interfaz para definir un ArbolBinario ordenado.

	Define una interfaz para definir un ArbolBinarioOrdenado.

	\arg G define el campo de información a contener en el arbol.
	\pre G debe tener definidos los operadores < y ==.
	*/
	template<class G>
	class ArbolBinarioOrdenadoEnlazado:public ArbolBinarioOrdenado<G>
	{
	private:

		/*!\brief Define un nodo del arbol binario.*/
		class NodoArbolBinario
		{
		private:
			G _info;  //Valor informativo almacenado en el nodo
			NodoArbolBinario * _izquierdo;  //Puntero al hijo izquierdo
			NodoArbolBinario * _derecho;  //Puntero al hijo derecho

		public:
			NodoArbolBinario (const G &info)
			{
				this->_info=info;
				this->_izquierdo=NULL;
				this->_derecho=NULL;

				#ifndef NDEBUG
				assert(this->esHoja());
				#endif
			}

			NodoArbolBinario (const NodoArbolBinario &n)
			{
				this->_info=n.getInfo();
				this->_izquierdo=n.getIzquierdo();
				this->_derecho=n.getDerecho();

				#ifndef NDEBUG
				assert(this->getInfo() == n.getInfo());
				assert(this->getDerecho() == n.getDerecho());
				assert(this->getIzquierdo() == n.getIzquierdo());
				#endif
			}

			/*!\brief Observadores.*/
			inline const G & getInfo() const
			{
				return _info;
			}

			NodoArbolBinario *getIzquierdo() const
			{
				return _izquierdo;
			}

			NodoArbolBinario *getDerecho() const
			{
				return _derecho;
			}

			bool esHoja() const
			{
				if(this->_izquierdo==NULL && this->_derecho==NULL){
					return true;
				}
				return false;
			}

			void recorridoPreOrden (OperadorNodo<G> &operador) const
			{
				if(!operador.aplicar(this->getInfo())) {
					return ;
				}
				if(this->getIzquierdo()!= NULL){
					this->getIzquierdo()->recorridoPreOrden(operador);
				}
				if(this->getDerecho()!= NULL){
					this->getDerecho()->recorridoPreOrden(operador);
				}
			}

			void recorridoPostOrden (OperadorNodo<G> &operador) const
			{
				if(this->getIzquierdo()!= NULL){
					this->getIzquierdo()->recorridoPostOrden(operador);
				}
				if(this->getDerecho()!= NULL){
					this->getDerecho()->recorridoPostOrden(operador);
				}
				if(!operador.aplicar(this->getInfo())) {
					return ;
				}
			}

			void recorridoInOrden (OperadorNodo<G> &operador) const
			{
				if(this->getIzquierdo()!= NULL){
					this->getIzquierdo()->recorridoInOrden(operador);
				}
				if(!operador.aplicar(this->getInfo())) {
					return ;
				}
				if(this->getDerecho()!= NULL){
					this->getDerecho()->recorridoInOrden(operador);
				}
			}

			/*!\brief Modificadores. */
			void setInfo(const G &info)
			{
				_info=info;
			}

			void setIzquierdo(NodoArbolBinario *n)
			{
				_izquierdo=n;
			}

			void setDerecho(NodoArbolBinario *n)
			{
				_derecho= n;
			}

			NodoArbolBinario & operator=(const NodoArbolBinario &n)
			{

				this->_info=n.getInfo();
				this->_izquierdo=n.getIzquierdo();
				this->_derecho=n.getDerecho();

			}

		}; //Fin clase NodoArbolBinario

		//Implementación de la raíz
		NodoArbolBinario * _raiz; /*!<La raiz del árbol*/
		NodoArbolBinario * _actual; /*!<Cursor al nodo actual*/
		NodoArbolBinario * _padre; /*!<Cursor al nodo actual*/

	public:

		ArbolBinarioOrdenadoEnlazado ()
		{
			_raiz=NULL;
			#ifndef NDEBUG
				assert(this->estaVacio());
			#endif
		}

		ArbolBinarioOrdenadoEnlazado (const ArbolBinarioOrdenadoEnlazado<G>& a)
		{
			*this = a;	
		}

		~ArbolBinarioOrdenadoEnlazado ()
		{
			if (not estaVacio())
			borrarArbol();
			//cout << "Destructor Usado \n";
		}
		ArbolBinarioOrdenadoEnlazado &operator=(const ArbolBinarioOrdenadoEnlazado& a)
		{
			this->_raiz=a._raiz;
			this->_actual=a._actual;
			this->_padre=a._padre;
		}
		bool insertar(const G &x)
		{
			bool inst = false;
			if (this->estaVacio()){
				_raiz = new NodoArbolBinario(x);
				inst = true;
			}
			else{
				_padre = NULL;
				_actual = _raiz;
			}
			while (! inst){
				if (x > this->actual()){
					if (_actual->getDerecho() != NULL){
						_padre = _actual;
						_actual = _actual->getDerecho();
					}
					else{
						_actual->setDerecho(new NodoArbolBinario(x));
						inst = true;
					}
				}
				else{
					if (_actual->getIzquierdo() != NULL){
						_padre = _actual;
						_actual = _actual->getIzquierdo();
					}
					else{
						_actual->setIzquierdo(new NodoArbolBinario(x));
						inst = true;
					}
				}

			}
			
			return inst;
		}


		void borrarArbol()
		{
			_raiz=NULL;
			_actual=NULL;
			_padre=NULL;
		}

		bool borrar()
		{
			#ifndef NDEBUG
				assert(! this->estaVacio());
			#endif

			NodoArbolBinario *aux_pt_actual;
			NodoArbolBinario *aux_pt_padre;
			aux_pt_actual = _actual;
			aux_pt_padre = _padre;
			bool borrado = false;

			if(_actual->getDerecho() != NULL){
				_padre = _actual;
				_actual = _actual->getDerecho();

				while(_actual->getIzquierdo() != NULL){
					_padre = _actual;
					_actual = _actual->getIzquierdo();
				}

				
				if(_actual->getInfo() < _padre->getInfo()){
					_padre->setIzquierdo(_actual->getDerecho());
				}
				else{
					aux_pt_actual->setDerecho(_actual->getDerecho());
				}
				aux_pt_actual->setInfo(_actual->getInfo());
				borrado = true;
				_actual = aux_pt_actual;
				_padre = aux_pt_padre;
			}
			else if (_actual->getIzquierdo() != NULL){
				_padre = _actual;
				_actual = _actual->getIzquierdo();

				while(_actual->getDerecho() != NULL){
					_padre = _actual;
					_actual = _actual->getDerecho();
				}

				if(_actual->getInfo() > _padre->getInfo()){
					_padre->setDerecho(_actual->getIzquierdo());
				}
				else{
					aux_pt_actual->setIzquierdo(_actual->getIzquierdo());
				}
				aux_pt_actual->setInfo(_actual->getInfo());
				borrado = true;
				_actual = aux_pt_actual;
				_padre = aux_pt_padre;

			}
			else{
				if (_raiz == _actual){
					this->borrarArbol();
				}
				else if(_actual->getInfo() < _padre->getInfo()){
					_padre->setIzquierdo(NULL);
				}
				else{
					_padre->setDerecho(NULL);
				}
				borrado = true;
			}
			return borrado;
		}



		void recorridoPreOrden (OperadorNodo<G> &operador) const
		{
			_raiz->recorridoPreOrden(operador);
		}

		void recorridoPostOrden (OperadorNodo<G> &operador) const
		{
			_raiz->recorridoPostOrden(operador);
		}

		void recorridoInOrden (OperadorNodo<G> &operador) const
		{
			_raiz->recorridoInOrden(operador);
		}

		bool buscar(const G& x)
		{
			bool encontrado = false;
			_padre = NULL;
			_actual = _raiz;

			while((_actual != NULL)&&(! encontrado)){
				if (_actual->getInfo() > x){
					if (_actual->getIzquierdo() != NULL){
						_padre = _actual;
						_actual = _actual->getIzquierdo();
					}
					else{
						_actual = NULL;
					}
				}
				else if(_actual->getInfo() < x){
					if (_actual->getDerecho() != NULL){
						_padre = _actual;
						_actual = _actual->getDerecho();
					}
					else{
						_actual = NULL;
					}
				}
				else{
					encontrado = true;
				}
			}
			if (_actual == NULL){
				_padre = NULL;
				_actual = _raiz;
			}

			return encontrado;
		}
		bool estaVacio() const
		{
			if (_raiz == NULL){
				return true;
			}
			return false;
		}

		G raiz() const
		{
			return _raiz->getInfo();
		}

		bool existeActual() const
		{
			if (_actual == NULL){
				return false;
			}
			return true;	
		}

		G actual() const
		{
			return _actual->getInfo();
		}

		/*!@}*/
	};

} //namespace ed

#endif //__ARBOLORDENADO_HPP__
