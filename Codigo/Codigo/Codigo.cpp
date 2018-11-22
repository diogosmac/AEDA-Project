// AEDA-Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Hotel.h"

using namespace std;

int main()
{
	string nomeHotel;
	cout << "\nEscreva o nome do hotel que pretende reservar:" << endl;
	getline(cin, nomeHotel);

	ifstream ficheiro;
	string nomeFicheiro = nomeHotel + "_espacos.txt";

	ficheiro.open(nomeFicheiro);
	while (!ficheiro.is_open()) {
		string confirm;
		cout << "Nao foi possivel abrir o ficheiro " << nomeFicheiro << "\n";
		cout << "Deseja importar os dados de um ficheiro externo? (s/n): ";
		cin.ignore(1000, '\n');
		cin >> confirm;
		while (confirm != "s" && confirm != "n") {
			cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
			cin >> confirm;
			cin.ignore(1000, '\n');
		}

		if (confirm == "n") {
			cout << "\nO programa sera agora encerrado.\n";
			cin.ignore();
			cin.get();
			exit(1);
		}

		cout << "\nInsira o nome do ficheiro: ";
		cin >> nomeFicheiro;
		if (nomeFicheiro.length() < 4 || nomeFicheiro.substr(nomeFicheiro.length() - 4, 4) != ".txt") {
			nomeFicheiro += ".txt";
		}

		ficheiro.open(nomeFicheiro);
	}

	cin.ignore(1000, '\n');
	
	Hotel h(nomeHotel, ficheiro);

	ficheiro.close();

	//h.adicionaCliente("Pedro", 19);
	//h.adicionaCliente("Diogo Machado", 19);
	//h.adicionaCliente("Margarida", 19);

	/*h.importInfoClientes();*/

	cout << "N Clientes: " << h.nClientes() << endl;
	cout << "N Espacos: " << h.nEspacos() << "\n\n";

	//Date d1(23, 11, 2018);
	//Date d2(26, 11, 2018);
	//Date d3(28, 11, 2018);
	//Date d4(29, 11, 2018);
	//h.efetuaReserva(h.getClientes().at(1), 4, d1, d2);
	//h.efetuaReserva(h.getClientes().at(1), 4, d3, d4);
	
	/*h.importInfoReservas();*/

	//Funcionario* f1 = new Funcionario("Omar Salgado");
	//Funcionario* f2 = new Supervisor("Jacinto Leite");
	//Funcionario* f3 = new Supervisor("Adolfo Dias");
	//h.adicionaFuncionario(f1);
	//h.adicionaFuncionario(f2);
	//h.adicionaFuncionario(f3);
	//h.alocaSupervisores();
	
	/*h.importInfoFuncionarios();*/

	h.importAllInfo();

	//h.exportInfoClientes();
	//h.exportInfoEspacos();
	//h.exportInfoReservas();
	//h.exportInfoFuncionarios();

	h.exportAllInfo();

    cout << "\nBuildou sem problemas\n"; 

	cout << "\nPrima ENTER para sair do programa . . .";
	cin.ignore(9999999, '\n');
	cin.clear();

	return 0;
}
