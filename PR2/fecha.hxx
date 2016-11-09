/** @brief Implementacion de la clase fecha */
using namespace std;

//constructor por defecto
fecha::fecha(){

	sec = 0;
	min = 0;
	hour = 0;
	mday = 0;
	mon = 0;
	year = 0;
	
}

//constructor de copia
fecha::fecha(const fecha & x){

	sec = x.sec;
	min = x.min;
	hour = x.hour;
	mday = x.mday;
	mon = x.mon;
	year = x.year;

}

//constructor desde string
//s es una fecha con formato mm/dd/aaaa hh:mm:ss AM/PM
fecha::fecha (const string & s){
	string aux;
	int formato_hora;

	aux = s.substr(20,2);
	if (aux == "AM")
		formato_hora = 0;
	else
		formato_hora = 12;

	mon = stoi(s.substr(0,2));
	mday = stoi(s.substr(3,2));
	year = stoi(s.substr(6,4));
	hour = stoi(s.substr(11,2)) + formato_hora;
	min = stoi(s.substr(14,2));
	sec = stoi(s.substr(17,2));
}

//asignacion fecha-fecha
fecha & fecha::operator=(const fecha & f) {
	
	sec = f.sec;
	min = f.min;
	hour = f.hour;
	mday = f.mday;
	mon = f.mon;
	year = f.year;

	return *this;
}

//asignacion fecha-cadenaString
//s es una fecha con formato mm/dd/aaaa hh:mm:ss AM/PM
fecha & fecha::operator=(const string & s) {
	string aux;
	int formato_hora;

	aux = s.substr(20,2);
	if (aux == "AM")
		formato_hora = 0;
	else
		formato_hora = 12;

	mon = stoi(s.substr(0,2));
	mday = stoi(s.substr(3,2));
	year = stoi(s.substr(6,4));
	hour = stoi(s.substr(11,2)) + formato_hora;
	min = stoi(s.substr(14,2));
	sec = stoi(s.substr(17,2));

	return *this;
}

//devuelve una string con el formato mm/dd/aaaa hh:mm:ss AM/PM
string fecha::toString() const {

	string s;	
	
	s = to_string(mon) + '/' + to_string(mday) + '/' + to_string(year) + 
	    " " + to_string(hour) + ':' + to_string(min) + ':' + to_string(sec);

	return s;
}	


//Todos los operadores relacionales:
//==
bool fecha:: operator==(const fecha & f) const {
	
	bool son_iguales = sec == f.sec && min == f.min &&
							 hour == f.hour && mday == f.mday &&
							 mon == f.mon && year == f.year;
		
	return son_iguales;
}

//!=
bool fecha::operator!=(const fecha & f)const {
	return !(f==*this);
}

//<
bool fecha::operator<(const fecha & f) const {
	bool es_menor = true;

	if (year > f.year)
		es_menor = false;
	else if (mon > f.mon)
		es_menor = false;
	else if (mday > f.mday)
		es_menor = false;
	else if (hour > f.hour)
		es_menor = false;
	else if (min > f.min)
		es_menor = false;
	else if (sec >= f.sec)
		es_menor = false;


	return es_menor;
}

//>
 bool fecha::operator>(const fecha & f) const {
	bool es_mayor = true;

	if (year < f.year)
		es_mayor = true;
	else if (mon < f.mon)
		es_mayor = true;
	else if (mday < f.mday)
		es_mayor = true;
	else if (hour < f.hour)
		es_mayor = true;
	else if (min < f.min)
		es_mayor = true;
	else if (sec <= f.sec)
		es_mayor = false;

	return es_mayor;
}

//<=
bool fecha::operator<=(const fecha & f) const {
	bool es_menor_igual = true;

	if (year > f.year)
		es_menor_igual = false;
	else if (mon > f.mon)
		es_menor_igual = false;
	else if (mday > f.mday)
		es_menor_igual = false;
	else if (hour > f.hour)
		es_menor_igual = false;
	else if (min > f.min)
		es_menor_igual = false;
	else if (sec > f.sec)
		es_menor_igual = false;
		

		

	return es_menor_igual;
}

//>=
bool fecha::operator>=(const fecha & f) const {
	bool es_mayor_igual = true;

	if (year < f.year)
		es_mayor_igual = false;
	else if (mon < f.mon)
		es_mayor_igual = false;
	else if (mday < f.mday)
		es_mayor_igual = false;
	else if (hour < f.hour)
		es_mayor_igual = false;
	else if (min < f.min)
		es_mayor_igual = false;
	else if (sec < f.sec)
		es_mayor_igual = false;

	return es_mayor_igual;
}

//sobrecarga del operador de salida como funcion amiga
 ostream& operator<< ( ostream& os, const fecha & f){

	os << f.toString();

   return os;
 }



