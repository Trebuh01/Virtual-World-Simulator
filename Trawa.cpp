#include <iostream>

#include "Swiat.h"
#include "Organizm.h"
#include "Roslina.h"
#include "Trawa.h"

Trawa::Trawa() : Roslina()
{
	sila = 0;
}

Trawa::Trawa(int x, int y, Swiat* swiat) : Roslina(0, x, y, swiat)
{

}

char Trawa::GetSymbol() const
{
	return symbol;
}

string Trawa::GetNazwa() const
{
	return "Trawa";
}

void Trawa::Akcja()
{
	int los = rand() % 100;
	if (los < prawdopodobienstwo)
	{
		Roslina::Akcja();
	}
}

void Trawa::Kolizja(Organizm* atakujacy)
{
	Roslina::Kolizja(atakujacy);
}