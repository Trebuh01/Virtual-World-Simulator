#pragma once
#include <iostream>
#include <string.h>
using namespace std;
class Organizm;
class Czlowiek;
class Swiat
{
private:
	Organizm** organizmy;
	Czlowiek* czlowiek;
	int liczba_Org;
	int liczba_Org_Bez_Nowonarodzonych;
	Organizm*** plansza;
	int _n;				//x
	int _m;				//y
	int tura;
	bool czy_Czlowiek_Zyje;
	string* komentarze;
	int liczba_Komentarzy;
	void AkcjaWszystkich();
public:
	Swiat();
	Swiat(int n, int m);

	void SetRozmiarPlanszy(int n, int m);
	void SetPolePlanszy(int x, int y, Organizm* org);
	void SetTura(int tura);
	void DodajKomentarz(string komentarz);	

	int GetN() const;
	int GetM() const;
	int GetLiczbaOrg() const;
	int GetTura() const;
	Organizm* GetPolePlanszy(int x, int y) const;
	Organizm* GetOrganizm(int i) const;
	Czlowiek* GetCzlowiek() const;

	void DodajOrganizm(Organizm* org);
	void UsunOrganizm(Organizm* org);
	void GenerowaniePustychPunktow(int x, int y, int* positionX, int* positionY, int* ruch, int* pointsCount);

	void WykonajTure();
	void RysujSwiat();

	~Swiat();
};
