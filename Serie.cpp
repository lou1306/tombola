/* 
 * File:   Serie.cpp
 * Author: luca
 * 
 * Created on 27 novembre 2010, 13.41
 */
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "Serie.h"

Serie::Serie() {
    Serie(false,false);
}

Serie::Serie(bool o, bool m) {
    Ordinate = o;
    Max3 = m;
    /* Rigenera il pool */
    p.Reset();
    for (int i = 0; i < 6; i++) {
        /* Assegna il pool alle cartelle */
        cartelle[i].setPool(&p);
    }
}

void Serie::GeneraSerie() {
    for (int i = 0; i < 6; i++) {
        cartelle[i].Genera();
    }
}

void Serie::StampaTabelle(int serieAttuale) {
    for (int i = 0; i < 6; i++) {
        cout << "Cartella " << (serieAttuale * 6) + i + 1 << "\n"
                << cartelle[i].CreaTabella(Ordinate, Max3);
    }
}

ostream & operator<<(ostream& out, const Serie &orig) {
    for (int i = 0; i < 6; i++)
        out << orig.cartelle[i] << endl;
    return out;
}

bool Serie::isValid() const {
    return (cartelle[0].isValid(Max3) && cartelle[1].isValid(Max3) &&
            cartelle[2].isValid(Max3) && cartelle[3].isValid(Max3) &&
            cartelle[4].isValid(Max3) && cartelle[5].isValid(Max3));
}