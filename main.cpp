//N Regine Solver v1.0 - Valerio Pinsone 2013
/* Inclusione librerie */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;
 
/* Dichiarazioni globali */
#define DIM 8 //Definisce la costante N nel problema N regine in una scacchiera NxN
char scacchiera[DIM][DIM]; //Creao una scacchiera NxN
 
/* Prototipi funzioni */
void inizializza(); //Inizializza la matrice
void risolvi(int rig, int col, int err); //(Riga, Colonna, Errore)
int controllo(int x, int y); // Controlla se una posizione (x,y) è attaccata [Restituisce 1] [0 se è libera]
void stampa();  //Stampa la matrice
void crea_file(); //crea un file HTML per una visualizzazione migliore
 
 
/* Main programma*/
int main(int n, char **argv){
    string scelta;
    inizializza();
    risolvi(0,0,0);
    stampa();
    cout << "\nVuoi visualizzare il risultato nel browser? (si/no): ";
    cin >> scelta;
    if(scelta=="si"||scelta=="Si"||scelta=="sI"||scelta=="SI"){
    crea_file();
    system("start n_regine.html");
    }
    return (EXIT_SUCCESS);
}
 
 
/* Funzioni */
 
/* Algoritmo ricorsivo di risoluzione (BackTracking) */
void risolvi(int rig, int col ,int err){
 
    if(err){  //Se la riga successiva non ha dato risultati
        for(int i = 0; i<DIM; i++){
            if(scacchiera[i][rig]=='R'){ //Trovo la regina attuale
               scacchiera[i][rig] = 'E'; //La rimuovo e segno la posizione
               break; //Interrompo il ciclo
            }
        }
    }
 
    if(rig<DIM){ //Se la riga non supera la dimensione massima
        for(int jx=col; jx<DIM; jx++){ //Ciclo che va dalla colonna input funzione alla dimensione massima (-1)
            int c = controllo(jx,rig); //Controllo se quella posizione è attaccata da altre regine
            if(c==0&&scacchiera[jx][rig]!='E'){ //Se non lo è AND non è una posizione che ho già usato
                scacchiera[jx][rig] = 'R'; //Inserisco la Regina
                risolvi(rig+1,0,0);   //Passo alla riga successiva
                return; //Ritorno la funzione
            }
        }
 
        //Nessuna soluzione nella riga
        for(int i = 0; i<DIM; i++){ //Ciclo che va da 0 a [DIM-1]
              scacchiera[i][rig] = ' '; //Azzero la riga
 
        }
 
              risolvi(rig-1,0,1); //BackTracking (riga precedente, colonna 0, errore 1)
    }
 
    }
 
/* Controlla posizione */
int controllo(int x, int y){
    int x_app, y_app; //Dichiaro due variabili di appoggio
 
    //Controllo Riga
    for(int i = 0; i<DIM; i++){
        if(scacchiera[i][y]=='R'){ //se la posizione [i][y] (per i che va da 0 a (DIM-1) è occupata
            return 1; //Ritorno 1
        }
    }
 
    //Controllo Colonna
    for(int i = 0; i<DIM; i++){
        if(scacchiera[x][i]=='R'){ //se la posizione [x][i] (per i che va da 0 a (DIM-1) è occupata
            return 1; //Ritorno 1
        }
    }
 
    //Controllo diagonale SX --> DX
    x_app = x; //Assegno alla variabile di appoggio x_app il valore di x
    y_app = y; //Assegno alla variabile di appoggio y_app il valore di y
 
    while(x_app>0&&y_app>0){ //Mentre la variabile x o y sono diverse dalla posizione iniziale ESEGUO:
        x_app--; //decremento la variabile
        y_app--; //decremento la variabile
    }
 
    while(x_app<DIM&&y_app<DIM){ //Controllo la diagonale che va da sx a dx
        if(scacchiera[x_app][y_app]=='R'){  //Se trovo una regina nella diagonale
            return 1; //Ritorno 1
        }
        x_app++; y_app++; //incremento le variabili x e y (mi muovo in basso a destra)
    }
 
    //Controllo diagonale DX --> SX
    x_app = x; //riassegno i valori iniziali alle variabili di appoggio
    y_app = y;
 
    while(x_app<DIM&&y_app>0){ //Mentre la coordinata x è minore della pos massima e la variabile y è maggiore della pos minima
        x_app++; //Incremento x
        y_app--; //Decremento y
    }
 
    while(x_app>=0&&y_app<DIM){ //Controllo la diagonale che va da dx a sx
        if(scacchiera[x_app][y_app]=='R'){ //Se trovo una regina nella diagonale
            return 1; //Ritorno 1
        }
        x_app--; y_app++; //decremento x e incremento y (mi muovo in basso a sinistra)
    }
 
    /*Nessun conflitto*/
    return 0; //se non ho ritornato 1 non ho trovato conflitti, quindi ritorno 0.
}
 
