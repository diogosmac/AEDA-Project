#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "EspacosReserva.h"

using namespace std;

class Cliente 
{

	int idCliente;
	string nome;
	int idade;
	int freqReserva;

public:

	/**
	*	Construtor da classe Cliente
	*/
	Cliente(string nome, int idade);

	/**
	*	Retorna o nome do cliente
	*/
	string getNome() const;

	/**
	*	Retorna a idade do cliente
	*/
	int getIdade() const;

	/**
	*	Retorna o id do cliente
	*/
	int getIDCliente() const;

	/**
	*	Retorna o numero de reservas colocadas pelo cliente
	*/
	int getFreqReserva() const;

	/**
	*	Incrementa o dado com o numero de reservas feitas pelo cliente
	*/
	void registaReserva();

	/**
	*	Faz freqReserva--
	*/
	void decNReservas();

	/**
	*	Usado para exportar informação relativa ao objeto para ficheiros
	*/
	friend ostream& operator << (ostream& ofs, const Cliente *cliente);

	/**
	*	Usado para verificar igualdade (principalmente utilizado na class Hotel)
	*/
	bool operator==(const Cliente &c2) const;

	/**
	*	Usado para verificar se um cliente é inferior a outro alfabeticamente
	*/
	bool operator<(const Cliente &c2) const;

	/**
	*	Usado para verificar se um cliente é superior a outro alfabeticamente
	*/
	//bool operator>(const Cliente &c2) const;

	/**
	*	Usado para verificar se um cliente é inferior a outro no que toca à sua frequencia de reservas
	*/
	//bool compFreq(const Cliente &c2) const;

	/**
	*	Usado para verificar se um cliente é superior a outro no que toca à sua frequencia de reservas
	*/
	//bool compFreq2(const Cliente &c2) const;

	/**
	*	Usado para verificar se um cliente é inferior a outro no que toca à sua idade
	*/
	//bool compIdade(const Cliente &c2) const;

	/**
	*	Usado para verificar se um cliente é superior a outro no que toca à sua idade
	*/
	//bool compIdade2(const Cliente &c2) const;

	/**
	*	Faz nextClientID = 1
	*/
	static void resetNextClientID();

	/**
	*	Faz nextClientID = novoID
	*/
	static void setNextClientID(int novoID);

	/**
	*	Retorna nextClientID
	*/
	static int getNextClientID();

	/**
	*	Torna idCliente = a id
	*/
	void setID(size_t id);

private:
	static int nextClientID;
};