#include "mylib.h"

int main() {
	setlocale(LC_ALL, "");
	int kerroin = 2, toiminto, luku_taysi = 0;
	const int KOKO = 12;
	bool koti = false, vieras = false, kotij = false, vierasj = false;
	Joukkue tiimi[KOKO], kierros;
	vector<Joukkue> otteluhistoria;
	cout <<  "\t \t  \t \t J��kiekon SM-liigan sarjataulukko \n\n";
	toiminto = valikko();
	while (toiminto != 4) {
		if (toiminto == 1) {
			alku:
			kierros = keraatiedot();								//haetaan kierroksen tiedot
			otteluhistoria.push_back(kierros);						// ker�� tiedot otteluhistoriaan

			luku_taysi = 0;
			for (int i = 0; i < 12; i++) {							//tarkistaa, onko sarjataulukko jo t�ynn�
				if (tiimi[i].joukkue != "-") {
					luku_taysi++;
				}
				else {}
			}
			if (luku_taysi == 12) {									// tarkistaa onko kaikki joukkuepaikat jo t�ytetty. N�m� ja seuraava boolean - ehtolause tarvitaan
				for (int i = 0; i < 12; i++) {						// tilanteeseen,jossa joukkuepaikat ovat t�ynn� ja k�ytt�j� antaa tunnettuja joukkueita.
					if (tiimi[i].joukkue == kierros.kotijoukkue) {	// Antaa ilmoituksen VAIN kun annetaan "uusia" joukkueita.
						kotij = true;
					}
					if (tiimi[i].joukkue == kierros.vierasjoukkue) {
						vierasj = true;
					}
				}
			}
			if (luku_taysi == 12 && (kotij == false || vierasj == false)) {					// ilmoittaa k�ytt�j�lle jos joukkupaikat on jo t�ytetty, siirtyy alkuun.
				cout << "Kaikki joukkueet on jo annettu, ei voi lis�t� en�� uusia joukkueita!" << endl;
				goto alku;
			}

			if (tiimi[0].joukkue == "-") {							// lis�t��n 2 ensimm�ist� joukkuetta
				tiimi[0].joukkue = kierros.kotijoukkue;
				tiimi[1].joukkue = kierros.vierasjoukkue;
			}
			else {													// tutkitaan, l�ytyyk� annetut joukkueet jo sarjataulukosta.
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
				if (koti == false) {								//lis�� kotijoukkueen jos ei l�ydy sarjataulukosta
					for (int i = 0; i < 12; i++) {
						if (tiimi[i].joukkue == "-") {
							tiimi[i].joukkue = kierros.kotijoukkue;
							break;
						}
					}
				}
				if (vieras == false) {								// lis�� vierasjoukkueen jos ei l�ydy sarjataulukosta
					for (int i = 0; i < 12; i++) {
						if (tiimi[i].joukkue == "-") {
							tiimi[i].joukkue = kierros.vierasjoukkue;
							break;
						}
					}
				}
			}

			for (int i = 0; i <= 11; i++) {							// sy�tt�� tiedot jos kotijoukkue voittaa ottelun
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
				else if (kierros.maalit.paastetyt_maalit > kierros.maalit.tehdyt_maalit) { // sy�tt�� tiedot jos vierasjoukkue voittaa ottelun
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
					if (tiimi[i].joukkue == kierros.kotijoukkue) {							// sy�tt�� tiedot, jos tulee tasapeli
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
		tiimi[KOKO-1] = jarjesta_joukkueet(tiimi, KOKO-1);			// aliohjelma, joka j�rjest�� joukkueet sarjataulukkoon
		tulosta_joukkue(tiimi);										// aliohjelma joka tulostaa joukkueet
		
		}
		else if (toiminto == 3) {									// tulostaa otteluhistorian
			tulosta_otteluhistoria(otteluhistoria);
		}
		toiminto = valikko();
	}
	cout << "\n Kiitos ohjelman k�yt�st�! ";
	return EXIT_SUCCESS;
}