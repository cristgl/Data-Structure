/** @brief fichero de implementación de crimen
*/

#include "crimen.h"
using namespace std;
crimen::crimen()
:Date(){
	ID=0;
	CaseNumber="";
	IUCR="";
	PrimaryType="";
	Description="";
	LocationDescription="";
	Arrest=false;
	Domestic=false;
	Latitude=0;
	Longitude=0;

}

crimen::crimen(const crimen &x) 
:ID(x.ID),
CaseNumber(x.CaseNumber),
Date(x.Date),
IUCR(x.IUCR),
PrimaryType(x.PrimaryType),
Description(x.Description),
LocationDescription(x.LocationDescription),
Arrest(x.Arrest),
Domestic(x.Domestic),
Latitude(x.Latitude),
Longitude(x.Longitude)
{}

crimen & crimen::operator=(const crimen & x){
	ID=x.ID;
	CaseNumber=x.CaseNumber;
	Date=x.Date;
	IUCR=x.IUCR;
	PrimaryType=x.PrimaryType;
	Description=x.Description;
	LocationDescription=x.LocationDescription;
	Arrest=x.Arrest;
	Domestic=x.Domestic;
	Latitude=x.Latitude;
	Longitude=x.Longitude;
	
	return *this;
}

void crimen::setID(long int &id){
  ID=id;
}

void crimen::setCaseNumber(const string &s){
  CaseNumber=s;
}

void crimen::setDate(const fecha &d){
  Date = d;
}

void crimen::setIUCR(const string &IU){
     IUCR=IU;     
}

void crimen::setPrimaryType(const string &PType){
   PrimaryType=PType;     
}

void crimen::setDescription(const string &Desc){
     Description=Desc;
}

void crimen::setLocationDescription(const string &LDesc){
     LocationDescription=LDesc;
}

void crimen::setLatitude(const double &lat){
     Latitude=lat;
}

void crimen::setLongitude(const double &longt){
     Longitude=longt;
}

void crimen::setArrest(bool a){
  Arrest=a;
}

void crimen::setDomestic(bool d){
  Domestic=d;
}

long int crimen::getID() const{
  return ID;
}

string crimen::getCaseNumber() const{
  return CaseNumber;
}

fecha crimen::getDate() const{
  return Date;
}

string crimen::getIUCR() const{

	return IUCR;
}

string crimen::getDescription() const{

	return Description;
}

string crimen::getPrimaryType() const{
   return PrimaryType;
}

string crimen::getLocationDescription() const{
   return LocationDescription;
}

bool crimen::getArrest() const{
   return Arrest;
}

bool crimen::getDomestic() const{
   return Domestic;
}

double crimen::getLatitude() const{
   return Latitude;
}

double crimen::getLongitude() const{
   return Longitude;
}

bool crimen::operator==(const crimen & x) const{
  return ID==x.ID && IUCR==x.IUCR && Date==x.Date;
}

bool crimen::operator<(const crimen & x) const{
  return ID<x.ID;
}

ostream& operator<<(ostream &flujo, const crimen &c){
	flujo << "ID = " << c.getID() << "\n CaseNumber = " << c.getCaseNumber() << "\n Date = " << c.getDate() <<
    "\n IUCR = " << c.getIUCR() << "\n Description = " << c.getDescription() << "\n Primary Type = " << c.getPrimaryType() <<
    "\n Location Description = " << c.getLocationDescription() << "\n Arrest = " << c.getArrest() << "\n Domestic = " << c.getDomestic() <<
    "\n Latitude = " << c.getLatitude() << "\n Longitude = " << c.getLongitude() << endl;

	return flujo;
}

