#pragma once

#include <iostream>
#include <vector>
#include "EspacosReserva.h"

using namespace std;

class funcionario
{
	string nome;
	int idade;

public:

	funcionario(string nome, int idade);
	string getNome() const;
	int getIdade() const;
};

class supervisor : public funcionario
{
	vector <espaco *> locaisResponsavel;

public:

	vector <espaco *> getLocaisResponsavel() const;

};