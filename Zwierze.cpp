#include <iostream>
#include <cstdlib>
#include <string>

#include "Swiat.h"
#include "Organizm.h"
#include "Zwierze.h"

#include "Wilk.h"
#include "Owca.h"
#include "Lis.h"
#include "Zolw.h"
#include "Antylopa.h"

#define GORA 1
#define PRAWO 2
#define DOL 3
#define LEWO 4
#define SIZE 20

using namespace std;

Zwierze::Zwierze() : Organizm()
{
	ostatni_ruch = NULL;
}

Zwierze::Zwierze(int sila, int ini, int x, int y, Swiat* swiat) : Organizm(sila, ini, x, y, swiat)
{
	ostatni_ruch = NULL;
}

void Zwierze::SetRuch(char ruch)
{
	ostatni_ruch = ruch;
}

int Zwierze::GetOstatniRuch() const
{
	return ostatni_ruch;
}

string Zwierze::Wypisz() const
{
	string result = this->GetNazwa() + " " + to_string(sila) + " " + to_string(inicjatywa) + " "+ to_string(_x) + " " + to_string(_y) + " " + to_string(wiek);
	return result;
}

void Zwierze::Akcja()
{
	this->RuchOIlesPol(1);
}

void Zwierze::Kolizja(Organizm* atakujacy)
{
	string komentarz;
	atakujacy->KomentarzOZabiciu(this);

	if (this->GetSymbol() == atakujacy->GetSymbol() && atakujacy->GetWiek() > 0) this->Rozmnazanie(atakujacy, _swiat);
	else if (this->GetSymbol() == atakujacy->GetSymbol() && atakujacy->GetWiek() <= 0)
	{
		atakujacy->Cofniecie();
		komentarz = "Proba rozmnozenia z mlodym organizmem";
		_swiat->DodajKomentarz(komentarz);
	}
	else if (this->GetSila() > atakujacy->GetSila())
	{
		_swiat->UsunOrganizm(atakujacy);
	}
	else
	{
		_swiat->SetPolePlanszy(this->GetX(), this->GetY(), atakujacy);
		_swiat->UsunOrganizm(this);
		atakujacy->Rysowanie();
	}
}

void Zwierze::Cofniecie()
{
	int atakujacyX = this->GetX();
	int atakujacyY = this->GetY();
	if (this->GetOstatniRuch() == GORA) this->SetPolozenie(atakujacyX - 1, atakujacyY);
	else if (this->GetOstatniRuch() == PRAWO) this->SetPolozenie(atakujacyX - 2, atakujacyY - 1);
	else if (this->GetOstatniRuch() == DOL) this->SetPolozenie(atakujacyX - 1, atakujacyY - 2);
	else if (this->GetOstatniRuch() == LEWO) this->SetPolozenie(atakujacyX, atakujacyY - 1);

	this->Rysowanie();
}

bool Zwierze::CzyZwierze()
{
	return true;
}

void Zwierze::KomentarzOZabiciu(Organizm* atakowany)
{
	string komentarz = this->GetNazwa() + ": \t\tzaatakowal(a) organizm " + atakowany->GetNazwa();
	_swiat->DodajKomentarz(komentarz);
}

void Zwierze::RuchNaWolnePole()
{
	string komentarz;
	_swiat->SetPolePlanszy(_x, _y, nullptr);
	int* pointsX = new int[4];
	int* pointsY = new int[4];
	int* ruch = new int[4];
	int pointsCount = 0;

	_swiat->GenerowaniePustychPunktow(_x, _y, pointsX, pointsY, ruch, &pointsCount);

	komentarz = this->GetNazwa() + ": \t\tprzemieszczenie z (" + to_string(_x) + ", " + to_string(_y) + ") na (";

	if (pointsCount != 0)
	{
		int los = rand() % pointsCount;
		_x = pointsX[los];
		_y = pointsY[los];
		ostatni_ruch = ruch[los];
	}
	else
	{
		this->Rysowanie();
		ostatni_ruch = 0;
	}

	komentarz += to_string(_x) + ", " + to_string(_y) + ")";
	_swiat->DodajKomentarz(komentarz);
}

