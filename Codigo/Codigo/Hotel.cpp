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

EspacoNaoPertenceHotel::EspacoNaoPertenceHotel(size_t num_ID)
{
	this->num_ID = num_ID;
	cerr << "Espaco de id:" << num_ID << " nao pertence ao hotel!" << endl;
	getNumID();
}

size_t EspacoNaoPertenceHotel::getNumID() const
{
	return this->num_ID;
}

void Hotel::removeEspaco(size_t numID)
{
	bool encontrado = false;

	//Remove do vetor todosEspacos, caso n encontre dá erro.
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

	//Remove do vetor espacosDisponiveis, caso encontre.
	for (size_t i = 0; i < this->espacosDisponiveis.size(); i++)
	{
		if (espacosDisponiveis.at(i)->getNumID() == numID)
		{
			espacosDisponiveis.erase(espacosDisponiveis.begin() + i);
			break;
		}
	}

}

FuncionarioNaoTrabalhaHotel::FuncionarioNaoTrabalhaHotel(size_t ID_Code)
{
	this->ID_Code = ID_Code;
	cerr << "O Funcionario de id:" << ID_Code << " nao trabalha no hotel!" << endl;
	getID_Code();
}

size_t FuncionarioNaoTrabalhaHotel::getID_Code() const
{
	return this->ID_Code;
}

void Hotel::removeFuncionario(size_t ID_Code)
{
	bool encontrado = false;

	//Remove funcionario, caso n o encontre dá erro.
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

ClienteNaoEncontrado::ClienteNaoEncontrado(string nome)
{
	this->nome = nome;
	cerr << "O cliente de nome " << this->nome << " nao consta na nossa lista de clientes!" << endl;
	this->getNome();
}

string ClienteNaoEncontrado::getNome() const
{
	return this->nome;
}

double Hotel::nClientes() const
{
	return this->clintesHotel.size();
}

void Hotel::adicionaCliente(Cliente * cliente)
{
	this->clintesHotel.push_back(cliente);
}

void Hotel::removeCliente(string nome)
{
	bool encontrado = false;

	for (size_t i = 0; i < this->clintesHotel.size(); i++)
	{
		if (this->clintesHotel.at(i)->getNome() == nome)
		{
			encontrado = true;
			this->clintesHotel.erase(this->clintesHotel.begin() + i);
		}
	}

	if (!encontrado)
	{
		throw ClienteNaoEncontrado(nome);
	}
}

Cliente * Hotel::encontraCliente(string nome)
{

	for (size_t i = 0; i < this->clintesHotel.size(); i++)
	{
		if (this->clintesHotel.at(i)->getNome() == nome)
		{
			return this->clintesHotel.at(i);
		}
	}

	throw ClienteNaoEncontrado(nome);
	
}

bool Hotel::verificaCliente(string nome)
{
	for (size_t i = 0; i < this->clintesHotel.size(); i++)
	{
		if (this->clintesHotel.at(i)->getNome() == nome)
		{
			return true;
		}
	}

	return false;
}

ClienteDemasiadoNovoReserva::ClienteDemasiadoNovoReserva(Cliente * cliente)
{
	this->cliente = cliente;
	cerr << "O Cliente de nome " << this->cliente->getNome() << " e demasiado novo para efutuar uma reserva!" << endl;
	this->getCliente();
}

string ClienteDemasiadoNovoReserva::getCliente() const
{
	return this->cliente->getNome();
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

EspacoNaoDisponivel::EspacoNaoDisponivel(size_t numID)
{
	this->numID = numID;
	cerr << "Espaco de id = " << this->numID << " nao esta disponivel!" << endl;
	getNum_ID();
}

size_t EspacoNaoDisponivel::getNum_ID() const
{
	return this->numID;
}

void Hotel::efetuaReserva(Cliente * cliente, Espaco * espaco)
{
	if (cliente->getIdade() >= 18)
	{

		if (!verificaCliente(cliente->getNome()))//Caso ainda o cliente ainda n esteja na lista de clientes do hotel -> adicionado
		{
			this->adicionaCliente(cliente);
		}

		if (this->verificaEspaco(espaco))//Verifica se o espaco está disponivel, caso contrario dá erro
		{
			this->reservaEspaco(espaco);
		}
		else
		{
			throw EspacoNaoDisponivel(espaco->getNumID());
		}

		cliente->adicionaEspacoReservado(espaco);//Guarda no objeto cliente o respetivo espaço reservado
				
	}
	else
	{
		throw ClienteDemasiadoNovoReserva(cliente);
	}
}