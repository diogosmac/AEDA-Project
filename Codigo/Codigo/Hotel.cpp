#include "Hotel.h"

Hotel::Hotel(string nome)
{
	nomeHotel = nome;

	importInfoEspacos();

	//string line;
	//while (getline(ficheiro, line) && !line.empty()) {
	//	size_t index = line.find_first_of(';');
	//	string tipoEspaco = line.substr(index + 1, line.find(';', index + 1) - index - 1);
	//	index = line.find(';', index + 1);
	//	string dado1 = line.substr(index + 1, line.find(';', index + 1) - index - 1);
	//	index = line.find(';', index + 1);

	//	if (tipoEspaco == "Quarto") {
	//		string dado2 = line.substr(index + 1);

	//		bool duplo = true;
	//		bool frente = true;
	//		if (dado1.at(0) == '-') duplo = false;
	//		if (dado2.at(0) == '-') frente = false;
	//		Espaco* e = new Quarto(duplo, frente);
	//		todosEspacos.push_back(e);
	//		cout << "Quarto (numero " << e->getNumID() << ") adicionado.\n";
	//	}
	//	else if (tipoEspaco == "SalaDeReunioes") {
	//		string dado2 = line.substr(index + 1, line.find(';', index + 1) - index - 1);
	//		index = line.find(';', index + 1) - index - 1;
	//		string dado3 = line.substr(index + 1);

	//		bool video = true;
	//		bool audio = true;
	//		int cap = stoi(dado1);
	//		if (dado2.at(0) == '-') video = false;
	//		if (dado3.at(0) == '-') audio = false;
	//		Espaco* e = new SalaDeReunioes(cap, video, audio);
	//		todosEspacos.push_back(e);
	//		cout << "Sala de Reunioes (numero " << e->getNumID() << ") adicionada.\n";
	//	}
	//	else {
	//		cout << "Linha invalida, nenhum espaco foi adicionado.\n";
	//	}
	//}
	//Reservas r1(todosEspacos);
	//todasReservas = r1;

	cout << endl;
}

size_t Hotel::nEspacos() const {
	return this->todosEspacos.size();
}

vector<Espaco *> Hotel::getTodosEspacos() const
{
	return this->todosEspacos;
}

