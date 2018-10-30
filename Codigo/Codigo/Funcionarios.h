#pragma once

#include <string>
#include <vector>

#include "EspacosReserva.h"

using namespace std;

class Funcionario {

    string nome;
    size_t ID_Code;

public:

    Funcionario(string nome, size_t ID_Code);
    string getNome() const;
    size_t getID_Code() const;

};

class Supervisor : public Funcionario {

    vector<Espaco *> Espacos;

public:

    Supervisor(string nome, size_t ID_Code);
    void AcrescentaEspaco(size_t idEspaco);
    void RemoveEspaco(size_t idEspaco);
	vector<Espaco *> getLocaisResponsavel() const;

};

class EspacoInexistente {   // exception for function RemoveEspaco
    size_t num_ID;
public:
    EspacoInexistente(size_t idEspaco) { num_ID = idEspaco; }
    int getNumID() { return num_ID; }
};