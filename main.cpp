/* 
 * File:   main.cpp
 * Author: luca
 *
 * Created on 26 novembre 2010, 23.08
 */
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include "Pool.h"
#include "Cartella.h"
#include "Serie.h"

using namespace std;

/* Questo programma genera n serie di cartelle per giocare a tombola.
 * Una "serie" è formata da sei cartelle e contiene *tutti* i numeri da
 * 1 a 90 (15 numeri per ogni cartella, disposti in righe da 5).
 * L'output è pensato per essere scritto su un file csv e importato in
 * un foglio di calcolo. Le opzioni per generare le cartelle sono:
 * -n   <x> Genera x serie (x*6 cartelle). Per default si suppone -n 1.
 * -o   Genera cartelle Ordinate: i numeri di una colonna sono disposti in
 *      ordine crescente. Inoltre 90 si troverà sempre nell'ultima casella
 *      (terza riga, nona colonna)
 * -m   Le cartelle non conterranno più di 3 elementi adiacenti sulla stessa
 *      riga. Una riga (1) (13) (21) (35), ad esempio, non è considerata valida.
 * Sia -o che -m sono disabilitate di default.
 */

bool isInteger(char str[]) {
    /* Servirà per il parsing di -n */
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (!isdigit(str[i])) // if1
            return false;
    }
    return true;
}

int main(int argc, char** argv) {
    /* Generiamo il seed per rand() con l'ora di sistema */
    srand(time(NULL));
    int num_serie = 1;
    bool Max3, Ordinate;
    Ordinate = Max3 = false;
    Serie* s;
    /* Parser delle opzioni da linea di comando */
    for (int i = 1; i < argc; ++i) {
        if (string(argv[i]) == "-n") {
            /* Legge il numero delle serie da generare */
            if (i + 1 != argc) {
                if (isInteger(argv[i + 1])) {
                    num_serie = atoi(argv[i + 1]);
                    /* ++i serve ad impedire che il ciclo
                     * legga l'argv successivo, cioè
                     * argv[i+1] (cosa che abbiamo appena fatto)
                     */
                    ++i;
                } else {
                    cout << "Argomenti non validi.\n";
                    exit(1);
                }
            } else cout << "!?!?!!?\n";
        } else if (string(argv[i]) == "-h" || string(argv[i]) == "--help") {
            /* Stampa l'help ed esce senza errori */
            cout << "Utilizzo: Tombola [OPZIONI] \n"
                    << "-n NUMERO_SERIE\tSerie da generare\n"
                    << "\t\t(default :1)\n"
                    << "-o\t\tCrea cartelle Ordinate\n"
                    << "\t\t(disattivato di default)\n"
                    << "-m\t\tCrea cartelle con max. 3 elementi adiacenti\n"
                    << "\t\tsulla stessa riga (disattivato di default)\n"
                    << "-h, --help\tMostra questo help ed esce\n";
            exit(0);
        } else if (string(argv[i]) == "-o") {
            Ordinate = true;
        } else if (string(argv[i]) == "-m") {
            Max3 = true;
        } else {
            cout << "Argomenti non validi.\n";
            exit(1);
        }
    }
    for (int i = 0; i < num_serie; i++) {
        /* Iniziamo a generare le nostre n serie. Per evitare
         * di riempire la RAM, ogni serie viene creata in memoria
         * dinamica e distrutta alla fine di ciascuna iterazione
         * del ciclo for.
         */
        s = new Serie(Ordinate, Max3);
        do {
            /* Se la serie appena creata non è valida,
             * viene distrutta e rigenerata. */
            if (!s->isValid()) {
                delete s;
                s = new Serie(Ordinate, Max3);
            }
            s->GeneraSerie();
        } while (!s->isValid());
        /* Stampa la serie appena creata e dealloca la memoria. */
        s->StampaTabelle(i);
        delete s;
    }
    return 0;
}