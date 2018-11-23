#pragma once

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

	/**
	*	Contém a data de início da reserva
	*/
	Date inicio;

	/**
	*	Contém a data de fim da reserva
	*/
	Date fim;

	/**
	*	Contém o id do cliente que efetuou a reserva
	*/
	int idCliente;

public:

	/**
	*	Contrutor da class Reserva
	*/
	Reserva(int idCliente, Date &inicio, Date &fim);

	/**
	*	Retorna a data de início da reserva
	*/
	Date returnInicio() const;

	/**
	*	Retorna a data de fim da reserva
	*/
	Date returnFim() const;

	/**
	*	Retorna o id do cliente que efetuou a reserva
	*/
	int returnidCliente() const;

	/**
	*	Retorna true se as reservas forem incompativeis, isto é, se não puderem existir em simultâneo;
	*/
	bool operator - (Reserva& reserva2);

	/**
	*	Retorna true se as reservas forem iguais, isto é, se as datas de inicio e fim e o id do cliente em ambas forem iguais
	*/
	bool operator == (Reserva& reserva2);

	/**
	*	Usado para exportar toda a informação dos objetos desta class para ficheiros de texto
	*/
	friend ostream & operator << (ostream & out, const Reserva & r1);
};

class Reservas {

	/**
	*	Estrutura map que contém como primeiro elemento o id de um espaço e como segundo elemento um vetor de objetos da classe Reserva
	*/
	map <size_t, vector<Reserva>> reservasHotel;

public:

	/**
	*	Construtor da class Reservas (sem parâmetros)
	*/
	Reservas();

	/**
	*	Construtor da class Reservas
	*/
	Reservas(vector<Espaco *> espacos);

	/**
	*	Adiciona mais um espaço e respetivo vetor Reserva à estrutura map
	*/
	void updateReservas(Espaco * espaco);

	/**
	*	Remove um espaço e respetivo vetor Reserva da estrutura map
	*/
	void removeEspaco(size_t numID);

	/**
	*	Retorna a estrutura map que contém todas as reservas efetuadas
	*/
	map <size_t, vector<Reserva>> returnReservas();

	/**
	*	Adiciona uma reserva ao espaço com id numID
	*/
	bool adicionaReserva(size_t numID, Reserva r1);

	/**
	*	Remove a reserva passada como parâmetro do espaço com id numID
	*/
	bool removeReserva(size_t numID, Reserva r1);

	/**
	*	Altera a reserva rAntiga do espaço numID para a reserva rNova
	*/
	bool alteraReserva(size_t numID, Reserva rAntiga, Reserva rNova);

	/**
	*	Verifica se existe uma reserva igual a r1 no espaço de id numID.
	*	Caso exista retorna true, caso contrário retorna false
	*/
	bool reservaExiste(size_t numID, Reserva r1);

	/**
	*	Verifica se o espaço de id numID tem alguma reserva.
	*	Retorna true se estiver, caso contrário, retorna false.
	*/
	bool temReservas(size_t numID);

	/**
	*	Verifica se o espaço de id numID está ocupado na data d1.
	*	Retorna true se estiver, caso contrário, retorna false.
	*/
	bool verificaEspaco(size_t numID, Date d1) const;

	/**
	*	Mostra um calendário com a disponibilidade do espaço de id numID nesse mês
	*/
	void showMonth(size_t numId, size_t month, size_t year);

};

// -----------------------------------------------------------Exceptions--------------------------------------------------------// 

class EspacoNaoPertenceHotel
{
	/**
	*	Contém o numID do espaço inserido e que não pertence ao hotel
	*/
	size_t num_ID;

public:

	/**
	*	Contrutor da exceção
	*/
	EspacoNaoPertenceHotel(size_t id) {
		num_ID = id;
		cerr << "Espaco de ID:" << num_ID << " nao pertence ao hotel!" << endl;
	}

	/**
	*	Retorna o numID do espaço inserido e que não pertence ao hotel
	*/
	size_t getNumID() const { return num_ID; }
};

