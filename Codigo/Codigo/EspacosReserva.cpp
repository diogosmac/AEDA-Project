#include "EspacosReserva.h"

Date::Date() {
	day = month = year = 0;
}

Date::Date(size_t d, size_t m, size_t y): year(y), month(m), day(d){
	if (!this->validDate())
		throw CriaDataInvalida(d, m, y);
}

Date::Date(string yearMonthDay)
{
	size_t y, m, d;
	d = stoi(yearMonthDay.substr(8));
	m = stoi(yearMonthDay.substr(5, 2));
	y = stoi(yearMonthDay.substr(0, 4));

	bool valid = false;
	if (y >= 2018) {
		if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
		{
			if (d > 0 && d <= 31)
				valid = true;
		}
		if (m == 4 || m == 6 || m == 9 || m == 11)
		{
			if (m > 0 && m <= 30)
				valid = true;
		}

		if (m == 2)
		{
			if (bissexto())
			{
				if (d > 0 && d <= 29)
					valid = true;
			}
			else
				if (d > 0 && d <= 28)
					valid = true;
		}

	}
	if (valid)
	{
		year = y;
		month = m;
		day = d;
	}
	else throw invalid_argument("Data invalida");
}


string Date::getDate() const {
	ostringstream oss;
	oss << getDay() << '/' << getMonth() << '/' << getYear();
	return oss.str();
}

void Date::increaseDay() 
{
	if (this->day == this->numDaysOfMonth())
	{
		this->day = 1;

		if (this->month == 12)
		{
			this->month = 1;
			this->year++;
		}
		else
		{
			this->month++;
		}
	}
	else
	{
		this->day++;
	}	
}

