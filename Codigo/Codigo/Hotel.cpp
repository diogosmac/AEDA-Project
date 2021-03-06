﻿#include "Hotel.h"

Hotel::Hotel(string nome) : restaurantesProximosHotel(Restaurante("", "", 0))
{
	nomeHotel = nome;
}

string Hotel::getNomeHotel() const
{
	return nomeHotel;
}

size_t Hotel::nEspacos() const
{
	return this->todosEspacos.size();
}

vector<Espaco *> Hotel::getTodosEspacos() const
{
	return this->todosEspacos;
}

tabHClientes Hotel::getClientes() const
{
	return this->clientesHotel;
}

vector<Espaco *> Hotel::getEspacosDisponiveis(Date data) const
{
	vector<Espaco *> disp;
	for (size_t i = 0; i < todosEspacos.size(); i++) {
		if (!(this->todasReservas.verificaEspaco(todosEspacos[i]->getNumID(), data)))
			disp.push_back(todosEspacos[i]);
	}
	return disp;
}

vector<Espaco *> Hotel::getEspacosDisponiveis(Date data1, Date data2) const
{
	vector<Espaco *> disp;

	for (size_t i = 0; i < todosEspacos.size(); i++) 
	{
		bool disponivel = true;
		Date data_aux = data1;

		while (!(data_aux > data2)) 
		{
			if (this->todasReservas.verificaEspaco(todosEspacos[i]->getNumID(), data_aux))
				disponivel = false;
			data_aux.increaseDay();
		}
		if (disponivel) 
		{
			disp.push_back(todosEspacos[i]);
		}
	}

	return disp;
}

vector<Funcionario *> Hotel::getFuncionarios() const
{
	return this->funcionarios;
}

Reservas Hotel::getReservas() const
{
	return todasReservas;
}

double Hotel::nEspacosDisponiveis(Date data)
{
	double contador = 0;
	for (size_t i = 0; i < this->todosEspacos.size(); i++)
	{
		if (!(this->todasReservas.verificaEspaco(todosEspacos[i]->getNumID(), data)))
			contador++;
	}
	return contador;
}

double Hotel::lotacao(Date data)
{
	return (this->nEspacosDisponiveis(data) / this->todosEspacos.size()) * 100;
}

void Hotel::adicionaEspaco(Espaco * espaco)
{
	this->todosEspacos.push_back(espaco);
	todasReservas.updateReservas(espaco);
}

void Hotel::adicionaFuncionario(Funcionario * func)
{
	this->funcionarios.push_back(func);
	try
	{
		alocaSupervisores();
	}
	catch (NaoHaSupervisores e)
	{
		cerr << "Impossivel alocar os supervisores no hotel " << e.getNomeHotel() << ".\n";
	}
}

void Hotel::removeEspaco(size_t numID)
{
	bool encontrado = false;

	// Remove do vetor todosEspacos. Caso nao encontre, da erro.
	for (size_t i = 0; i < this->todosEspacos.size(); i++)
	{
		if (todosEspacos.at(i)->getNumID() == numID)
		{
			if (!(todasReservas.temReservas(numID)))
			{
				todosEspacos.erase(todosEspacos.begin() + i);
				encontrado = true;
				todasReservas.removeEspaco(numID);
				break;
			}
		}
	}

	if (!encontrado)
	{
		throw EspacoNaoPertenceHotel(numID);
	}
}

void Hotel::removeFuncionario(size_t ID_Code)
{
	bool encontrado = false;

	// Remove funcionario. Caso nao o encontre, d� erro.
	for (size_t i = 0; i < this->funcionarios.size(); i++)
	{
		if (funcionarios.at(i)->getID_Code() == ID_Code)
		{
			funcionarios.erase(funcionarios.begin() + i);
			encontrado = true;
			break;
		}
	}

	if (!encontrado)
	{
		throw FuncionarioNaoTrabalhaHotel(ID_Code);
	}
}

size_t Hotel::nClientes() const
{
	return this->clientesHotel.size();
}

void Hotel::removeCliente(string nome, size_t idCliente)
{
	bool encontrado = false;


	for (tabHClientes::const_iterator it = clientesHotel.begin(); it != clientesHotel.end(); it++)
	{
		if (((*it).getNome() == nome) && ((*it).getIDCliente() == idCliente))
		{
			encontrado = true;
			it = clientesHotel.erase(it);
			break;
		}
	}
	

	if (!encontrado)
	{
		throw ClienteNaoEncontrado(nome);
	}
}

bool Hotel::verificaCliente(string nome, size_t idade)
{

	for (tabHClientes::const_iterator it = clientesHotel.begin(); it != clientesHotel.end(); it++)
	{
		if (((*it).getNome() == nome) && ((*it).getIdade() == idade))
		{
			return true;
		}
	}

	return false;

}

int Hotel::idCliente(string nome, size_t idade)
{

	for (tabHClientes::const_iterator it = clientesHotel.begin(); it != clientesHotel.end(); it++)
	{
		if (((*it).getNome() == nome) && ((*it).getIdade() == idade))
		{
			return (*it).getIDCliente();
		}
	}

	return -1;

}

void Hotel::adicionaCliente(string nome, size_t idade, size_t id)
{

	if (!verificaCliente(nome, idade))
	{
		Cliente c1(nome, idade);

		if (id != 9001)
		{
			c1.setID(id);
		}
			
		this->clientesHotel.insert(c1);
	}

}

Cliente * Hotel::encontraCliente(string nome)
{

	for (tabHClientes::const_iterator it = clientesHotel.begin(); it != clientesHotel.end(); it++)
	{
		if ((*it).getNome() == nome)
		{
			Cliente temp = (*it);
			return &temp;
		}
	}

	throw ClienteNaoEncontrado(nome);

}

Cliente Hotel::encontraCliente(size_t id)
{

	for (tabHClientes::const_iterator it = clientesHotel.begin(); it != clientesHotel.end(); it++)
	{
		if ((*it).getIDCliente() == id)
		{
			return (*it);
		}
	}

	throw ClienteNaoEncontrado(id);

}

