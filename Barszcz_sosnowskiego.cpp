#include <iostream>
#include "Swiat.h"
#include "Organizm.h"
#include "Roslina.h"
#include "Barszcz_sosnowskiego.h"

Barszcz_sosnowskiego::Barszcz_sosnowskiego() : Roslina()
{
	sila = 10;
}

Barszcz_sosnowskiego::Barszcz_sosnowskiego(int x, int y, Swiat* swiat) : Roslina(10, x, y, swiat)
{

}

char Barszcz_sosnowskiego::GetSymbol() const
{
	return symbol;
}

string Barszcz_sosnowskiego::GetNazwa() const
{
	return "Barszcz sosnowskiego";
}

void Barszcz_sosnowskiego::Akcja()
{
	Organizm** org = new Organizm * [4];
	org[0] = _swiat->GetPolePlanszy(_x, _y - 1);
	org[1] = _swiat->GetPolePlanszy(_x + 1, _y);
	org[2] = _swiat->GetPolePlanszy(_x, _y + 1);
	org[3] = _swiat->GetPolePlanszy(_x - 1, _y);

	for (int i = 0; i < 4; i++) {
		if (org[i] != nullptr && org[i]->CzyZwierze()) {
			this->KomentarzOZabiciu(org[i]);
			_swiat->UsunOrganizm(org[i]);
		}
	}

	int los = rand() % 100;
	if (los < prawdopodobienstwo) {
		Roslina::Akcja();
	}
}

void Barszcz_sosnowskiego::Kolizja(Organizm* atakujacy)
{
	atakujacy->KomentarzOZabiciu(this);

	_swiat->UsunOrganizm(atakujacy);
}