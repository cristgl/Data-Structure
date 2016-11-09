#ifndef __CONJUTO_H
#define __CONJUTO_H
#include <string>
#include <vector>
#include <iostream> 

/* 
 * conjunto.h
 * 
 * Copyright  (C) Juan F. Huete
*/
#include "crimen.h"

using namespace std;

//! Clase conjunto
/*! Metodos--> conjunto:: conjunto(), insert(), find(),  findIUCR(), findDESCR(), erase(), size(), empty()

 * Tipos--> conjunto::entrada, conjunto::size_type

 * Descripcion

* Un conjunto es un contenedor que permite almacenar en orden creciente un conjunto de elementos no repetidos.  En nuestro caso el conjunto va a tener un subconjunto restringido de metodos (insercion de elementos, consulta de un elemento, etc). Este conjunto "simulara" un conjunto de la stl, con algunas claras diferencias pues, entre otros,  no estara dotado de la capacidad de iterar (recorrer) a traves de sus elementos.

* Asociado al conjunto, tendremos el tipo  \code conjunto::entrada \endcode que permite hacer referencia al elemento  almacenados en cada una de las posiciones del conjunto, en nuestro caso delitos (crimenes). Para esta entrada el requisito es que tenga definidos el operador< y operator=

* Ademas encontraremos el tipo \code conjunto::size_type \endcode que permite hacer referencia al numero de elementos en el conjunto.

* El numero de elementos en el conjunto puede variar dinamicamente; la gestion de la memoria es automatica. 
 
 Ejemplo de su uso:
\code
...
conjunto DatosChicago, agresion;
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


class conjunto
{  
private:
	vector<crimen> vc;
	 /** \invariant
 
 IR: rep ==> bool
 
\li Para todo i, 0 <= i < vc.size() se cumple
	vc[i].ID > 0;
\li Para todo i, 0 <= i <= D.dic.size()-1 se cumple
	vc[i].ID< vc[i+1].ID

*/

	
  /** @brief Chequea el Invariante de la representacion 
      @return true si el invariante es correcto, falso en caso contrario
*/
	bool cheq_rep( ) const;
	friend ostream &  operator << ( ostream & sal, const conjunto & D);
	friend class iterator;
	friend class const_iterator;

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
	conjunto (const conjunto & d);
//declaraciones previa de los iteradores
	class iterator;  
  	class const_iterator;
  	class arrest_iterator;
	class const_arrest_iterator;
  	class description_iterator;
 	class const_description_iterator;
/** @brief busca un crimen en el conjunto
	@param id identificador del crimen  buscar
	@return Si existe una entrada en el conjunto devuelve un iterador a la posicion donde esta el elemento. Si  no se encuentra devuelve end()
	@post no modifica el conjunto.
	\code Ejemplo
       

	if (C.find(12345)!=C.end() ) cout << "Esta" ;
	else cout << "No esta";
	\endcode
	*/
	iterator  find( const long int & id);
	/** @brief busca un crimen en el conjunto
	@param id identificador del crimen  buscar
	@return Si existe una entrada en el conjunto devuelve un iterador a lo posicion donde esta el elemento. Si  no se encuentra devuelve end()
	@post no modifica el conjunto.
	\code Ejemplo
       

	if (C.find(12345)!=C.end() ) cout << "Esta" ;
	else cout << "No esta";
	\endcode
	*/
	const_iterator  find( const long int & id) const;
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
	conjunto   findDESCR( const string & descr) const;
/** @brief Inserta una entrada en el conjunto
@param e entrada a insertar
@return true si la entrada se ha podido insertar con exito. False en caso contrario
@post 	 Si e no esta en el conjunto, el size() sera incrementado en 1.
*/
	bool insert( const conjunto::entrada & e);
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
	conjunto & operator=( const conjunto & org);
		/** @brief numero de entradas en el conjunto
@post  No se modifica el conjunto.
*/
	size_type size() const ;
	/** @brief Chequea si el conjunto esta vacio
   @return true si size()==0, false en caso contrario.
*/
	bool empty() const;
	
	