vector<Cliente *> Hotel::getClientes() const {
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

// void Hotel::adicionaEspacoOcupado(Espaco * espaco)
// {
// 	this->todosEspacos.push_back(espaco);
// }

void Hotel::adicionaEspaco(Espaco * espaco)
{
	this->todosEspacos.push_back(espaco);
	todasReservas.updateReservas(espaco);

}

void Hotel::adicionaFuncionario(Funcionario * func)
{
	this->funcionarios.push_back(func);
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

	for (size_t i = 0; i < this->clientesHotel.size(); i++)
	{
		if ((this->clientesHotel.at(i)->getNome() == nome) && (this->clientesHotel.at(i)->getIDCliente() == idCliente))
		{
			encontrado = true;
			this->clientesHotel.erase(this->clientesHotel.begin() + i);
		}
	}

	if (!encontrado)
	{
		throw ClienteNaoEncontrado(nome);
	}
}

bool Hotel::verificaCliente(string nome, size_t idade)
{
	for (size_t i = 0; i < this->clientesHotel.size(); i++)
	{
		if (this->clientesHotel.at(i)->getNome() == nome && this->clientesHotel.at(i)->getIdade() == idade)
		{
			return true;
		}
	}

	return false;
}

int Hotel::idCliente(string nome, size_t idade)
{

	for (size_t i = 0; i < this->clientesHotel.size(); i++)
	{
		if (this->clientesHotel.at(i)->getNome() == nome && this->clientesHotel.at(i)->getIdade() == idade)
		{
			return clientesHotel.at(i)->getIDCliente();
		}
	}

	return -1;
}

void Hotel::adicionaCliente(string nome, size_t idade)
{
	if (!verificaCliente(nome, idade))
	{
		Cliente *c1 = new Cliente(nome, idade);
		this->clientesHotel.push_back(c1);
	}
}

Cliente * Hotel::encontraCliente(string nome)
{
	for (size_t i = 0; i < clientesHotel.size(); i++) {
		if (clientesHotel.at(i)->getNome() == nome) {
			return clientesHotel.at(i);
		}
	}
	throw ClienteNaoEncontrado(nome);
}

bool Hotel::efetuaReserva(Cliente* cliente, size_t idEspaco, Date inicio, Date fim)
{
	try {
		if (cliente->getIdade() < 18) {
			throw ClienteDemasiadoNovoReserva(cliente->getNome());
		}

		bool espacoExiste = false;
		for (size_t i = 0; i < todosEspacos.size(); i++) {
			if (todosEspacos[i]->getNumID() == idEspaco)
				espacoExiste = true;
		}
		if (!espacoExiste) {
			throw EspacoNaoPertenceHotel(idEspaco);
		}

		bool espacoDisponivel = true;

		Reserva res(cliente->getIDCliente(), inicio, fim);
		for (size_t i = 0; i < todasReservas.returnReservas().at(idEspaco).size(); i++) {
			if (res - todasReservas.returnReservas().at(idEspaco).at(i))
				espacoDisponivel = false;
		}
		if (!espacoDisponivel) {
			throw EspacoNaoDisponivel(idEspaco);
		}
		else {
			reservaEspaco(idEspaco, res);
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
	else {
		cout << "Reserva efetuada com sucesso!\n";
		cout << "Espaco reservado: " << idEspaco << '\t';
		for (size_t i = 0; i < clientesHotel.size(); i++) {
			if (clientesHotel.at(i)->getIDCliente() == res.returnidCliente()) {
				cout << "Reserva em nome de " << clientesHotel.at(i)->getNome() << " : ID do Cliente - " << res << '\n';
				break;
			}
		}
	}
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
	//Escreve todos os clientes
	for (size_t i = 0; i < this->clientesHotel.size(); i++)
	{
		if (i == this->clientesHotel.size() - 1)
		{
			ficheiroCli << clientesHotel.at(i) << '\n';
			cout << "Toda a informacao relativa aos clientes foi guardada com sucesso!\n\n";
		}
		else
		{
			ficheiroCli << clientesHotel.at(i) << '\n';
		}
	}

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
	//Escreve todos os espaços
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
	//Escreve todas as reservas
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
	//Escreve todas as reservas
	for (size_t i = 0; i < funcionarios.size(); i++) {
		ficheiroFun << funcionarios.at(i) << '\n';
		if (i == funcionarios.size() - 1) {
			cout << "Toda a informacao relativa aos funcionarios foi guardada com sucesso!\n";
		}
	}

	ficheiroFun.close();
}

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
			OUTPUT CLIENTE: idCliente;nomeCliente;idadeCliente
		*/
		int index = line.find_first_of(';');
		string nome = line.substr(index + 1, line.find(';', index + 1) - index - 1);
		index = line.find(';', index + 1) + 1;
		string idade_str = line.substr(index);
		int idade = stoi(idade_str);
		adicionaCliente(nome, idade);
	}
	cout << "Clientes do hotel " << nomeHotel << " importados com sucesso!\n\n";

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
			//index = line.find(';', index + 1);
			while (line.find(';', index + 1) != line.npos) {
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

				bool encontrou = false;
				for (size_t i = 0; i < clientesHotel.size(); i++) {
					if (clientesHotel.at(i)->getIDCliente() == idCli) {
						encontrou = true;
						if (!efetuaReserva(clientesHotel.at(i), idEsp, data_ini, data_fim))
							failedExtracts++;
					}
				}
				if (!encontrou) {
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

	cout << "Reservas do hotel " << nomeHotel << " importadas com sucesso!\n\n";

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
	while (getline(ficheiroFun, line))
	{
		/*
			OUTPUT FUNCIONÁRIO: idFunc;nomeFunc;supervisor(yes/no)
			OUTPUT SUPERVISOR: out_func//idEsp,idEsp(...)
		*/
		int index = line.find_first_of(';');
		string nome = line.substr(index + 1, line.find(';', index + 1) - index - 1);
		index = line.find(';', index + 1);
		if (line.find('/', index + 1) == line.npos) {
			Funcionario* func = new Funcionario(nome);
			adicionaFuncionario(func);
		}
		else {
			Funcionario* func = new Supervisor(nome);
			index = line.find('/', index + 1) + 1;
			while (index != line.npos) {
				string idEsp_str = line.substr(index + 1, line.find(',', index + 1) - index - 1);
				int idEsp = stoi(idEsp_str);
				for (size_t i = 0; i < todosEspacos.size(); i++) {
					if (idEsp == todosEspacos.at(i)->getNumID()) {
						func->AcrescentaEspaco(todosEspacos.at(i));
					}
				}
				index = line.find(',', index + 1);
			}
			adicionaFuncionario(func);
		}
	}
	cout << "Funcionarios do hotel " << nomeHotel << " importados com sucesso!\n";

	cout << "Deseja re-alocar os supervisores dos espacos? (s/n): ";
	cin >> confirm;
	cin.ignore(1000, '\n');
	while (confirm != "s" && confirm != "n")
	{
		cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
		cin >> confirm;
		cin.ignore(1000, '\n');
	}
	if (confirm == "s")
	{
		try {
			alocaSupervisores();
			cout << "Os supervisores foram re-alocados.\n";
		}
		catch (NaoHaSupervisores e1) {
			cout << "O hotel " << e1.getNomeHotel() << " nao tem qualquer supervisor.\n";
		}
	}

	cout << "A informacao dos funcionarios foi importada.\n";
	
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
	while (getline(ficheiroEsp, line) && !line.empty())
	{
		size_t index = line.find_first_of(';');
		string tipoEspaco = line.substr(index + 1, line.find(';', index + 1) - index - 1);
		index = line.find(';', index + 1);
		string dado1 = line.substr(index + 1, line.find(';', index + 1) - index - 1);
		index = line.find(';', index + 1);

		if (tipoEspaco == "Quarto") {
			string dado2 = line.substr(index + 1);

			bool duplo = true;
			bool frente = true;
			if (dado1.at(0) == '-') duplo = false;
			if (dado2.at(0) == '-') frente = false;
			Espaco* e = new Quarto(duplo, frente);
			todosEspacos.push_back(e);
			cout << "Quarto (numero " << e->getNumID() << ") adicionado.\n";
		}
		else if (tipoEspaco == "SalaDeReunioes") {
			string dado2 = line.substr(index + 1, line.find(';', index + 1) - index - 1);
			index = line.find(';', index + 1) - index - 1;
			string dado3 = line.substr(index + 1);

			bool video = true;
			bool audio = true;
			int cap = stoi(dado1);
			if (dado2.at(0) == '-') video = false;
			if (dado3.at(0) == '-') audio = false;
			Espaco* e = new SalaDeReunioes(cap, video, audio);
			todosEspacos.push_back(e);
			cout << "Sala de Reunioes (numero " << e->getNumID() << ") adicionada.\n";
		}
		else {
			cout << "Linha invalida, nenhum espaco foi adicionado.\n";
		}
	}
	Reservas r1(todosEspacos);
	todasReservas = r1;

	cout << "Espacos do hotel " << nomeHotel << " importados com sucesso!\n";

	return true;
}

void Hotel::exportAllInfo()
{
	exportInfoEspacos();
	exportInfoClientes();
	exportInfoReservas();
	exportInfoFuncionarios();
}

void Hotel::importAllInfo()
{
	bool importouClientes, importouEspacos;
	if (!(importouClientes = importInfoClientes()))
	{
		cout << "A importacao da informacao dos clientes falhou.\n";
		cout << "Nota: sera impossivel importar a informacao das reservas sem a informacao dos clientes.\n";
	}
	
	if (!(importouEspacos = importInfoEspacos()))
	{
		cout << "A importacao da informacao dos espacos falhou.\n";
		cout << "Nota: sera impossivel importar a informacao das reservas sem a informacao dos clientes.\n";
	} 
	
	if (importouClientes && importouEspacos)
	{
		if (!importInfoReservas()) {
			cout << "A importacao da informacao das reservas falhou.\n";
		}
	}

	if (!importInfoFuncionarios()) {
		cout << "A importacao da informacao dos funcionarios falhou.\n";
	}
}
