#include "EspacosReserva.h"

Date::Date(size_t d, size_t m, size_t y) : day(d), month(m), year(y) {}

string Date::getDate() const {
	ostringstream oss;
	oss << getDay() << '/' << getMonth() << '/' << getYear();
	return oss.str();
}

// ----------------------------------------------------------------------------------------------------------------------------//

size_t Espaco::nextSpaceID = 0;

//-----------------------------------------------------------Espaco------------------------------------------------------------//

Espaco::Espaco() : numID(nextSpaceID++) {}

size_t Espaco::getNumID() const 
{
	return numID;
}

ostream& Espaco::operator >> (ostream& ofs)
{
	ofs << "^" << this->getNumID() << ";" << endl;
	return ofs;
}
//-----------------------------------------------------------Quarto------------------------------------------------------------//


Quarto::Quarto(bool duplo, bool frente) : Espaco() 
{
	this->duplo = duplo;
	this->frente = frente;
}

double Quarto::getPrecoReservaDiario() const 
{
	double precoDiario = 50;

	if (isDuplo)
	{
		precoDiario *= 2;
	}

	if (isFrente)
	{
		precoDiario = precoDiario + (precoDiario * 0.30);
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

ostream& Quarto::operator >> (ostream& ofs)
{
	ofs << "%" << this->getNumID() << ";" << this->isDuplo() << ";" << this->isFrente() << ";" << endl;
	return ofs;
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
	else if (capacidade > 500)
	{
		precoDiario = 480;
	}

	if (getEquipamentoVideo)
	{
		precoDiario = precoDiario + (precoDiario * 0.2);
	}

	if (getEquipamentoAudio)
	{
		precoDiario = precoDiario + (precoDiario * 0.1);
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

ostream& SalaDeReunioes::operator >> (ostream& ofs)
{
	ofs << "@" << this->getNumID() << ";" << this->getCapacidade() << ";" << this->getEquipamentoVideo() << ";" << this->getEquipamentoAudio() << ";" << endl;
	return ofs;
}