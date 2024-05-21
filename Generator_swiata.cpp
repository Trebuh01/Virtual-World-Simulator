#include <fstream>
#include <string>
#include <Windows.h>

#include "Swiat.h"
#include "Generator_swiata.h"

#include "Organizm.h"
#include "Czlowiek.h"
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

#define WSZYSTKIE_GATUNKI 10
#define WOLNYCH_MIEJSC 20			//na 10 zwierzat (po jednym z kazdego gatunku)

using namespace std;

Generator_swiata::Generator_swiata(Swiat* swiat)
{
	_swiat = swiat;
}

void Generator_swiata::Generowanie_swiata()
{
	int n = _swiat->GetN();
	int m = _swiat->GetM();
	int ileZwierzatZGatunku = n * m / (WSZYSTKIE_GATUNKI + WOLNYCH_MIEJSC);
	int* polaZajete = new int[ileZwierzatZGatunku * WSZYSTKIE_GATUNKI + 1];
	this->Generowanie_Punktow_Dla_Organizmow(polaZajete, &ileZwierzatZGatunku);
	int j = 0;
	int x = polaZajete[j] % n;
	int y = (polaZajete[j] - x) / n;
	Organizm* gracz = new Czlowiek(x, y, _swiat);
	_swiat->DodajOrganizm(gracz);
	j++;

	for (int s = 0; s < ileZwierzatZGatunku; s++)
	{
		Organizm* organizmy[10];
		for (int i = 0; i < 10; i++) {
			Odczytanie_Wspolrzednych(polaZajete, &x, &y, &j);
			switch (i) {
			case 0: organizmy[i] = new Wilk(x, y, _swiat); break;
			case 1: organizmy[i] = new Owca(x, y, _swiat); break;
			case 2: organizmy[i] = new Lis(x, y, _swiat); break;
			case 3: organizmy[i] = new Zolw(x, y, _swiat); break;
			case 4: organizmy[i] = new Antylopa(x, y, _swiat); break;
			case 5: organizmy[i] = new Trawa(x, y, _swiat); break;
			case 6: organizmy[i] = new Mlecz(x, y, _swiat); break;
			case 7: organizmy[i] = new Guarana(x, y, _swiat); break;
			case 8: organizmy[i] = new Wilcze_jagody(x, y, _swiat); break;
			case 9: organizmy[i] = new Barszcz_sosnowskiego(x, y, _swiat); break;
			}
			_swiat->DodajOrganizm(organizmy[i]);
		}
	}
}

bool Generator_swiata::Wczytaj_swiat()
{
	bool result = true;
	const string plik = "dane.txt";
	ifstream odczyt(plik.c_str());
	if (odczyt.good())
	{
		int n, m, tura, liczbaOrg;
		odczyt >> n >> m >> tura >> liczbaOrg;
		_swiat->SetRozmiarPlanszy(n, m);
		_swiat->SetTura(tura);

		string nazwa, nazwa2;
		int sila, inicjatywa, x, y, wiek, umiejetnoscAktywowana, turybezUmiejetnoscia;
		bool aktywowana, czypiectur;

		for (int i = 0; i < liczbaOrg; i++)
		{
			odczyt >> nazwa;
			if (nazwa == "Wilcze" || nazwa == "Barszcz")
			{
				odczyt >> nazwa2;
				nazwa += " " + nazwa2;
			}
			odczyt >> sila >> inicjatywa >> x >> y >> wiek;
			if (nazwa == "Czlowiek")
			{
				odczyt >> umiejetnoscAktywowana >> turybezUmiejetnoscia>> czypiectur;
				Organizm* org = new Czlowiek(x - 1, y - 1, _swiat);
				org->SetSila(sila);
				org->SetInicjatywa(inicjatywa);
				org->SetWiek(wiek);
				if (umiejetnoscAktywowana == 0) aktywowana = false;
				else aktywowana = true;
				_swiat->DodajOrganizm(org);
				_swiat->GetCzlowiek()->SetCzyUmiejetnoscAktywowana(aktywowana);
				_swiat->GetCzlowiek()->SetTuryStanuUmiejetnosci(turybezUmiejetnoscia);
				_swiat->GetCzlowiek()->SetCzyPiecTur(czypiectur);
			}
			else Wczytanie_Organizmu(nazwa, sila, inicjatywa, x - 1, y - 1, wiek);
		}

		odczyt.close();
		cout << "Wczytano gre" << endl;
	}
	else
	{
		cout << "Nie znaleziono pliku" << endl;
		result = false;
	}

	return result;

}

void Generator_swiata::Zapisz_swiat()
{
	ofstream zapis("dane.txt");
	if (!zapis) {
		cerr << "Nie uda³o siê otworzyæ pliku" << endl;
		return;
	}
	int liczbaOrg = _swiat->GetLiczbaOrg();
	zapis << _swiat->GetN() << " " << _swiat->GetM() << " " << _swiat->GetTura() << " " << liczbaOrg << endl;
	for (int i = 0; i < liczbaOrg; i++)
	{
		Organizm* org = _swiat->GetOrganizm(i);
		zapis << org->Wypisz() << endl;
	}
	zapis.close();
	cout << "Zapisano stan gry do pliku" << endl;
}

void Generator_swiata::Generowanie_Punktow_Dla_Organizmow(int* pola, int* ileZwZGat)
{
	int n = _swiat->GetN();
	int m = _swiat->GetM();
	int ileMiejsc = (*ileZwZGat) * WSZYSTKIE_GATUNKI + 1;		//+1 bo czlowiek
	int* wszystkiePola = new int[n * m];
	int los;
	fill(wszystkiePola, wszystkiePola + n * m, 0);
	for (int i = 0; i < ileMiejsc; i++)
	{
		do
		{
			los = rand() % (n * m);
		} while (wszystkiePola[los] == 1);
		wszystkiePola[los] = 1;
		pola[i] = los;
	}

}

void Generator_swiata::Odczytanie_Wspolrzednych(int* pola, int* x, int* y, int* ktory)
{
	int n = _swiat->GetN();
	*x = pola[*ktory] % n;
	*y = (pola[*ktory] - *x) / n;
	(*ktory)++;
}

void Generator_swiata::Wczytanie_Organizmu(string nazwa, int sila, int ini, int x, int y, int wiek)
{
	Organizm* org = nullptr;
	if (nazwa == "Wilk") org = new Wilk(x, y, _swiat);
	else if (nazwa == "Owca")org = new Owca(x, y, _swiat);
	else if (nazwa == "Lis")org = new Lis(x, y, _swiat);
	else if (nazwa == "Zolw") org = new Zolw(x, y, _swiat);
	else if (nazwa == "Antylopa") org = new Antylopa(x, y, _swiat);
	else if (nazwa == "Trawa") org = new Trawa(x, y, _swiat);
	else if (nazwa == "Mlecz") org = new Mlecz(x, y, _swiat);
	else if (nazwa == "Guarana") org = new Guarana(x, y, _swiat);
	else if (nazwa == "Barszcz sosnowskiego") org = new Barszcz_sosnowskiego(x, y, _swiat);
	else if (nazwa == "Wilcze jagody") org = new Wilcze_jagody(x, y, _swiat);
	
	if (org != nullptr)
	{
		org->SetSila(sila);
		org->SetInicjatywa(ini);
		org->SetWiek(wiek);
		_swiat->DodajOrganizm(org);
	}
	else cout << "Odczyt organizmu nieudany" << nazwa << endl;

}

Generator_swiata::~Generator_swiata()
{
	delete _swiat;
}