bool Hotel::efetuaReserva(Cliente* cliente, size_t idEspaco, Date inicio, Date fim)
{
	try 
	{
		if (cliente->getIdade() < 18) 
		{
			throw ClienteDemasiadoNovoReserva(cliente->getNome());
		}

		bool espacoExiste = false;

		for (size_t i = 0; i < todosEspacos.size(); i++) 
		{
			if (todosEspacos[i]->getNumID() == idEspaco)
				espacoExiste = true;
		}

		if (!espacoExiste) 
		{
			throw EspacoNaoPertenceHotel(idEspaco);
		}

		bool espacoDisponivel = true;

		Reserva res(cliente->getIDCliente(), inicio, fim);

		for (size_t i = 0; i < todasReservas.returnReservas().at(idEspaco).size(); i++) 
		{
			if (res - todasReservas.returnReservas().at(idEspaco).at(i))
				espacoDisponivel = false;
		}

		if (!espacoDisponivel) 
		{
			throw EspacoNaoDisponivel(idEspaco);
		}
		else 
		{
			reservaEspaco(idEspaco, res);

			int tempID = Cliente::getNextClientID();//Copia nextID, uma vez que vai ser criado um objeto temp da classe, que se pretende que nao incremente nextClientID

			Cliente *temp = cliente;
			this->removeCliente(cliente->getNome(), cliente->getIDCliente());
			temp->registaReserva();

			Cliente::setNextClientID(tempID);//Volta a repor o valor anterior, para que clientes novos tenham id's corretos

			clientesHotel.insert(*temp);
		}

		return true;
	}
	catch (EspacoNaoPertenceHotel e1) {
		cerr << "Espaco de id " << e1.getNumID() << " nao pertence ao hotel!" << endl;
	}
	catch (ClienteDemasiadoNovoReserva e2) {
		cerr << "O Cliente de nome " << e2.getNome() << " e demasiado novo para efetuar uma reserva!" << endl;	
	}
	catch (EspacoNaoDisponivel e3) {
		cerr << "O espaco de id = " << e3.getNumID() << " nao esta disponivel!" << endl;
	}
	catch (DatasInvalidas e4) {
		cout << "Data inicio: " << inicio.getDate() << "\tData fim: " << fim.getDate() << endl;
		cerr << "A data de fim da reserva do cliente " << e4.getIdCliente() << " e anterior a data de inicio!" << endl;
	}

	return false;
}

void Hotel::reservaEspaco(size_t idEspaco, Reserva res)
{
	if (!todasReservas.adicionaReserva(idEspaco, res)) {
		cout << "Algo correu mal. A reserva nao pode ser efetuada.\n";
	}
	// else {
	// 	cout << "Reserva efetuada com sucesso!\n";
	// 	cout << "Espaco reservado: " << idEspaco << '\t';
	// 	for (size_t i = 0; i < clientesHotel.size(); i++) {
	// 		if (clientesHotel.at(i)->getIDCliente() == res.returnidCliente()) {
	// 			cout << "Reserva em nome de " << clientesHotel.at(i)->getNome() << " : ID do Cliente - " << res << '\n';
	// 			break;
	// 		}
	// 	}
	// }
}

size_t Hotel::nReservas()
{
	size_t ret = 0;
	for (size_t i = 0; i < todosEspacos.size(); i++) {
		size_t id = todosEspacos.at(i)->getNumID();
		for (size_t j = 0; j < todasReservas.returnReservas()[id].size(); j++) {
			ret++;
		}
	}
	return ret;
}

bool Hotel::removeReserva(size_t idEspaco, Reserva res)
{
	if (todasReservas.removeReserva(idEspaco, res))
	{
		int tempID = Cliente::getNextClientID();//Copia nextID, uma vez que vai ser criado um objeto temp da classe, que se pretende que nao incremente nextClientID

		Cliente temp = this->encontraCliente(res.returnidCliente());
		this->removeCliente(temp.getNome(), temp.getIDCliente());
		temp.decNReservas();

		Cliente::setNextClientID(tempID);//Volta a repor o valor anterior, para que clientes novos tenham id's corretos

		clientesHotel.insert(temp);

		return true;
	}

	return false;
}

void Hotel::alocaSupervisores()
{
	vector<Funcionario *> supervisores;
	for (size_t i = 0; i < funcionarios.size(); i++) {
		if (funcionarios.at(i)->isSupervisor())
			supervisores.push_back(funcionarios.at(i));
	}

	if (supervisores.empty()) {
		throw NaoHaSupervisores(nomeHotel);
	}

	for (size_t i = 0; i < supervisores.size(); i++) {
		supervisores.at(i)->RemoveEspacos();
	}

	for (size_t i = 0, j = 0; i < todosEspacos.size(); i++, j++) {
		if (j == supervisores.size()) {
			j = 0;
		}
		supervisores.at(j)->AcrescentaEspaco(todosEspacos.at(i));
	}
}

double Hotel::getPrecoReserva(size_t idEspaco, Reserva res)
{
	int idRes = 0;
	map<size_t, vector<Reserva>> res_map = todasReservas.returnReservas();
	for (size_t i = 0; i < res_map[idEspaco].size(); i++) {
		if (res_map[idEspaco].at(i) == res)
		{
			idRes = i;
			break;
		}
	}
	double preco = 0;
	Date aux = res_map[idEspaco].at(idRes).returnInicio();
	while (!(aux > res_map[idEspaco].at(idRes).returnFim()))
	{
		preco += todosEspacos.at(idEspaco)->getPrecoReservaDiario(aux);
		aux.increaseDay();
	}
	return preco;
}

