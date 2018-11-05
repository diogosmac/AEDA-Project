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
	Cliente(string nome, int idade);
	string getNome() const;
	int getIdade() const;
	void adicionaEspacoReservado(Espaco * espaco);
	int getIDCliente() const;
	friend ostream& operator << (ostream& ofs, const Cliente *cliente);

private:
	static int nextClientID;
};