#pragma once
#include <iostream>
#include <string.h>
#include "Zwierze.h"
using namespace std;

class Swiat;
class Organizm;
class Zwierze;

class Lis : public Zwierze
{
private:
	const char symbol = 'l';
public:
	Lis();
	Lis(int x, int y, Swiat* swiat);
	void SetRuch(char ruch) override;
	int GetOstatniRuch() const override;
	char GetSymbol() const override;
	string GetNazwa() const override;
	void Akcja() override;
	void Kolizja(Organizm* atakujacy) override;
};
