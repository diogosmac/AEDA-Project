#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include "EspacosReserva.h"
#include "Cliente.h"

using namespace std;

class Reserva {

private:
	Date inicio, fim;
	int idCliente;

public:
	Reserva(int idCliente, Date inicio, Date fim);
	Date returnInicio() const;
	Date returnFim() const;
	int returnidCliente();
	bool operator - (Reserva& reserva2); // retorna true se as reservas forem incompativeis, nao puderem existir em simultaneo;
	bool operator == (Reserva& reserva2);
	friend ostream & operator << (ostream & out, const Reserva & r1);
};

class Reservas {

	map <size_t, vector<Reserva>> reservasHotel;

public:
	Reservas();
	Reservas(vector<Espaco *> espacos);
	void updateReservas(Espaco * espaco);
	void removeEspaco(size_t numID);
	map <size_t, vector<Reserva>> returnReservas();
	bool adicionaReserva(size_t numID, Reserva r1);
	bool removeReserva(size_t numID, Reserva r1);
	bool alteraReserva(size_t numID, Reserva rAntiga, Reserva rNova);
	bool reservaExiste(size_t numID, Reserva r1);
	bool temReservas(size_t numID);
	bool verificaEspaco(size_t numID, Date d1) const;
	void showMonth(size_t numId, size_t month, size_t year);

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
