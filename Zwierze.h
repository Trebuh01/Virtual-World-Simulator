#pragma once
#include <iostream>
#include <string.h>
#include "Organizm.h"
using namespace std;

class Swiat;
class Organizm;

class Zwierze : public Organizm
{
private:
	void Rozmnazanie(Organizm* atakowany, Swiat* swiat);
	Organizm* StworzOrganizm(int x, int y, Swiat* swiat) override;
protected:
	int ostatni_ruch;
	void RuchNaWolnePole();
	void RuchOIlesPol(int length);
public:
	Zwierze();
	Zwierze(int sila, int ini, int x, int y, Swiat* swiat);
	void SetRuch(char ruch) override;
	int GetOstatniRuch() const override;
	virtual char GetSymbol() const = 0;
	virtual string GetNazwa() const = 0;
	string Wypisz() const override;
	void Akcja() override;
	void Kolizja(Organizm* atakujacy) override;	
	void Cofniecie() override;
	//void Uciekaj() override;
	bool CzyZwierze() override;
	void KomentarzOZabiciu(Organizm* atakowany) override;
};
