#pragma once
#include <iostream>
#include <string.h>
using namespace std;

class Swiat;

class Organizm
{
protected:	
	int sila;
	int inicjatywa;
	int _x;
	int _y;
	int wiek;
	Swiat* _swiat;
	virtual Organizm* StworzOrganizm(int x, int y, Swiat* swiat) = 0;
public:
	Organizm();
	Organizm(int sila, int ini, int x, int y, Swiat* swiat);

	void SetSila(int sila);
	void SetInicjatywa(int ini);
	void SetPolozenie(int x, int y);
	void SetWiek(int wiek);
	void SetSwiat(Swiat* swiat);
	virtual void SetRuch(char ruch) = 0;

	int GetSila() const;
	int GetInicjatywa() const;
	int GetX() const;
	int GetY() const;
	int GetWiek() const;
	Swiat* GetSwiat() const;
	virtual int GetOstatniRuch() const = 0;
	virtual char GetSymbol() const = 0;
	virtual string GetNazwa() const = 0;
	virtual string Wypisz() const = 0;

	virtual void Akcja() = 0;
	virtual void Kolizja(Organizm* atakujacy) = 0;
	void Rysowanie();
	virtual void Cofniecie() = 0;
	//virtual void Uciekaj() = 0;
	virtual bool CzyZwierze() = 0;
	virtual void KomentarzOZabiciu(Organizm* atakowany) = 0;
};
