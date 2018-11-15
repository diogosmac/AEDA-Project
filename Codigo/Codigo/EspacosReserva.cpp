#include "EspacosReserva.h"

Date::Date(size_t d, size_t m, size_t y) : day(d), month(m), year(y) {}

string Date::getDate() const {
	ostringstream oss;
	oss << getDay() << '/' << getMonth() << '/' << getYear();
	return oss.str();
}

// ----------------------------------------------------------

size_t Espaco::nextSpaceID = 0;

//-----------------------------------------------------------Espaco------------------------------------------------------------//

Espaco::Espaco() : numID(nextSpaceID++) {}

size_t Espaco::getNumID() const 
{
	return numID;
}

/*
ostream Espaco::getInfo()
{
	ostream out;
	out << numID << endl;
	return out;
}
*/
//-----------------------------------------------------------Quarto------------------------------------------------------------//


Quarto::Quarto(bool duplo, bool frente) : Espaco() 
{
	this->duplo = duplo;
	this->frente = frente;
}

double Quarto::getPrecoReservaDiario() const 
{

	return 50; //TO DO
}

bool Quarto::isDuplo() const 
{
	return this->duplo;
}

bool Quarto::isFrente() const 
{
	return this->frente;
}

//---------------------------------------------------------Sala Reunioes-------------------------------------------------------//

SalaDeReunioes::SalaDeReunioes(int capacidade, bool equipamentoVideo, bool equipamentoAudio) : Espaco() 
{

	this->capacidade = capacidade;
	this->equipamentoVideo = equipamentoVideo;
	this->equipamentoAudio = equipamentoAudio;
}


double SalaDeReunioes::getPrecoReservaDiario() const 
{
	return 50; // TO DO
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