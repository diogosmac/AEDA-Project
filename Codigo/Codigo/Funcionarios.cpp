#include "Funcionarios.h"

size_t Funcionario::nextWorkerID = 0;

//---------------------------------------------------------Funcionario--------------------------------------------------------//

Funcionario::Funcionario(string nome) : ID_Code(nextWorkerID++)
{
	this->nome = nome;
	supervisor_status = false;
}

string Funcionario::getNome() const 
{
	return this->nome;
}

size_t Funcionario::getID_Code() const 
{
	return this->ID_Code;
}

void Funcionario::makeSupervisor() 
{
	supervisor_status = true;
}

bool Funcionario::isSupervisor() const 
{
	return supervisor_status;
}

//----------------------------------------------------------Supervisor--------------------------------------------------------//

Supervisor::Supervisor(string nome) : Funcionario(nome) 
{
	this->makeSupervisor();
}

void Supervisor::AcrescentaEspaco(Espaco* espaco) 
{
	Espacos.push_back(espaco);
}

/*
void Supervisor::RemoveEspaco(size_t idEspaco) 
{
	for (size_t i = 0; i < this->Espacos.size(); i++) {
		if (this->Espacos.at(i)->getNumID() == idEspaco) {
			this->Espacos.erase(this->Espacos.begin() + i);
		}
	}
	throw EspacoInexistente(idEspaco);
}
*/

void Supervisor::RemoveEspacos() 
{
	this->Espacos.clear();
}

vector <Espaco *> Supervisor::getLocaisResponsavel() const 
{
	return this->Espacos;
}