#pragma once
#include <iostream>
#include <string.h>
#include "Roslina.h"
using namespace std;

class Swiat;
class Organizm;
class Roslina;

class Guarana : public Roslina
{
private:
	const char symbol = 'g';
	const int prawdopodobienstwo = 30;
public:
	Guarana();
	Guarana(int x, int y, Swiat* swiat);
	char GetSymbol() const override;
	string GetNazwa() const override;
	void Akcja() override;
	void Kolizja(Organizm* atakujacy) override;
};