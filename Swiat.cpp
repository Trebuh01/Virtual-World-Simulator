#include <stdio.h>
#include <conio.h>
#include <string>
#include "Organizm.h"
#include "Czlowiek.h"
#include "Swiat.h"
#include <windows.h>
#include "Wilk.h"
#include "Owca.h"
#include "Lis.h"
#include "Zolw.h"
#include "Antylopa.h"

#include "Trawa.h"
#include "Mlecz.h"
#include "Guarana.h"
#include "Wilcze_jagody.h"
#include "Barszcz_sosnowskiego.h"


#define WPROWADZENIE_ZNAKU 224
#define UP_KEY 72
#define RIGHT_KEY 77
#define DOWN_KEY 80
#define LEFT_KEY 75
#define KOMENTARZE_NA_ORG 5

using namespace std;

Swiat::Swiat() : Swiat(20, 20){}

Swiat::Swiat(int n, int m)
{
	_n = n;
	_m = m;

	liczba_Org_Bez_Nowonarodzonych = {};
	liczba_Org = {};
	tura = {};
	czy_Czlowiek_Zyje = false;
	czlowiek = nullptr;
	komentarze = new string[KOMENTARZE_NA_ORG * n * m];
	liczba_Komentarzy = {};

	organizmy = new Organizm * [_n * _m];

	plansza = new Organizm ** [m + 2];

	for (int y = 0; y < m + 2; y++)
	{
		plansza[y] = new Organizm * [n + 2];

		for (int x = 0; x < n + 2; x++)
		{
			plansza[y][x] = nullptr;
		}
	}
}

void Swiat::SetRozmiarPlanszy(int n, int m)
{
	_n = n;
	_m = m;
}

void Swiat::SetPolePlanszy(int x, int y, Organizm* org)
{
	plansza[y][x] = org;
}

void Swiat::SetTura(int ptura)
{
	tura = ptura;
}

void Swiat::DodajKomentarz(string komentarz)
{
	komentarze[liczba_Komentarzy++] = komentarz;
}

int Swiat::GetN() const
{
	return _n;
}

int Swiat::GetM() const
{
	return _m;
}

int Swiat::GetLiczbaOrg() const
{
	return liczba_Org;
}

int Swiat::GetTura() const
{
	return tura;
}

Organizm* Swiat::GetPolePlanszy(int x, int y) const
{
	if ((x > 0) && (x < (_n + 2)) && (y > 0) && (y < (_m + 2)))
	{
		return plansza[y][x];
	}
	return nullptr;
}

Organizm* Swiat::GetOrganizm(int i) const
{
	return organizmy[i];
}

Czlowiek* Swiat::GetCzlowiek() const
{
	return czlowiek;
}

void Swiat::DodajOrganizm(Organizm* org)
{
	string komentarz;
	if ((liczba_Org < _n * _m) && (plansza[org->GetY()][org->GetX()] == nullptr)) 
	{
		organizmy[liczba_Org] = org;
		liczba_Org++;
		if (liczba_Org > 1 && org->CzyZwierze())
		{
			Organizm* temp;
			int i = 0;
			while (i < liczba_Org && organizmy[i]->GetInicjatywa() >= org->GetInicjatywa())
			{
				i++;
			}
			for (int j = liczba_Org - 2; j >= i; j--)
			{
				temp = organizmy[j];
				organizmy[j] = organizmy[j + 1];
				organizmy[j + 1] = temp;
			}
		}
		org->Rysowanie();
		if (typeid(*org) == typeid(Czlowiek))
		{
			czy_Czlowiek_Zyje = true;
			czlowiek = dynamic_cast<Czlowiek*>(org);
		}
		komentarz = org->GetNazwa() + ": \t\tnarodziny nowego organizmu na polu (" +to_string(org->GetX()) + ", " + to_string(org->GetY()) + ")";

		this->DodajKomentarz(komentarz);
	}
	else if ((liczba_Org < _n * _m) && (plansza[org->GetY()][org->GetX()] != nullptr))
	{
		delete org;
	}
	else if (liczba_Org >= _n * _m)
	{
		komentarz = "Przpelnienie - brak mozliwosci dodania wiekszej ilosci organizmow";
		this->DodajKomentarz(komentarz);
	}
	
}