/* Inizializza la matrice */
void inizializza(){
    for(int i=0; i<DIM; i++){
        for(int j=0; j<DIM; j++){
            scacchiera[i][j] = ' '; //Inizializzo la matrice al char ' ' tramite for annidati
        }
    }
}
 
/* Stampa la matrice */
void stampa(){
    //Costruisce la tabella dos e stampa i valori nelle celle
    for(int i=0; i<DIM; i++ ){
 
        cout << "+---";
    }
    cout << "+" << endl;
    for(int i=0; i<DIM; i++){
        for(int j=0; j<DIM; j++){
            cout << "| ";
            if(scacchiera[j][i]!='E'){
                cout << scacchiera[j][i] << " ";
            }else{
                cout << "  ";
            }
 
        }
        cout << "|" << endl;
         for(int k=0; k<DIM; k++ ){
            cout << "+---";
         }
        cout << "+" << endl;
    }
}
 
/* Crea un file HTML */
void crea_file(){
    ofstream file;
    file.open("n_regine.html");
    file << "<html><head><style type=\"text/css\">a "
            "{color:#000;display:block;font-size:60px;height:80px;position:"
            "relative;text-decoration:none;text-shadow:0 1px #fff;"
            "width:80px;}#chess_board { border:5px solid #333; }#"
            "chess_board td {background:#fff;background:-moz-linear-gradient"
            "(top, #fff, #eee);background:-webkit-gradient(linear,0 0, 0 100%,"
            " from(#fff), to(#eee));box-shadow:inset 0 0 0 1px "
            "#fff;-moz-box-shadow:inset 0 0 0 1px #fff;-webkit-box-shadow:inset"
            " 0 0 0 1px #fff;height:80px;text-align:center;"
            "vertical-align:middle;width:80px;}#chess_board tr:nth-child(odd) td"
            ":nth-child(even),#chess_board tr:nth-child(even)"
            " td:nth-child(odd) {background:#ccc;background:-moz-linear-gradient"
            "(top, #ccc, #eee);background:-webkit-gradient"
            "(linear,0 0, 0 100%, from(#ccc), to(#eee));box-shadow:inset 0 0 "
            "10px rgba(0,0,0,.4);-moz-box-shadow:inset 0 0 10px"
            " rgba(0,0,0,.4);-webkit-box-shadow:inset 0 0 10px rgba(0,0,0,.4);}"
            "</style></head>";
    file << "<body bgcolor=\"#000\"><div align=\"center\"><table"
            " id=\"chess_board\" cellpadding=\"0\" cellspacing=\"0\">";
 
    for(int i=0; i<DIM; i++){
        file << "<tr>";
        for(int j=0; j<DIM; j++){
            if(scacchiera[j][i]=='R'){
                file << "<td id=\"H8\"><a href=\"#\" class=\"rook black\">&#9818;</a></td>";
            }else{
                file << "<td></td>";
            }
        }
        file << "</tr>";
    }
 
    file << "</table></div></body></html>";
    file.close();
 
}
