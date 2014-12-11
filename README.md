tombola
=======
Questo programma genera n serie di cartelle per giocare a tombola.

Una "serie" è formata da sei cartelle e contiene *tutti* i numeri da
1 a 90 (15 numeri per ogni cartella, disposti in righe da 5).

L'output è pensato per essere scritto su un file csv e importato in
un foglio di calcolo.

Le opzioni per generare le cartelle sono:
* `-n x`   Genera x serie (x*6 cartelle). Default:  1.
* `-o`  Genera cartelle Ordinate: i numeri di una colonna sono disposti in
     ordine crescente. Inoltre 90 si troverà sempre nell'ultima casella
    (terza riga, nona colonna)
* -m   Le cartelle non conterranno più di 3 elementi adiacenti sulla stessa
      riga. Una riga (1) (13) (21) (35), ad esempio, non è considerata valida.
 
 Sia -o che -m sono disabilitate di default.
