#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Prato
{
	/**
	*	Nome do Prato
	*/
	string nome;

	/**
	*	Preco do Prato
	*/
	double preco;

public:

	/**
	*	Construtor da classe Prato
	*/
	Prato(string nome, double preco);

	/**
	*	Retorna o nome do prato
	*/
	string getNome() const;

	/**
	*	Retorna preco do prato
	*/
	double getPreco() const;

	/**
	*	Altera o preco do prato para o valor passado por argumento
	*/
	void setPreco(double novoPreco);

};

class Restaurante
{
	/**
	*	Nome do restaurante
	*/
	string nome;

	/**
	*	Tipo de restaurante
	*/
	string tipoCozinha;

	/**
	*	Vetor que contem todos os pratos que o restaurante tem disponivel no seu menu
	*/
	vector <Prato*> menu;

	/**
	*	Distancia ao hotel
	*/
	double distanciaHotel;
	
public:

	/**
	*	Contrutor da classe restaurante (sem menu)
	*/
	Restaurante(string nome, string tipoCozinha, double distanciaHotel);

	/**
	*	Construtor da classe restaurante (com menu)
	*/
	Restaurante(string nome, string tipoCozinha, vector<Prato *> menu, double distanciaHotel);

	/**
	*	Retorna o nome do restaurante
	*/
	string getNome() const;

	/**
	*	Retorna o tipo de restaurante
	*/
	string getTipoCozinha() const;

	/**
	*	Retorna o vetor com todos os pratos servidos no restaurante
	*/
	vector <Prato*> getMenu() const;

	/**
	*	Retorna distancia do restaurante ao hotel
	*/
	double getDistanciaHotel() const;

	/**
	*	Altera o membro-dado menu para o vetor passado como argumento
	*/
	void setMenu(vector <Prato*> menu);

	/**
	*	Adiciona um prato ao vetor menu do restaurante
	*/
	void adicionaPrato(Prato * novoPrato);

	/**
	*	Operador usado para ordenacao de objetos desta classe na arvore de pesquisa binaria (membro-dado da classe hotel)
	*/
	bool operator < (const Restaurante &rest) const;

};