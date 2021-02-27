/*
 ============================================================================
 Name        : CasoDiStudio.c
 Author      : Maio Walter
 Version     : v 1.0
 Copyright   :
 Description : Caso di studio relativo alla traccia numero 3
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "users.h"
#include "utility.h"

int main(void) {

	//	system("mode con lines=37");

		FILE* loadGa;		  //puntatore a file utile al caricamento dei giochi dallo store
		FILE* loadUs;		  //puntatore a file utile al caricamento dei giocatori dal database
		FILE* loadRelat;	  //puntatore a file utile al caricamento delle possessioni dei giochi da parte dei giocatori
		gamer gamers[MAX];    //array di struct contenente i dati dei giocatori
		game store[MAX];	  //array di struct contenente i dati dei videogiochi
		owned relat[300];	  //array di struct utile alla memorizzazione delle relazioni < giocatore-gioco >
		char arraybuf[200];	  //array di supporto utile alla tokenizzazione delle informazioni del giocatore
		char x;				  //memorizza la scelta da parte dell'utente
		int contUs = 0;	      //memorizza il numero di giocatori inseriti
		int contGa = 0;		  //memorizza il numero dei videogiochi presenti sulla piattaforma
		int relat_len = 0;	  //memorizza il numero delle relazioni < giocatore-gioco >


        if((loadGa=fopen("store.csv", "r")) == NULL){
        	printf("Impossibile aprire il file 'store'. \n");
        	fflush(stdout);
        }
        else {
        		while(fgets(arraybuf, 200, loadGa) > 0){
        			strcpy(store[contGa].code, strtok(arraybuf, ","));
        			strcpy(store[contGa].name, strtok(NULL, ","));
        			strcpy(store[contGa].production , strtok(NULL, ","));
        			strcpy(store[contGa].category, strtok(NULL, ","));
        			store[contGa].price=strtof(strtok(NULL, ","), NULL);
        			store[contGa].agemin=strtol(strtok(NULL, ","), NULL, 10);

        			contGa = contGa + 1;
        		}
        }
        fclose(loadGa);


		if((loadUs=fopen("users.csv", "r")) == NULL){
				printf("Impossibile aprire il file 'users'. \n");
				fflush(stdout);
		}
		else {
				 while(fgets(arraybuf, 100, loadUs) > 0){
					strcpy(gamers[contUs].nickname, strtok(arraybuf, ","));
					strcpy(gamers[contUs].email, strtok(NULL, ","));
					strcpy(gamers[contUs].surname, strtok(NULL, ","));
					strcpy(gamers[contUs].name, strtok(NULL, ","));
					gamers[contUs].gender=strtok(NULL, ",")[0];
					gamers[contUs].played=strtof(strtok(NULL, ","), NULL);
					gamers[contUs].level=strtol(strtok(NULL, ","), NULL, 10);
					gamers[contUs].credit=strtof(strtok(NULL, ","), NULL);

					contUs = contUs + 1;
				 }
		 }
		 fclose(loadUs);


		 if((loadRelat=fopen("relat.csv", "r")) == NULL){
				printf("Impossibile aprire il file 'relat'. \n");
				fflush(stdout);
		 }
		 else {
				 while(fgets(arraybuf, 100, loadRelat) > 0){
					strcpy(relat[relat_len].iduser, strtok(arraybuf, ","));
					strcpy(relat[relat_len].idgame, strtok(NULL, "\n"));

					relat_len = relat_len + 1;
			     }
		 }
		 fclose(loadRelat);

			 SetColor(11);
			 printf("\t\t\t\t\t\t#######################\n");
			 printf("\t\t\t\t\t\t#        GAMEBOX      #\n");
			 printf("\t\t\t\t\t\t#######################\n");
			 printf("\t\t\t\t\t\t#         v1.0        #\n");
			 printf("\t\t\t\t\t\t#######################\n");
			 SetColor(15);

			printf("\t\t\t PROGRAMMA CHE SI OCCUPA DELLA GESTIONE DI UNO STORE DI VIDEOGIOCHI:\n\n");
			printf("Il software realizzato e' una piattaforma di videogiochi online,\ndove e' possibile svolgere funzionalita' per la migliore gestione di giocatori e di videogiochi\n\n");
			system("pause");
			system("cls");
		do{
			SetColor(18);
			printf("  INSERISCI LA SCELTA TRA LE OPZIONI DISPONIBILI:\n\n");
			SetColor(15);
			printf("Digita a per inserire un nuovo giocatore\n\n");
			printf("Digita b per modificare i dati di un giocatore\n\n");
			printf("Digita c per aggiungere un videogioco alla libreria dei videogiochi di un giocatore\n\n");
			printf("Digita d per aggiungere credito ad un giocatore\n\n");
			printf("Digita e per visualizzare la libreria dei videogiochi di un giocatore\n\n");
			printf("Digita f per aumentare le ore di gioco di un giocatore\n\n");
			printf("Digita g per visualizzare i giocatori piu' forti in base al livello\n\n");
			printf("Digita h per ricercare un videogioco nello store\n\n");
			printf("Digita i per visualizzare i dati di tutti i giocatori\n\n");
			printf("Digita l per visualizzare tutti i videogiochi presenti sulla piattaforma\n\n");
			printf("Digita m per per scrivere su file la libreria dei videogiochi di un giocatore\n\n");
			printf("Digita 0 per uscire dal programma\n\n");
			puts("----------------------------------------------------------------------------\n");
			fflush(stdin);											//Svuoto il buffer di input
			x = getchar();											//Acquisisco il carattere per la scelta
			if(getchar() != '\n'){									//Controllo che il secondo carattere sia invio, errore inserimento altrimenti
				x = '\0';
			}

			switch (x){

			case 'a':{
				newUser(gamers, &contUs);
				printFile(gamers, contUs);
			}
			break;

			case 'b':{
				modUser(gamers, contUs);
				printFile(gamers, contUs);
			}
			break;

			case 'c':{
				addGame(gamers, store, relat, &relat_len, contUs, contGa);
				printFileRelat(relat, relat_len);
				printFile(gamers, contUs);
			}
			break;

			case 'd':{
				addCredit(gamers, contUs);
				printFile(gamers, contUs);
			}
			break;

			case 'e':{
				gameListU(gamers, store, relat, relat_len, contUs, contGa);
			}
			break;

			case 'f':{
				addHours(gamers, contUs);
				printFile(gamers, contUs);
			}
			break;

			case 'g':{
				system("cls");
				SetColor(18);
				puts("\t\tLista dei giocatori ordinati per livello decrescente:\n");
				SetColor(15);
				ordLevel(gamers, contUs);						//Visualizzo la lista di tutti i giocatori ordinati per livello maggiore

			}
			break;

			case 'h':{
				searchGameStore(store, contGa);
			}
			break;

			case 'i':{
				 system("cls");
				 SetColor(18);
				 puts("\t\tLista dei giocatori presenti sulla piattaforma:\n");
				 SetColor(15);
				 	 for (int i=0; i<contUs; i++){
				 		 printUser(gamers, i);						//Visualizzo la lista di tutti i giocatori presenti
				 	 }
						system("pause");
						system("cls");
			}
			break;

			case 'l':{
				 system("cls");
				 SetColor(18);
				 puts("\t\tLista dei videogiochi presenti sulla piattaforma:\n");
				 SetColor(15);
				 	 for (int i=0; i<contGa; i++){
				 		 printGame(store, i);						//Visualizzo la lista di tutti i videogiochi presenti
				 	 }
				 	system("pause");
				 	system("cls");
			}
			break;

			case 'm':{
				 printFileGamesUser(gamers, store, relat, relat_len, contUs, contGa);
			}
			break;

			case '0':{
				system("cls");
				SetColor(12);
				printf("\nIl Programma e' stato chiuso.\n");
				SetColor(10);
				printf("\t###################################\n");
				printf("\t#    Created by Maio Walter       #\n");
				printf("\t###################################\n");
				printf("\t#         v1.0 - 2017             #\n");
				printf("\t###################################\n\n");
				SetColor(15);
				system("pause");
			}
			break;

			default:{
				system("cls");
				SetColor(12);
				puts("\nErrore, la tua scelta non e' valida!\n");
				SetColor(15);
			}
			break;
			}
		}
	while(x != '0');
}
