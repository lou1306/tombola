/* 
 * File:   Tabella.h
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
/* Una Tabella è una disposizione di 15 numeri (forniti da una Cartella)
 * disposti su 3 righe (5 per riga, se ho fatto bene i conti): la disposizione
 * segue regole definite dall'utente all'avvio del programma e memorizzate in due
 * booleani.
 */

#ifndef TABELLA_H
#define	TABELLA_H
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
using namespace std;

class Tabella {
public:
    Tabella();
    Tabella(vector<int>*);
    void Crea();
    void Reset();
    void setColonneOrdinate(bool);
    void setMax3Consecutivi(bool);
    void OrdinaColonna(int);
    int ContaElementiColonna(int) const;
    bool RigaOk(int) const;
    friend ostream& operator<<(ostream& out, const Tabella &orig);
private:
    int table[3][9];
    vector<int> *numeri;
    bool Max3Consecutivi;
    bool ColonneOrdinate;
    void Swap(int riga, int c1, int c2);
    void Ordina(int);
    void Confronta(int);

};

#endif	/* TABELLA_H */

