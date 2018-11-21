#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "EspacosReserva.h"

using namespace std;

class Cliente {

	int idCliente;
	string nome;
	int idade;
	vector<Espaco *> espacosReservados;

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
	*	Adiciona um apontador para um espaco ao vetor espacosReservados
	*/
	void adicionaEspacoReservado(Espaco * espaco);

	/**
	*	Retorna o id do cliente
	*/
	int getIDCliente() const;

	/**
	*	Usado para exportar informação relativa ao objeto para ficheiros
	*/
	friend ostream& operator << (ostream& ofs, const Cliente *cliente);

private:
	static int nextClientID;
};