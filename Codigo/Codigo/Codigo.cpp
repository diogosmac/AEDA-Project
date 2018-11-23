// AEDA-Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Hotel.h"

using namespace std;


#define EXIT_TO_MAIN_MENU	0
#define	EXIT_AND_CLOSE		1
#define ERROR_CODE			2

void clearScreen()
{
	cout << string(100, '\n');
}

int atendeCliente()
{
	clearScreen();
	cout << endl;
	cout << "//////////////////////////////////////\n";
	cout << "////      GestHotel - Cliente     ////\n";
	cout << "//////////////////////////////////////\n";
	cout << endl;

	// escolher nome hotel
	string nomeHotel;
	cout << "Escreva o nome do hotel que pretende reservar:" << endl;
	getline(cin, nomeHotel);

	Hotel h(nomeHotel);
	if (h.importAllInfo() != true)
	{
		cout << "A informacao relativa ao hotel " << nomeHotel << " e invalida.\n";
		cout << "A plataforma de cliente sera encerrada.\n";
		return ERROR_CODE;
	}

	cout << endl;
	cout << "Ola! Bem-vindo! ";
	cout << "Como podemos ajuda-lo hoje ? \n";
	cout << endl;
	cout << "\tr\t-\tEfetuar uma reserva no hotel " << nomeHotel << ";\n";
	cout << "\tv\t-\tVerificar disponibilidade dos espacos do hotel " << nomeHotel << ";\n";
	cout << "\tp\t-\tConferir a informacao dos precos do hotel " << nomeHotel << ";\n";
	cout << "\ts\t-\tSair da plataforma de cliente.\n";
	cout << endl;

	string reply;
	cout << "Opcao: ";
	cin >> reply;
	cin.ignore();
	bool validInput;
	while (reply != "s") {
		validInput = true;
		if (reply.length() == 1) {
			char rep = reply.at(0);
			switch (rep)
			{
			case 'r':
				cout << endl;
				cout << "placeholder: reservar espaco;\n";
				cout << endl;
				break;

			case 'v':
				cout << endl;
				cout << "placeholder: verificar disponibilidade;\n";
				cout << endl;
				break;

			case 'p':
				cout << endl;
				cout << "placeholder: conferir precos;\n";
				cout << endl;
				break;

			case 's':
				break;

			default:
				validInput = false;
				break;
			}
		}
		else
		{
			validInput = false;
		}

		if (!validInput)
		{
			cout << "Por favor insira uma opcao valida!\n\n";
		}

		if (reply != "s") {
			cout << "Como podemos ajuda-lo hoje ? \n";
			cout << endl;
			cout << "\tr\t-\tEfetuar uma reserva no hotel " << nomeHotel << ";\n";
			cout << "\tv\t-\tVerificar disponibilidade dos espacos do hotel " << nomeHotel << ";\n";
			cout << "\tp\t-\tConferir a informacao dos precos do hotel " << nomeHotel << ";\n";
			cout << "\ts\t-\tSair da plataforma de cliente.\n";
			cout << endl;

			cout << "Opcao: ";
			cin >> reply;
			cin.ignore();
		}
	}

	cout << "Obrigado por reservar connosco. Esperamos ve-lo em breve!\n";
	cout << endl;
	cout << "\tm\t-\tSair para o menu principal;\n";
	cout << "\tf\t-\tFechar a plataforma.\n";
	cout << endl;

	string confirm;
	cin >> confirm;
	cin.ignore();
	while (confirm != "m" && confirm != "f")
	{
		cout << "Resposta invalida, por favor insira \"m\" ou \"f\" para responder: ";
		cin >> confirm;
		cin.ignore();
	}
	if (confirm == "m")
	{
		cout << "Saindo para o menu principal.\n";
		cout << "Prima ENTER para encerrar a plataforma de cliente . . .\n";
		cin.ignore();
		clearScreen();
		return EXIT_TO_MAIN_MENU;
	}


	cout << "Prima ENTER para encerrar a plataforma de cliente . . .\n";
	cin.ignore();
	clearScreen;
	return EXIT_AND_CLOSE;
}

