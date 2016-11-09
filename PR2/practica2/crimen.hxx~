#include "crimen.h"

void crimen::setID(long int &id){
  ID=id;
}

void crimen::setCaseNumber(const string &s){
  CaseNumber=s;
}

void crimen::setDate(const fecha &d){
  Date = d;
}

void crimen::setArrest(bool a){
  Arrest=a;
}

void crimen::setDomestic(bool d){
  Domestic=d;
}

long int getID() const{
  return ID;
}

string getCaseNumber() const{
  return CaseNumber;
}

fecha getDate() const{
  return Date;
}

bool operator==(const crimen & x) const{
  return ID==x.ID && IUCR==x.IUCR && Date==x.Date;
}

bool operator<(const crimen & x) const{
  return Date<x.Date;
}




