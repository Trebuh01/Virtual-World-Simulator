#include <iostream>

#include "Swiat.h"
#include "Organizm.h"
#include "Zwierze.h"
#include "Owca.h"

Owca::Owca() : Zwierze()
{
	sila = 4;
	inicjatywa = 4;
}

Owca::Owca(int x, int y, Swiat* swiat) : Zwierze(4, 4, x, y, swiat)
{

}

void Owca::SetRuch(char ruch)
{
	Zwierze::SetRuch(ruch);
}

int Owca::GetOstatniRuch() const
{
	return Zwierze::GetOstatniRuch();
}

char Owca::GetSymbol() const
{
	return symbol;
}

string Owca::GetNazwa() const
{
	return "Owca";
}

void Owca::Akcja()
{
	Zwierze::Akcja();
}

void Owca::Kolizja(Organizm* atakujacy)
{
	Zwierze::Kolizja(atakujacy);
}