void Zwierze::RuchOIlesPol(int length)
{
	string komentarz;
	_swiat->SetPolePlanszy(_x, _y, nullptr);
	int* pointsX = new int[4];
	int* pointsY = new int[4];
	int* ruch = new int[4];
	int pointsCount = 0;
	//ruch w gore
	if (_y - length > 0)
	{
		pointsX[pointsCount] = _x;
		pointsY[pointsCount] = _y - length;
		ruch[pointsCount] = GORA;
		pointsCount++;
	}
	//ruch w prawo
	if (_x + length < _swiat->GetN() + 1)
	{
		pointsX[pointsCount] = _x + length;
		pointsY[pointsCount] = _y;
		ruch[pointsCount] = PRAWO;
		pointsCount++;
	}
	//ruch w dol
	if (_y + length < _swiat->GetM() + 1)
	{
		pointsX[pointsCount] = _x;
		pointsY[pointsCount] = _y + length;
		ruch[pointsCount] = DOL;
		pointsCount++;
	}
	//ruch w lewo
	if (_x - length > 0)
	{
		pointsX[pointsCount] = _x - length;
		pointsY[pointsCount] = _y;
		ruch[pointsCount] = LEWO;
		pointsCount++;
	}

	komentarz = this->GetNazwa() + ": \t\tprzemieszczenie z (" + to_string(_x) + ", " + to_string(_y) + ") na (";

	if (pointsCount != 0)
	{
		int los = rand() % pointsCount;
		_x = pointsX[los];
		_y = pointsY[los];
		ostatni_ruch = ruch[los];
	}
	else
	{
		this->Rysowanie();
		ostatni_ruch = 0;
	}

	komentarz += to_string(_x) + ", " + to_string(_y) + ")";
	_swiat->DodajKomentarz(komentarz);
}

Organizm* Zwierze::StworzOrganizm(int x, int y, Swiat* swiat)
{
	if (typeid(*this) == typeid(Wilk))
	{
		Wilk* zw = new Wilk(x - 1, y - 1, swiat);
		return zw;
	}
	else if (typeid(*this) == typeid(Owca))
	{
		Owca* zw = new Owca(x - 1, y - 1, swiat);
		return zw;
	}
	else if (typeid(*this) == typeid(Lis))
	{
		Lis* zw = new Lis(x - 1, y - 1, swiat);
		return zw;
	}
	else if (typeid(*this) == typeid(Zolw))
	{
		Zolw* zw = new Zolw(x - 1, y - 1, swiat);
		return zw;
	}
	else if (typeid(*this) == typeid(Antylopa))
	{
		Antylopa* zw = new Antylopa(x - 1, y - 1, swiat);
		return zw;
	}
}

void Zwierze::Rozmnazanie(Organizm* atakujacy, Swiat* swiat)
{
	int* positionX = new int[6];
	int* positionY = new int[6];
	int* ruch = new int[6];
	int point = 0;

	int x = 0;
	int y = 0;
	int pointsCount = 0;
	atakujacy->Cofniecie();
	if (atakujacy->GetOstatniRuch() == GORA || atakujacy->GetOstatniRuch() == DOL)
	{
		swiat->GenerowaniePustychPunktow(atakujacy->GetX(), atakujacy->GetY(), positionX, positionY, ruch, &pointsCount);
		swiat->GenerowaniePustychPunktow(this->GetX(), this->GetY(), positionX, positionY, ruch, &pointsCount);

		if (pointsCount != 0)
		{
			point = rand() % pointsCount;
			Organizm* org = this->StworzOrganizm(positionX[point], positionY[point], swiat);
			swiat->DodajOrganizm(org);
		}
	}
	else if (atakujacy->GetOstatniRuch() == LEWO || atakujacy->GetOstatniRuch() == PRAWO)
	{
		swiat->GenerowaniePustychPunktow(atakujacy->GetX(), atakujacy->GetY(), positionX, positionY, ruch, &pointsCount);
		swiat->GenerowaniePustychPunktow(this->GetX(), this->GetY(), positionX, positionY, ruch, &pointsCount);

		if (pointsCount != 0)
		{
			point = rand() % pointsCount;
			Organizm* org = this->StworzOrganizm(positionX[point], positionY[point], swiat);
			swiat->DodajOrganizm(org);
		}
	}
}