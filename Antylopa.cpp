#include <iostream>

#include "Swiat.h"
#include "Organizm.h"
#include "Zwierze.h"
#include "Antylopa.h"

Antylopa::Antylopa() : Zwierze()
{
	sila = 4;
	inicjatywa = 4;
}

Antylopa::Antylopa(int x, int y, Swiat* swiat) : Zwierze(4, 4, x, y, swiat)
{

}

void Antylopa::SetRuch(char ruch)
{
	Zwierze::SetRuch(ruch);
}

int Antylopa::GetOstatniRuch() const
{
	return Zwierze::GetOstatniRuch();
}

char Antylopa::GetSymbol() const
{
	return symbol;
}

string Antylopa::GetNazwa() const
{
	return "Antylopa";
}


void Antylopa::Akcja()
{
	_swiat->SetPolePlanszy(_x, _y, nullptr);
	this->RuchOIlesPol(2);
}

void Antylopa::Kolizja(Organizm* atakujacy)
{
	int los = rand() % 100 + 1;
	if (los % 2 == 0 && atakujacy->GetSymbol() != symbol)
	{
		this->RuchNaWolnePole();
		if (ostatni_ruch != 0)
		{
			return;
		}
	}
	
	Zwierze::Kolizja(atakujacy);
}