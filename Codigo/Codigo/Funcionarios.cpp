#include "Funcionarios.h"

//---------------------------------------------------------Funcionario--------------------------------------------------------//

Funcionario::Funcionario(string nome) : ID_Code(nextID++)
{
	this->nome = nome;
}

string Funcionario::getNome() const {
	return this->nome;
}

size_t Funcionario::getID_Code() const {
	return this->ID_Code;
}

//----------------------------------------------------------Supervisor--------------------------------------------------------//

Supervisor::Supervisor(string nome) : Funcionario(nome) {

}

void Supervisor::AcrescentaEspaco(size_t idEspaco) {
	// a implementar
	// vai ao objeto da class Hotel, à lista de espaços
}

void Supervisor::RemoveEspaco(size_t idEspaco) {
	for (size_t i = 0; i < this->Espacos.size(); i++) {
		if (this->Espacos.at(i)->getNumID() == idEspaco) {
			this->Espacos.erase(this->Espacos.begin() + i);
		}
	}
	throw EspacoInexistente(idEspaco);
}

vector <Espaco *> Supervisor::getLocaisResponsavel() const {
	return this->Espacos;
}