void Hotel::exportInfoClientes()
{
	cout << "\nConfirma que deseja exportar a informacao dos clientes? (s/n): ";
	string confirm;
	cin >> confirm;
	cin.ignore(1000, '\n');
	while (confirm != "s" && confirm != "n") {
		cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
		cin >> confirm;
		cin.ignore(1000, '\n');
	}

	if (confirm == "n") {
		cout << "Operacao cancelada a seu pedido.\n";
		return;
	}


	ofstream ficheiroCli;
	string nomeFicheiro = nomeHotel + "_clientes.txt";

	ficheiroCli.open(nomeFicheiro);

	if (!ficheiroCli.is_open())
	{
		cerr << "Erro na abertura do ficheiro.\n" << endl;
		return;
	}


	cout << "A guardar a informacao no ficheiro " << nomeFicheiro << " . . ." << endl;

	// Escreve todos os clientes

	for (tabHClientes::iterator it = clientesHotel.begin(); it != clientesHotel.end(); it++)
	{
		Cliente temp = (*it);
		ficheiroCli << &temp << '\n';
	}

	cout << "Toda a informacao relativa aos clientes foi guardada com sucesso!\n\n";



	ficheiroCli.close();

}

void Hotel::exportInfoEspacos()
{
	cout << "\nConfirma que deseja exportar a informacao dos Espacos? (s/n): ";
	string confirm;
	cin >> confirm;
	cin.ignore(1000, '\n');
	while (confirm != "s" && confirm != "n") {
		cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
		cin >> confirm;
		cin.ignore(1000, '\n');
	}

	if (confirm == "n") {
		cout << "Operacao cancelada a seu pedido.\n";
		return;
	}


	ofstream ficheiroEsp;
	string nomeFicheiro = nomeHotel + "_espacos.txt";

	ficheiroEsp.open(nomeFicheiro);

	if (!ficheiroEsp.is_open())
	{
		cerr << "Erro na abertura do ficheiro.\n" << endl;
		return;
	}

	cout << "A guardar a informacao no ficheiro " << nomeFicheiro << " . . ." << endl;
	// Escreve todos os espaços
	for (size_t i = 0; i < this->todosEspacos.size(); i++)
	{
		ficheiroEsp << todosEspacos.at(i) << '\n';
		if (i == this->todosEspacos.size() - 1) {
			ficheiroEsp << '\n';
			cout << "Toda a informacao relativa aos espacos foi guardada com sucesso!\n\n";
		}
	}

	ficheiroEsp.close();

}

void Hotel::exportInfoReservas()
{
	cout << "\nConfirma que deseja exportar a informacao das reservas? (s/n): ";
	string confirm;
	cin >> confirm;
	cin.ignore(1000, '\n');
	while (confirm != "s" && confirm != "n") {
		cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
		cin >> confirm;
		cin.ignore(1000, '\n');
	}

	if (confirm == "n") {
		cout << "Operacao cancelada a seu pedido.\n";
		return;
	}

	
	ofstream ficheiroRes;
	string nomeFicheiro = nomeHotel + "_reservas.txt";

	ficheiroRes.open(nomeFicheiro);
	
	if (!ficheiroRes.is_open())
	{
		cerr << "Erro na abertura do ficheiro.\n" << endl;
		return;
	}

	cout << "A guardar a informacao no ficheiro " << nomeFicheiro << " . . ." << endl;
	// Escreve todas as reservas
	for (size_t i = 0; i < todosEspacos.size(); i++)
	{
		size_t id = todosEspacos.at(i)->getNumID();
		if (todasReservas.temReservas(id)) {
			ficheiroRes << id << "; ";
			for (size_t i = 0; i < todasReservas.returnReservas()[id].size(); i++) {
				ficheiroRes << todasReservas.returnReservas()[id].at(i) << "; ";
			}
			ficheiroRes << '\n';
		}
		else {
			ficheiroRes << id << "; SemReservas\n";
		}
		if (i == this->todosEspacos.size() - 1)
		{
			ficheiroRes << '\n';
			cout << "Toda a informacao relativa as reservas foi guardada com sucesso!\n\n";
		}
	}

	ficheiroRes.close();
}

void Hotel::exportInfoFuncionarios()
{
	cout << "\nConfirma que deseja exportar a informacao dos funcionarios? (s/n): ";
	string confirm;
	cin >> confirm;
	cin.ignore(1000, '\n');
	while (confirm != "s" && confirm != "n")
	{
		cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
		cin >> confirm;
		cin.ignore(1000, '\n');
	}

	if (confirm == "n")
	{
		cout << "Operacao cancelada a seu pedido.\n";
		return;
	}


	ofstream ficheiroFun;
	string nomeFicheiro = nomeHotel + "_funcionarios.txt";

	ficheiroFun.open(nomeFicheiro);

	if (!ficheiroFun.is_open())
	{
		cerr << "Erro na abertura do ficheiro.\n" << endl;
		return;
	}

	cout << "A guardar a informacao no ficheiro " << nomeFicheiro << " . . ." << endl;
	// Escreve todos os funcionarios
	for (size_t i = 0; i < funcionarios.size(); i++) {
		ficheiroFun << funcionarios.at(i) << '\n';
		if (i == funcionarios.size() - 1) {
			cout << "Toda a informacao relativa aos funcionarios foi guardada com sucesso!\n";
		}
	}

	ficheiroFun.close();
}

void Hotel::showInfoClientes()
{

	for (tabHClientes::const_iterator it = clientesHotel.begin(); it != clientesHotel.end(); it++)
	{
		Cliente temp = (*it);
		cout << &temp << endl;
	}

	cout << endl;
}

void Hotel::showInfoEspacos()
{
	for (size_t i = 0; i < this->todosEspacos.size(); i++)
	{
		cout << todosEspacos.at(i) << '\n';
	}
	cout << endl;
}

void Hotel::showInfoReservas()
{
	for (size_t i = 0; i < todosEspacos.size(); i++)
	{
		size_t id = todosEspacos.at(i)->getNumID();
		if (todasReservas.temReservas(id)) {
			cout << id << "; ";
			for (size_t i = 0; i < todasReservas.returnReservas()[id].size(); i++) {
				cout << todasReservas.returnReservas()[id].at(i) << "; ";
			}
			cout << '\n';
		}
		else {
			cout << id << "; SemReservas\n";
		}
	}
	cout << endl;
}

