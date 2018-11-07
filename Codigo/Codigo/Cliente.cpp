#include "Cliente.h"

int Cliente::nextClientID = 0;

//teste

Cliente::Cliente(string nome, int idade) : idCliente(nextClientID++)
{
	this->nome = nome;
	this->idade = idade;
}

string Cliente::getNome() const
{
	return this->nome;
}

int Cliente::getIdade() const
{
	return this->idade;
}

void Cliente::adicionaEspacoReservado(Espaco * espaco)
{
	this->espacosReservados.push_back(espaco);
}


int Cliente::getIDCliente() const
{
	return this->idCliente;
}

ostream& operator << (ostream& ofs, const Cliente *cliente)
{
	ofs << "*" << cliente->nome << ';' << cliente->idade << ';' << cliente->idCliente << ";" << endl;
	return ofs;
}