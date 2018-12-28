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
	*	Usado para exportar informação relativa ao objeto para ficheiros
	*/
	friend ostream& operator << (ostream& ofs, const Cliente *cliente);

	/**
	*	Usado para verificar igualdade (principalmente utilizado na class Hotel)
	*/
	bool operator==(const Cliente &c2) const;

private:
	static int nextClientID;
};