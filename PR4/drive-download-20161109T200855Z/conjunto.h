#ifndef __CONJUTO_H
#define __CONJUTO_H
#include <string>
#include <vector>
#include <iostream> 

#include "crimen.h"

using namespace std;
//! Clase conjunto
/*! Metodos--> conjunto:: conjunto(), insert(), find(),  findIUCR(), findDESCR(), erase(), size(), empty()

 * Tipos--> conjunto::entrada, conjunto::size_type

 * Descripcion

* Un conjunto es un contenedor que permite almacenar en un orden dado por un funtor un conjunto de elementos no repetidos.  En nuestro caso el conjunto va a tener un subconjunto restringido de metodos (insercion de elementos, consulta de un elemento, etc). Este conjunto "simulara" un conjunto de la stl.

* Asociado al conjunto, tendremos el tipo  \code conjunto::entrada \endcode que permite hacer referencia al elemento  almacenados en cada una de las posiciones del conjunto, en nuestro caso delitos (crimenes). Para esta entrada el requisito es que tenga definidos el operador< y operator=

* Ademas encontraremos el tipo \code conjunto::size_type \endcode que permite hacer referencia al numero de elementos en el conjunto.

* El numero de elementos en el conjunto puede variar dinamicamente; la gestion de la memoria es automatica. 
 
 Ejemplo de su uso:
\code
...
conjunto<CrecientePorFecha> DatosChicago, agresion;
crimen cr;

conjunto.insert(cr);
...
agresion = conjunto.findDESCR("BATTERY");

if (!agresion.empty()){
 cout <<"Tenemos "<< agresion.size() << " agresiones" << endl;
 cout << agresion << endl;
} else "No hay agresiones en el conjunto" << endl;
...
\endcode
 
 */
template<class CMP>
class conjunto
{  
private:
	vector<crimen> vc;
	bool cheq_rep( ) const;	
//	friend ostream &  operator << ( ostream & sal, const conjunto & D);
	friend class iterator;
	friend class const_iterator;
	CMP comp;

public:
/** @brief entrada permite hacer referencia al elemento  almacenados en cada una de las posiciones del conjunto
    */
	typedef crimen entrada;
	/** @brief size_type numero de elementos en el conjunto
         */
	typedef unsigned int size_type;
/** @brief constructor primitivo. 
	*/
	conjunto( );
	/** @brief constructor de copia
	@param[in] d conjunto a copiar
	*/
	conjunto (const conjunto<CMP> & d);
	class iterator;  
  	class const_iterator;
	template<class IT>
/**@brief Constructor de rango, valido para cualquier tipo de contenedor de crimenes
	@param ini, fin iteradores que indican el inicio y fin del rango a copiar, pueden pertenecer a otro contenedor
	*/
	conjunto(const IT &ini,const IT &fin);

/** @brief busca un crimen en el conjunto
	@param id identificador del crimen  buscar
	@return Si existe una entrada en el conjunto devuelve un iterador a la posicion donde esta el elemento. Si  no se encuentra devuelve end()
	@post no modifica el conjunto.
	\code Ejemplo
       

	if (C.find(12345)!=C.end() ) cout << "Esta" ;
	else cout << "No esta";
	\endcode
	*/
	conjunto::iterator find( const long int & id);
	/**@brief devuelve un iterador al crimen pasado como parametro
	@param e crimen a buscar
	@return iterador al crimen indicado en el caso de que lo encuentre, iterador al end del conjuntoen caso contrario
	*/
	conjunto::iterator find(const conjunto::entrada &e);
	/**@brief devuelve un iterador constante al crimen pasado como parametro
	@param e crimen a buscar
	@return iterador constante al crimen indicado en el caso de que lo encuentre, iterador al end del conjuntoen caso contrario
	@post No cambia el estado del conjunto
	*/
	conjunto::const_iterator find(const conjunto::entrada &e) const;
	/** @brief busca un crimen en el conjunto
	@param id identificador del crimen  buscar
	@return Si existe una entrada en el conjunto devuelve un iterador a lo posicion donde esta el elemento. Si  no se encuentra devuelve end()
	@post no modifica el conjunto.
	\code Ejemplo
       

	if (C.find(12345)!=C.end() ) cout << "Esta" ;
	else cout << "No esta";
	\endcode
	*/
	conjunto::const_iterator  find( const long int & id) const;
	/** @brief busca los crimenes con el mismo codigo IUCR
	@param iucr identificador del crimen  buscar
	@return Devuelve un  conjunto con todos los crimenes con el codigo IUCR. Si no existe ninguno devuelve el conjunto vacio.
	@post no modifica el conjunto.
	\verbatim Uso
        vector<crimen> C, A;
        ....
        A = C.findIUCR("0460");
	\endverbatim
	*/
	conjunto findIUCR( const string & iucr) const;
	/** @brief busca los crimenes que contienen una determinada descripcion 
	@param descr string que representa la descripcion del delito buscar
	@return Devuelve un  conjunto con todos los crimenes  que contengan descr en su descripcionR. Si no existe ninguno devuelve el conjunto vacio.
	@post no modifica el conjunto.
	\verbatim Uso
        vector<crimen> C, A;
        ....
        A = C.findDESCR("BATTERY");
	\endverbatim
	*/
	conjunto findDESCR( const string & descr) const;
/** @brief Inserta una entrada en el conjunto
@param e entrada a insertar
@return true si la entrada se ha podido insertar con exito. False en caso contrario
@post 	 el size() sera incrementado en 1.
*/
	bool insert( const conjunto<CMP>::entrada & e);
	/** @brief Borra el delito dado un identificacador.

Busca la entrada con id en el conjunto  y si la encuentra la borra

@param[in] id a borrar
@return true si la entrada se ha podido borrar con exito. False en caso contrario
@post Si esta en el conjunto su tamaño se decrementa en 1.
*/
	bool erase(const long int & id);
	/** @brief Borra una crimen con identificador dado por e.getID() en el conjunto.
Busca la entrada con id en el conjunto (o e.getID() en el segundo caso) y si la encuentra la borra

@param[in] entrada con e.getID() que geremos borrar, el resto de los valores no son tenidos en cuenta
@return true si la entrada se ha podido borrar con exito. False en caso contrario
@post Si esta en el conjunto su tamaño se decrementa en 1.
*/
	bool erase(const  conjunto::entrada & e);
/** @brief operador de asignacion
@param[in] org conjunto  a copiar.
 Crea un conjunto duplicado exacto de org.
*/
	conjunto & operator=( const conjunto<CMP> & org);
		/** @brief numero de entradas en el conjunto
@post  No se modifica el conjunto.
*/
	size_type size() const ;
	/** @brief Chequea si el conjunto esta vacio
   @return true si size()==0, false en caso contrario.
*/
	bool empty() const;
     /**@brief devuelve iterador al inicio del conjunto
     */
	iterator begin();
    /**@brief devuelve iterador al final (posicion siguiente al ultimo del conjunto)
     */
	iterator end();
     /**@brief devuelve iterador constante al inicio del conjunto
     */
	const_iterator cbegin() const;
    /**@brief devuelve iterador constante al final (posicion siguiente al ultimo del conjunto)
     */
	const_iterator cend() const;
	/**@brief devuelve un iterador al crimen que se le pasa comp parametro o al siguiente si no
	se encuentra en el conjunto
	*/
	iterator lower_bound(const conjunto::entrada &x);
	/**@brief devuelve un iterador constante al crimen que se le pasa comp parametro o al siguiente si no
	se encuentra en el conjunto
	@post no se modifica el conjunto
	*/
	const_iterator lower_bound(const conjunto::entrada &x) const;
	/**@brief devuelve un iterador al crimen siguente al que se le pase como parametro
 	*/
	iterator upper_bound(const conjunto::entrada &x);
	/**@brief devuelve un iterador constante al crimen siguente al que se le pase como parametro
 	*/
	const_iterator upper_bound(const conjunto::entrada &x)const;

