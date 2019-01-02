#include "Funcionarios.h"

size_t Funcionario::nextWorkerID = 1;

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

void Funcionario::RemoveEspacos() {
	cerr << "Impossivel remover espacos deste funcionario, pois ele nao e supervisor!\n";
}

void Funcionario::AcrescentaEspaco(Espaco* espaco) {
	cerr << "Impossivel colocar o espaco #" << espaco->getNumID() << " a cargo deste funcionario, pois ele nao e supervisor!\n";
}

string Funcionario::getOutputString()
{
	ostringstream ofs;
	ofs << this->getID_Code() << "; " << this->getNome() << " - " << "Funcionario";
	return ofs.str();
}

ostream& operator << (ostream& ofs, Funcionario* func)
{
	ofs << func->getOutputString();
	return ofs;
}

void Funcionario::resetWorkerID()
{
	nextWorkerID = 1;
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

void Supervisor::RemoveEspacos() 
{
	this->Espacos.clear();
}

vector <Espaco *> Supervisor::getLocaisResponsavel() const 
{
	return this->Espacos;
}

string Supervisor::getOutputString()
{
	ostringstream ofs;
	ofs << this->getID_Code() << "; " << this->getNome() << " - " << "Supervisor - Responsavel pelos espacos: ";

	for (size_t i = 0; i < this->getLocaisResponsavel().size() - 1; i++)
	{
		ofs << this->getLocaisResponsavel().at(i)->getNumID() << " ";
	}
	if (!this->getLocaisResponsavel().empty())
		ofs << this->getLocaisResponsavel().at(this->getLocaisResponsavel().size() - 1)->getNumID();

	return ofs.str();
}
