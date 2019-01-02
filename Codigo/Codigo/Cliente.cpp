#include "Cliente.h"

int Cliente::nextClientID = 1;

//teste

Cliente::Cliente(string nome, int idade) : idCliente(nextClientID++)
{
	this->nome = nome;
	this->idade = idade;
	freqReserva = 0;
}

string Cliente::getNome() const
{
	return this->nome;
}

int Cliente::getIdade() const
{
	return this->idade;
}

int Cliente::getIDCliente() const
{
	return this->idCliente;
}

int Cliente::getFreqReserva() const
{
	return this->freqReserva;
}

void Cliente::registaReserva()
{
	freqReserva++;
}

ostream& operator << (ostream& ofs, const Cliente *cliente)
{
	ofs << cliente->getIDCliente() << "; " << cliente->getNome() << "; " << cliente->getIdade() << " anos; " << cliente->getFreqReserva() << " reservas feitas";
	return ofs;
}

bool Cliente::operator==(const Cliente &c2) const
{
	if ((this->getNome() == c2.getNome()) && (this->getIDCliente() == c2.getIDCliente()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Cliente::resetNextClientID()
{
	nextClientID = 1;
}