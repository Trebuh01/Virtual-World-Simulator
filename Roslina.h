#pragma once
#include <iostream>
#include <string.h>
#include "Organizm.h"
using namespace std;

class Swiat;
class Organizm;

class Roslina : public Organizm
{
protected:
	Organizm* StworzOrganizm(int x, int y, Swiat* swiat) override;
public:
	Roslina();
	Roslina(int sila, int x, int y, Swiat* swiat);
	int GetOstatniRuch() const override;
	virtual char GetSymbol() const = 0;
	virtual string GetNazwa() const = 0;
	string Wypisz() const override;
	void Akcja() override;
	void Kolizja(Organizm* atakujacy) override;
	bool CzyZwierze() override;
	void KomentarzOZabiciu(Organizm* atakowany) override;
	void SetRuch(char ruch) override;
	void Cofniecie() override;
	//void Uciekaj() override;
};
