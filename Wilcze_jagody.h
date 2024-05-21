#pragma once
#include <iostream>
#include <string.h>
#include "Roslina.h"
using namespace std;

class Swiat;
class Organizm;
class Roslina;

class Wilcze_jagody : public Roslina
{
private:
	const char symbol = 'j';
	const int prawdopodobienstwo = 20;
public:
	Wilcze_jagody();
	Wilcze_jagody(int x, int y, Swiat* swiat);
	char GetSymbol() const override;
	string GetNazwa() const override;
	void Akcja() override;
	void Kolizja(Organizm* atakujacy) override;
};