// ================================= ITERADORES ========================================/

     /**@brief devuelve iterador al inicio del conjunto
     */
   iterator begin();
    /**@brief devuelve iterador al final (posicion siguiente al ultimo del conjunto)
     */
   iterator end();
   	/** @brief  
         @return Devuelve el const_iterator a la primera posicion del conjunto.
	@post no modifica el diccionario
        */
	const_iterator cbegin() const;
		/** @brief iterador al final
         @return Devuelve el iterador constante a la  posicion final del conjunto.
	@post no modifica el diccionario
        */
	const_iterator cend() const;
	 
	/**   @brief devolver primera posicion del elemento que empareja con la descripcion descr
	@param[in] descr descripcion de buscamos
	@return un iterador que apunta a la primera posicion, el emparejamiento se hace teniendo en cuenta que descr debe ser una subcadena de la descripcion del delito.
	*/
	description_iterator dbegin(const string & descr);
		 /**   @brief devolver fin del conjunto
	@return un iterador que apunta a la posicion final
	*/
	description_iterator dend( );
		/**   @brief devolver primera posicion del elemento que empareja con la descripcion descr
	@param[in] descr descripcion de buscamos
	@return un iterador constante que apunta a la primera posicion, el emparejamiento se hace teniendo en cuenta que descr debe ser una subcadena de la descripcion del delito.
	*/
	const_description_iterator cdbegin(const string & descr) const;
			 /**   @brief devolver fin del conjunto
	@return un iterador constante que apunta a la posicion final
	*/
	const_description_iterator cdend() const;
	 /**@brief devuelve iterador al primer crimen con arresto del conjunto
     */
	arrest_iterator abegin();
	/**@brief devuelve iterador al final (posicion siguiente al ultimo del conjunto)
     */
	arrest_iterator aend();
	/**@brief devuelve iterador constante al primer crimen con arresto del conjunto
     */
	const_arrest_iterator cabegin() const;
	/**@brief devuelve iterador constante al final (posicion siguiente al ultimo del conjunto)
     */
	const_arrest_iterator caend() const;
	
 	/** @brief class iterator
	 * forward iterador sobre el conjunto, LECTURA
	 *  iterator() ,operator*(), operator++, operator++(int) operator=, operator==, operator!=
	 * */
	class iterator {
		public:       
			/** @brief Constructor por defecto del iterador. */
			iterator();
			/** @brief Constructor de copia.
	 		@param[in] it   */
      	iterator (const iterator & it);
       /** @brief Operador * para acceder al contenido del iterador. */
       const entrada & operator*() const;
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
		 iterator & operator=(const iterator & it);
       private:
           friend class conjunto;
           vector<entrada>::iterator itv;
	};

	/** @brief class const_iterator
	 * forward iterador constante sobre el diccionario, Lectura 
	 *  const_iterator ,operator*, operator++, operator++(int) operator=, operator==, operator!=
	 * */
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
			const_iterator & operator=(const const_iterator & it);
		private:
	  		vector<entrada>::const_iterator c_itv;
	  		friend class conjunto;
	  
	};
/** @brief class description_iterator
	 * forward iterador constante sobre el diccionario, Lectura 
	 *  const_iterator ,operator*, operator++, operator++(int) operator=, operator==, operator!=
         * esta clase itera sobre todos los elementos que emparejan con una descripcion
	 * */
	class description_iterator {
	public:
     /** @brief Constructor por defecto del iterador. */
	  description_iterator();
	  /** @brief Constructor de copia.
	 		@param[in] it   */
	  description_iterator(const description_iterator & it);
      /** @brief Operador * para acceder al contenido del iterador. */
	 	const conjunto::entrada & operator*() const;
	 	/** @brief Operador ++ para el postincremento del iterador. */
		description_iterator operator++( int );
		/** @brief Operador ++ para el preincremento. */
		description_iterator & operator++();
		/** @brief Operador -- para el postdecremento del iterador. */
		description_iterator operator--(int);
		/** @brief Operador -- para el predecremento del iterador. */
		description_iterator & operator--();
		/** @brief Operador == que comprueba si dos iteradores son iguales.
    	   @param[in] it iterador a comparar */
		bool operator==(const description_iterator & it);
		/** @brief Operador != que comprueba si dos iteradores son distintos.
    	   @param[in] it iterador a comparar */
		bool operator!=(const description_iterator & it);
		/** @brief Operador de asignacion
		   @param[in] it iterador a asignar */
		description_iterator & operator=(const description_iterator & it);
	private:
		const vector<entrada>* mi_conj;
		string descr;// se asigna en dbegin()
		vector<entrada>::iterator itv;
		friend class conjunto;
	 
	};
