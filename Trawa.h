#pragma once
#include <iostream>
#include <string.h>
#include "Roslina.h"
using namespace std;

class Swiat;
class Organizm;
class Roslina;

class Trawa : public Roslina
{
private:
	const char symbol = 't';
	const int prawdopodobienstwo = 50;
public:
	Trawa();
	Trawa(int x, int y, Swiat* swiat);
	char GetSymbol() const override;
	string GetNazwa() const override;
	void Akcja() override;
	void Kolizja(Organizm* atakujacy) override;
};
