/* 
 * File:   Pool.h
 * Author: luca
 *
 * Created on 26 novembre 2010, 23.11
 */
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/* Un pool è un array di 91 booleani.
 * numeri[0] resta inutilizzato;
 * numeri[i] (i va da 1 a 90) è
 * - TRUE se i è stato estratto
 * - FALSE se è ancora disponibile.
 * Insomma, si tratta di un'urna virtuale dalla quale estraiamo
 * i numeri per comporre le cartelle di una serie.
 */

#ifndef POOL_H
#define	POOL_H
#include <time.h>
#include <stdlib.h>

class Pool {
public:
    Pool();
    int Extract(int, int);
    void Reset();
    int itemsInPool() const;
    int estrazioniPossibili(int, int) const;
    void putIn(int n);
private:
    bool numeri[91];
};

#endif	/* POOL_H */