bool Date::bissexto()
{
	return((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}


bool Date::validDate (){
	if(year>=2018){
		if(month==1|| month==3||month==5||month==7||month==8||month==10||month==12)
		{
			if (day>0 && day<=31)
				return true;
		}
		if(month == 4 || month == 6 || month == 9 || month == 11)
		{
			if (month > 0 && month <= 30)
				return true;
		}

		if(month==2)
		{
			if(bissexto())
			{
				if(day>0&& day<=29)
					return true;
			}
			else
				if(day>0&& day<=28)
					return true;
		}

	}
	return false;
}

bool Date::isWeekend() {
	return(this->dayOfWeek() == 0 || this->dayOfWeek() == 1);
}

bool Date::isEpocaAlta() {
	return(this->getMonth() >= 5 && this->getMonth() <= 9);
}

size_t Date::numDaysOfMonth()
{
	switch (month)
	{
	case 1:case 3:case 5:case 7:case 8:case 10:case 12: return 31;
	case 4:case 6:case 9:case 11: return 30;
	case 2:
		if (bissexto())
			return 29;
		else
			return 28;
	}
	throw invalid_argument("Mes tem de ser um número entre 1 e 12");
}

size_t Date::dayOfWeek()
{
	size_t ds, s, a, c;
	s = year / 100;
	a = year % 100;

	int cTab[12][2] = { { 0,6 },{ 3,2 },{ 3,3 },{ 6,6 },{ 1,1 },{ 4,4 },{ 6,6 },{ 2,2 },{ 5,5 },{ 0,0 },{ 3,3 },{ 5,5 } };
	c = cTab[month - 1][bissexto()]; //bissexto restorna true, ou seja 1 no caso de um ano ser bissexto e retorna false, ou seja, 0 caso o ano nao seja bissesto

	ds = (((5 * a) / 4) + c + day - 2 * (s % 4) + 7) % 7;
	return ds;

}

bool Date::operator< (Date date2) 
{
	if (this->getYear() < date2.getYear()) 
	{
		return true;
	}
	else if (this->getYear() == date2.getYear() && this->getMonth() < date2.getMonth()) 
	{
		return true;
	}
	else if (this->getYear() == date2.getYear() && this->getMonth() == date2.getMonth() && this->getDay() < date2.getDay()) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool Date::operator== (Date date2) {
	return (this->getDay() == date2.getDay() && this->getMonth() == date2.getMonth() && this->getYear() == date2.getYear());
}

bool Date::operator> (Date date2) {
	return !(*this < date2 || *this == date2);
}

Date Date::operator+ (int offset) {
	Date d1;
	for (int i = 0; i < offset; i++) {
		Date aux1(day + 1, month, year);
		if (aux1.validDate())
			d1 = aux1;
		else {
			Date aux2(1, month + 1, year);
			if (aux2.validDate())
				d1 = aux2;
			else {
				Date aux3(1, 1, year + 1);
				d1 = aux3;
			}
		}
	}

	return d1;
}

// ----------------------------------------------------------------------------------------------------------------------------//

size_t Espaco::nextSpaceID = 1;

//-----------------------------------------------------------Espaco------------------------------------------------------------//

Espaco::Espaco() : numID(nextSpaceID++) {}

size_t Espaco::getNumID() const 
{
	return numID;
}

void Espaco::resetNextSpaceID()
{
	nextSpaceID = 1;
}

string Espaco::getOutputString() {
	ostringstream ofs;
	ofs << numID;
	return ofs.str();
}

ostream& operator << (ostream& ofs, Espaco* espaco)
{
	ofs << espaco->getOutputString();
	return ofs;
}

//-----------------------------------------------------------Quarto------------------------------------------------------------//


Quarto::Quarto(bool duplo, bool frente) : Espaco() 
{
	this->duplo = duplo;
	this->frente = frente;
}

double Quarto::getPrecoReservaDiario(Date data) const
{
	double precoDiario = 50;

	if (duplo)
	{
		precoDiario *= 2;
	}

	if (frente)
	{
		precoDiario = precoDiario + (precoDiario * 0.30);
	}

	if (data.isWeekend())
	{
		precoDiario *= 1.05;
	}

	if (data.isEpocaAlta())
	{
		precoDiario *= 1.2;
	}

	return precoDiario;
}

bool Quarto::isDuplo() const 
{
	return this->duplo;
}

bool Quarto::isFrente() const 
{
	return this->frente;
}

string Quarto::getOutputString() 
{
	ostringstream ofs;
	ofs << getNumID() << "; " << "Quarto - ";
	if (!duplo)
		ofs << "Single, ";
	else
		ofs << "Duplo, ";
	if (!frente)
		ofs << "Traseiras";
	else
		ofs << "Frente";

	return ofs.str();
}

//---------------------------------------------------------Sala Reunioes-------------------------------------------------------//

SalaDeReunioes::SalaDeReunioes(int capacidade, bool equipamentoVideo, bool equipamentoAudio) : Espaco() 
{

	this->capacidade = capacidade;
	this->equipamentoVideo = equipamentoVideo;
	this->equipamentoAudio = equipamentoAudio;
}


double SalaDeReunioes::getPrecoReservaDiario(Date data) const
{
	double precoDiario = 0;
	

	if (capacidade < 30)
	{
		precoDiario = 20;
	}
	else if (capacidade < 50)
	{
		precoDiario = 35;
	}
	else if (capacidade < 80)
	{
		precoDiario = 50;
	}
	else if (capacidade < 120)
	{
		precoDiario = 85;
	}
	else if (capacidade < 200)
	{
		precoDiario = 140;
	}
	else if (capacidade < 500)
	{
		precoDiario = 250;
	}
	else
	{
		precoDiario = 480;
	}

	if (equipamentoVideo)
	{
		precoDiario = precoDiario + (precoDiario * 0.2);
	}

	if (equipamentoAudio)
	{
		precoDiario = precoDiario + (precoDiario * 0.1);
	}

	if(data.isWeekend())
	{
		precoDiario *= 1.05;
	}

	if(data.isEpocaAlta())
	{
		precoDiario *= 1.2;
	}

	return precoDiario;
}

int SalaDeReunioes::getCapacidade() const 
{
	return this->capacidade;
}

bool SalaDeReunioes::getEquipamentoVideo() const 
{
	return this->equipamentoVideo;
}

bool SalaDeReunioes::getEquipamentoAudio() const 
{  
	return this->equipamentoAudio;
}

string SalaDeReunioes::getOutputString()
{
	ostringstream ofs;
	ofs << getNumID() << ";" << " Sala de Reunioes - " << capacidade << " pessoas, ";
	
	if (equipamentoVideo)
		ofs << "Com ";
	else
		ofs << "Sem ";

	ofs << "Video, ";
	
	if (equipamentoAudio)
		ofs << "Com ";
	else
		ofs << "Sem ";
	
	ofs << "Audio";
	
	return ofs.str();
}