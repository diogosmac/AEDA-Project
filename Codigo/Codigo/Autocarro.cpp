#include "Autocarro.h"


Autocarro::Autocarro(size_t id, size_t tamanho) : nLugares (tamanho)
{
	this->id = id;

	for (size_t i = 0; i < nLugares; i++)
	{
		lugares.push_back("Vazio");
	}
}


size_t Autocarro::getNLugaresLivres() const
{
	return nLugares - getNLugaresOcupados();
}


size_t Autocarro::getID() const
{
	return this->id;
}

size_t Autocarro::getCapacidade()
{
	return this->nLugares;
}


void Autocarro::incNLugaresOcupados()
{
	this->nLugaresOcupados++;
}

void Autocarro::setNLugares(size_t n)
{
	this->nLugares = n;

	vector <string> novoVetorLugares;

	for (size_t i = 0; i < n; i++)
	{
		novoVetorLugares.push_back("Vazio");
	}

	this->lugares = novoVetorLugares;
}

void Autocarro::setId(size_t newID)
{
	this->id = newID;
}

void Autocarro::setNameAt(size_t posicaoLugar, string nome)
{
	this->lugares.at(posicaoLugar - 1) = nome;
}

void Autocarro::clearLugares()
{
	for (size_t i = 0; i < this->lugares.size(); i++)
	{
		lugares.at(i) = "Vazio";
	}
}

size_t Autocarro::getNLugaresOcupados() const
{
	size_t counter = 0;

	for (size_t i = 0; i < lugares.size(); i++)
	{
		if (lugares.at(i) != "Vazio")
			counter++;
	}

	return counter;
}


bool Autocarro::adicionaNPessoas(size_t n)
{
	if (getNLugaresLivres() < n)
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i < n; i++)
		{
			string nome;
			cout << "Qual o nome da " << i + 1 << "a pessoa que pretende adicionar ao autocarro?";
			getline(cin, nome);

			while (!isalpha(nome.at(0)))
			{
				cout << "Nome invalido. Por favor insira devidamente o nome: ";
				getline(cin, nome);
			}
			cout << endl;

			for (size_t i = 0; i < lugares.size(); i++)
			{
				if (lugares.at(i) == "Vazio")
				{
					lugares.at(i) = nome;
					break;
				}
			}

			incNLugaresOcupados();
		}
			

		return true;
	}
}

bool Autocarro::operator < (const Autocarro &a) const
{
	return this->getNLugaresLivres() < a.getNLugaresLivres();
}

ostream& operator << (ostream& ofs, Autocarro a)
{
	ofs << '#' << a.getID() << ';' << ' ' << a.getCapacidade() << ';' << endl;

	for (size_t i = 0; i < a.lugares.size(); i++)
	{
		ofs << (i + 1) << '-' << a.lugares.at(i) << ';' << endl;
	}

	ofs << "-----" << endl;

	return ofs;
}