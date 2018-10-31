#include "Cliente.h"

int proximoID = 1;

Cliente::Cliente(string nome, int idade)
{
	this->nome = nome;
	this->idade = idade;

	//this->idCliente = proximoID;
	//proximoID++;
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


/*
int Cliente::getIDCliente() const
{
	return this->idCliente;
}
*/