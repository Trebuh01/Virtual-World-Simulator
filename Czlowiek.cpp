#include <iostream>
#include <string>
#include "Swiat.h"
#include "Organizm.h"
#include "Zwierze.h"
#include "Czlowiek.h"

#define UP_KEY 72
#define RIGHT_KEY 77
#define DOWN_KEY 80
#define LEFT_KEY 75
#define GORA 1
#define PRAWO 2
#define DOL 3
#define LEWO 4

using namespace std;

Czlowiek::Czlowiek(int x, int y, Swiat* swiat) : Zwierze(5, 4, x, y, swiat)
{
	turyStanuUmiejetnosci = 0;
	CzyumiejetnoscAkt = false;
}

void Czlowiek::SetRuch(char ruch)
{
	if (ruch == UP_KEY) ostatni_ruch = GORA;		
	else if (ruch == RIGHT_KEY) ostatni_ruch = PRAWO;
	else if (ruch == DOWN_KEY) ostatni_ruch = DOL;
	else if (ruch == LEFT_KEY) ostatni_ruch = LEWO;
}
void Czlowiek::SetCzyPiecTur(bool tury)
{
	czy_piec_tur = tury;
}
void Czlowiek::SetCzyUmiejetnoscAktywowana(bool umiejetnoscAktywowana)
{
	CzyumiejetnoscAkt = umiejetnoscAktywowana;
}

void Czlowiek::SetTuryStanuUmiejetnosci(int tury)
{
	turyStanuUmiejetnosci = tury;
}

int Czlowiek::GetOstatniRuch() const
{
	return Zwierze::GetOstatniRuch();
}
bool Czlowiek::CzyPiecTur() const
{
	return czy_piec_tur;
}
bool Czlowiek::CzyUmiejetnoscAktywowana() const
{
	return CzyumiejetnoscAkt;
}

int Czlowiek::GetTuryStanuUmiejetnosci() const
{
	return turyStanuUmiejetnosci;
}

char Czlowiek::GetSymbol() const
{
	return symbol;
}

string Czlowiek::GetNazwa() const
{
	return "Czlowiek";
}

string Czlowiek::Wypisz() const
{
	string result = this->GetNazwa() + " " + to_string(sila) + " " + to_string(inicjatywa) + " ";
	result += to_string(_x) + " " + to_string(_y) + " " + to_string(wiek);
	result += " " + to_string(CzyumiejetnoscAkt) + " " + to_string(turyStanuUmiejetnosci) + " " + to_string(czy_piec_tur);
	return result;
}

void Czlowiek::Akcja()
{
	string komentarz;
	komentarz = this->GetNazwa() + ": \tprzemieszczenie z (" + to_string(_x) + ", " + to_string(_y) + ") na (";

	_swiat->SetPolePlanszy(_x, _y, nullptr);
	if ((ostatni_ruch == 1) && (_y - 1 != 0)) _y -= 1;
	else if ((ostatni_ruch == 2) && (_x + 1 != _swiat->GetN() + 1)) _x += 1;
	else if ((ostatni_ruch == 3) && (_y + 1 != _swiat->GetM() + 1)) _y += 1;
	else if ((ostatni_ruch == 4) && (_x - 1 != 0)) _x -= 1;
	else
	{
		ostatni_ruch = 0;
		this->Rysowanie();
	}
	komentarz += to_string(_x) + ", " + to_string(_y) + ")";
	_swiat->DodajKomentarz(komentarz);
}

void Czlowiek::Kolizja(Organizm* atakujacy)
{
	Zwierze::Kolizja(atakujacy);
}

void Czlowiek::AktywujUmiejetnosc()
{
	CzyumiejetnoscAkt = true;
	turyStanuUmiejetnosci = 0;
	sila = 10;
	cout << "Umiejetnosc aktywowana" << endl;
}

void Czlowiek::DezaktywujUmiejetnosc()
{
	CzyumiejetnoscAkt = false;
	turyStanuUmiejetnosci = 0;
}