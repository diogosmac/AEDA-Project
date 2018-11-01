#pragma once

#include <string>
#include <vector>

#include "EspacosReserva.h"

using namespace std;

class Funcionario {
	
    string nome;
    size_t ID_Code;
	bool supervisor_status;

public:

    Funcionario(string nome);
    string getNome() const;
    size_t getID_Code() const;
	void makeSupervisor();
	bool isSupervisor() const { return isSupervisor; }

private:
	static size_t nextWorkerID;

};

class Supervisor : public Funcionario {

    vector<Espaco *> Espacos;

public:

    Supervisor(string nome);
    void AcrescentaEspaco(Espaco* espaco);
    void RemoveEspaco(size_t idEspaco);
	void RemoveTodosEspacos();
	vector<Espaco *> getLocaisResponsavel() const;

};

class EspacoInexistente {   // exception for function RemoveEspaco
    size_t num_ID;
public:
    EspacoInexistente(size_t idEspaco) { num_ID = idEspaco; }
    int getNumID() { return num_ID; }
};