	class iterator {
		public:
			/** @brief Constructor por defecto del iterador. */
		 iterator();
			/** @brief Constructor de copia.
	 		@param[in] it   */
       iterator (const iterator & it);
       /** @brief Operador * para acceder al contenido del iterador. */
       const conjunto::entrada & operator*() const;
       /** @brief Operador ++ para el postincremento del iterador. */
       iterator operator++( int );
     /** @brief Operador ++ para el preincremento. */
       iterator & operator++();
		 /** @brief Operador -- para el postdecremento del iterador. */
       iterator operator--(int);
/** @brief Operador -- para el predecremento del iterador. */
       iterator & operator--();
       /** @brief Operador == que comprueba si dos iteradores son iguales.
    	 @param[in] it iterador a comparar */
       bool operator==(const iterator & it);
       /** @brief Operador != que comprueba si dos iteradores son distintos.
		  @param[in] it iterador a comparar*/
       bool operator!=(const iterator & it);
     /** @brief Operador de asignacion
		 @param[in] it iterador a asignar */
		 iterator& operator=(const iterator & it);
       private:
           friend class conjunto<CMP>;
           vector<entrada>::iterator itv;

};

	class const_iterator {
		public:
			/** @brief Constructor por defecto del iterador. */
			const_iterator();
			/** @brief Constructor de copia.
	 		@param[in] it   */
	 		const_iterator(const const_iterator & it);
	 		/** @brief Convierte iterator en const_iterator
          */
	  		const_iterator(const iterator & it);
			/** @brief Operador * para acceder al contenido del iterador. */
	  		const conjunto::entrada & operator*() const;
	  		/** @brief Operador ++ para el postincremento del iterador. */
	  		const_iterator operator++( int );
	  		/** @brief Operador ++ para el preincremento. */
	  		const_iterator & operator++();
	  		/** @brief Operador -- para el postdecremento del iterador. */
 	  		const_iterator operator--(int);
 	  		/** @brief Operador -- para el predecremento del iterador. */
     		const_iterator & operator--();
  		   /** @brief Operador == que comprueba si dos iteradores son iguales.
    	   @param[in] it iterador a comparar */
	  		bool operator==(const const_iterator & it);
	  		/** @brief Operador != que comprueba si dos iteradores son distintos.
    	   @param[in] it iterador a comparar */
	  		bool operator!=(const const_iterator & it);
	  		/** @brief Operador de asignacion
		   @param[in] it iterador a asignar */
			const_iterator &operator=(const const_iterator & it);

		private:
	  		vector<entrada>::const_iterator c_itv;
	  		friend class conjunto<CMP>;
	};


};

//ostream &  operator << ( ostream & sal, const conjunto & D);
 

#include "conjunto.hxx"

#endif
