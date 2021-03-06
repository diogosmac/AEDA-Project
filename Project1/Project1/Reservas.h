#pragma once

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include "EspacosReserva.h"
#include "Cliente.h"
#include "Hotel.h"

using namespace std;

class Reserva {

private:
	Date inicio, fim;
	int idCliente;

public:
	Reserva(string nome, size_t idade, Date inicio, Date fim, Hotel h);
	Date returnInicio();
	Date returnFim();
	int returnidCliente();
	bool operator - (Reserva& reserva2) const; // retorna true se as reservas forem incompativeis, nao puderem existir em simultaneo;
	bool operator == (Reserva& reserva2) const;
};

class Reservas {

	map <size_t, vector<Reserva>> reservasHotel;

public:
	Reservas(Hotel h);
	void updateReservas(Espaco * espaco);
	void removeEspaco(size_t numID);
	map <size_t, vector<Reserva>> returnReservas();
	bool adicionaReserva(size_t numID, Reserva r1);
	bool removeReserva(size_t numID, Reserva r1);
	bool alteraReserva(size_t numID, Reserva rAntiga, Reserva rNova);
	bool reservaExiste(size_t numID, Reserva r1);
	bool temReservas(size_t numID);
	bool verificaEspaco(size_t numID, Date d1);
	void showMonth(size_t numId, size_t month, size_t year);

};
