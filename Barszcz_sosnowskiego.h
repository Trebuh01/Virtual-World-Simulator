#pragma once
#include <iostream>
#include <string.h>
#include "Roslina.h"
using namespace std;

class Swiat;
class Organizm;
class Roslina;

class Barszcz_sosnowskiego : public Roslina
{
private:
	const char symbol = 'b';
	const int prawdopodobienstwo = 10;
public:
	Barszcz_sosnowskiego();
	Barszcz_sosnowskiego(int x, int y, Swiat* swiat);
	char GetSymbol() const override;
	string GetNazwa() const override;
	void Akcja() override;
	void Kolizja(Organizm* atakujacy) override;
};