void Hotel::showInfoFuncionarios()
{
	for (size_t i = 0; i < funcionarios.size(); i++) {
		cout << funcionarios.at(i) << '\n';
	}
	cout << endl;
}


// <customized sorting>

struct comp_alfa
{
	inline bool operator() (const Funcionario* func1, const Funcionario* func2)
	{
		return (func1->getNome() < func2->getNome());
	}
};

void Hotel::sortFuncionariosA()
{
	sort(funcionarios.begin(), funcionarios.end(), comp_alfa());
}

struct comp_alfa_inv
{
	inline bool operator() (const Funcionario* func1, const Funcionario* func2)
	{
		return (func2->getNome() < func1->getNome());
	}
};

void Hotel::sortFuncionariosAA()
{
	sort(funcionarios.begin(), funcionarios.end(), comp_alfa_inv());
}

struct comp_ID
{
	inline bool operator() (const Funcionario* func1, const Funcionario* func2)
	{
		return (func1->getID_Code() < func2->getID_Code());
	}
};

void Hotel::sortFuncionariosID()
{
	sort(funcionarios.begin(), funcionarios.end(), comp_ID());
}

// </customized sorting>


bool Hotel::importInfoClientes()
{
	cout << "\nConfirma que deseja importar a informacao dos clientes? (s/n): ";
	string confirm;
	cin >> confirm;
	cin.ignore(1000, '\n');
	while (confirm != "s" && confirm != "n") {
		cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
		cin >> confirm;
		cin.ignore(1000, '\n');
	}

	if (confirm == "n") {
		cout << "Operacao cancelada a seu pedido.\n";
		return false;
	}


	ifstream ficheiroCli;
	string nomeFicheiro = nomeHotel + "_clientes.txt";

	ficheiroCli.open(nomeFicheiro);

	if (!ficheiroCli.is_open())
	{
		cerr << "Nao foi possivel obter a informacao relativa aos clientes do hotel " << nomeHotel << "!\n";
		return false;
	}

	cout << "A importar a informacao dos clientes . . .\n";
	string line;
	while (getline(ficheiroCli, line))
	{
		/*
			OUTPUT CLIENTE: idCliente; nomeCliente; idadeCliente
		*/
		size_t idCliente = 9999;

		int index = line.find_first_of(';');

		idCliente = stoi(line.substr(0, index));

		string nome = line.substr(index + 2, line.find(';', index + 1) - index - 2);
		index = line.find(';', index + 1) + 2;
		string idade_str = line.substr(index, line.find('a', index) - index);
		int idade = stoi(idade_str);

		adicionaCliente(nome, idade, idCliente);
	}
	cout << "Clientes do hotel " << nomeHotel << " importados com sucesso!\n";

	return true;
}

bool Hotel::importInfoReservas()
{
	cout << "\nConfirma que deseja importar a informacao das reservas? (s/n): ";
	string confirm;
	cin >> confirm;
	cin.ignore(1000, '\n');
	while (confirm != "s" && confirm != "n")
	{
		cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
		cin >> confirm;
		cin.ignore(1000, '\n');
	}

	if (confirm == "n")
	{
		cout << "Operacao cancelada a seu pedido.\n";
		return false;
	}


	ifstream ficheiroRes;
	string nomeFicheiro = nomeHotel + "_reservas.txt";

	ficheiroRes.open(nomeFicheiro);

	if (!ficheiroRes.is_open())
	{
		cerr << "Nao foi possivel obter a informacao relativa as reservas do hotel " << nomeHotel << "!\n";
		return false;
	}

	cout << "A importar a informacao das reservas . . .\n";
	string line;
	int counter = 0;
	int failedExtracts = 0;
	while (getline(ficheiroRes, line) && !line.empty())
	{
		/*
			OUTPUT SEM RESERVAS: idEspaco;SemReservas
			OUTPUT RESERVA: idEspaco;idCliente:di/mi/yi-df/mf/yf;idCliente:di/mi/yi-df/mf/yf;(...)
		*/

		int index = line.find_first_of(';');
		string idEsp_str = line.substr(0, index);
		int idEsp = stoi(idEsp_str);
		if (line.substr(index + 1) != " Sem Reservas")
		{
			// index = line.find(';', index + 1);
			while (line.find(';', index + 1) != line.npos) 
			{
				int index_break = line.find(';', index + 1);

				string idCli_str = line.substr(index + 2, line.find(':', index) - index - 2);
				int idCli = stoi(idCli_str);
				index = line.find(':', index);

				string di_str = line.substr(index + 2, line.find('/', index) - index - 2);
				int di = stoi(di_str);
				index = line.find('/', index);
				string mi_str = line.substr(index + 1, line.find('/', index + 1) - index - 1);
				int mi = stoi(mi_str);
				index = line.find('/', index + 1);
				string yi_str = line.substr(index + 1, line.find('-', index + 1) - index - 1);
				int yi = stoi(yi_str);
				index = line.find('-', index);

				string df_str = line.substr(index + 2, line.find('/', index) - index - 2);
				int df = stoi(df_str);
				index = line.find('/', index);
				string mf_str = line.substr(index + 1, line.find('/', index + 1) - index - 1);
				int mf = stoi(mf_str);
				index = line.find('/', index + 1);
				string yf_str = line.substr(index + 1, line.find(';', index + 1) - index - 1);
				int yf = stoi(yf_str);
				index = line.find(';', index);

				Date data_ini(di, mi, yi);
				Date data_fim(df, mf, yf);

				counter++;
				bool encontrou = false;


				for (auto it = clientesHotel.begin(); it != clientesHotel.end(); it++)
				{
					if ((*it).getIDCliente() == idCli)
					{
						encontrou = true;
						Cliente temp = (*it);

						if (!efetuaReserva(&temp, idEsp, data_ini, data_fim))
						{
							failedExtracts++;
						}
						else
						{
							break;
						}
							
					}
				}

				if (!encontrou) 
				{
					failedExtracts++;
				}

				index = index_break;
			}
		}
	}

	if (failedExtracts) {
		if (failedExtracts == 1)
			cout << "Por erro nos dados, falhou a extracao de 1 reserva.\n";
		else
			cout << "Por erro nos dados, falhou a extracao de " << failedExtracts << " reservas.\n";
	}

	cout << (counter - failedExtracts) << " reservas do hotel " << nomeHotel << " importadas com sucesso!\n";

	return true;
}