class FuncionarioNaoTrabalhaHotel
{
	/**
	*	Contém o id do funcionário inserido e que não pertence ao hotel
	*/
	size_t ID_Code;

public:

	/**
	*	Construtor da exceção
	*/
	FuncionarioNaoTrabalhaHotel(size_t id) {
		ID_Code = id;
		cerr << "O Funcionario de id:" << ID_Code << " nao trabalha no hotel!" << endl;
	}

	/**
	*	Retorna o id do funcionário inserido e que não pertence ao hotel
	*/
	size_t getID_Code() const { return ID_Code; }
};

class ClienteNaoEncontrado
{
	/**
	*	Contém o nome do Cliente inserido e que não foi encontrado
	*/
	string nome;

public:

	/**
	*	Contrutor da exceção
	*/
	ClienteNaoEncontrado(string nom) {
		nome = nom;
		cerr << "O cliente de nome " << this->nome << " nao consta da nossa lista de clientes!" << endl;
	}

	/**
	*	Retorna o nome do Cliente inserido e que não foi encontrado
	*/
	string getNome() const { return nome; }
};

class ClienteDemasiadoNovoReserva
{
	/**
	*	Nome do cliente que é demasiado novo para efetuar uma reserva
	*/
	string nome;

public:

	/**
	*	Contrutor da exceção
	*/
	ClienteDemasiadoNovoReserva(string nom) {
		nome = nom;
	}

	/**
	*	Retorna o nome do cliente que é demasiado novo para efetuar a reserva
	*/
	string getNome() const { return nome; }
};

class EspacoNaoDisponivel
{
	/**
	*	Contém o numID do espaço que não se encontra disponível
	*/
	size_t numID;

public:

	/**
	*	Construtor da exceção
	*/
	EspacoNaoDisponivel(size_t id) {
		numID = id;
	}
	/**
	*	Retorna o numID do espaço que não se encontra disponível
	*/
	size_t getNumID() const { return numID; }
};

class ReservasCoincidem
{
	/**
	*	Contém o numID do espaço que já tem uma reserva na data inserida
	*/
	size_t numID;

public:

	/**
	*	Construtor da exceção
	*/
	ReservasCoincidem(size_t id) {
		numID = id;
		cerr << "O espaco de id = " << this->numID << " ja tem uma reserva nesta data" << endl;
	}
	
	/**
	*	Retorna o numID do espaço que já tem uma reserva na data inserida
	*/
	size_t getNum_ID() const { return numID; }
};

class ReservaNaoExiste
{
	/**
	*	Contém o numID do espaço que não contém nenhuma reserva na data inserida
	*/
	size_t numID;

public:

	/**
	*	Construtor da exceção
	*/
	ReservaNaoExiste(size_t id) {
		numID = id;
		cerr << "O espaco de id = " << this->numID << " nao tem uma reserva nesta data" << endl;
	}

	/**
	*	Retorna o numID do espaço que não contém nenhuma reserva na data inserida
	*/
	size_t getNum_ID() const { return numID; }
};

class NaoHaSupervisores
{
	/**
	*	Contém o nome do Hotel onde não existe qualquer Supervisor.
	*/
	string nomeHotel;

public:

	/**
	*	Construtor da exceção
	*/
	NaoHaSupervisores(string nome) { nomeHotel = nome; }

	/**
	*	Retorna o nome do Hotel onde não existem Supervisores.
	*/
	string getNomeHotel() const { return nomeHotel; }
};

class DatasInvalidas
{
	/**
	*	Contém o id do Cliente que tentou fazer uma reserva com datas inválidas.
	*/
	int idCliente;

public:

	/**
	*	Construtor da exceção
	*/
	DatasInvalidas(int id_cli) { idCliente = id_cli; }

	/**
	*	Retorna o id do Cliente que tentou fazer a reserva inválida.
	*/
	int getIdCliente() const { return idCliente; }
};
