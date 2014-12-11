/* 
 * File:   Cartella.h
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

/* Una cartella è un vettore di 15 numeri pescati a
 * caso da un pool condiviso con altre 5 cartelle.
 * Non va confusa con la Tabella, che è una sua rappresentazione
 * "grafica".
 */

#ifndef CARTELLA_H
#define	CARTELLA_H
#include "Pool.h"
#include "Tabella.h"
#include <vector>
#include <algorithm>
#include <ostream>
using namespace std;

class Cartella {
public:
    Cartella();
    Cartella(Pool*);
    void setPool(Pool*);
    void Genera();
    void Reset();
    int getSize() const;
    Tabella CreaTabella(bool, bool);
    bool isValid(bool) const;
    friend ostream& operator<<(ostream& out, const Cartella &orig);
private:
    Pool *p;
    vector<int> num;
    
};
#endif	/* CARTELLA_H */