bool Hotel::importInfoFuncionarios()
{
	ifstream ficheiroFun;

	string nomeFicheiro = nomeHotel + "_funcionarios.txt";

	cout << "\nConfirma que deseja importar a informacao dos funcionarios? (s/n): ";
	string confirm;
	cin >> confirm;
	cin.ignore(1000, '\n');
	while (confirm != "s" && confirm != "n")
	{
		cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
		cin >> confirm;
		cin.ignore(1000, '\n');
	}

	if (confirm == "n")
	{
		cout << "Operacao cancelada a seu pedido.\n";
		return false;
	}

	ficheiroFun.open(nomeFicheiro);

	if (!ficheiroFun.is_open())
	{
		cerr << "Nao foi possivel obter a informacao relativa aos funcionarios do hotel " << nomeHotel << "!\n";
		return false;
	}

	cout << "A importar a informacao dos funcionarios . . .\n";
	string line;
	int counter = 0;
	while (getline(ficheiroFun, line))
	{
		/*
			OUTPUT FUNCIONÁRIO: idFunc;nomeFunc;supervisor(yes/no)
			OUTPUT SUPERVISOR: out_func// idEsp,idEsp(...)
		*/
		int index = line.find_first_of(';') + 2;
		string nome = line.substr(index, line.find('-', index) - index - 1);
		index = line.find('-', index) + 2;
		string status = line.substr(index, line.find('-', index) - index - 1);
		if (status == "Funcionario") {
			counter++;
			Funcionario* func = new Funcionario(nome);
			adicionaFuncionario(func);
		}
		else if (status == "Supervisor") {
			counter++;
			Funcionario* sup = new Supervisor(nome);
			index = line.find(':') + 1;
			while (index != line.npos) {
				index += 1;
				string idEsp_str = line.substr(index, line.find(' ', index) - index);
				int idEsp = stoi(idEsp_str);
				for (size_t i = 0; i < todosEspacos.size(); i++) {
					if (idEsp == todosEspacos.at(i)->getNumID()) {
						sup->AcrescentaEspaco(todosEspacos.at(i));
					}
				}
				index = line.find(' ', index);
			}
			adicionaFuncionario(sup);
		}
		else {
			cout << "Linha invalida, nenhum funcionario foi adicionado.\n";
		}
	}
	cout << counter << " funcionarios do hotel " << nomeHotel << " importados com sucesso!\n";

	return true;
}

bool Hotel::importInfoEspacos() 
{
	ifstream ficheiroEsp;

	string nomeFicheiro = nomeHotel + "_espacos.txt";

	cout << "\nConfirma que deseja importar a informacao dos espacos? (s/n): ";
	string confirm;
	cin >> confirm;
	cin.ignore(1000, '\n');
	while (confirm != "s" && confirm != "n")
	{
		cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
		cin >> confirm;
		cin.ignore(1000, '\n');
	}

	if (confirm == "n")
	{
		cout << "Operacao cancelada a seu pedido.\n";
		return false;
	}

	ficheiroEsp.open(nomeFicheiro);

	if (!ficheiroEsp.is_open())
	{
		cerr << "Nao foi possivel obter a informacao relativa aos espacos do hotel " << nomeHotel << "!\n";
		return false;
	}

	cout << "A importar a informacao dos espacos . . .\n";
	string line;
	int counter = 0;
	while (getline(ficheiroEsp, line) && !line.empty())
	{
		size_t index = line.find_first_of(';') + 2;
		string tipoEspaco = line.substr(index, line.find('-', index + 1) - index - 1);
		
		bool valido = true;
		if (tipoEspaco == "Quarto") {
			index = line.find_first_of('-') + 2;
			string dup = line.substr(index, line.find(',', index) - index);
			index = line.find(',', index) + 2;
			string fre = line.substr(index);
			bool duplo = (dup == "Duplo");
			bool frente = (fre == "Frente");
			if (!duplo && dup != "Single")
				valido = false;
			if (!frente && fre != "Traseiras")
				valido = false;
			if (valido) {
				Espaco* esp = new Quarto(duplo, frente);
				adicionaEspaco(esp);
				counter++;
			}
		}
		else if (tipoEspaco == "Sala de Reunioes") {
			index = line.find_first_of('-') + 2;
			string pax_str = line.substr(index, line.find(' ', index) - index);
			int pax = stoi(pax_str);
			index = line.find_first_of(',') + 2;
			string vid_stat = line.substr(index, 3);
			index = line.find(',', index) + 2;
			string aud_stat = line.substr(index, 3);
			bool video = (vid_stat == "Com");
			bool audio = (aud_stat == "Com");
			if (!video && vid_stat != "Sem")
				valido = false;
			if (!audio && aud_stat != "Sem")
				valido = false;
			if (valido) {
				Espaco* esp = new SalaDeReunioes(pax, video, audio);
				adicionaEspaco(esp);
				counter++;
			}
		}
		else {
			cout << "Linha invalida, nenhum espaco foi adicionado.\n";
		}
	}
	Reservas r1(todosEspacos);
	todasReservas = r1;

	cout << counter << " espacos do hotel " << nomeHotel << " importados com sucesso!\n";

	return true;
}

void Hotel::exportAllInfo()
{
	exportInfoEspacos();
	Espaco::resetNextSpaceID();

	exportInfoClientes();
	Cliente::resetNextClientID();

	exportInfoReservas();

	exportInfoFuncionarios();
	Funcionario::resetWorkerID();

	//exportInfoRestaurantes();

	exportInfoAutocarro();
}

