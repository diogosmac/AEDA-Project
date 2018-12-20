#include "Restaurante.h"

	Prato::Prato(string nome, double preco)
	{
		this->nome = nome;
		this->preco = preco;
	}


	string Prato::getNome() const
	{
		return this->getNome();
	}


	double Prato::getPreco() const
	{
		return this->getPreco();
	}

	void Prato::setPreco(double novoPreco)
	{
		this->preco = novoPreco;
	}

//-------------------------------------------------------------------------------------------------------------------------------------------//

	Restaurante::Restaurante(string nome, string tipoCozinha, double distanciaHotel)
	{
		this->nome = nome;
		this->tipoCozinha = tipoCozinha;
		this->distanciaHotel = distanciaHotel;
	}

	Restaurante::Restaurante(string nome, string tipoCozinha, vector<Prato *> menu, double distanciaHotel)
	{
		this->nome = nome;
		this->tipoCozinha = tipoCozinha;
		this->menu = menu;
		this->distanciaHotel = distanciaHotel;
	}

	string Restaurante::getNome() const
	{
		return this->nome;
	}

	string Restaurante::getTipoCozinha() const
	{
		return this->tipoCozinha;
	}

	vector <Prato*> Restaurante::getMenu() const
	{
		return this->menu;
	}

	double Restaurante::getDistanciaHotel() const
	{
		return this->distanciaHotel;
	}

	void Restaurante::setMenu(vector <Prato*> menu)
	{
		this->menu = menu;
	}

	void Restaurante::adicionaPrato(Prato * novoPrato)
	{
		this->menu.push_back(novoPrato);
	}

	bool Restaurante::operator < (const Restaurante &rest) const
	{
		if (this->getTipoCozinha() == rest.getTipoCozinha())
		{
			return this->getDistanciaHotel() < rest.getDistanciaHotel();
		}
		
		return this->getTipoCozinha() < rest.getTipoCozinha();
		
	}
