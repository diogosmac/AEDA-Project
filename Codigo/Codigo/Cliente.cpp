#include "Cliente.h"

Cliente::Cliente(string nome, int idade) : idCliente(proximoID++)
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