int atendeGestor()
{
	clearScreen();
	cout << endl;
	cout << "/////////////////////////////////////\n";
	cout << "////      GestHotel - Gestor     ////\n";
	cout << "/////////////////////////////////////\n";
	cout << endl;

	cout << "Pretende criar um novo hotel, ou modificar um ja existente na plataforma?\n";
	cout << endl;
	cout << "\tc\t-\tCriar um novo hotel;\n";
	cout << "\tm\t-\tModificar um hotel existente;\n";
	cout << "\ts\t-\tSair da plataforma de gestao.\n";
	cout << endl;

	string reply;
	cout << "Opcao: ";
	cin >> reply;
	cin.ignore();
	bool validInput;
	while (reply != "s") {
		validInput = true;
		if (reply.length() == 1) {
			char rep = reply.at(0);
			switch (rep)
			{
			case 'c':
				cout << endl;
				cout << "placeholder: criar hotel;\n";
				cout << endl;
				break;

			case 'm':
				cout << endl;
				cout << "placeholder: modificar hotel;\n";
				cout << endl;
				break;

			case 's':
				break;

			default:
				validInput = false;
				break;
			}
		}
		else
		{
			validInput = false;
		}

		if (!validInput)
		{
			cout << "Por favor insira uma opcao valida!\n\n";
		}

		if (reply != "s") {
			cout << "Pretende criar um novo hotel, ou modificar um ja existente na plataforma?\n";
			cout << endl;
			cout << "\tc\t-\tCriar um novo hotel;\n";
			cout << "\tm\t-\tModificar um hotel existente;\n";
			cout << "\ts\t-\tSair da plataforma de gestao.\n";
			cout << endl;

			cout << "Opcao: ";
			cin >> reply;
			cin.ignore();
		}
	}

	cout << "Obrigado por trabalhar connosco. Esperamos ve-lo em breve!\n";
	cout << endl;
	cout << "\tm\t-\tSair para o menu principal;\n";
	cout << "\tf\t-\tFechar a plataforma.\n";
	cout << endl;

	string confirm;
	cin >> confirm;
	cin.ignore();
	while (confirm != "m" && confirm != "f")
	{
		cout << "Resposta invalida, por favor insira \"m\" ou \"f\" para responder: ";
		cin >> confirm;
		cin.ignore();
	}
	if (confirm == "m")
	{
		cout << "Saindo para o menu principal.\n";
		cout << "Prima ENTER para encerrar a plataforma de cliente . . .\n";
		cin.ignore();
		clearScreen();
		return EXIT_TO_MAIN_MENU;
	}


	cout << "Prima ENTER para encerrar a plataforma de cliente . . .\n";
	cin.ignore();
	clearScreen();
	return EXIT_AND_CLOSE;
}

int mostrarAjuda()
{
	cout << endl;
	cout << "Na plataforma de cliente, e possivel, relativamente a um dos nossos hoteis:\n";
	cout << "\t\t- Efetuar uma reserva;\n";
	cout << "\t\t- Verificar a disponibilidade dos espacos;\n";
	cout << "\t\t- Conferir a informacao de precos.\n";
	cout << endl;
	cout << "Na plataforma de gestao, e possivel:\n";
	cout << "\t\t- Criar um novo hotel, para ser gerido atraves da plataforma;\n";
	cout << "\t\t- Verificar a informacao de um dos hoteis ja existentes na plataforma;\n";
	cout << "\t\t- Modificar a informacao de um dos hoteis previamente adicionados.\n";
	cout << endl;

	return EXIT_TO_MAIN_MENU;
}