void Hotel::showAllInfo()
{
	cout << "Prima ENTER para ver a informacao sobre os espacos . . .\n";
	cin.ignore();
	showInfoEspacos();
	cout << "Prima ENTER para ver a informacao sobre os clientes . . .\n";
	cin.ignore();
	showInfoClientes();
	cout << "Prima ENTER para ver a informacao sobre as reservas . . .\n";
	cin.ignore();
	showInfoReservas();
	cout << "Prima ENTER para ver a informacao sobre os funcionarios . . .\n";
	cin.ignore();
	showInfoFuncionarios();
	cout << "Prima ENTER para ver a informacao sobre os restaurantes proximos do hotel . . .\n";
	cin.ignore();
	showInfoRestaurantes();
	cout << "Prima ENTER para ver a informacao sobre os autocarros do hotel . . .\n";
	cin.ignore();
	showInfoAutocarrosGestor();
}

bool Hotel::importAllInfo()
{
	bool importouClientes = false;
	bool importouEspacos = false;
	bool importouReservas = false;
	bool importouFuncionarios = false;
	bool importouRestaurantes = false;
	bool importouAutocarros = false;

	importouClientes = importInfoClientes();
	if (!importouClientes)
	{
		cout << "A importacao da informacao dos clientes falhou.\n";
		cout << "Nota: sera impossivel importar a informacao das reservas sem a informacao dos clientes.\n";
	}
	
	importouEspacos = importInfoEspacos();
	if (!importouEspacos)
	{
		cout << "A importacao da informacao dos espacos falhou.\n";
		cout << "Nota: sera impossivel importar a informacao das reservas sem a informacao dos clientes.\n";
	} 
	
	if (importouClientes && importouEspacos)
	{
		importouReservas = importInfoReservas();
		if (!importouReservas) 
		{
			cout << "A importacao da informacao das reservas falhou.\n";
		}
	}

	importouFuncionarios = importInfoFuncionarios();
	if (!importouFuncionarios) 
	{
		cout << "A importacao da informacao dos funcionarios falhou.\n";
	}

	importouRestaurantes = importInfoRestaurantes();
	if (!importouRestaurantes)
	{
		cout << "A importacao da informacao dos restaurantes falhou.\n";
	}

	importouAutocarros = importInfoAutocarro();
	if (!importouAutocarros)
	{
		cout << "A importacao da informacao dos autocarros falhou.\n";
	}

	return (importouClientes && importouEspacos && importouReservas && importouFuncionarios && importouRestaurantes && importouAutocarros);
}

void Hotel::addRestaurant(Restaurante r)
{
	this->restaurantesProximosHotel.insert(r);
	this->exportInfoRestaurantes();
}

vector<Restaurante> Hotel::getRestaurantesDoTipo(string tipoCozinha)
{
	vector<Restaurante> resultadoPesquisa;
	BSTItrIn<Restaurante> it(restaurantesProximosHotel);

	while (!it.isAtEnd())
	{
		Restaurante temp = it.retrieve();

		if (temp.getTipoCozinha() == tipoCozinha)
		{
			resultadoPesquisa.push_back(temp);
		}

		it.advance();
	}

	return resultadoPesquisa;
}

vector<Restaurante> Hotel::getRestaurantesNMetros(double n)
{
	vector<Restaurante> resultadoPesquisa;
	BSTItrIn<Restaurante> it(restaurantesProximosHotel);

	int roundedN = ceil(n);

	while (!it.isAtEnd())
	{
		Restaurante temp = it.retrieve();

		if (temp.getDistanciaHotel() <= roundedN)
		{
			resultadoPesquisa.push_back(temp);
		}

		it.advance();
	}

	return resultadoPesquisa;
}

void Hotel::exportInfoRestaurantes()
{
	//cout << "\nConfirma que deseja exportar a informacao dos Restaurantes? (s/n): ";
	//string confirm;
	//cin >> confirm;
	//cin.ignore(1000, '\n');
	//while (confirm != "s" && confirm != "n") {
	//	cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
	//	cin >> confirm;
	//	cin.ignore(1000, '\n');
	//}

	//if (confirm == "n") {
	//	cout << "Operacao cancelada a seu pedido.\n";
	//	return;
	//}

	ofstream ficheiroRest;
	string nomeFicheiro = nomeHotel + "_restaurantes.txt";

	ficheiroRest.open(nomeFicheiro);

	if (!ficheiroRest.is_open())
	{
		cerr << "Erro ao guardar a informacao dos restaurantes.\n" << endl;
		return;
	}

	cout << "A guardar a informacao no ficheiro " << nomeFicheiro << " . . ." << endl;


	BSTItrIn<Restaurante> it(this->restaurantesProximosHotel);


	// Escreve todos os restaurantes
	while (!it.isAtEnd())
	{
		ficheiroRest << it.retrieve();
		it.advance();
	}

	//ficheiroRest << '\n';
	cout << "Toda a informacao relativa aos restaurantes foi guardada com sucesso!\n\n";

	ficheiroRest.close();
}

bool Hotel::importInfoRestaurantes()
{
	ifstream ficheiroRest;

	string nomeFicheiro = nomeHotel + "_restaurantes.txt";

	ficheiroRest.open(nomeFicheiro);

	if (!ficheiroRest.is_open())
	{
		cerr << "\nNao foi possivel obter a informacao relativa aos restaurantes proximos do hotel " << nomeHotel << "!\n";
		return false;
	}

	cout << "\nA importar a informacao dos restaurantes proximos do hotel . . .\n";

	string line;
	int counter = 0;
	Restaurante restTemp("", "", 0);
	BST<Restaurante> placeholder(restTemp);

	while (getline(ficheiroRest, line)) 
	{
		if (line.at(0) == ' ')
		{
			string nomeTemp;
			double precoTemp;

			line = line.substr(1); // Deletes ' '

			size_t tempIndex = line.find_first_of(';');
			nomeTemp = line.substr(0, tempIndex);
			line = line.substr(tempIndex + 1);

			tempIndex = line.find_first_of(';');
			string precoStr = line.substr(0, tempIndex);
			precoTemp = stod(precoStr);

			Prato *p1 = new Prato(nomeTemp, precoTemp);
			restTemp.adicionaPrato(p1);
		}
		else
		{
			//Imports the last restaurant (before its modified)
			if (counter == 0) {
				BST<Restaurante> nova(restTemp);
				placeholder = nova;
			}

			if (restTemp.getMenu().size() != 0)
			{
				placeholder.insert(restTemp);
				restTemp.apagaMenu();
				counter++;
			}
			else if (restTemp.getNome() != "")
			{
				placeholder.insert(restTemp);
				counter++;
			}
				

			size_t tempIndex = line.find_first_of(';');
			string nomeTemp = line.substr(0, tempIndex);
			line = line.substr(tempIndex + 1);

			tempIndex = line.find_first_of(';');
			string tipoComidaTemp = line.substr(1, tempIndex - 1);
			line = line.substr(tempIndex + 1);

			tempIndex = line.find_first_of(';');
			string distStr = line.substr(0, tempIndex);
			double distancia = stod(distStr);

			restTemp.setNome(nomeTemp);
			restTemp.setTipoCozinha(tipoComidaTemp);
			restTemp.setDistancia(distancia);

		}
		
	}

	//Let's not forget the last one
	placeholder.insert(restTemp);
	counter++;

	this->restaurantesProximosHotel = placeholder;
	
	cout << counter << " restaurantes do hotel " << nomeHotel << " importados com sucesso!\n";

	return true;
}

