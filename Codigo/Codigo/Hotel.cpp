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

void Hotel::removeCliente(string nome)
{
	bool encontrado = false;

	for (size_t i = 0; i < this->clientesHotel.size(); i++)
	{
		if (this->clientesHotel.at(i)->getNome() == nome)
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

bool Hotel::verificaCliente(string nome)
{
	for (size_t i = 0; i < this->clientesHotel.size(); i++)
	{
		if (this->clientesHotel.at(i)->getNome() == nome)
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

		if (!verificaCliente(cliente->getNome()))	// Caso o cliente ainda nao esteja na
		{											// lista de clientes do hotel -> adicionado
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