void Swiat::UsunOrganizm(Organizm* org)
{
	string komentarz;
	Organizm* temp;
	Organizm* atakowany;
	bool uciekl = true;
	if (org == czlowiek && czlowiek->CzyUmiejetnoscAktywowana())
	{
		atakowany = plansza[org->GetY()][org->GetX()];
		if (atakowany == nullptr)
		{
			czlowiek->Rysowanie();
		}
		else
		{
			atakowany->Kolizja(czlowiek);
		}
	}
	if (org != czlowiek || !czlowiek->CzyUmiejetnoscAktywowana())
	{
		atakowany = plansza[org->GetY()][org->GetX()];
		if (atakowany == org)
		{
			plansza[org->GetY()][org->GetX()] = nullptr;
		}
		if (typeid(*org) == typeid(Czlowiek))
		{
			czy_Czlowiek_Zyje = false;
		}
		for (int i = 0; i < liczba_Org; i++)
		{
			if (organizmy[i] == org)
			{
				organizmy[i] = nullptr;
				for (int j = i; j < liczba_Org - 1; j++)
				{
					temp = organizmy[j];
					organizmy[j] = organizmy[j + 1];
					organizmy[j + 1] = temp;
				}
				i = liczba_Org;
			}
			
		}
		liczba_Org--;
		liczba_Org_Bez_Nowonarodzonych--;

		komentarz = org->GetNazwa() + ": \tsmierc organizmu";
		this->DodajKomentarz(komentarz);
		delete org;
	}
}

void Swiat::GenerowaniePustychPunktow(int x, int y, int* positionX, int* positionY, int* ruch, int* pointsCount)
{
	
	int kierunek[4][2] = { {0,-1},{1,0},{0,1},{-1,0} }; //definicja kierunków
	for (int i = 0; i < 4; i++) {
		int newX = x + kierunek[i][0];
		int newY = y + kierunek[i][1];
		if (newX >= 1 && newY >= 1 && newX <= _n && newY <= _m && plansza[newY][newX] == nullptr) {
			positionX[*pointsCount] = newX;
			positionY[*pointsCount] = newY;
			ruch[*pointsCount] = i + 1; //i+1 to numer kierunku odpowiadaj¹cy temu w kierunek[]
			(*pointsCount)++;
		}
	}

}

void Swiat::WykonajTure()
{
	liczba_Org_Bez_Nowonarodzonych = liczba_Org;
	if (czy_Czlowiek_Zyje)
	{
		cout << endl;
		if (!czlowiek->CzyUmiejetnoscAktywowana())
		{
			cout << "Wcisnij X, aby aktywowac umiejetnosc." << endl;
		}
		else if (czlowiek->CzyUmiejetnoscAktywowana() && czlowiek->GetSila() > 5)
		{
			czlowiek->SetSila(czlowiek->GetSila() - 1);
			int sila_po_zmniejszeniu = czlowiek->GetSila();
			if (sila_po_zmniejszeniu == 5)czlowiek->SetCzyPiecTur(true);
		}
		cout << "Uzyj strzalek, aby poruszac postacia." << endl;
	}
	bool czyRuszac = true;

	if (czy_Czlowiek_Zyje)
	{
		unsigned char znak = _getch();
		unsigned char znak2 = '0';

		switch (znak)
		{
			case 'x':
				if (!czlowiek->CzyUmiejetnoscAktywowana())
				{
					czlowiek->AktywujUmiejetnosc();
					znak2 = _getch();
				}
				if ((znak2 != WPROWADZENIE_ZNAKU) || (znak2 == '0' && czlowiek->CzyUmiejetnoscAktywowana()))
				{
					cout << "Zly klawisz" << endl;
					czyRuszac = false;
					
				}
				break;
			case WPROWADZENIE_ZNAKU:
				znak = _getch();
				czlowiek->SetRuch(znak);
				break;
			default:
				cout << "Zly klawisz" << endl;
				czyRuszac = false;
				break;
		}
	}
	if (czyRuszac) AkcjaWszystkich();
}