void Hotel::showInfoRestaurantes()
{
	if (this->importInfoRestaurantes()) {
	
		BSTItrIn<Restaurante> it(this->restaurantesProximosHotel);

		// Escreve todos os restaurantes
		while (!it.isAtEnd())
		{
			cout << it.retrieve() << '\n';
			it.advance();
		}
	}
}

void Hotel::addPratoRestaurante(string nomeRestaurante)
{
	string nomePrato;
	cout << "Qual e o nome do prato que pretende adicionar? ";
	getline(cin, nomePrato);

	while (!isalpha(nomePrato.at(0)))
	{
		cout << "Nome invalido. Por favor insira devidamente o seu nome: ";
		getline(cin, nomePrato);
	}
	cout << endl;

	double precoPrato;
	string precoPrato_str;
	bool valid = false;

	cout << "Indique o preco do novo prato: ";
	getline(cin, precoPrato_str);

	while (!valid)
	{
		try
		{
			stod(precoPrato_str);
			valid = true;

		}
		catch (invalid_argument iArg)
		{
			cout << "O preco que inseriu nao e valido, tente outra vez: ";
			getline(cin, precoPrato_str);
		}
		catch (out_of_range oRange)
		{
			cout << "O preco que inseriu nao e valido, tente outra vez: ";
			getline(cin, precoPrato_str);
		}

		precoPrato = stod(precoPrato_str);

		if (precoPrato < 0)
		{
			cout << "O numero inserido tem de ser maior ou igual a 0... Insira um numero valido: ";
			valid = false;
			getline(cin, precoPrato_str);
			continue;
		}

	}

	

	BSTItrIn<Restaurante> it(this->restaurantesProximosHotel);
	

	while (!it.isAtEnd())
	{
		Restaurante temp = it.retrieve();

		if (it.retrieve().getNome() == nomeRestaurante)
		{
			this->restaurantesProximosHotel.remove(temp);
			Prato* prt = new Prato(nomePrato, precoPrato);
			temp.adicionaPrato(prt);
			this->restaurantesProximosHotel.insert(temp);

			cout << "DEBUG: " << temp << endl;
			cout << "Prato inserido com sucesso!" << endl;

			this->exportInfoRestaurantes();

			return;
		}
		else
		{
			it.advance();
		}

	}
	
	cout << "Restaurante nao encontrado, verifique o nome inserido e tente novamente" << endl;
	
}

void Hotel::exportInfoAutocarro()
{
	cout << "\nConfirma que deseja exportar a informacao dos Autocarros? (s/n): ";
	string confirm;
	cin >> confirm;
	cin.ignore(1000, '\n');
	while (confirm != "s" && confirm != "n") {
		cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
		cin >> confirm;
		cin.ignore(1000, '\n');
	}

	if (confirm == "n") {
		cout << "Operacao cancelada a seu pedido.\n";
		return;
	}

	ofstream ficheiroRest;
	string nomeFicheiro = nomeHotel + "_autocarros.txt";
	ficheiroRest.open(nomeFicheiro);


	if (!ficheiroRest.is_open())
	{
		cerr << "Erro na abertura do ficheiro.\n" << endl;
		return;
	}

	cout << "A guardar a informacao no ficheiro " << nomeFicheiro << " . . ." << endl;

	priority_queue<Autocarro> buffer = this->autocarrosHotel;

	// Escreve todos os restaurantes
	while (!buffer.empty())
	{
		ficheiroRest << buffer.top();
		buffer.pop();
	}

	//ficheiroRest << '\n';
	cout << "Toda a informacao relativa aos autocarros do hotel foi exportada com sucesso!\n\n";

	ficheiroRest.close();
}

bool Hotel::encontraIdAutocarro(size_t id)
{
	priority_queue <Autocarro> temp = this->autocarrosHotel;

	while (!temp.empty())
	{
		if (temp.top().getID() == id)
		{
			return true;
		}
		else
		{
			temp.pop();
		}
	}

	return false;

}

