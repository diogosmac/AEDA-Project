#pragma once

#include <string>
#include <vector>

#include "EspacosReserva.h"

using namespace std;

class Funcionario 
{
	
    string nome;
    size_t ID_Code;
	bool supervisor_status;

public:

	/**
	*	Construtor Funcionarios
	*/
    Funcionario(string nome);

	/**
	*	Destrutor Funcionarios
	*/
	virtual ~Funcionario() {}

	/**
	*	Retorna nome funcionario
	*/
    string getNome() const;

	/**
	*	Retorna id funcionario
	*/
    size_t getID_Code() const;

	/**
	*	Torna funcionario um supervisor
	*/
	void makeSupervisor();

	/**
	*	Retorna se o funcionario é ou não supervisor
	*/
	bool isSupervisor() const;

	/**
	*	Adiciona um espaco ao vetor de espacos de que o funcionario está responsavel
	*/
	virtual void AcrescentaEspaco(Espaco* espaco) = 0;	// temporary solutions
	
	
	/**
	*	Remove todos os espacos do vetor de espacos de que o funcionario está responsavel
	*/
	virtual void RemoveEspacos() = 0;	

	/**
	*	Usado para exportar informação relativa ao objeto para ficheiros
	*/
	virtual ostream& operator >> (ostream& ofs);

private:
	static size_t nextWorkerID;

};

class Supervisor : public Funcionario 
{

    vector<Espaco *> Espacos;

public:

	/**
	*	Construtor Funcionarios
	*/
    Supervisor(string nome);

	/**
	*	Adiciona um espaco ao vetor de espacos de que o funcionario está responsavel
	*/
    void AcrescentaEspaco(Espaco* espaco);
    // void RemoveEspaco(size_t idEspaco);

	/**
	*	Remove todos os espacos do vetor de espacos de que o funcionario está responsavel
	*/
	void RemoveEspacos();

	/**
	*	Retorna um vetor com todos os espacos de que o funcionario é responsavel
	*/
	vector<Espaco *> getLocaisResponsavel() const;

	/**
	*	Usado para exportar informação relativa ao objeto para ficheiros
	*/
	ostream& operator >> (ostream& ofs);
	

};

class EspacoInexistente    // exception for function RemoveEspaco
{
    size_t num_ID;
public:
    EspacoInexistente(size_t idEspaco) { num_ID = idEspaco; }
    int getNumID() { return num_ID; }
};