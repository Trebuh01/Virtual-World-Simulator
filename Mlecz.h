#pragma once
#include <iostream>
#include <string.h>
#include "Roslina.h"
using namespace std;

class Swiat;
class Organizm;
class Roslina;

class Mlecz : public Roslina
{
private:
	const char symbol = 'm';
	const int prawdopodobienstwo = 40;
public:
	Mlecz();
	Mlecz(int x, int y, Swiat* swiat);
	char GetSymbol() const override;
	string GetNazwa() const override;
	void Akcja() override;
	void Kolizja(Organizm* atakujacy) override;

};
