#pragma once
#include <iostream>
#include <string.h>
#include "Zwierze.h"
using namespace std;

class Swiat;
class Organizm;
class Zwierze;

class Czlowiek : public Zwierze
{
private:
	bool czy_piec_tur;
	const char symbol = 'X';
	bool CzyumiejetnoscAkt;
	int turyStanuUmiejetnosci;
public:
	Czlowiek(int x, int y, Swiat* swiat);
	void SetCzyPiecTur(bool tury);
	void SetRuch(char ruch) override;
	void SetCzyUmiejetnoscAktywowana(bool umiejetnoscAktywowana);
	void SetTuryStanuUmiejetnosci(int tury);
	int GetOstatniRuch() const override;
	bool CzyPiecTur() const;
	bool CzyUmiejetnoscAktywowana() const;
	int GetTuryStanuUmiejetnosci() const;
	char GetSymbol() const override;
	string GetNazwa() const override;
	string Wypisz() const override;
	void Akcja() override;
	void Kolizja(Organizm* atakujacy) override;
	//void Uciekaj() override;
	void AktywujUmiejetnosc();
	void DezaktywujUmiejetnosc();
};
