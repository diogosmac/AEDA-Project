#include "Hotel.h"

Hotel::Hotel() {
	Reservas r1(todosEspacos);
	reservas = r1;
}
vector<Espaco *> Hotel::getTodosEspacos() const
{
	return this->todosEspacos;
}

vector<Cliente *> Hotel::getClientes() const {
	return this->clientesHotel;
}

// vector<Espaco *> Hotel::getEspacosDisponiveis() const
// {
// 	return this->espacosDisponiveis;
// }

vector<Funcionario *> Hotel::getFuncionarios() const
{
	return this->funcionarios;
}

double Hotel::nEspacosDisponiveis(Date data)
{
	double contador = 0;
	for (size_t i = 0; i < this->todosEspacos.size(); i++)
	{
		if (!this->reservas.verificaEspaco(todosEspacos[i]->getNumID(), data))
			contador++;
	}
	return contador;
}

double Hotel::lotacao(Date data)
{
	return (this->nEspacosDisponiveis(data) / this->todosEspacos.size()) * 100;
}

// void Hotel::adicionaEspacoOcupado(Espaco * espaco)
// {
// 	this->todosEspacos.push_back(espaco);
// }

void Hotel::adicionaEspaco(Espaco * espaco)
{
	this->todosEspacos.push_back(espaco);
	reservas.updateReservas(espaco);

}

void Hotel::adicionaFuncionario(Funcionario * func)
{
	this->funcionarios.push_back(func);
	if (func->isSupervisor())
		this->supervisores.push_back(func);
}


void Hotel::removeEspaco(size_t numID)
{
	bool encontrado = false;

	// Remove do vetor todosEspacos. Caso nao encontre, da erro.
	for (size_t i = 0; i < this->todosEspacos.size(); i++)
	{
		if (todosEspacos.at(i)->getNumID() == numID)
		{
			if (!(reservas.temReservas(numID)(todosEspacos.at(i))))
			{
				todosEspacos.erase(todosEspacos.begin() + i);
				encontrado = true;
				reservas.removeEspaco(numID);
				break;
			}
		}
	}

	if (!encontrado)
	{
		throw EspacoNaoPertenceHotel(numID);
	}
}

void Hotel::removeFuncionario(size_t ID_Code)
{
	bool encontrado = false;

	// Remove funcionario. Caso nao o encontre, d� erro.
	for (size_t i = 0; i < this->funcionarios.size(); i++)
	{
		if (funcionarios.at(i)->getID_Code() == ID_Code)
		{
			funcionarios.erase(funcionarios.begin() + i);
			encontrado = true;
			break;
		}
	}

	if (!encontrado)
	{
		throw FuncionarioNaoTrabalhaHotel(ID_Code);
	}
}

double Hotel::nClientes() const
{
	return this->clientesHotel.size();
}

void Hotel::removeCliente(string nome, size_t idCliente)
{
	bool encontrado = false;

	for (size_t i = 0; i < this->clientesHotel.size(); i++)
	{
		if ((this->clientesHotel.at(i)->getNome() == nome) && (this->clientesHotel.at(i)->getIDCliente() == idCliente))
		{
			encontrado = true;
			this->clientesHotel.erase(this->clientesHotel.begin() + i);
		}
	}

	if (!encontrado)
	{
		throw ClienteNaoEncontrado(nome);
	}
}

bool Hotel::verificaCliente(string nome, size_t idade)
{
	for (size_t i = 0; i < this->clientesHotel.size(); i++)
	{
		if (this->clientesHotel.at(i)->getNome() == nome && this->clientesHotel.at(i)->getIdade() == idade)
		{
			return true;
		}
	}

	return false;
}

int Hotel::idCliente(string nome, size_t idade) {

	for (size_t i = 0; i < this->clientesHotel.size(); i++)
	{
		if (this->clientesHotel.at(i)->getNome() == nome && this->clientesHotel.at(i)->getIdade() == idade)
		{
			return clientesHotel.at(i)->getIDCliente();
		}
	}

	return -1;
}

void Hotel::adicionaCliente(string nome, size_t idade)
{
	if (!verificaCliente(nome, idade))
	{
		Cliente *c1 = new Cliente(nome, idade);
		this->clientesHotel.push_back(c1);
	}
}

Cliente * Hotel::encontraCliente(string nome) {
	for (size_t i = 0; i < clientesHotel.size(); i++) {
		if (clientesHotel.at(i)->getNome() == nome) {
			return clientesHotel.at(i);
		}
	}
	throw ClienteNaoEncontrado(nome);
}


// void Hotel::reservaEspaco(Espaco * espaco)
// {
// 	for (size_t i = 0; i < this->espacosDisponiveis.size(); i++)
// 	{
// 		if (espaco->getNumID() == this->espacosDisponiveis.at(i)->getNumID())
// 		{
// 			espacosDisponiveis.erase(espacosDisponiveis.begin() + i);
// 		}
// 	}
// }

void Hotel::alocaSupervisores() {
	for (size_t i = 0; i < supervisores.size(); i++) {
		supervisores.at(i)->RemoveEspacos();
	}

	for (size_t i = 0, j = 0; i < todosEspacos.size(); i++, j++) {
		if (j == supervisores.size()) {
			j = 0;
		}
		supervisores.at(j)->AcrescentaEspaco(todosEspacos.at(i));
	}
}


void Hotel::importInfo()
{
	/*

	ifstream ficheiro;
	string nomeFicheiro;

	cout << "Escreva o nome do ficheiro de onde pretende importar os dados" << endl;

	do
	{
		cin >> nomeFicheiro;
		ficheiro.open(nomeFicheiro);

		if (!ficheiro.is_open())
		{
			cerr << "Erro ao abrir o ficheiro, escreva novamente o nome do mesmo" << endl;
			cin.ignore(9999999, '\n');
			cin.clear();
		}

	}while(!ficheiro.is_open())

	*/
}

void Hotel::exportInfo()
{
	ofstream ficheiro;

	string nomeFicheiro;

	cout << "Escreva o nome do ficheiro de texto onde pretende guardar os dados" << endl;
	cout << "Nota: Caso o ficheiro com nome inserido ja existir, o mesmo sera substituido pelo novo" << endl;


	cin >> nomeFicheiro;

	if (nomeFicheiro.length() < 4 || nomeFicheiro.substr(nomeFicheiro.length() - 4, 4) != ".txt") {
		nomeFicheiro += ".txt";
	}

	ficheiro.open(nomeFicheiro);

	cin.ignore(9999999, '\n');
	cin.clear();

	if (!ficheiro.is_open())
	{
		cerr << "Erro opening file!" << endl;
		return;
	}

	//Escreve todos os clientes
	for (size_t i = 0; i < this->clientesHotel.size(); i++)
	{
		if (i == this->clientesHotel.size() - 1)
		{
			ficheiro << clientesHotel.at(i);
			ficheiro << '\n';
			cout << "Toda a informacao relativa aos clientes foi guardada com sucesso!" << endl;
		}
		else
		{
			ficheiro << clientesHotel.at(i);
		}
	}

}
