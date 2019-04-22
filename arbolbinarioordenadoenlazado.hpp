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
				assert(this->_izquierdo==NULL && this->_derecho==NULL);
				#endif
			}

			NodoArbolBinario (const NodoArbolBinario &n)
			{
				this->_info=n.getInfo();
				this->_izquierdo=n.getIzquierdo();
				this->_derecho=n.getDerecho();

				#ifndef NDEBUG
				NodoArbolBinario const aux=*this ;
				assert(aux == n);
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
				this->getIzquierdo()->recorridoPreOrden(operador);
				this->getDerecho()->recorridoPreOrden(operador);
			}

			void recorridoPostOrden (OperadorNodo<G> &operador) const
			{
				this->getIzquierdo()->recorridoPostOrden(operador);
				this->getDerecho()->recorridoPostOrden(operador);
				if(!operador.aplicar(this->getInfo())) {
					return ;
				}
			}

			void recorridoInOrden (OperadorNodo<G> &operador) const
			{
				this->getIzquierdo()->recorridoInOrden(operador);
				if(!operador.aplicar(this->getInfo())) {
					return ;
				}
				this->getDerecho()->recorridoInOrden(operador);
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
				#ifndef NDEBUG
				NodoArbolBinario const aux=*this ;
				assert(aux != n);
				#endif

				this->_info=n.getInfo();
				this->_izquierdo=n.getIzquierdo();
				this->_derecho=n.getDerecho();

				#ifndef NDEBUG
				assert(aux == n);
				#endif
				
			}

		}; //Fin clase NodoArbolBinario

		//Implementación de la raíz
		NodoArbolBinario * _raiz; /*!<La raiz del árbol*/
		NodoArbolBinario * _actual; /*!<Cursor al nodo actual*/
		NodoArbolBinario * _padre; /*!<Cursor al nodo actual*/

	public:

		ArbolBinarioOrdenadoEnlazado ()
		{
			
		}

		ArbolBinarioOrdenadoEnlazado (const ArbolBinarioOrdenadoEnlazado<G>& a)
		{
			this = a;	
		}

		~ArbolBinarioOrdenadoEnlazado ()
		{
			if (not estaVacio())
			borrarArbol();
			cout << "Destructor Usado \n";
		}

		ArbolBinarioOrdenadoEnlazado &operator=(const ArbolBinarioOrdenadoEnlazado& a)
		{
			
		}

		bool insertar(const G &x)
		{
			while(_actual->esHoja() == false){
				if(_actual->getInfo() > x){
					_actual = _actual->getDerecho();
				}
				else{
					_actual = _actual->getIzquierdo();
				}
			}

  			NodoArbolBinario var(x);
  			NodoArbolBinario * aux= &var;
 

			if(_actual->getInfo() > x){

					_actual->setDerecho(aux);
					return true;
			}
			else{
					_actual->setIzquierdo(aux);
					return true;
			}

			return false;
		}

		void borrarArbol()
		{
			_raiz=NULL;
			_actual=NULL;
			_padre=NULL;
		}

		bool borrar()
		{
			// TODO
			return false;
		}

		void recorridoPreOrden (OperadorNodo<G> &operador) const
		{
			if(!operador.aplicar(_raiz->getInfo())) {
					return ;
				}
			_raiz->getIzquierdo()->recorridoPreOrden(operador);
			_raiz->getDerecho()->recorridoPreOrden(operador);
		}

		void recorridoPostOrden (OperadorNodo<G> &operador) const
		{
			if(!operador.aplicar(_raiz->getInfo())) {
					return ;
				}
			_raiz->getIzquierdo()->recorridoPostOrden(operador);
			_raiz->getDerecho()->recorridoPostOrden(operador);
		}

		void recorridoInOrden (OperadorNodo<G> &operador) const
		{
			_raiz->getIzquierdo()->recorridoInOrden(operador);
			if(!operador.aplicar(_raiz->getInfo())) {
					return ;
				}
			_raiz->getDerecho()->recorridoInOrden(operador);
		}

		bool buscar(const G& x) const
		{
			/*while(_actual->esHoja() == false){
				if(_actual->getInfo() == x){
					return true;
				}
				if(_actual->getInfo() > x){
					_actual = _actual->getDerecho();
				}
				if(_actual->getInfo() < x){
					_actual = _actual->getIzquierdo();
				}
			}

			if(_actual->getInfo() == x){

					return true;
			}
			*/
			return false;
		}

		bool estaVacio() const
		{
			if (_raiz == NULL){
				return false;
			}
			return true;
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
