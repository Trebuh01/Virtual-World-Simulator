#include <iostream>
#include <conio.h>
#include <string>
#include <time.h>
#include <windows.h>
#include "Generator_swiata.h"
#include "Swiat.h"

#define WPROWADZENIE_ZNAKU 224

#define WSZYSTKIE_GATUNKI 10
#define WOLNYCH_MIEJSC 20			//na 10 zwierzat - po jednym z kazdego gatunku

using namespace std;

int main()
{
	srand(time(NULL));
	int n, m;
	char wybor1 = NULL;
	char wybor2 = NULL;
	bool wczytano = true;

	cout << " +------Menu------+" << endl;
	cout << " | R: Wczytaj gre |" << endl;
	cout << " | N: Nowa gra    |" << endl;
	cout << " +----------------+" << endl;

	Swiat* swiat = nullptr;
	Generator_swiata* generator = nullptr;

	do
	{
		wczytano = true;
		wybor1 = _getch();
		switch (wybor1)
		{
		case 114:
			swiat = new Swiat();
			generator = new Generator_swiata(swiat);
			if (!generator->Wczytaj_swiat())
			{
				cout << "Wybierz jeszcze raz" << endl;
				wczytano = false;
			}
			break;
		case 110:
			do
			{
				system("cls");
				cout << " +---------Nowa gra---------+" << endl;
				cout << " |  Podaj wymiary planszy   |" << endl;
				cout << " +--------------------------+" << endl;
				
				cin >> n >> m;
				system("cls");// czyszczenie ekranu
			} while (n * m < (WSZYSTKIE_GATUNKI + WOLNYCH_MIEJSC));

			swiat = new Swiat(n, m);
			generator = new Generator_swiata(swiat);
			generator->Generowanie_swiata();
			break;
		default:
			cout << "Niepoprawny przycisk, sproboj jeszcze raz" << endl;
		}
	} while ((wybor1 != 114 || !wczytano) && wybor1 != 110);

	system("cls");
	swiat->RysujSwiat();
	
	do
	{
		wybor2 = _getch();
		switch (wybor2)
		{
			case 115:
				generator->Zapisz_swiat();
				break;
			case 13:
				swiat->WykonajTure();
				system("cls");
				swiat->RysujSwiat();
				break;
			case 110:
				system("cls");
				cout << " +---------Nowa gra---------+" << endl;
				do
				{
					cout << " |  Podaj wymiary planszy   |"<<endl;
					cout << " +--------------------------+" << endl;
					cin >> n >> m;
					system("cls");
				} while (n * m < (WSZYSTKIE_GATUNKI + WOLNYCH_MIEJSC));

				swiat = new Swiat(n, m);
				generator = new Generator_swiata(swiat);
				generator->Generowanie_swiata();
				system("cls");
				swiat->RysujSwiat();
				break;
			default:
				cout << "Zly klawisz, sprobuj jeszcze raz" << endl;
		}
	} while (true);

	delete generator;
	delete swiat;

	return 0;
}