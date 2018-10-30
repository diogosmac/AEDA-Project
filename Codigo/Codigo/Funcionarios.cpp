#include "Funcionarios.h"

//---------------------------------------------------------Funcionario--------------------------------------------------------//

funcionario::funcionario(string nome, int idade)
{
	this->nome = nome;
	this->idade = idade;
}

string funcionario::getNome() const
{
	return this->nome;
}

int funcionario::getIdade() const
{
	return this->idade;
}

//----------------------------------------------------------Supervisor--------------------------------------------------------//

vector <espaco *> supervisor::getLocaisResponsavel() const
{
	return this->locaisResponsavel;
}