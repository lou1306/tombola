/* 
 * File:   Serie.h
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

/* Una serie è una composizione di 6 cartelle;
 * la serie mette loro a disposizione un pool
 * unificato da cui estrarre i 90 numeri.
 * Inoltre contiene due parametri booleani per
 * le impostazioni scelte dall'utente. */

#ifndef SERIE_H
#define	SERIE_H
#include "Pool.h"
#include "Cartella.h"
#include <ostream>
using namespace std;

class Serie {
public:
    Serie();
    Serie(bool, bool);
    void GeneraSerie();
    void setOrdinate(bool);
    void setMax3(bool);
    void StampaTabelle(int);
    bool isValid() const;
    friend ostream& operator<<(ostream& out, const Serie &orig);
private:
    Cartella cartelle[6];
    Pool p;
    bool Ordinate;
    bool Max3;
};
#endif	/* SERIE_H */