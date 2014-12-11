/* 
 * File:   Pool.cpp
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

#include "Pool.h"


Pool::Pool() {
    this->Reset();
}

int Pool::Extract(int min, int max) {
    /* Estrae un numero a caso tra min e max (estremi inclusi) */
	int estratto;
	do {
	estratto = min + (rand() % (max-min+1));
	} while (numeri[estratto] == true);  //Ignora i numeri già estratti
	numeri[estratto] = true;
	return estratto;
}

void Pool::Reset() {
    /* Rimette tutti i numeri nel pool. numeri[0]
     * è sempre "true" per non falsare il risultato
     * del metodo Pool::itemsInPool().
     */
    this->numeri[0]=true;
    for (int i = 1; i < 91; i++) {
	this->numeri[i]=false;
    }
}

int Pool::itemsInPool() const {
    /* Restituisce il numero di elementi ancora nel pool
     * (cioè pronti per essere estratti)
     */
    int result = 0;
    for (int i= 0; i < 91; i++) {
	if (numeri[i] == false)
	    ++result;
    }
    return result;
}

void Pool::putIn(int n) {
    /* Rimette "n" nel pool */
    if (n>0 && n < 91)
	this->numeri[n] = false;
}

int Pool::estrazioniPossibili(int start, int end) const {
    /* Indica quanti numeri tra start e end (inclusi)
     * sono ancora nel pool (cioè possono ancora essere estratti).
     * Se ve ne sono più di tre restituisce comunque 3
     * (sarebbe difficile piazzare 4 numeri su 3 righe, no?)
     */
    int count = 0;
    for(start; start <= end; start++)
	if (numeri[start] == false)
	    ++count;
    if (count > 3)  return 3;
    else return count;
}