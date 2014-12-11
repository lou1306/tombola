/* 
 * File:   Tabella.cpp
 * Author: luca
 * 
 * Created on 27 novembre 2010, 19.44
 */
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "Tabella.h"

Tabella::Tabella() {
    /* Di default si comporta così: */
    ColonneOrdinate = false;
    Max3Consecutivi = false;
}

Tabella::Tabella(vector<int> *l) {
    Tabella();
    numeri = l;
}

void Tabella::Crea() {
    vector<int>::const_iterator i;
    int colonna, riga, numero;
    do {
        /* Pone tutte le caselle a zero */
        Reset();
        /* Se la tabella dev'essere in ordine, posiziona 90
         * (se è presente nel vettore "numeri") in basso a destra
         */
        if (ColonneOrdinate) {
            vector<int>::iterator novanta;
            novanta = find(numeri->begin(), numeri->end(), 90);
            if (novanta != numeri->end())
                table[2][8] = 90;
        }
        /* Prende un numero alla volta, lo posiziona nella
         * colonna corrispondente e in una riga a caso
         */
        for (i = numeri->begin(); i != numeri->end(); ++i) {
            numero = *i;
            if (numero == 90) {
                if (ColonneOrdinate)
                    /* In questo caso, 90 era già stato piazzato:
                     * passiamo al prossimo numero.
                     */
                    continue;
                else
                    colonna = 8;
            } else
                colonna = numero / 10;
            do {
                riga = rand() % 3;
                /* "gira" finché non trova una casella vuota */
            } while (table[riga][colonna] != 0);
            table[riga][colonna] = numero;  /* Scrive il numero */
        }
        /* Il ciclo si ripete finché ogni riga contiene esattamente 5 numeri */
    } while (!RigaOk(0) || !RigaOk(1) || !RigaOk(2));
    if (ColonneOrdinate) {
        for (int i = 0; i < 9; ++i)
            OrdinaColonna(i);
    }
}

void Tabella::OrdinaColonna(int colonna) {
    /* Mette gli elementi di una colonna in ordine crescente
     * dall'alto in basso.
     */
    switch (ContaElementiColonna(colonna)) {
        case 2: Confronta(colonna);
            break;
        case 3: Ordina(colonna);
            break;
        default: break;
    }
}

int Tabella::ContaElementiColonna(int colonna) const {
    int count = 0;
    for (int i = 0; i < 3; ++i)
        if (table[i][colonna] != 0) ++count;
    return count;
}

void Tabella::Confronta(int colonna) {
    /* Confronta i due elementi di una colonna e
     * li mette in ordine crescente (dall'alto verso il basso) */
    int zero;
    for (int i = 0; i < 3; ++i) {
        if (table[i][colonna] == 0)
            zero = i;
    }
    int primo, secondo;
    switch (zero) {
        case 0: primo = 1;
            secondo = 2;
            break;
        case 1: primo = 0;
            secondo = 2;
            break;
        case 2: primo = 0;
            secondo = 1;
            break;
    }
    if (table[primo][colonna] > table[secondo][colonna])
        Swap(primo, secondo, colonna);
}

void Tabella::Ordina(int colonna) {
    /* Un bubble sort per ordinare una colonna piena di numeri
     * (è l'algoritmo meno efficace, ma sono solo
     * tre elementi...)
     */
    bool scambio = true;
    while (scambio) {
        scambio = false;
        for (int i = 0; i < 2; ++i)
            if (//table[i][colonna] != 0
                   // && table[i + 1][colonna] != 0
                    1&& table[i][colonna] > table[i + 1][colonna]) {
                Swap(i, i + 1, colonna);
                scambio = true;
            }
    }
}

void Tabella::Swap(int r1, int r2, int colonna) {
    /* Scambia due elementi di una stessa colonna */
    int temp = table[r1][colonna];
    table[r1][colonna] = table[r2][colonna];
    table[r2][colonna] = temp;
}

bool Tabella::RigaOk(int riga) const {
    /* Una riga della Tabella è valida se contiene esattamente
     * cinque numeri. Se poi Max3Consecutivi è true, la riga
     * non può avere quattro o più numeri adiacenti.
     */
    int count = 0;
    for (int i = 0; i < 9; ++i) {
        if (table[riga][i] != 0)
            ++count;
    }
    if (Max3Consecutivi == false) {
        return (count == 5);
    }
    else {
        int riga_count = 0;
        for (int i = 0; i < 3 && riga_count < 4; ++i) {
            riga_count = 0;
            for (int j = 0; j < 9 && riga_count < 4; ++j) {
                if (table[i][j] != 0) ++riga_count;
                else riga_count = 0;
            }
        }
        return (count == 5 && riga_count < 4);
    }
}

void Tabella::Reset() {
    /* Azzera tutte le caselle della Tabella */
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 9; ++j) {
            table[i][j] = 0;
        }
    }
}

void Tabella::setColonneOrdinate(bool b) {
    ColonneOrdinate = b;
}

void Tabella::setMax3Consecutivi(bool b) {
    Max3Consecutivi = b;
}

ostream & operator<<(ostream& out, const Tabella &orig) {
    for (int i = 0; i < 3; ++i) {
        cout << "\t";
        for (int j = 0; j < 9; ++j) {
            if (orig.table[i][j] != 0)
                out << orig.table[i][j] << "\t";
            else out << " \t";
        }
        out << endl;
    }
    return out;
}