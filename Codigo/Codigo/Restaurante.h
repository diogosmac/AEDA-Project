#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Prato
{
	string nome;
	double preco;

public:

	Prato(string nome, double preco);
	string getNome() const;
	double getPreco() const;
	void setPreco(double novoPreco);

};

class Restaurante
{
	string nome;
	string tipoCozinha;
	vector <Prato*> menu;
	double distanciaHotel;
	
public:

	Restaurante(string nome, string tipoCozinha, double distanciaHotel);
	Restaurante(string nome, string tipoCozinha, vector<Prato *> menu, double distanciaHotel);
	string getNome() const;
	string getTipoCozinha() const;
	vector <Prato*> getMenu() const;
	double getDistanciaHotel() const;
	void setMenu(vector <Prato*> menu);
	void adicionaPrato(Prato * novoPrato);
	bool operator < (const Restaurante &rest) const;

};