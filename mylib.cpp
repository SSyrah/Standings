#include "mylib.h"

// Ohjelma kysyy toiminnon ja tarkistaa käyttäjän syötteen valikkoa koskien.
int valikko() {
	bool virhe;
	int valinta;
	do {
		virhe = false;
		string syote;
		cout << "Syötä toiminto (1 = tuloksen lisääminen, 2 = sarjataulukon tulostaminen, 3 = tulosta otteluhistoria, 4 = lopetus): ";
		cin >> syote;
		istringstream arvo(syote);
		char temp = '\0';
		if (!(arvo>>valinta) || arvo.get(temp) || valinta < 1 || valinta > 4) {
			cout << "En tunnista toimintoa, syota uudelleen." << endl;
			virhe = true;
			cin.ignore(100, '\n');
			}
	} while (virhe);
	return valinta;
}

// Ohjelma tarkistaa syotteen koskien maalituloksia
int maalientarkistus() {
	bool virhe;
	int x;
	do {
		virhe = false;
		string syote;
		cin >> syote;
		istringstream arvo(syote);
		char temp = '\0';														
		if (!(arvo>>x) || arvo.get(temp) || x < 0 || x > 71) {		// tuskin jääkiekossa tehdään yli 70 maalia pelissä? =D
			cout << "Väärä syöte, anna maalit uudelleen. " << endl;				// if-lause katsoo, onko kyseessä puhdas int vai ei.
			virhe = true;														// eka ehto, jos arvo ei mene x:ään (on puhdas string),arvo on true.
			cout << "Syötä maalit uudelleen: ";									// toinen ehto: temp katkoo ekaan ei int-arvoon. Jos löytyy ei-int, tämä ehto true.
			cin.ignore(100,'\n');
		}																		
	} while (virhe);															
	return x;
}


