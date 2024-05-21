#pragma once
#include <iostream>
#include <string.h>
using namespace std;

class Swiat;

class Generator_swiata
{
private:
	Swiat* _swiat;
	void Generowanie_Punktow_Dla_Organizmow(int* pola, int* ileZwZGat);
	void Odczytanie_Wspolrzednych(int* pola, int* x, int* y, int* ktory);
	void Wczytanie_Organizmu(string nazwa, int sila, int ini, int x, int y, int wiek);
public:
	Generator_swiata(Swiat* swiat);
	void Generowanie_swiata();
	bool Wczytaj_swiat();
	void Zapisz_swiat();
	~Generator_swiata();
};