void Hotel::addAutocarro()
{
	int id;
	string id_str;
	bool valid = false;

	cout << "Indique o id do autocarro que quer adicionar: ";
	getline(cin, id_str);

	while (!valid)
	{
		try
		{
			stoi(id_str);
			valid = true;

		}
		catch (invalid_argument iArg)
		{
			cout << "O numero que tentou inserir nao e valido, tente outra vez: ";
			getline(cin, id_str);
		}
		catch (out_of_range oRange)
		{
			cout << "O numero que tentou inserir nao e valido, tente outra vez: ";
			getline(cin, id_str);
		}

		id = stoi(id_str);

		if (id < 0)
		{
			cout << "O numero inserido tem de ser maior que 0... Insira um numero valido: ";
			valid = false;
			getline(cin, id_str);
			continue;
		}

		if (encontraIdAutocarro(id))
		{
			cout << "O id inserido ja existe, como tal nao e valido. Por favor insira o correto: ";
			valid = false;
			getline(cin, id_str);
			continue;
		}

	}

	size_t capacidade;
	string capacidade_str;
	valid = false;

	cout << "Indique a capacidade do novo autocarro: ";
	getline(cin, capacidade_str);

	while (!valid)
	{
		try
		{
			stoi(capacidade_str);
			valid = true;

		}
		catch (invalid_argument iArg)
		{
			cout << "O numero que tentou inserir nao e valido, tente outra vez: ";
			getline(cin, capacidade_str);
		}
		catch (out_of_range oRange)
		{
			cout << "O numero que tentou inserir nao e valido, tente outra vez: ";
			getline(cin, capacidade_str);
		}

		capacidade = stoi(capacidade_str);

		if (capacidade < 0)
		{
			cout << "O numero inserido tem de ser maior que 0... Insira um numero valido: ";
			valid = false;
			getline(cin, id_str);
			continue;
		}

	}

	Autocarro a1(id, capacidade);
	this->autocarrosHotel.push(a1);
	cout << "Autocarro adicionado com sucesso!\n";
}

bool Hotel::importInfoAutocarro()
{
	cout << "\nConfirma que deseja importar a informacao dos autocarros? (s/n): ";
	string confirm;
	cin >> confirm;
	cin.ignore(1000, '\n');
	while (confirm != "s" && confirm != "n") {
		cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
		cin >> confirm;
		cin.ignore(1000, '\n');
	}

	if (confirm == "n") {
		cout << "Operacao cancelada a seu pedido.\n";
		return false;
	}


	ifstream ficheiroCli;
	string nomeFicheiro = nomeHotel + "_autocarros.txt";

	ficheiroCli.open(nomeFicheiro);

	if (!ficheiroCli.is_open())
	{
		cerr << "Nao foi possivel obter a informacao relativa aos autocarros do hotel " << nomeHotel << "!\n";
		return false;
	}

	cout << "A importar a informacao dos autocarros do hotel . . .\n";
	string line;

	size_t counter = 0;
	Autocarro temp(9001, 1);

	while (getline(ficheiroCli, line))
	{

		//OUTPUT autocarro:
		/*
			#1; 25;
			1-Vazio;
			2-Vazio;
			3-Vazio;
			4-Vazio;
			5-Vazio;
			6-Vazio;
			7-Vazio;
			8-Vazio;
		*/

		size_t idAutocarro = 9999;
		size_t capacidade = 9999;
		

		if (line.at(0) == '#')
		{
			int index = line.find_first_of(';');
			idAutocarro = stoi(line.substr(1, index));
			capacidade = stoi(line.substr(index + 1, line.find_last_of(';')));

			temp.setId(idAutocarro);
			temp.setNLugares(capacidade);
		}
		else if (line.at(0) == '-')
		{
			autocarrosHotel.push(temp);
			counter++;
		}
		else
		{
			int idTraco = line.find_first_of('-');
			int nLugar = stoi(line.substr(0, idTraco));
			string nome = line.substr(idTraco + 1, line.find_first_of(';') - (idTraco + 1));

			temp.setNameAt(nLugar, nome);
		}

	}

	cout << counter << " autocarros do hotel " << nomeHotel << " foram importados com sucesso!\n";
	return true;
}

void Hotel::showInfoAutocarrosGestor()
{
	cout << "Sera mostrada toda a informacao relativa aos autocarros dos hotel:" << endl << endl;
	priority_queue <Autocarro> buffer = autocarrosHotel;

	while (!buffer.empty())
	{
		Autocarro temp = buffer.top();
		buffer.pop();
		cout << temp << endl;
	}

}

void Hotel::showInfoAutocarrosCliente()
{
	cout << endl;
	cout << endl;
	cout << "Informacao relativa aos autocarros do hotel:" << endl;
	cout << endl;

	priority_queue <Autocarro> buffer = autocarrosHotel;

	while (!buffer.empty())
	{
		Autocarro temp = buffer.top();
		buffer.pop();
		cout << "Autocarro #" << temp.getID() << "; Capacidade: " << temp.getCapacidade() << "; Numero de lugares livres: " << temp.getNLugaresLivres() << ";"  << endl;
	}

	cout << endl;

}

void Hotel::reservaLugaresAutocarro()
{
	size_t nPessoas;
	string nPessoas_str;
	bool valid = false;

	cout << "Indique o numero de pessoas para o qual deseja efetuar a reserva de lugar(s) no autocarro: ";
	getline(cin, nPessoas_str);

	while (!valid)
	{
		try
		{
			stoi(nPessoas_str);
			valid = true;

		}
		catch (invalid_argument iArg)
		{
			cout << "O numero que tentou inserir nao e valido, tente outra vez: ";
			getline(cin, nPessoas_str);
		}
		catch (out_of_range oRange)
		{
			cout << "O numero que tentou inserir nao e valido, tente outra vez: ";
			getline(cin, nPessoas_str);
		}

		nPessoas = stoi(nPessoas_str);

		if (nPessoas < 0)
		{
			cout << "O numero inserido tem de ser maior que 0... Insira um numero valido: ";
			valid = false;
			getline(cin, nPessoas_str);
			continue;
		}

	}

	priority_queue <Autocarro> temp;

	while (!autocarrosHotel.empty())
	{
		Autocarro checkN = autocarrosHotel.top();
		autocarrosHotel.pop();

		if (!checkN.adicionaNPessoas(nPessoas))
		{
			temp.push(checkN);
		}
		else
		{
			autocarrosHotel.push(checkN);

			while (!temp.empty())
			{
				Autocarro tempTop = temp.top();
				autocarrosHotel.push(tempTop);
				temp.pop();
			}

			cout << "Reserva efetuada com sucesso!" << endl;
			return;
		}
	}

	cout << "Pedimos desculpa, mas de momento nao existe nenhum autocarro com lugares disponiveis suficientes para levar todas essas pessoas." << endl;
	autocarrosHotel = temp;
}