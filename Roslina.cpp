#include <iostream>
#include <string>

#include "Swiat.h"
#include "Organizm.h"
#include "Roslina.h"

#include "Trawa.h"
#include "Mlecz.h"
#include "Guarana.h"
#include "Wilcze_jagody.h"
#include "Barszcz_sosnowskiego.h"

using namespace std;

Roslina::Roslina() : Organizm()
{
	
}

Roslina::Roslina(int sila, int x, int y, Swiat* swiat) : Organizm(sila, 0, x, y, swiat)
{

}

int Roslina::GetOstatniRuch() const
{
	return 0;
}

string Roslina::Wypisz() const
{
	string result = this->GetNazwa() + " " + to_string(this->GetSila()) + " " + to_string(this->GetInicjatywa()) + " ";
	result += to_string(this->GetX()) + " " + to_string(this->GetY()) + " " + to_string(this->GetWiek());
	return result;
}

void Roslina::Akcja()
{
	string komentarz;
	int* pointsX = new int[4];
	int* pointsY = new int[4];
	int* ruch = new int[4];				//tablica potrzebna do wygenerowania punktow
	int pointsCount = 0;
	_swiat->GenerowaniePustychPunktow(_x, _y, pointsX, pointsY, ruch, &pointsCount);

	if (pointsCount != 0)
	{
		int los = rand() % pointsCount;
		Organizm* org = this->StworzOrganizm(pointsX[los], pointsY[los], _swiat);
		_swiat->DodajOrganizm(org);

		komentarz = this->GetNazwa() + ": \trozprzestrzenienie rosliny z pola (" + to_string(_x) + ", ";
		komentarz += to_string(_y) + ") na pole (" + to_string(pointsX[los]) + ", " + to_string(pointsY[los]) + ")";
		_swiat->DodajKomentarz(komentarz);
	}
}

void Roslina::Kolizja(Organizm* atakujacy)
{
	atakujacy->KomentarzOZabiciu(this);

	if (this->GetSila() > atakujacy->GetSila()) _swiat->UsunOrganizm(atakujacy);
	else
	{
		_swiat->SetPolePlanszy(this->GetX(), this->GetY(), atakujacy);
		_swiat->UsunOrganizm(this);
		atakujacy->Rysowanie();
	}
}

bool Roslina::CzyZwierze()
{
	return false;
}


void Roslina::KomentarzOZabiciu(Organizm* atakowany)
{
	string komentarz;
	komentarz = this->GetNazwa() + ": \tzaatakowal organizm " + atakowany->GetNazwa();
	_swiat->DodajKomentarz(komentarz);
}

Organizm* Roslina::StworzOrganizm(int x, int y, Swiat* swiat)
{
	if (typeid(*this) == typeid(Trawa))
	{
		Trawa* r = new Trawa(x - 1, y - 1, swiat);
		return r;
	}
	else if (typeid(*this) == typeid(Mlecz))
	{
		Mlecz* r = new Mlecz(x - 1, y - 1, swiat);
		return r;
	}
	else if (typeid(*this) == typeid(Guarana))
	{
		Guarana* r = new Guarana(x - 1, y - 1, swiat);
		return r;
	}
	else if (typeid(*this) == typeid(Wilcze_jagody))
	{
		Wilcze_jagody* r = new Wilcze_jagody(x - 1, y - 1, swiat);
		return r;
	}
	else if (typeid(*this) == typeid(Barszcz_sosnowskiego))
	{
		Barszcz_sosnowskiego* r = new Barszcz_sosnowskiego(x - 1, y - 1, swiat);
		return r;
	}
}

void Roslina::SetRuch(char ruch)
{
	cout << "Blad: proba wywolania metody Roslina::SetRuch()" << endl;
}

void Roslina::Cofniecie()
{
	cout << "Blad: proba wywolania metody Roslina::Cofniecie()" << endl;
}
