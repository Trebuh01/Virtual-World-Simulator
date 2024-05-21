#include <iostream>
#include <string>
#include "Swiat.h"
#include "Organizm.h"
#include "Zwierze.h"
#include "Lis.h"

Lis::Lis() : Zwierze()
{
	sila = 3;
	inicjatywa = 7;
}

Lis::Lis(int x, int y, Swiat* swiat) : Zwierze(3, 7, x, y, swiat)
{

}

void Lis::SetRuch(char ruch)
{
	Zwierze::SetRuch(ruch);
}

int Lis::GetOstatniRuch() const
{
	return Zwierze::GetOstatniRuch();
}

char Lis::GetSymbol() const
{
	return symbol;
}

string Lis::GetNazwa() const
{
	return "Lis";
}

void Lis::Akcja()
{
	string komentarz;
	int* pointsX = new int[4];
	int* pointsY = new int[4];
	int* ruch = new int[4];
	int pointsCount = 0;
	Organizm** org = new Organizm * [4];
	Organizm* atakowany = _swiat->GetPolePlanszy(_x, _y);
	if (atakowany == this) _swiat->SetPolePlanszy(_x, _y, nullptr);
	org[0] = _swiat->GetPolePlanszy(_x, _y - 1);
	org[1] = _swiat->GetPolePlanszy(_x + 1, _y);
	org[2] = _swiat->GetPolePlanszy(_x, _y + 1);
	org[3] = _swiat->GetPolePlanszy(_x - 1, _y);


	int directions[4][2] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };

	for (int i = 0; i < 4; i++)
	{
		int newX = _x + directions[i][0];
		int newY = _y + directions[i][1];

		if (newX >= 1 && newX <= _swiat->GetN() && newY >= 1 && newY <= _swiat->GetM() && (org[i] == nullptr || org[i]->GetSila() <= sila))
		{
			pointsX[pointsCount] = newX;
			pointsY[pointsCount] = newY;
			ruch[pointsCount] = i + 1;
			pointsCount++;
		}
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

void Lis::Kolizja(Organizm* atakujacy)
{
	Zwierze::Kolizja(atakujacy);
}