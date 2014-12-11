/* 
 * File:   Cartella.cpp
 * Author: luca
 * 
 * Created on 27 novembre 2010, 9.30
 */
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "Cartella.h"

Cartella::Cartella() {

}

Cartella::Cartella(Pool *pool) {
    this->p = pool;
}

void Cartella::setPool(Pool* pool) {
    this->p = pool;
}

void Cartella::Genera() {
    /* Riempie num con 15 valori casuali.
     * Prima estrae "finché può" dal pool */
    int start,end, a,j,max;
	for (int i = 0; i<9; i++) {
	    switch(i){
		    //case 0: start= 1; end=9; break;
		    case 8: start= 80; end= 90; break;
		    default: start= i*10; end=start+9; break;
		}
	    max=p->estrazioniPossibili(start, end);
            /* Estrae solo se c'è almeno un numero tra
             * start e end ancora nel pool.
             */
	    if (max != 0){
		for (j=0; j<max; j++) {
		    a = p->Extract(start, end);
		    num.push_back(a);
		}
	    }
	}
    /* Reinserimento nel pool dei valori in eccesso */
    int da_rimuovere = num.size()-15;
    if (da_rimuovere >0) {
        random_shuffle(num.begin(), num.end());
        for(int i=0; i<da_rimuovere; i++) {
            p->putIn(num.back());
            num.pop_back();
    }
    }
    sort(num.begin(), num.end());
}

int Cartella::getSize() const {
    return num.size();
}

void Cartella::Reset() {
    while(num.size() != 0){
	p->putIn(num.back());
	num.pop_back();
    }
}

ostream& operator <<(ostream &out, const Cartella &orig) {
    vector<int>::const_iterator i;
    for(i=orig.num.begin(); i!=orig.num.end(); i++)
	out << *i << " ";
    out << "\n(" << orig.num.size() << "), ";
    out << endl;
    return out;
}

bool Cartella::isValid(bool Max3) const {
    /* Una serie di controlli sulla validità della cartella */
    if (num.size() != 15)
	return false;
    int count = 0, decina;
    bool errore = false;
    vector<int>::const_iterator i,i_prec;
    i = i_prec = num.begin();
    i++;
//    while (i!= num.end() && !errore) {
//        /* Controlla che non vi siano più di tre numeri per ciascuna
//         * decina (90 è nella stessa decina di 80). Per farlo usa due
//         * iteratori (uno punta a num[x], l'altro a num[x+1]) e
//         * confronta i valori puntati.
//         * Siccome ho migliorato pool.EstrazioniPossibili(int start, int end)
//         * questo controllo non è più necessario, lo lascio commentato
//         * come esempio sull'uso degli iteratori :)
//         */
//	if (*i == 90)
//	    decina = 8;
//	else
//	    decina = *i / 10;
//	if (decina == *i_prec / 10)
//	    ++count;
//	else count = 0;
//	if (count > 2) errore = true;
//	++i;
//	++i_prec;
//    }
    if (Max3) {
        /* Questa è un po' ostica ^^
         * La richiesta di non avere più di tre elementi adiacenti rende
         * alcune cartelle impossibili da ordinare in modo soddisfacente:
         * - Due colonne piene adiacenti
         * - Qualsiasi combinazione di colonne adiacenti che contengano
         *   (2 elementi) (3 elem.) (2 elem.) (3 elem.)
         * Quindi bisogna contare il numero di elementi di ciascuna colonna,
         * memorizzarli su un array (chiamato "check") ed effettuare una
         * serie di controlli.
         */
	int check[9]={0,0,0,0,0,0,0,0,0};
	for (i = num.begin(); i!= num.end(); i++) {
	    if (*i != 90)
		++check[*i/10];
	    else ++check[8];
	    for(int i=0; i<8; ++i) {
		if ((check[i]==3 && check[i+1]==3)
		    ||	(check[i]==2 && check[i+1]==3
		    && check[i+2]==2 && check[i+3]==3)
		    ||	(check[i]==3 && check[i+1]==2
		    && check[i+2]==3 && check[i+3]==2)
		    ||  (check[i]==2 && check[i+1]==2
		    && check[i+2]==3 && check[i+3]==3)
		    ||  (check[i]==3 && check[i+1]==2
		    && check[i+2]==2 && check[i+3]==3))
		    errore = true;
	    }
	}
    }
    return !errore;
}

Tabella Cartella::CreaTabella(bool Ordinata, bool Max3) {
    /* Restituisce una Tabella contenente i numeri della
     * Cartella attuale. */
    Tabella t(&num);
    t.setColonneOrdinate(Ordinata);
    t.setMax3Consecutivi(Max3);
    t.Crea();
    return t;
}