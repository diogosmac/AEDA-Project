#include "Reservas.h"

Reserva::Reserva(string nome, size_t idade, Date inicio, Date fim, Hotel h) {

	if (inicio < fim)
		if (h.verificaCliente(nome, idade))
			if (idade >= 18)
			{
				this->inicio = inicio;
				this->fim = fim;
				this->idCliente = h.idCliente(nome, idade);
			}
			else
				throw ClienteDemasiadoNovoReserva(h.encontraCliente(nome));
		else
			throw ClienteNaoEncontrado(nome);
	else
		throw invalid_argument("Data de inicio posterior à data do fim");
};


Date Reserva::returnInicio() {
	return inicio;
}
Date Reserva::returnFim() {
	return fim;
}

int Reserva::returnidCliente() {
	return idCliente;
}

bool Reserva::operator - (Reserva& reserva2) const {

	if (this->inicio >= reserva2.returnFim() || this->fim <= reserva2.returnInicio())
		return false;
	return true;
}

bool Reserva::operator == (Reserva& reserva2) const {
	return(this->inicio == reserva2.returnInicio() && this->fim == reserva2.returnFim() && this->idCliente == reserva2.returnidCliente());
}

Reservas::Reservas(Hotel h) {
	vector<Espaco *> espacos = h.getTodosEspacos();
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
		//throw EspacoNaoPertenceHotel(numID);
		return false;
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
		//throw EspacoNaoPertenceHotel(numID);
		return false;
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
				//throw reservasCoincidem;
				//throw invalid_argument("Datas da reserva coincidem com uma reserva ja existente");
				return false;
			}

		}
		reservasHotel[numID].push_back(r1);
		return true;
	}

}

bool Reservas::removeReserva(size_t numID, Reserva r1) {

	if (reservasHotel.find(numID) == reservasHotel.end())
	{
		//throw EspacoNaoPertenceHotel(numID);
		return false;
	}

	vector<Reserva> reservas = reservasHotel[numID];
	size_t i = 0;
	for (vector<Reserva>::iterator it = reservas.begin(); it != reservas.end(); it++, i++)
	{
		if (reservas[i] == r1)
		{
			reservasHotel[numID].erase(it);
			return true;
		}
	}
	return false;
}

bool Reservas::alteraReserva(size_t numID, Reserva rAntiga, Reserva rNova) {
	if (reservasHotel.find(numID) == reservasHotel.end())
	{
		//throw EspacoNaoPertenceHotel(numID);
		return false;
	}

	if (this->reservaExiste(numID, rAntiga))
	{
		if (this->adicionaReserva(numID, rNova))
		{
			this->removeReserva(numID, rAntiga);
			return true;
		}
	}
	return false;
}

bool Reservas::temReservas(size_t numID) {
	if (reservasHotel.find(numID) == reservasHotel.end())
	{
		//throw EspacoNaoPertenceHotel(numID);
		return false;
	}
	if (reservasHotel[numID].size() == 0)
		return false;
	else
		return true;

}

bool Reservas::verificaEspaco(size_t numID, Date d1) {
	if (reservasHotel.find(numID) == reservasHotel.end())
	{
		//throw EspacoNaoPertenceHotel(numID);
		return false;
	}
	vector<Reserva> reservas = reservasHotel[numID];

	for (size_t i = 0; i < reservas.size(); i++)
	{
		if (reservas[i].returnInicio() < d1&&d1 < reservas[i].returnFim())
			return true;
		if (reservas[i].returnInicio() == d1 || reservas[i].returnFim() == d1)
			return true;
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
	for (int i = 1; i <= d1.numDaysOfMonth(); i++)
	{
		cout << setw(3) << i << " ";
		d1.increaseDay();
		if (ds == 0)
		{
			cout << endl;
			for (size_t i = 0; i < 7; i++)
			{
				if (this->verificaEspaco(numId, d1))
					cout << setw(3) << "X" << " ";
				else
					cout << setw(3) << " " << " ";
			}

			ds = (ds + 1) % 7;
		}
	}
	cout << endl << endl;

}
