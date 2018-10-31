#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "EspacosReserva.h"

using namespace std;

class Cliente
{
	//static int proximoID; 
	string nome;
	int idade;
	//int idCliente;
	vector<Espaco *> espacosReservados;

public:
	Cliente(string nome, int idade);
	string getNome() const;
	int getIdade() const;
	void adicionaEspacoReservado(Espaco * espaco);
	//int getIDCliente() const;
	
};