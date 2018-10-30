#pragma once

#include <iostream>
#include "Funcionarios.h"
#include "EspacosReserva.h"
#include <vector>

using namespace std;

class Hotel
{
	vector<Espaco *> todosEspacos; //Contem todos os espacos que pertencem ao hotel
	vector<Espaco *> espacosDisponiveis; //Contem todos os espacos que se encontram disponiveis
	vector<Funcionario *> funcionarios; //Contem todos os funcionarios do hotel
	//TO DO: class cliente

public: 

	vector<Espaco *> getTodosEspacos() const;
	vector<Espaco *> getEspacosDisponiveis() const;
	vector<Funcionario *> getFuncionarios() const;
	double nEspacosDisponiveis();
	double lotacao();//Em percentagem
	void adicionaEspacoOcupado(Espaco * espaco);//Adiciona um espaco ao hotel (nao disponivel)
	void adicionaEspaco(Espaco * espaco);//Adiciona um espaco ao hotel
	void adicionaFuncionario(Funcionario * func); //Adiciona um funcionario ao vetor de funcionarios que trabalham no hotel
	void removeEspaco(size_t numID);
	void removeFuncionario(size_t ID_Code);
};

//-----------------------------------------------------------Exceptions--------------------------------------------------------//

class EspacoNaoPertenceHotel
{
	size_t num_ID;

public:

	EspacoNaoPertenceHotel(size_t num_ID);
	size_t getNumID() const;
};

class FuncionarioNaoTrabalhaHotel
{
	size_t ID_Code;

public:

	FuncionarioNaoTrabalhaHotel(size_t ID_Code);
	size_t getID_Code() const;
};