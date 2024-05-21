#include <iostream>

#include "Swiat.h"
#include "Organizm.h"

using namespace std;

Organizm::Organizm()
{
	sila = 0;
	inicjatywa = 0;
	_x = 0;
	_y = 0;
	_swiat = nullptr;
	wiek = 0;
}

Organizm::Organizm(int psila, int ini, int x, int y, Swiat* swiat)
{
	sila = psila;
	inicjatywa = ini;
	_x = x + 1;
	_y = y + 1;
	_swiat = swiat;
	wiek = 0;
}

void Organizm::SetSila(int psila)
{
	sila = psila;
}

void Organizm::SetInicjatywa(int ini)
{
	inicjatywa = ini;
}

void Organizm::SetPolozenie(int x, int y)
{
	_x = x + 1;
	_y = y + 1;
}

void Organizm::SetWiek(int pwiek)
{
	wiek = wiek;
}

void Organizm::SetSwiat(Swiat* swiat)
{
	_swiat = swiat;
}

int Organizm::GetSila() const
{
	return sila;
}

int Organizm::GetInicjatywa() const
{
	return inicjatywa;
}

int Organizm::GetX() const
{
	return _x;
}

int Organizm::GetY() const
{
	return _y;
}

int Organizm::GetWiek() const
{
	return wiek;
}

Swiat* Organizm::GetSwiat() const
{
	return _swiat;
}

void Organizm::Rysowanie()
{
	_swiat->SetPolePlanszy(_x, _y, this);
}