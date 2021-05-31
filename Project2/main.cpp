#include "robot.h"
#include "jogador.h"
#include "post.h"
#include "game.h"
#include "geral.h"
#include <fstream>
#include <vector>
using namespace std;

/*T7_G11
ANA SOFIA TEIXEIRA UP201806466 MIEIC T7*/

int main() {
	int option = menu();
	if (option == 1) { //Mostra as instruções do Jogo
		fstream newfile;
		newfile.open("RULES.txt", ios::in); //abre o ficheiro
		if (newfile.is_open()) { //verifica se o ficheiro está aberto
			string auxiliar;
			while (getline(newfile, auxiliar)) { //lê os dados do ficheiro e passa para a string auxiliar
				cout << auxiliar << "\n"<<endl; //imprime os dados guardados na string
			}
			newfile.close(); //fecha o objeto do ficheiro criado no início.
		}
	}
	if (option == 0) { // Exit the game
		cout << "See you soon..." << "\n" << endl;
	}
	if (option == 2) { //Play the game
		char again;
		string mazeSelected = choose_maze(); //o jogador escolhe que labirinto quer jogar
		Game board = Game(mazeSelected);
		board.playing();
		cout << "Play again? (y/n)" << endl; // se o jogador quiser jogar novamente
		cin >> again;
		while (!(again == 'y' || again == 'n' || again == 'Y' || again == 'N')) { //verifica se o jogador escreveu y ou n (Y ou N)
			cout << "Play again? (y/n)" << endl;
			cin >> again;
		}
		if (again == 'y' || again == 'Y') {
			mazeSelected = choose_maze(); //o jogador escolhe que labirinto quer jogar
			board = Game(mazeSelected);
			board.playing();
		}
	}
	if (option == 3) {
		string mazeSelected = choose_maze(); //o jogador escolhe que labirinto quer jogar
		Game board1 = Game(mazeSelected);
		board1.printwinners();
	}
	return 0;
}
