#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "EspacosReserva.h"

using namespace std;

class Cliente
{
	static int nextClientID;
	int idCliente;
	string nome;
	int idade;
	vector<Espaco *> espacosReservados;

public:
	Cliente(string nome, int idade);
	string getNome() const;
	int getIdade() const;
	void adicionaEspacoReservado(Espaco * espaco);
	int getIDCliente() const;
	
};

int Cliente::nextClientID = 0;