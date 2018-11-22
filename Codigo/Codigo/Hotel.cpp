#include "Hotel.h"

Hotel::Hotel(string nome, istream &ficheiro)
{
	nomeHotel = nome;

	cout << endl;

	string line;
	while (getline(ficheiro, line)) {
		size_t index = line.find_first_of(';');
		string tipoEspaco = line.substr(0, index);
		string dado1 = line.substr(index + 1, line.find(';', index + 1) - index - 1);
		index = line.find(';', index + 1) - index - 1;

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
			cout << "Linha inválida, nenhum espaço foi adicionado.\n";
		}
	}
	Reservas r1(todosEspacos);
	todasReservas = r1;

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

void Hotel::efetuaReserva(Cliente* cliente, size_t idEspaco, Date inicio, Date fim)
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
	}
	catch (EspacoNaoPertenceHotel e1) {
		cerr << "Espaco de ID:" << e1.getNumID() << " nao pertence ao hotel!" << endl;
	}
	catch (ClienteDemasiadoNovoReserva e2) {
		cerr << "O Cliente de nome " << e2.getNome() << " e demasiado novo para efetuar uma reserva!" << endl;	
	}
	catch (EspacoNaoDisponivel e3) {
		cerr << "O espaco de id = " << e3.getNumID() << " nao esta disponivel!" << endl;
	}
}

void Hotel::reservaEspaco(size_t idEspaco, Reserva res)
{
	if (!todasReservas.adicionaReserva(idEspaco, res)) {
		cout << "Algo correu mal. A reserva não pôde ser efetuada.\n";
	}
	else {
		cout << "Reserva efetuada com sucesso!\n";
		cout << "Espaco reservado: " << idEspaco << '\t' << res;
		for (size_t i = 0; i < clientesHotel.size(); i++) {
			if (clientesHotel.at(i)->getIDCliente() == res.returnidCliente()) {
				cout << " - Reserva a nome de " << clientesHotel.at(i)->getNome() << " .\n";
				break;
			}
		}
	}
}

