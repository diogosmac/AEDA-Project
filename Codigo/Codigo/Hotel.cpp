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