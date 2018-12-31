#include "Reservas.h"

Reserva::Reserva(int idCliente, Date &inicio, Date &fim) {

	if (inicio < fim && inicio.validDate() && fim.validDate())
	{
		this->inicio = inicio;
		this->fim = fim;
		this->idCliente = idCliente;
	}

	else
		throw DatasInvalidas(idCliente);
};


Date Reserva::returnInicio() const {
	return inicio;
}
Date Reserva::returnFim() const {
	return fim;
}

int Reserva::returnidCliente() const {
	return idCliente;
}

bool Reserva::operator - (Reserva& reserva2){

	if (reserva2.returnFim() < this->inicio || reserva2.returnInicio() > this->fim)
		return false;
	return true;

}

bool Reserva::operator == (Reserva& reserva2) {
	return(this->inicio == reserva2.returnInicio() && this->fim == reserva2.returnFim() && this->idCliente == reserva2.returnidCliente());
}

ostream & operator << (ostream & out, const Reserva & r1) {
	out << r1.returnidCliente() << " : " << r1.returnInicio().getDate() << " - " << r1.returnFim().getDate();
	return out;
}

// --------------------------------------------------------------------------------------------

Reservas::Reservas() {}

Reservas::Reservas(vector<Espaco *> espacos) {
	vector<Reserva> constructor;

	//for(vector<Espaco *>::iterator it= espacos.begin(); it!= espacos.end(); it++)
	for (size_t i = 0; i < espacos.size(); i++)
	{
		size_t numID = espacos[i]->getNumID();
		reservasHotel.insert(pair<size_t, vector<Reserva>>(numID, constructor));
		//reservasHotel[numID]= constructor;

	}
}


void Reservas::updateReservas(Espaco * espaco) {
	vector<Reserva> constructor;
	reservasHotel.insert(pair<size_t, vector<Reserva>>(espaco->getNumID(), constructor));
}

void Reservas::removeEspaco(size_t numID) {

	if (reservasHotel.find(numID) == reservasHotel.end())
	{
		throw EspacoNaoPertenceHotel(numID);
	}

	map <size_t, vector<Reserva>>::iterator it = reservasHotel.find(numID);
	reservasHotel.erase(it);
}

map <size_t, vector<Reserva>> Reservas::returnReservas() {
	return reservasHotel;
}

bool Reservas::reservaExiste(size_t numID, Reserva r1) {

	if (reservasHotel.find(numID) == reservasHotel.end())
	{
		throw EspacoNaoPertenceHotel(numID);
	}
	vector<Reserva> reservas = reservasHotel[numID];
	for (size_t i = 0; i < reservas.size(); i++)
	{
		if (reservas[i] == r1)
			return true;
	}
	return false;
}

bool Reservas::adicionaReserva(size_t numID, Reserva r1) {
	if (reservasHotel.find(numID) == reservasHotel.end())
	{
		throw EspacoNaoPertenceHotel(numID);
	}

	if (reservasHotel[numID].size() == 0)
	{
		reservasHotel[numID].push_back(r1);
		return true;
	}
	else
	{
		vector<Reserva> reservas = reservasHotel[numID];
		for (size_t i = 0; i < reservas.size(); i++)
		{
			if (reservas[i] - r1)
			{
				throw ReservasCoincidem(numID);
			}

		}
		reservasHotel[numID].push_back(r1);
		return true;
	}

}

bool Reservas::removeReserva(size_t numID, Reserva r1) {

	if (reservasHotel.find(numID) == reservasHotel.end())
	{
		throw EspacoNaoPertenceHotel(numID);
	}

	for (vector<Reserva>::iterator it = reservasHotel[numID].begin(); it != reservasHotel[numID].end(); it++)
	{
	
		if ((*it) == r1)
		{
			it = reservasHotel[numID].erase(it);
			return true;
		}

	}
	throw ReservaNaoExiste(numID);
}

bool Reservas::alteraReserva(size_t numID, Reserva rAntiga, Reserva rNova) {
	if (reservasHotel.find(numID) == reservasHotel.end())
	{
		throw EspacoNaoPertenceHotel(numID);
	}

	if (this->reservaExiste(numID, rAntiga))
	{
		if (this->adicionaReserva(numID, rNova))
		{
			this->removeReserva(numID, rAntiga);
			return true;
		}
	}
	throw ReservaNaoExiste(numID);
}

bool Reservas::temReservas(size_t numID) {
	if (reservasHotel.find(numID) == reservasHotel.end())
	{
		throw EspacoNaoPertenceHotel(numID);
	}
	if (reservasHotel[numID].size() == 0)
		return false;
	else
		return true;

}

bool Reservas::verificaEspaco(size_t numID, Date d1) const {
	if (reservasHotel.find(numID) == reservasHotel.end())
	{
		throw EspacoNaoPertenceHotel(numID);
	}
	vector<Reserva> reservas = this->reservasHotel.at(numID);

	for (size_t i = 0; i < reservas.size(); i++)
	{
		if (reservas[i].returnInicio() < d1 && d1 < reservas[i].returnFim())
			return true;
		//if (reservas[i].returnInicio() == d1 || reservas[i].returnFim() == d1)
		//	return true;
	}
	return false;
}

void Reservas::showMonth(size_t numId, size_t month, size_t year) {

	Date d1 = Date(1, month, year);
	int numSpaceBlocks, ds;
	string months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

	cout << months[month - 1] << endl;
	cout << "Sun Mon Tue Wed Thu Fri Sat" << endl;

	ds = d1.dayOfWeek();
	numSpaceBlocks = (ds + 6) % 7;

	for (int i = 1; i <= numSpaceBlocks; i++)
		cout << "    ";
	for (size_t i = 1; i <= d1.numDaysOfMonth(); i++)
	{
		if (i == d1.numDaysOfMonth())
		{
			cout << setw(3) << i << " ";
			cout << endl;
			while (d1.getDay() <= d1.numDaysOfMonth())
			{
				if (this->verificaEspaco(numId, d1))
				{
					cout << setw(3) << "X" << " ";
					d1.increaseDay();
				}

				else
				{
					cout << setw(3) << "O" << " ";
					d1.increaseDay();
				}
			}

		}

		else {
			cout << setw(3) << i << " ";
			if (ds == 0) {
				cout << endl;
				if (d1.getDay() == 1) {
					for (int j = 1; j <= numSpaceBlocks; j++)
						cout << "    ";
					for (int j = 0; j < 7 - numSpaceBlocks; j++)
					{
						if (this->verificaEspaco(numId, d1))
						{
							cout << setw(3) << "X" << " ";
							d1.increaseDay();
						}

						else
						{
							cout << setw(3) << "O" << " ";
							d1.increaseDay();
						}
					}

				}

				else {
					for (size_t j = 0; j < 7; j++)
					{
						if (this->verificaEspaco(numId, d1))
						{
							cout << setw(3) << "X" << " ";
							d1.increaseDay();
						}

						else
						{
							cout << setw(3) << "O" << " ";
							d1.increaseDay();
						}
					}
				}
				cout << endl;
			}

			ds = (ds + 1) % 7;
		}
	}
	cout << endl << endl;
}
