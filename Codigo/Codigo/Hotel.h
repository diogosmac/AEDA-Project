#pragma once

#include <iostream>
#include "Funcionarios.h"
#include "EspacosReserva.h"
#include "Cliente.h"
#include "Reservas.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Hotel
{
	vector<Espaco *> todosEspacos; // Contem todos os espacos que pertencem ao hotel
	//vector<Espaco *> espacosDisponiveis; // Contem todos os espacos que se encontram disponiveis
	vector<Funcionario *> funcionarios; // Contem todos os funcionarios do hotel
	vector<Funcionario *> supervisores; // Contem todos os supervisores do hotel
	vector<Cliente *> clientesHotel; // Contem todos os clientes do hotel
	Reservas reservas;

public:

	Hotel();
	vector<Espaco *> getTodosEspacos() const;
	//vector<Espaco *> getEspacosDisponiveis() const;
	vector<Cliente *> getClientes() const;
	vector<Funcionario *> getFuncionarios() const;
	double nEspacosDisponiveis(Date data);
	double lotacao(Date data); // Em percentagem
	// void adicionaEspacoOcupado(Espaco * espaco); // Adiciona um espaco ao hotel (nao disponivel)
	void adicionaEspaco(Espaco * espaco); // Adiciona um espaco ao hotel
	void adicionaFuncionario(Funcionario * func); // Adiciona um funcionario ao vetor de funcionarios que trabalham no hotel
	void removeEspaco(size_t numID);
	void removeFuncionario(size_t ID_Code);
	double nClientes() const;
	bool verificaCliente(string nome, size_t idade); // Retorna true se encontrar o cliente de nome = parametro, caso contrario, false
	int idCliente(string nome, size_t idade);
	void adicionaCliente(string nome, size_t idade);
	void removeCliente(string nome, size_t idCliente);
	Cliente * encontraCliente(string nome); // Retorna o objeto * objeto clinete com nome = parametro, se nao encontrar d� erro
	// void efetuaReserva(Cliente * cliente, Espaco * espaco); // Pretty obvious *-*; idade cliente >= 18, senao -> erro
	// void reservaEspaco(Espaco * espaco); // Nao deve ser usado, n faz verificacoes nenhumas; � chamado por efetuaReserva (apos verificaoes)
	void alocaSupervisores();
	void atendeCliente();
	void importInfo();
	void exportInfo();
};

// -----------------------------------------------------------Exceptions--------------------------------------------------------// 

class EspacoNaoPertenceHotel
{
	size_t num_ID;

public:

	EspacoNaoPertenceHotel(size_t id) {
		num_ID = id;
		cerr << "Espaco de ID:" << num_ID << " nao pertence ao hotel!" << endl;
	}
	size_t getNumID() const { return num_ID; }
};

class FuncionarioNaoTrabalhaHotel
{
	size_t ID_Code;

public:

	FuncionarioNaoTrabalhaHotel(size_t id) {
		ID_Code = id;
		cerr << "O Funcionario de id:" << ID_Code << " nao trabalha no hotel!" << endl;
	}
	size_t getID_Code() const { return ID_Code; }
};

class ClienteNaoEncontrado
{
	string nome;

public:

	ClienteNaoEncontrado(string nom) {
		nome = nom;
		cerr << "O cliente de nome " << this->nome << " nao consta da nossa lista de clientes!" << endl;
	}
	string getNome() const { return nome; }
};

class ClienteDemasiadoNovoReserva
{

	Cliente * cliente;

public:

	ClienteDemasiadoNovoReserva(Cliente * cli) {
		cliente = cli;
		cerr << "O Cliente de nome " << this->cliente->getNome() << " e demasiado novo para efetuar uma reserva!" << endl;
	}
	string getCliente() const { return cliente->getNome(); }
};

class EspacoNaoDisponivel
{

	size_t numID;

public:

	EspacoNaoDisponivel(size_t id) {
		numID = id;
		cerr << "O espaco de id = " << this->numID << " nao esta disponivel!" << endl;
	}
	size_t getNum_ID() const { return numID; }
};

class ReservasCoincidem
{
	size_t numID;

public:

	ReservasCoincidem(size_t id) {
		numID = id;
		cerr << "O espaco de id = " << this->numID << " ja tem uma reserva nesta data" << endl;
	}
	size_t getNum_ID() const { return numID; }
};

class ReservaNaoExiste
{
	size_t numID;

public:

	ReservaNaoExiste(size_t id) {
		numID = id;
		cerr << "O espaco de id = " << this->numID << " nao tem uma reserva nesta data" << endl;
	}
	size_t getNum_ID() const { return numID; }
};