void Swiat::AkcjaWszystkich()
{
	Organizm* org;
	Organizm* atakowany;
	Organizm* atakujacy;
	
	int i = 0;

	while (i < liczba_Org_Bez_Nowonarodzonych)
	{
		org = organizmy[i];
		org->Akcja();
		atakowany = plansza[org->GetY()][org->GetX()];
		if (atakowany == nullptr || org->GetOstatniRuch() == 0)org->Rysowanie();
		else atakowany->Kolizja(org);
		i++;
	}

	for (int i = 0; i < liczba_Org_Bez_Nowonarodzonych; i++)
	{
		org = organizmy[i];
		org->SetWiek(org->GetWiek() + 1);
	}

	if (czy_Czlowiek_Zyje && czlowiek->CzyPiecTur()==true && czlowiek->CzyUmiejetnoscAktywowana())
	{
		czlowiek->SetTuryStanuUmiejetnosci(czlowiek->GetTuryStanuUmiejetnosci() + 1);
		if (czlowiek->GetTuryStanuUmiejetnosci() == 5)
		{
			czlowiek->DezaktywujUmiejetnosc();
			czlowiek->SetCzyPiecTur(false);
		}
	}
	tura++;
}

void Swiat::RysujSwiat()
{
	cout << " +-------------------------------------+" << endl;
	cout << " | Autor: Hubert Szymczak              |" << endl;
	cout << " | Tura: " << tura <<"                             |" <<endl;
	cout << " | N: rozpocznij nowa gre              |" << endl;
	cout << " | S: zapisz (przed rozpoczeciem tury) |" << endl;
	cout << " | Aby rozpoczac ture wcisnij enter    |" << endl;
	cout << " +-------------------------------------+" << endl;
	cout << endl;
	cout << " +---------------Legenda---------------+" << endl;
	cout << " | a - antylopa                        |" << endl;
	cout << " | b - Barszcz sosnowskiego            |" << endl;
	cout << " | X - Czlowiek                        |" << endl;
	cout << " | g - guarana                         |" << endl;
	cout << " | l - lis                             |" << endl;
	cout << " | m - mlecz                           |" << endl;
	cout << " | o - owca                            |" << endl;
	cout << " | t - trawa                           |" << endl;
	cout << " | j - Wilcze jagody                   |" << endl;
	cout << " | w - wilk                            |" << endl;
	cout << " | z - zolw                            |" << endl;
	cout << " +-------------------------------------+" << endl;
	for (int i = 0; i < liczba_Org; i++)
	{
		organizmy[i]->Rysowanie();
	}
	cout << " | Sila czlowieka:" << czlowiek->GetSila()<< endl;
	cout << " | Tury do ponownej mozliwosci wlaczenia umiejetnosci:" << czlowiek->GetTuryStanuUmiejetnosci() << endl;
	cout << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);
	// rysowanie tabelki
	for (int i = 1; i <= _m; i++) {
		// rysowanie linii poziomej
		cout << "+";
		for (int j = 0; j < _n; j++) {
			cout << "-+";
		}
		cout << endl;

		// rysowanie zawartoœci
		cout << "|";
		for (int j = 1; j <= _n; j++) {
			if (GetPolePlanszy(j, i) != nullptr)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
				if (GetPolePlanszy(j, i)->GetSymbol() == 'X')
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
					cout << GetPolePlanszy(j, i)->GetSymbol();
				}else cout << GetPolePlanszy(j, i)->GetSymbol();
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED );
				cout << "|";
			}
			
			else cout << " " << "|";
		}
		cout << endl;
	}

	// rysowanie dolnej krawêdzi tabelki
	cout << "+";
	for (int j = 0; j < _n; j++) {
		cout << "-+";
	}
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << endl << endl;
	string text;
	for (int i = 0; i < liczba_Komentarzy; i++)
	{
		cout << komentarze[i] << endl;
		
	}
	
	liczba_Komentarzy = 0;
}

Swiat::~Swiat()
{
	delete[] organizmy;
	delete czlowiek;
	for (int y = 0; y < _m; y++)
	{
		for (int x = 0; x < _n; x++)
		{
			delete plansza[y];
		}
	}
	delete[] komentarze;

}