/** @brief class const_description_iterator
	 * forward iterador constante sobre el diccionario, Lectura 
	 *  const_iterator ,operator*, operator++, operator++(int) operator=, operator==, operator!=
         * esta clase itera sobre todos los elementos que emparejan con una descripcion
	 * */
	class const_description_iterator {
	public:
 	   /** @brief Constructor por defecto del iterador. */
		const_description_iterator();
		/** @brief Constructor de copia.
	 		@param[in] it   */
		const_description_iterator(const const_description_iterator & it);   
		/** @brief Convierte description_iterator en const_description_iterator
          */
		const_description_iterator(const description_iterator & it);
		/** @brief Operador * para acceder al contenido del iterador. */
	 	const conjunto::entrada & operator*() const;
	 	/** @brief Operador ++ para el postincremento del iterador. */
		const_description_iterator operator++( int );
		/** @brief Operador ++ para el preincremento. */
		const_description_iterator & operator++();
		/** @brief Operador -- para el postdecremento del iterador. */
		const_description_iterator operator--(int);
		/** @brief Operador -- para el predecremento del iterador. */
		const_description_iterator & operator--();
		/** @brief Operador == que comprueba si dos iteradores son iguales.
    	   @param[in] it iterador a comparar */
		bool operator==(const const_description_iterator & it);
		/** @brief Operador != que comprueba si dos iteradores son distintos.
    	   @param[in] it iterador a comparar */
		bool operator!=(const const_description_iterator & it);
			/** @brief Operador de asignacion
		   @param[in] it iterador a asignar */
		const_description_iterator & operator=(const const_description_iterator & it);
	private:
		const vector<entrada>* mi_conj;
		string descr;// se asigna en cdbegin()
		vector<conjunto::entrada>::const_iterator c_itv;
		friend class conjunto;
	};
/** @brief class arrest_iterator
	 * forward iterador constante sobre el conjunto, Lectura 
	 *  const_iterator ,operator*, operator++, operator++(int) operator=, operator==, operator!=
	 * */
	class arrest_iterator {
		public:
		   /** @brief Constructor por defecto del iterador. */
			arrest_iterator();
			/** @brief Constructor de copia.
	 		@param[in] it   */
			arrest_iterator(const arrest_iterator & it);
			/** @brief Operador * para acceder al contenido del iterador. */
			const conjunto::entrada & operator*() const;
			/** @brief Operador ++ para el postincremento del iterador. */
			arrest_iterator operator++(int);
			/** @brief Operador ++ para el preincremento. */
			arrest_iterator & operator++();
			/** @brief Operador -- para el predecremento del iterador. */
			arrest_iterator & operator--();
			/** @brief Operador -- para el postdecremento del iterador. */
			arrest_iterator operator--(int);
			/** @brief Operador == que comprueba si dos iteradores son iguales.
    	   @param[in] it iterador a comparar */
			bool operator==(const arrest_iterator & it);
			/** @brief Operador != que comprueba si dos iteradores son distintos.
    	   @param[in] it iterador a comparar */
			bool operator!=(const arrest_iterator & it);
			/** @brief Operador de asignacion
		   @param[in] it iterador a asignar */
			arrest_iterator & operator=(const arrest_iterator & it);
		private:
			const vector<entrada>* mi_conj;
			vector<conjunto::entrada>::iterator itv;
			friend class conjunto;
	};
/** @brief class const_arrest_iterator
	 * forward iterador constante sobre el conjunto, Lectura 
	 *  const_iterator ,operator*, operator++, operator++(int) operator=, operator==, operator!=
	 * */
	class const_arrest_iterator{
		public:
			const_arrest_iterator();
			const_arrest_iterator(const const_arrest_iterator & it);
			/** @brief Convierte arrest_iterator en const_arrest_iterator
          */
			const_arrest_iterator(const arrest_iterator & it);
			/** @brief Operador * para acceder al contenido del iterador. */
			const conjunto::entrada & operator*() const;
			/** @brief Operador ++ para el postincremento del iterador. */
			const_arrest_iterator operator++(int);
			/** @brief Operador ++ para el preincremento. */
			const_arrest_iterator & operator++();
			/** @brief Operador -- para el predecremento del iterador. */
			const_arrest_iterator & operator--();
			/** @brief Operador -- para el postdecremento del iterador. */
			const_arrest_iterator operator--(int);
			/** @brief Operador == que comprueba si dos iteradores son iguales.
    	   @param[in] it iterador a comparar */
			bool operator==(const const_arrest_iterator & it);
			/** @brief Operador != que comprueba si dos iteradores son distintos.
    	   @param[in] it iterador a comparar */
			bool operator!=(const const_arrest_iterator & it);	
			/** @brief Operador de asignacion
		   @param[in] it iterador a asignar */
			const_arrest_iterator & operator=(const const_arrest_iterator & it);
		private:
			const vector<entrada>* mi_conj;
			vector<conjunto::entrada>::const_iterator c_itv;
			friend class conjunto;
	};
};

/** @brief imprime todas las entradas del conjunto 
@post  No se modifica el conjunto.
@todo implementar esta funcion
	*/
ostream &  operator << ( ostream & sal, const conjunto & D);
 

#include "conjunto.hxx"

#endif