bool atendimento()
{
	cout << "/////////////////////////////\n";
	cout << "////      GestHotel      ////\n";
	cout << "/////////////////////////////\n";
	cout << endl;
	cout << "Pretende utilizar a nossa plataforma enquanto cliente, ou enquanto gestor de um dos nossos hoteis?\n";
	cout << endl;
	cout << " [o seu input]\t-\t[acao a realizar]\n";
	cout << "\tc\t-\tutilizar a plataforma de cliente\n";
	cout << "\tg\t-\tutilizar a plataforma de gestao\n";
	cout << "\ta\t-\tobter ajuda\n";
	cout << "\ts\t-\tsair do programa\n\n";

	string reply;
	cout << "Opcao: ";
	cin >> reply;
	cin.ignore();
	bool validInput;
	while (reply != "s") {
		validInput = true;
		if (reply.length() == 1) {
			char rep = reply.at(0);
			int atendeuCliente;
			int atendeuGestor;
			switch (rep)
			{
			case 'c':
				atendeuCliente = atendeCliente();
				if (atendeuCliente == ERROR_CODE)
				{
					cout << "A plataforma de cliente obteve um erro inesperado!\n";
					cout << "Pretende encerrar a plataforma? (s/n): ";
					string confirm;
					cin >> confirm;
					cin.ignore();
					while (confirm != "s" && confirm != "n")
					{
						cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
						cin >> confirm;
						cin.ignore();
					}
					if (confirm == "s")
					{
						cout << "A plataforma sera agora encerrada.\n";
						return false;
					}
				}
				else if (atendeuCliente == EXIT_TO_MAIN_MENU)
				{
					cout << "A plataforma de cliente foi encerrada com sucesso!\n\n";
				}
				else
				{
					cout << "A plataforma de cliente foi encerrada com sucesso!\n";
					reply = "s";
				}
				break;

			case 'g':
				atendeuGestor = atendeGestor();
				if (atendeuGestor == ERROR_CODE)
				{
					cout << "A plataforma de cliente obteve um erro inesperado!\n";
					cout << "Pretende encerrar a plataforma? (s/n): ";
					string confirm;
					cin >> confirm;
					cin.ignore();
					while (confirm != "s" && confirm != "n")
					{
						cout << "Resposta invalida, por favor insira \"s\" ou \"n\" para responder: ";
						cin >> confirm;
						cin.ignore();
					}
					if (confirm == "s")
					{
						cout << "A plataforma sera agora encerrada.\n";
						return false;
					}
				}
				else if (atendeuGestor == EXIT_TO_MAIN_MENU)
				{
					cout << "A plataforma de gestao foi encerrada com sucesso!\n\n";
				}
				else
				{
					cout << "A plataforma de gestao foi encerrada com sucesso!\n";
					reply = "s";
				}
				break;

			case 'a':
				if (mostrarAjuda() != EXIT_TO_MAIN_MENU)
				{
					cout << "Ocorreu um erro ao exibir o painel de ajuda!\n\n";
				}
				break;

			case 's':
				break;

			default:
				validInput = false;
				break;
			}
		}
		else {
			validInput = false;
		}

		if (!validInput)
		{
			cout << "Por favor insira uma opcao valida!\n\n";
		}

		if (reply != "s") {
			cout << "Pretende utilizar a nossa plataforma enquanto cliente, ou enquanto gestor de um dos nossos hoteis?\n";
			cout << endl;
			cout << " [o seu input]\t-\t[acao a realizar]\n";
			cout << "\tc\t-\tUtilizar a plataforma de cliente;\n";
			cout << "\tg\t-\tUtilizar a plataforma de gestao;\n";
			cout << "\ta\t-\tObter ajuda;\n";
			cout << "\ts\t-\tSair do programa.\n\n";

			cout << "Opcao: ";
			cin >> reply;
			cin.ignore();
		}

	}
	
	cout << "Obrigado por utilizar a nossa plataforma. Esperamos que tenha tido uma boa experiencia!\n";
	cout << "Prima ENTER para encerrar a plataforma . . .\n";
	cin.get();

	return true;
}

int main()
{
	if (atendimento() == false) {
		cout << "Pedimos desculpa pelo incomodo, estamos a trabalhar para reparar a plataforma! :)\n";
		cout << "Prima ENTER para encerrar a plataforma . . .\n";
		cin.ignore();
		cin.get();
	}

	return 0;
}
