#include "Hotel.h"

vector<Espaco *> Hotel::getTodosEspacos() const
{
	return this->todosEspacos;
}

vector<Espaco *> Hotel::getEspacosDisponiveis() const
{
	return this->espacosDisponiveis;
}

vector<Funcionario *> Hotel::getFuncionarios() const
{
	return this->funcionarios;
}

double Hotel::nEspacosDisponiveis()
{
	return this->espacosDisponiveis.size();
}

double Hotel::lotacao()
{
	return (this->nEspacosDisponiveis() / this->todosEspacos.size()) * 100;
}

void Hotel::adicionaEspacoOcupado(Espaco * espaco)
{
	this->todosEspacos.push_back(espaco);
}

void Hotel::adicionaEspaco(Espaco * espaco)
{
	this->todosEspacos.push_back(espaco);
	this->espacosDisponiveis.push_back(espaco);
}

bool Hotel::verificaEspaco(Espaco * espaco)
{
	for (size_t i = 0; i < this->espacosDisponiveis.size(); i++)
	{
		if (this->espacosDisponiveis.at(i)->getNumID() == espaco->getNumID())
		{
			return true;
		}
	}

	return false;
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
			todosEspacos.erase(todosEspacos.begin() + i);
			encontrado = true;
			break;
		}
	}

	if (!encontrado)
	{
		throw EspacoNaoPertenceHotel(numID);
	}

	// Remove do vetor espacosDisponiveis, caso encontre.
	for (size_t i = 0; i < this->espacosDisponiveis.size(); i++)
	{
		if (espacosDisponiveis.at(i)->getNumID() == numID)
		{
			espacosDisponiveis.erase(espacosDisponiveis.begin() + i);
			break;
		}
	}

}

void Hotel::removeFuncionario(size_t ID_Code)
{
	bool encontrado = false;

	// Remove funcionario. Caso nao o encontre, dá erro.
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

void Hotel::adicionaCliente(Cliente * cliente)
{
	this->clientesHotel.push_back(cliente);
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

Cliente * Hotel::encontraCliente(string nome)
{

	for (size_t i = 0; i < this->clientesHotel.size(); i++)
	{
		if (this->clientesHotel.at(i)->getNome() == nome)
		{
			return this->clientesHotel.at(i);
		}
	}

	throw ClienteNaoEncontrado(nome);
	
}

bool Hotel::verificaCliente(string nome, size_t idCliente)
{
	for (size_t i = 0; i < this->clientesHotel.size(); i++)
	{
		if ((this->clientesHotel.at(i)->getNome() == nome) && (this->clientesHotel.at(i)->getIDCliente() == idCliente))
		{
			return true;
		}
	}

	return false;
}

void Hotel::reservaEspaco(Espaco * espaco)
{
	for (size_t i = 0; i < this->espacosDisponiveis.size(); i++)
	{
		if (espaco->getNumID() == this->espacosDisponiveis.at(i)->getNumID())
		{
			espacosDisponiveis.erase(espacosDisponiveis.begin() + i);
		}
	}
}

void Hotel::efetuaReserva(Cliente * cliente, Espaco * espaco)
{
	if (cliente->getIdade() >= 18)
	{

		if (!verificaCliente(cliente->getNome(), cliente->getIDCliente()))	// Caso o cliente ainda nao esteja na
		{																	// lista de clientes do hotel -> adicionado
			this->adicionaCliente(cliente);
		}

		if (this->verificaEspaco(espaco))			// Verifica se o espaco está disponivel,
		{											// caso contrario dá erro
			this->reservaEspaco(espaco);
		}
		else
		{
			throw EspacoNaoDisponivel(espaco->getNumID());
		}

		cliente->adicionaEspacoReservado(espaco);	// Guarda no objeto cliente o respetivo espaço reservado
				
	}
	else
	{
		throw ClienteDemasiadoNovoReserva(cliente);
	}
}

void Hotel::alocaSupervisores() 
{
	for (size_t i = 0; i < supervisores.size(); i++) 
	{
		supervisores.at(i)->RemoveEspacos();
	}

	for (size_t i = 0, j = 0; i < todosEspacos.size(); i++, j++) 
	{
		if (j == supervisores.size()) 
		{ 
			j = 0; 
		}
		supervisores.at(j)->AcrescentaEspaco(todosEspacos.at(i));
	}
}

void Hotel::atendeCliente()
{

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

	cout << "Escreva o nome do ficheiro onde pretende guardar os dados" << endl;
	cout << "Nota: Caso o ficheiro com nome inserido ja existir, o mesmo sera substituido pelo novo" << endl;

	
	cin >> nomeFicheiro;
	ficheiro.open(nomeFicheiro + ".txt");

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