// tämä ohjelma kerää yhden kierroksen tiedot ja tulostaa ruudulle, kuka voitti vai tuliko tasapeli.
// Lisäksi kerää tiedot ylös kierroksesta ja palauttaa ne pääohjelmaan.
Joukkue keraatiedot() {
	Joukkue tempkierros;
	string syote;
	bool virhe;
	aloitus:
	cin.ignore(256, '\n');
	cout << "\nKotijoukkueen nimi:  ";
	getline(cin,tempkierros.kotijoukkue);
	cout << "Vierasjoukkueen nimi:  ";
	getline(cin,tempkierros.vierasjoukkue);
	if (tempkierros.kotijoukkue == tempkierros.vierasjoukkue) {
		cout << "Annoit saman joukkueen kahdesti, syötä uudelleen joukkueet." << endl;
		goto aloitus;
	}
	cout << "Syöttämäsi joukkueet ovat:\nKotijoukkue =  " << tempkierros.kotijoukkue << "\nVierasjoukkue =  " << tempkierros.vierasjoukkue << "\nHaluatko jatkaa? (k/e) ";
	cin >> syote;
	while (syote != "k") {										// tarkistaa syötteen, jos k, siirtyy koko while-loopin ohi, jos muuta siirtyy do-while looppiin.
		do {
			if (syote == "e") {
				goto aloitus;
			}
			else if (syote == "k") {
				break;
			}
			virhe = false;
			if (cin.fail() || syote != "e" || syote != "k") {
				virhe = true;
				cin.clear();
				cin.ignore(256, '\n');
				cout << "En tunnista komentoa syötä uudelleen (k/e): ";
				cin >> syote;
			}
		} while (virhe);
	}
	cout << "\nKotijoukkueen maalit (max 70 maalia):  ";										//kotijoukkueen maalit
	tempkierros.maalit.tehdyt_maalit = maalientarkistus();
	cout << "Vierasjoukkueen maalit (max 70 maalia):  ";										//vierasjoukkueen maalit
	tempkierros.maalit.paastetyt_maalit = maalientarkistus();

	if (tempkierros.maalit.tehdyt_maalit > tempkierros.maalit.paastetyt_maalit) {			//jos kotijoukkue voittaa siirtyy tähän
		cout << "\n" << tempkierros.kotijoukkue << " voitti maalein: " << tempkierros.maalit.tehdyt_maalit << " - " << tempkierros.maalit.paastetyt_maalit << "." << endl;
		cout << "Tulos lisätty sarjataulukkoon." << endl << endl;
		tempkierros.pisteet.pisteet_koti = 3;
		tempkierros.haviot = 1;
		tempkierros.voitot = 1;
	}
	else if (tempkierros.maalit.tehdyt_maalit < tempkierros.maalit.paastetyt_maalit) {		//jos vierasjoukkue voittaa, siirtyy tähän
		cout << "\n" << tempkierros.vierasjoukkue << " voitti maalein: " << tempkierros.maalit.tehdyt_maalit << " - " << tempkierros.maalit.paastetyt_maalit << "." << endl;
		cout << "Tulos lisätty sarjataulukkoon." << endl << endl;
		tempkierros.pisteet.pisteet_vieras = 3;
		tempkierros.haviot = 1;
		tempkierros.voitot = 1;

	}
	else {																					// jos tasapeli, siirtyy tähän
		cout << "\n Joukkuuet pelasivat tasan maalein: " << tempkierros.maalit.tehdyt_maalit << " - " << tempkierros.maalit.paastetyt_maalit << "." << endl;
		cout << "Tulos lisätty sarjataulukkoon." << endl << endl;
		tempkierros.pisteet.pisteet_tasa = 1;

	}
	return tempkierros;
}
// asettaa joukkueet pisteiden mukaan suuruusjärjestykseen
Joukkue jarjesta_joukkueet(Joukkue tiimi[], int x) {
	Joukkue temp;
	for (int i = 0; i < 11; i++) {
		for (int j = i + 1; j <= 11; j++) {
			if (tiimi[i].kokonaispisteet <= tiimi[j].kokonaispisteet) {				// tarkistaa kummalla suuremmat pisteet
				temp = tiimi[j];
				tiimi[j] = tiimi[i];
				tiimi[i] = temp;
				if (tiimi[i].kokonaispisteet == tiimi[j].kokonaispisteet && tiimi[i].voitot <= tiimi[j].voitot) {	//jos pisteet samat, tarkistaa, kummalla enemmän voittoja
					temp = tiimi[j];
					tiimi[j] = tiimi[i];
					tiimi[i] = temp;

					if (tiimi[i].voitot == tiimi[j].voitot && tiimi[i].maalit.tehdyt_maalit - tiimi[i].maalit.paastetyt_maalit
						<= tiimi[j].maalit.tehdyt_maalit - tiimi[j].maalit.paastetyt_maalit) {						//jos voitot samat, tarkista, kummalla parempi maaliero
						temp = tiimi[j];
						tiimi[j] = tiimi[i];
						tiimi[i] = temp;

						if (tiimi[i].maalit.tehdyt_maalit - tiimi[i].maalit.paastetyt_maalit == tiimi[j].maalit.tehdyt_maalit - tiimi[j].maalit.paastetyt_maalit
							&& tiimi[i].maalit.tehdyt_maalit <= tiimi[j].maalit.tehdyt_maalit) {					// jos maaliero sama, tarkistaa, kummalla enemmän tehtyjä maaleja
							temp = tiimi[j];
							tiimi[j] = tiimi[i];
							tiimi[i] = temp;
						}
					}
				}

			}
		}
	}
	return tiimi[x];
}

// tulostaa joukkueet sarjataulukkona
void tulosta_joukkue(Joukkue x[12]) {
	cout << "\nJoukkue		V	T	H     Maalit	P " << endl;
	for (int i = 0; i <= 11; i++) {
		if (x[i].joukkue != "-") {				// tulostaa kaikki joukkueet, jotka eivät ole "tyhjiä"
			cout << left << setw(10) << x[i].joukkue << "\t" << x[i].voitot << "\t" << x[i].tasapelit << "\t";
			cout << x[i].haviot << "\t" << x[i].maalit.tehdyt_maalit << "-" << x[i].maalit.paastetyt_maalit << "\t" << x[i].kokonaispisteet << endl;
		}
	} cout << endl;
}

// tulostaa koko otteluhistorian
void tulosta_otteluhistoria(vector<Joukkue> &temp) {
	cout << "\n  	 Otteluhistoria:		" << endl;
	cout << "Kotijoukkue	Maalit	Vierasjoukkue" << endl;
	for (int i = 0; i < temp.size(); i++) {
		cout << left << setw(10) << temp[i].kotijoukkue << "\t" << temp[i].maalit.tehdyt_maalit << " - " << temp[i].maalit.paastetyt_maalit << "\t" << temp[i].vierasjoukkue << endl;
	}
	cout << endl;
}
