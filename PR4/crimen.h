/* 
 * meteorito.h
 * 
 * Copyright  (C) Juan F. Huete
*/
#ifndef __CRIMEN_H
#define __CRIMEN_H

#include <string>
#include <iostream> 

#include "fecha.h"
//! Clase crimen, asociada a la definición de un crimen 
/*! crimen::crimen,  .....

 *! Métodos --> crimen::crimen(), crimen::crimen(const crimen& x), 
setID(long int & id), setCaseNumber(const string &  s), 
setDate(const fecha & d), setIUCR(const string &IU), 
setPrimaryType(const string &PType), 
setDescription(const string &Desc), 
setLocationDescription(const string &LDesc), 
setLatitude(const double &lat), setLongitude(const double &longt),
setArrest(const bool a), setDomestic(const bool d), getID( ), getCaseNumber( ), 
getIUCR(), getDescription(), getPrimaryType(), getLocationDescription(), getArrest(),
getDomestic(), getLatitude(),
 getLongitude(), getDate( )

* Descripción 
* Contiene toda la información asociada a un crimen.

*/


class crimen {
 public:
	/** @brief Constructor primitivo.
	*/
  crimen();
	/** @brief Constructor de copia.
	@param[in] x objeto crimen a copiar */
  crimen(const crimen& x);
	/** @brief Establece la ID del crimen.
	@param[in] id ID */
  void setID(long int & id);
	/** @brief Establece el número de caso.
	@param[in] s Número del caso, formato string */
  void setCaseNumber(const string &  s);
	/** @brief Establece la fecha del crimen.
	@param[in] d objeto de la clase Fecha */
  void setDate(const fecha & d);
	/** @brief Establece la IUCR (Illinois Uniform Crime Reporting) del crimen.
	@param[in] IU IUCR,formato string */
  void setIUCR(const string &IU);
	/** @brief Establece tipo de delito.
	@param[in] PType Tipo de delito, formato string */
  void setPrimaryType(const string &PType);
	/** @brief Establece la descripción del crimen.
	@param[in] Desc Descripción en formato string */
  void setDescription(const string &Desc);
	/** @brief Establece la descripción del escenario del crimen.
	@param[in] LDesc Descripcion del escenario, formato string */
  void setLocationDescription(const string &LDesc);
	/** @brief Establece la latitud en la que se produjo el crimen.
	@param[in] lat Latitud */
  void setLatitude(const double &lat);
	/** @brief Establece la longitud en la que se produjo el crimen.
	@param[in] longt Longitud */
  void setLongitude(const double &longt);
	/** @brief Establece si se produjo un arresto.
	@param[in] a true si se produjo, false en caso contrario */
  void setArrest(const bool a);
	/** @brief Establece si fue crimen doméstico o no.
	@param[in] d true si lo fue, false en caso contrario */
  void setDomestic(const bool d); 

  
  	/** @brief Devuelve la ID del crimen.
	*/
  long int getID( ) const;
  	/** @brief Devuelve el número del caso.
	*/
  string getCaseNumber( ) const;
  	/** @brief Devuelve la IUCR del crimen.
	*/
  string getIUCR() const;
  	/** @brief Devuelve la descripción del crimen.
	*/
  string getDescription() const;
  	/** @brief Devuelve el tipo de delito.
	*/
  string getPrimaryType() const;
  	/** @brief Devuelve la descripción del escenario del crimen.
	*/
  string getLocationDescription() const;
  	/** @brief Devuelve si se produjo un arresto.
	@return true si hubo arresto, false en caso contrario*/
  bool getArrest() const;
  	/** @brief Devuelve si fue un crimen doméstico.
	@return true si fue doméstico, false en caso contrario*/
  bool getDomestic() const;
  	/** @brief Devuelve la latitud en la que se produjo el crimen.
	*/
  double getLatitude() const;
  	/** @brief Devuelve la longitud en la que se produjo el crimen.
	*/
  double getLongitude() const;
  	/** @brief Devuelve la fecha del crimen.
	@return devuelve un objeto de la clase Fecha*/
  fecha getDate( ) const;
  
  // -...

  	/** @brief Sobrecarga del operador de asignación.
	*/
   crimen & operator=(const crimen & c);
  	/** @brief Sobrecarga del operador ==.
	@return Devuelve true si la ID de dos casos es la misma, false en caso contrario.*/
   bool operator==(const crimen & x) const;
  	/** @brief Sobrecarga del operador <.
	@return Devuelve true si la ID es menor.*/
   bool operator<(const crimen & x) const;
 private:
  	/** @brief Sobrecarga de la salida estándar.
	@return Escribe cada uno de los atributos junto a su valor en una línea distinta.*/
   friend ostream& operator<< ( ostream& , const crimen& );
   //Atributos 
   long int ID; 
   string CaseNumber;
   fecha Date;
   string IUCR;
   string PrimaryType;
   string Description;
   string LocationDescription;
   bool Arrest;
   bool Domestic;
   double Latitude;
   double Longitude;

};

  ostream& operator<< ( ostream& , const crimen& );


#include "crimen.hxx"
#endif

