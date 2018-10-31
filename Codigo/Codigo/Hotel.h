#pragma once

#include <iostream>
#include "Funcionarios.h"
#include "EspacosReserva.h"
#include "Cliente.h"
#include <vector>
#include <string>

using namespace std;

class Hotel
{
	vector<Espaco *> todosEspacos; //Contem todos os espacos que pertencem ao hotel
	vector<Espaco *> espacosDisponiveis; //Contem todos os espacos que se encontram disponiveis
	vector<Funcionario *> funcionarios; //Contem todos os funcionarios do hotel
	vector<Cliente *> clintesHotel; //Contem todos os clientes do hotel

public: 

	vector<Espaco *> getTodosEspacos() const;
	vector<Espaco *> getEspacosDisponiveis() const;
	vector<Funcionario *> getFuncionarios() const;
	double nEspacosDisponiveis();
	double lotacao();//Em percentagem
	void adicionaEspacoOcupado(Espaco * espaco);//Adiciona um espaco ao hotel (nao disponivel)
	void adicionaEspaco(Espaco * espaco);//Adiciona um espaco ao hotel
	bool verificaEspaco(Espaco * espaco);//Retorna true se encontrar um espaco disponivel = parametro, caso contratio, false
	void adicionaFuncionario(Funcionario * func); //Adiciona um funcionario ao vetor de funcionarios que trabalham no hotel
	void removeEspaco(size_t numID);
	void removeFuncionario(size_t ID_Code);
	double nClientes() const;
	void adicionaCliente(Cliente * cliente);
	void removeCliente(string nome /*Possivel de se adicionar tbm iD_Cliente*/);
	Cliente * encontraCliente(string nome); //Retorna o objeto * objeto clinete com nome = parametro, se nao encontrar dá erro
	bool verificaCliente(string nome); //Retorna true se encontrar o cliente de nome = parametro, caso contratio, false
	void efetuaReserva(Cliente * cliente, Espaco * espaco); //Pretty obvious *-*; idade cliente >= 18, senao -> erro
	void reservaEspaco(Espaco * espaco); //Nao deve ser usado, n faz verificacoes nenhumas; É chamado por efetuaReserva (apos verificaoes)
	//Distribuir Supervisores pelos espacos
	//Funcao atende cliente?
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

class ClienteNaoEncontrado
{
	string nome;

public:

	ClienteNaoEncontrado(string nome);
	string getNome() const;
};

class ClienteDemasiadoNovoReserva
{

	Cliente * cliente;

public:

	ClienteDemasiadoNovoReserva(Cliente * cliente);
	string getCliente() const;
};

class EspacoNaoDisponivel
{

	size_t numID;

public:

	EspacoNaoDisponivel(size_t numID);
	size_t getNum_ID() const;
};