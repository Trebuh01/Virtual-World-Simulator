#include <iostream>

#include "Swiat.h"
#include "Organizm.h"
#include "Roslina.h"
#include "Guarana.h"

Guarana::Guarana() : Roslina()
{
	sila = 0;
}

Guarana::Guarana(int x, int y, Swiat* swiat) : Roslina(0, x, y, swiat)
{

}

char Guarana::GetSymbol() const
{
	return symbol;
}

string Guarana::GetNazwa() const
{
	return "Guarana";
}

void Guarana::Akcja()
{
	int los = rand() % 100;
	if (los < prawdopodobienstwo)
	{
		Roslina::Akcja();
	}
}

void Guarana::Kolizja(Organizm* atakujacy)
{
	if (this->GetSila() > atakujacy->GetSila())
	{
		this->KomentarzOZabiciu(atakujacy);
		_swiat->UsunOrganizm(atakujacy);
	}
	else
	{
		atakujacy->KomentarzOZabiciu(this);
		atakujacy->SetSila(atakujacy->GetSila() + 3);

		string komentarz = this->GetNazwa() + ": \twzmocnienie " + atakujacy->GetNazwa() + " o 3 pkt";
		_swiat->DodajKomentarz(komentarz);

		_swiat->SetPolePlanszy(this->GetX(), this->GetY(), atakujacy);
		_swiat->UsunOrganizm(this);
		atakujacy->Rysowanie();
	}
}