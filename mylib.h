#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>
using namespace std;

struct Maalit {												//alitaulukko maaleille
	int paastetyt_maalit = 0,
		tehdyt_maalit = 0;
};

struct Pisteet {											//alitaulukko pisteille
	int pisteet_koti = 0,
		pisteet_vieras = 0,
		pisteet_tasa = 0;
};

struct Joukkue {
	string kotijoukkue = "-", 
		vierasjoukkue = "-", 
		joukkue = "-";
	int voitot = 0,
		tasapelit = 0,
		haviot = 0,
		kokonaispisteet = 0;
	Maalit maalit;
	Pisteet pisteet;
};

int valikko();												//aliohjelma joka tulostaa valikon
int maalientarkistus();									    //tarkistaa, ett‰ k‰ytt‰j‰ antaa numeroita maaleihin
Joukkue keraatiedot();										//ker‰‰ tiedot yhdelt‰ kierrokselta
Joukkue jarjesta_joukkueet(Joukkue[], int);					//j‰rjest‰‰ joukkueet oikeaan j‰rjestykseen sarjataulukossa (pisteet,voitot,maaliero jne.)
void tulosta_joukkue(Joukkue[]);							//tulostaa sarjataulukon
void tulosta_otteluhistoria(vector<Joukkue>&);				//tulostaa kaikki pelatut ottelut otteluhistoriana