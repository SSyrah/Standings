#include "mylib.h"

int main() {
	setlocale(LC_ALL, "");
	int kerroin = 2, toiminto, luku_taysi = 0;
	const int KOKO = 12;
	bool koti = false, vieras = false, kotij = false, vierasj = false;
	Joukkue tiimi[KOKO], kierros;
	vector<Joukkue> otteluhistoria;
	cout <<  "\t \t  \t \t Jääkiekon SM-liigan sarjataulukko \n\n";
	toiminto = valikko();
	while (toiminto != 4) {
		if (toiminto == 1) {
			alku:
			kierros = keraatiedot();								//haetaan kierroksen tiedot
			otteluhistoria.push_back(kierros);						// kerää tiedot otteluhistoriaan

			luku_taysi = 0;
			for (int i = 0; i < 12; i++) {							//tarkistaa, onko sarjataulukko jo täynnä
				if (tiimi[i].joukkue != "-") {
					luku_taysi++;
				}
				else {}
			}
			if (luku_taysi == 12) {									// tarkistaa onko kaikki joukkuepaikat jo täytetty. Nämä ja seuraava boolean - ehtolause tarvitaan
				for (int i = 0; i < 12; i++) {						// tilanteeseen,jossa joukkuepaikat ovat täynnä ja käyttäjä antaa tunnettuja joukkueita.
					if (tiimi[i].joukkue == kierros.kotijoukkue) {	// Antaa ilmoituksen VAIN kun annetaan "uusia" joukkueita.
						kotij = true;
					}
					if (tiimi[i].joukkue == kierros.vierasjoukkue) {
						vierasj = true;
					}
				}
			}
			if (luku_taysi == 12 && (kotij == false || vierasj == false)) {					// ilmoittaa käyttäjälle jos joukkupaikat on jo täytetty, siirtyy alkuun.
				cout << "Kaikki joukkueet on jo annettu, ei voi lisätä enää uusia joukkueita!" << endl;
				goto alku;
			}

			if (tiimi[0].joukkue == "-") {							// lisätään 2 ensimmäistä joukkuetta
				tiimi[0].joukkue = kierros.kotijoukkue;
				tiimi[1].joukkue = kierros.vierasjoukkue;
			}
			else {													// tutkitaan, löytyykö annetut joukkueet jo sarjataulukosta.
				for (int i = 0; i < 12; i++) {						 
					if (tiimi[i].joukkue == kierros.kotijoukkue) {
						koti = true;
					} else {}
				}
				for (int i = 0; i < 12; i++) {
					if (tiimi[i].joukkue == kierros.vierasjoukkue) {
						vieras = true;
					} else {}
				}
				if (koti == false) {								//lisää kotijoukkueen jos ei löydy sarjataulukosta
					for (int i = 0; i < 12; i++) {
						if (tiimi[i].joukkue == "-") {
							tiimi[i].joukkue = kierros.kotijoukkue;
							break;
						}
					}
				}
				if (vieras == false) {								// lisää vierasjoukkueen jos ei löydy sarjataulukosta
					for (int i = 0; i < 12; i++) {
						if (tiimi[i].joukkue == "-") {
							tiimi[i].joukkue = kierros.vierasjoukkue;
							break;
						}
					}
				}
			}

			for (int i = 0; i <= 11; i++) {							// syöttää tiedot jos kotijoukkue voittaa ottelun
				if (kierros.maalit.tehdyt_maalit > kierros.maalit.paastetyt_maalit) {
					if (tiimi[i].joukkue == kierros.kotijoukkue) {
						tiimi[i].maalit.tehdyt_maalit = tiimi[i].maalit.tehdyt_maalit + kierros.maalit.tehdyt_maalit;
						tiimi[i].maalit.paastetyt_maalit = tiimi[i].maalit.paastetyt_maalit + kierros.maalit.paastetyt_maalit;
						tiimi[i].voitot = tiimi[i].voitot + kierros.voitot;
						tiimi[i].kokonaispisteet = tiimi[i].kokonaispisteet + kierros.pisteet.pisteet_koti;
					}
					else if (tiimi[i].joukkue == kierros.vierasjoukkue) {
						tiimi[i].maalit.tehdyt_maalit = tiimi[i].maalit.tehdyt_maalit + kierros.maalit.paastetyt_maalit;
						tiimi[i].maalit.paastetyt_maalit = tiimi[i].maalit.paastetyt_maalit + kierros.maalit.tehdyt_maalit;
						tiimi[i].haviot = tiimi[i].haviot + kierros.haviot;
					}
				}
				else if (kierros.maalit.paastetyt_maalit > kierros.maalit.tehdyt_maalit) { // syöttää tiedot jos vierasjoukkue voittaa ottelun
					if (tiimi[i].joukkue == kierros.kotijoukkue) {
						tiimi[i].maalit.tehdyt_maalit = tiimi[i].maalit.tehdyt_maalit + kierros.maalit.tehdyt_maalit;
						tiimi[i].maalit.paastetyt_maalit = tiimi[i].maalit.paastetyt_maalit + kierros.maalit.paastetyt_maalit;
						tiimi[i].haviot = tiimi[i].haviot + kierros.haviot;
					}
					else if (tiimi[i].joukkue == kierros.vierasjoukkue) {
						tiimi[i].maalit.tehdyt_maalit = tiimi[i].maalit.tehdyt_maalit + kierros.maalit.paastetyt_maalit;
						tiimi[i].maalit.paastetyt_maalit = tiimi[i].maalit.paastetyt_maalit + kierros.maalit.tehdyt_maalit;
						tiimi[i].voitot = tiimi[i].voitot + kierros.voitot;
						tiimi[i].kokonaispisteet = tiimi[i].kokonaispisteet + kierros.pisteet.pisteet_vieras;
					}
				}
				else {
					if (tiimi[i].joukkue == kierros.kotijoukkue) {							// syöttää tiedot, jos tulee tasapeli
						tiimi[i].maalit.tehdyt_maalit = tiimi[i].maalit.tehdyt_maalit + kierros.maalit.tehdyt_maalit;
						tiimi[i].maalit.paastetyt_maalit = tiimi[i].maalit.paastetyt_maalit + kierros.maalit.paastetyt_maalit;
						tiimi[i].kokonaispisteet = tiimi[i].kokonaispisteet + kierros.pisteet.pisteet_tasa;
					}
					else if (tiimi[i].joukkue == kierros.vierasjoukkue) {
						tiimi[i].maalit.tehdyt_maalit = tiimi[i].maalit.tehdyt_maalit + kierros.maalit.paastetyt_maalit;
						tiimi[i].maalit.paastetyt_maalit = tiimi[i].maalit.paastetyt_maalit + kierros.maalit.tehdyt_maalit;
						tiimi[i].kokonaispisteet = tiimi[i].kokonaispisteet + kierros.pisteet.pisteet_tasa;
					}
				}
			}
		kerroin = kerroin + 2;
		koti = false, vieras = false;
		}
		else if (toiminto == 2) {									// tulostaa sarjaulukon
		tiimi[KOKO-1] = jarjesta_joukkueet(tiimi, KOKO-1);			// aliohjelma, joka järjestää joukkueet sarjataulukkoon
		tulosta_joukkue(tiimi);										// aliohjelma joka tulostaa joukkueet
		
		}
		else if (toiminto == 3) {									// tulostaa otteluhistorian
			tulosta_otteluhistoria(otteluhistoria);
		}
		toiminto = valikko();
	}
	cout << "\n Kiitos ohjelman käytöstä! ";
	return EXIT_SUCCESS;
}