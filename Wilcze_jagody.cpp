#include <iostream>

#include "Swiat.h"
#include "Organizm.h"
#include "Roslina.h"
#include "Wilcze_jagody.h"

Wilcze_jagody::Wilcze_jagody() : Roslina()
{
	sila = 99;
}

Wilcze_jagody::Wilcze_jagody(int x, int y, Swiat* swiat) : Roslina(99, x, y, swiat)
{

}

char Wilcze_jagody::GetSymbol() const
{
	return symbol;
}

string Wilcze_jagody::GetNazwa() const
{
	return "Wilcze jagody";
}

void Wilcze_jagody::Akcja()
{
	int los = rand() % 100;
	if (los < prawdopodobienstwo)
	{
		Roslina::Akcja();
	}
}

void Wilcze_jagody::Kolizja(Organizm* atakujacy)
{
	atakujacy->KomentarzOZabiciu(this);

	_swiat->UsunOrganizm(atakujacy);
}