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
	Reservas todasReservas;

public:

	Hotel(istream &ficheiro);
	size_t nEspacos() const;
	vector<Espaco *> getTodosEspacos() const;
	vector<Espaco *> getEspacosDisponiveis(Date data) const;
	vector<Cliente *> getClientes() const;
	vector<Funcionario *> getFuncionarios() const;
	double nEspacosDisponiveis(Date data);
	double lotacao(Date data); // Em percentagem
	// void adicionaEspacoOcupado(Espaco * espaco); // Adiciona um espaco ao hotel (nao disponivel)
	void adicionaEspaco(Espaco * espaco); // Adiciona um espaco ao hotel
	void adicionaFuncionario(Funcionario * func); // Adiciona um funcionario ao vetor de funcionarios que trabalham no hotel
	void removeEspaco(size_t numID);
	void removeFuncionario(size_t ID_Code);
	size_t nClientes() const;
	bool verificaCliente(string nome, size_t idade); // Retorna true se encontrar o cliente de nome = parametro, caso contrario, false
	int idCliente(string nome, size_t idade);
	void adicionaCliente(string nome, size_t idade);
	void removeCliente(string nome, size_t idCliente);
	Cliente * encontraCliente(string nome); // Retorna o objeto * objeto clinete com nome = parametro, se nao encontrar d� erro
	void efetuaReserva(Cliente * cliente, size_t idEspaco, Date inicio, Date fim); // Pretty obvious *-*; idade cliente >= 18, senao -> erro
	void reservaEspaco(size_t idEspaco, Reserva r1); // Nao deve ser usado, n faz verificacoes nenhumas; � chamado por efetuaReserva (apos verificaoes)
	void alocaSupervisores();
	// void atendeCliente();
	void exportInfo();
};