void Hotel::alocaSupervisores()
{
	vector<Funcionario *> supervisores;
	for (size_t i = 0; i < funcionarios.size(); i++) {
		if (funcionarios.at(i)->isSupervisor())
			supervisores.push_back(funcionarios.at(i));
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
	ofstream ficheiroCli;

	string nomeFicheiro = nomeHotel + "_espacos.txt";

	ficheiroCli.open(nomeFicheiro);

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
	ofstream ficheiroEsp;

	string nomeFicheiro = nomeHotel + "_espacos.txt";

	ficheiroEsp.open(nomeFicheiro);

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
	ofstream ficheiroRes;

	string nomeFicheiro = nomeHotel + "_reservas.txt";

	ficheiroRes.open(nomeFicheiro);

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
			ficheiroRes << id << ';';
			for (size_t i = 0; i < todasReservas.returnReservas()[id].size(); i++) {
				ficheiroRes << todosEspacos.at(i)->getNumID() << '-' << todasReservas.returnReservas()[id].at(i) << ';';
			}
			ficheiroRes << '\n';
		}
		else {
			ficheiroRes << id << ";SemReservas\n";
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
	ofstream ficheiroFun;

	string nomeFicheiro = nomeHotel + "_funcionarios.txt";

	ficheiroFun.open(nomeFicheiro);

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
	ifstream ficheiroCli;

	string nomeFicheiro = nomeHotel + "_clientes.txt";

	ficheiroCli.open(nomeFicheiro);

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
	ifstream ficheiroRes;

	string nomeFicheiro = nomeHotel + "_reservas.txt";

	ficheiroRes.open(nomeFicheiro);

	cout << "\nConfirma que deseja importar a informacao dos clientes? (s/n): ";
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

	if (!ficheiroRes.is_open())
	{
		cerr << "Nao foi possivel obter a informacao relativa as reservas do hotel " << nomeHotel << "!\n";
		return false;
	}

	cout << "A importar a informacao das reservas . . .\n";
	string line;
	int failedExtracts = 0;
	while (getline(ficheiroRes, line))
	{
		int index = line.find_first_of(';');
		int index_brk = line.find(';', index + 1);
		while (index_brk != line.npos)
		{
			/*
				OUTPUT RESERVA: idReserva;idEspaço-idCliente:di/mi/yi-df/mf/yf;
			*/
			index = line.find('-', index_brk + 1);
			string id_esp_str = line.substr(index_brk + 1, index - index_brk - 1);
			int id_esp = stoi(id_esp_str);
			string id_cli_str = line.substr(index + 1, line.find(':', index + 1) - index - 1);
			int id_cli = stoi(id_cli_str);
			index = line.find(':', index + 1);

			string day_str = line.substr(index + 1, line.find('/', index + 1) - index - 1);
			int day = stoi(day_str);
			index = line.find('/', index + 1);
			string month_str = line.substr(index + 1, line.find('/', index + 1) - index - 1);
			int month = stoi(month_str);
			index = line.find('/', index + 1);
			string year_str = line.substr(index + 1, line.find('-', index + 1) - index - 1);
			int year = stoi(year_str);
			Date data_ini(day, month, year);

			index = line.find('-', index + 1);
			day_str = line.substr(index + 1, line.find('/', index + 1) - index - 1);
			day = stoi(day_str);
			index = line.find('/', index + 1);
			month_str = line.substr(index + 1, line.find('/', index + 1) - index - 1);
			month = stoi(month_str);
			index = line.find('/', index + 1);
			year_str = line.substr(index + 1, line.find('-', index + 1) - index - 1);
			year = stoi(year_str);
			Date data_fim(day, month, year);

			bool encontrou = false;
			for (size_t i = 0; i < clientesHotel.size(); i++) {
				if (id_cli == clientesHotel.at(i)->getIDCliente()) {
					encontrou = true;
					efetuaReserva(clientesHotel.at(i), id_esp, data_ini, data_fim);
				}
			}
			if (!encontrou) {
				failedExtracts++;
			}

		}
	}

	if (failedExtracts) {
		if (failedExtracts == 1)
			cout << "Falhou a extracao de 1 reserva.\n";
		else
			cout << "Falhou a extracao de " << failedExtracts << " reservas.\n";
	}

	cout << "Reservas do hotel " << nomeHotel << " importadas com sucesso!\n\n";

	return true;
}

bool Hotel::importInfoFuncionarios()
{
	ifstream ficheiroFun;

	string nomeFicheiro = nomeHotel + "_funcionarios.txt";

	ficheiroFun.open(nomeFicheiro);

	cout << "\nConfirma que deseja importar a informacao dos clientes? (s/n): ";
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
			OUTPUT SUPERVISOR: out_func//out_espaco//out_espaco//(...)
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
				string idEsp_str = line.substr(index + 1, line.find(';', index + 1) - index - 1);
				int idEsp = stoi(idEsp_str);
				for (size_t i = 0; i < todosEspacos.size(); i++) {
					if (idEsp == todosEspacos.at(i)->getNumID()) {
						func->AcrescentaEspaco(todosEspacos.at(i));
					}
				}
			}
			adicionaFuncionario(func);
		}
	}
	cout << "Funcionarios do hotel " << nomeHotel << " importados com sucesso!\n";

	cout << "Deseja re-alocar os supervisores dos espaços? (s/n): ";
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
		alocaSupervisores();
		cout << "Os supervisores foram re-alocados.\n";
	}

	cout << "A informacao dos funcionarios foi importada.\n";
	
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

	if (!importInfoClientes()) {
		cout << "A importacao da informacao dos clientes falhou.\n";
		cout << "Impossivel importar a informacao das reservas sem a informacao dos clientes.\n";
	}
	else {
		if (!importInfoReservas()) {
			cout << "A importacao da informacao das reservas falhou.\n";
		}
	}

	if (!importInfoFuncionarios()) {
		cout << "A importacao da informacao dos funcionarios falhou.\n";
	}
}
