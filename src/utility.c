#include <stdio.h>
#include <stdlib.h>
#include "users.h"
#include "utility.h"
#include <regex.h>
#include <windows.h>


/**
 * La funzione svolge il compito di controllare se un'e-mail e' presente o no,
 * effettua la ricerca confrontando ogni campo email di ogni giocatore presente nel database
 *
 * @param gamers e' l'array contenente i dati dei giocatori
 * @param contUs e' il contatore del numero dei giocatori
 * @param email e' il parametro che passo per effettuare la verifica, un array di caratteri
 * @return i = la posizione dell'e-mail del giocatore nel database se esiste, -1 altrimenti se non esiste nessun giocatore con quell'e-mail
 */
int searchMail(gamer gamers[], int contUs, char* email){
	int i, match;

	for(i=0; i<contUs; i++){
		 match = strcmp(email, gamers[i].email);		//Se match = 0 corrispondenza trovata, match != 0 e-mail non trovata
		 	if(match == 0){
		 		return i;								//Ritorno la posizione dell'e-mail del giocatore trovata
		 	}
	}
	return -1;											//Ritorno un valore di errore
}

/**
 * La funzione controlla che l'e-mail inserita sia valida secondo l'espressione regolare
 *
 *
 * @param email che passo per verificare la validita'
 * @return res = 0 se valida, res != 0 altrimenti
 */
int verEmail(char *email){
	const char *reg_exp = "[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?";
	   int res;
	   regex_t preg;
	   res = regcomp(&preg, reg_exp, REG_EXTENDED|REG_NOSUB);
	   res = regexec(&preg, email, (size_t)0, NULL, 0);
	   regfree(&preg);
	   return res;
}

/**
 * La funzione controlla se il livello del giocatore può essere aumentato oppure no
 * restituisce il livello incrementato se possibile altrimenti restituisce lo stesso livello
 *
 * @param played e' la variabile che contiene le ore di gioco che si stanno aumentando
 * @param levelOld e' il livello che passo alla funzione al momento della verifica dell'incremento
 * @return levelOld livello incrementato oppure stesso livello di partenza
 */
int levelCheck(int played, int levelOld){
	   int nextLevel;								//Memorizza il livello successivo a quello del momento
	   int hoursNeeded;								//Memorizza le ore necessarie per il livello successivo

	   for(int i=0; i<played; i++){
		   nextLevel = levelOld+1;					//Calcolo il livello successivo a quello preso in considerazione
		   hoursNeeded = nextLevel * nextLevel;		//Calcolo le ore necessarie affinche' il livello possa essere incrementato

	   	   if(played >= hoursNeeded){				//Controllo che le ore aggiunte siano maggiori o uguali alle ore necessarie
		   levelOld++;								//Incremento il livello
	   	   }
	   }
	 return levelOld;								//Ritorno il livello aggiornato oppure lo stesso di partenza
}


/**
 * La procedura opera un ordinamento decrescente in base al livello di ogni giocatore
 * e ne visualizza la lista aggiornata
 *
 * @param gamers e' l'array contenente i dati dei giocatori
 * @param contUs e' il contatore del numero dei giocatori
 */
void ordLevel(gamer gamers[], int contUs){
	gamer ordUs[MAX];
	gamer max;
	int i,j;

	memcpy(ordUs, gamers, sizeof(gamer)*MAX);				//Copio i dati in memoria riguardanti l'array gamers, in un array temporaneo alla procedura

	for(i=0; i<contUs-1; i++){							//Utilizzo l'algoritmo Selection Sort decrescente per ordinare in base al livello del giocatore
			max = ordUs[i];
			for(j=i+1; j<contUs; j++){
				if(ordUs[j].level > max.level){
					max = ordUs[j];
					ordUs[j] = ordUs[i];
					ordUs[i] = max;
				}
			}
	 }
		for (i=0; i<contUs; i++){
			printUser(ordUs, i);							//Stampo la lista di tutti gli utenti presenti ordinati per livello decrescente
		}
		system("pause");
		system("cls");
}

/**
 * La procedura permette di visualizzare la lista dei videogiochi posseduti da un giocatore,
 * effettua dei controlli sull'inserimento e se l'operazione va a buon fine mostra la lista dei giochi
 *
 * @param gamers e' l'array contenente i dati dei giocatori
 * @param store e' l'array contenente i dati dei videogiochi
 * @param relat e' l'array contenente i possessi dei videogiochi da parte dei giocatori
 * @param relat_len e' una variabile che memorizza quante relazioni <videogioco-giocatore> ci sono
 * @param contUs e' il contatore del numero dei giocatori
 * @param contGa e' il contatore del numero dei videogiochi
 */
void gameListU(gamer gamers[], game store[], owned relat[], int relat_len, int contUs, int contGa){
	char nick[25];
	int i;
	int error = 1;

		while(error){
			system("cls");																//Pulisco lo schermo
			SetColor(18);
			puts("VISUALIZZAZIONE LIBRERIA VIDEOGIOCHI DI UN GIOCATORE\n");
			SetColor(11);
			puts("Inserisci il nickname di cui vuoi visualizzarne la lista: \n");
			SetColor(15);
			fflush(stdin);														//Svuoto il buffer di input
			scanf("%s", nick);													//Acquisisco il nickname per la ricerca
				if(searchUser(gamers, contUs, nick) != -1){						//Controllo che il giocatore esista
					error = 0;													//Imposto gli errori a 0 = ho trovato il giocatore
				}
		}
				system("cls");												//Pulisco lo schermo
				SetColor(18);
				printf("\t\tLista dei giochi posseduti dall'utente %s:\n\n", nick);
				SetColor(15);

		for(i=0; i<relat_len; i++){											//Scansione array delle relazioni
			if(strcmp(relat[i].iduser, nick ) == 0){						//Confronto il nickname inserito con quelli presenti nell'array delle relazioni
				for(int k=0; k<contGa; k++){								//Scansione array dei giochi
					if(strcmp(relat[i].idgame, store[k].code) == 0){		//Confronto il codice del gioco inserito con quelli presenti nell'array delle relazioni

						printf("\n   Il codice del gioco e': %s\n", store[k].code);
						printf("   Il nome del gioco e': %s\n", store[k].name);
						printf("   Il produttore del gioco e': %s\n", store[k].production);
						printf("   La categoria del gioco e': %s\n", store[k].category);
						printf("   Il prezzo del gioco e': %.2f\n", store[k].price);
						printf("   L'eta' minima del gioco e': %d\n", store[k].agemin);
						puts("----------------------------------------------------------------------------");
					}
				}
			}
		}
		system("pause");
		system("cls");
}

/**
 * La funzione svolge il compito di controllare se un videogioco e' presente o no, effettua la ricerca
 * confrontando la chiave di ricerca con ogni campo codice del gioco di ogni videogioco presente nel database
 *
 * @param store e' l'array contenente i dati dei videogiochi
 * @param contGa e' il contatore del numero dei videogiochi
 * @param codeGa  e' il parametro che equivale al codice del gioco che passo per effettuare la verifica, un array di caratteri
 * @return i = la posizione del videogioco nel database se esiste, -1 altrimenti se non esiste nessun videogioco con quel codice
 */
int searchGame(game store[], int contGa, char* codeGa){
	int i, match;

	for(i=0; i<contGa; i++){
		match = strcmp(codeGa, store[i].code);				//Se match = 0 corrispondenza trovata, match != 0 videogioco non trovato
		if(match == 0){
		 	return i;										//Ritorno la posizione del videogioco trovato
		}
	}
	return -1;												//Ritorno un valore di errore
}


/**
 * E' una procedura che si occupa di ricercare un videogioco nello store e se il videogioco e' presente
 * visualizza tutti i dati associati ad esso.
 *
 * @param store e' l'array contenente i dati dei videogiochi
 * @param contGa e' il contatore del numero dei videogiochi
 */
void searchGameStore(game store[], int contGa){
	char game[25];
	int posG;
	int error = 1;

		while(error){
			system("cls");																//Pulisco lo schermo
			SetColor(18);
			puts("RICERCA DI UN VIDEOGIOCO NELLO STORE\n");
			SetColor(11);
			puts("Inserisci il codice valido del gioco che vuoi ricercare: \n");
			SetColor(15);
			fflush(stdin);											//Svuoto il buffer di input
			scanf("%s", game);										//Acquisisco il codice del videogioco da ricercare

			if(searchGame(store, contGa, game) != -1){				//Controllo che il videogioco esista
				error = 0;											//Imposto gli errori a 0 = ho trovato il videogioco
				posG=searchGame(store, contGa, game);				//Memorizzo la posizione del videogioco trovato
				system("cls");
				printf("\n   Il codice del gioco e': %s\n", store[posG].code);
				printf("   Il nome del gioco e': %s\n", store[posG].name);
				printf("   Il produttore del gioco e': %s\n", store[posG].production);
				printf("   La categoria del gioco e': %s\n", store[posG].category);
				printf("   Il prezzo del gioco e': %.2f euro\n", store[posG].price);
				printf("   L'eta' minima per il gioco e': %d anni\n", store[posG].agemin);
				puts("----------------------------------------------------------------------------\n\n");
			}
		}
		system("pause");
		system("cls");
}

/**
 * La procedura visualizza tutti i dati di un giocatore
 *
 * @param gamers e' l'array contenente i dati dei giocatori
 * @param i e' la posizione dell'array del giocatore di cui si vogliono visualizzare i dati
 */
void printUser(gamer gamers[], int i){
           printf("\n  Il nickname dell'utente numero %d e':\t\t %s\n", i+1, gamers[i].nickname);
           printf("  L'email dell'utente numero %d e':\t\t %s\n", i+1,  gamers[i].email);
           printf("  Il cognome dell'utente numero %d e':\t\t %s\n", i+1, gamers[i].surname);
           printf("  Il nome dell'utente numero %d e':\t\t %s\n", i+1, gamers[i].name);
           printf("  Il sesso dell'utente numero %d e':\t\t %c\n", i+1, gamers[i].gender);
           printf("  Le ore di gioco dell'utente numero %d sono:\t %d\n", i+1, gamers[i].played);
           printf("  Il livello dell'utente numero %d e':\t\t %d\n", i+1, gamers[i].level);
           printf("  Il credito dell'utente numero %d e':\t\t %.2f\n\n", i+1, gamers[i].credit);
           puts("----------------------------------------------------------------------------");
}

/**
 * La procedura visualizza tutti i dati relativi ad un videogioco
 *
 * @param store e' l'array contenente i dati dei videogiochi
 * @param i e' la posizione nell'array del videogioco di cui si vogliono visualizzare i dati
 */
void printGame(game store[], int i){
			printf("\n   Il codice del gioco numero %d e': %s\n", i+1, store[i].code);
			printf("   Il nome del gioco numero %d e': %s\n", i+1, store[i].name);
			printf("   Il produttore del gioco numero %d e': %s\n", i+1, store[i].production);
			printf("   La categoria del gioco numero %d e': %s\n", i+1, store[i].category);
			printf("   Il prezzo del gioco numero %d e': %.2f euro\n", i+1, store[i].price);
			printf("   L'eta' minima per il gioco numero %d e': %d anni\n\n", i+1, store[i].agemin);
			puts("----------------------------------------------------------------------------");
}


/**
 * La procedura scrive su file tutti i dati dei giocatori
 *
 * @param gamers e' l'array contenente i dati dei giocatori
 * @param contUs e' il contatore del numero dei giocatori
 */
void printFile(gamer gamers[], int contUs){
		FILE* loadUs;
			if((loadUs = fopen("users.csv", "w")) == NULL){
				printf("Impossibile aprire il file 'users'. \n");				//Visualizzo messaggio di errore se c'e' stato un problema sul file
				fflush(stdout);
			}
			else {
				for(int i=0; i<contUs; i++){
				//Stampo su file i dati relativi ai giocatori
				fprintf(loadUs, "%s,%s,%s,%s,%c,%d,%d,%.2f\n", gamers[i].nickname, gamers[i].email, gamers[i].surname, gamers[i].name, gamers[i].gender, gamers[i].played, gamers[i].level, gamers[i].credit);
				}
			}
	  		fclose(loadUs);
}

/**
 * La procedura scrive su file tutte le relazioni <giocatore-videogioco> che sono presenti sul database
 *
 * @param relat e' l'array contenente tutte le relazioni <giocatore-videogioco>
 * @param relat_len e' la dimensione dell'array e quindi il numero delle relazioni presenti
 */
void printFileRelat(owned relat[], int relat_len){
		FILE* loadRelat;
			if((loadRelat = fopen("relat.csv", "w")) == NULL){
				printf("Impossibile aprire il file 'relat'. \n");				//Visualizzo messaggio di errore se c'e' stato un problema sul file
				fflush(stdout);
			}
	  	    else {
	  	    	for(int i=0; i<relat_len; i++){
	  	    	fprintf(loadRelat, "%s,%s\n", relat[i].iduser, relat[i].idgame);	//Stampo su file i dati delle relazioni
	  	    	}
	  	    }
	  		fclose(loadRelat);
}

/**
 * La procedura scrive su file la libreria dei videogiochi di un giocatore,
 * inserendo un nickname se e' presente, verra' creato un nuovo file con la libreria
 * @param gamers e' l'array contenente i dati dei giocatori
 * @param store e' l'array contenente i dati dei videogiochi
 * @param relat e' l'array contenente tutte le relazioni <giocatore-videogioco>
 * @param relat_len e' la dimensione dell'array e quindi il numero delle relazioni presenti
 * @param contUs e' il contatore del numero dei giocatori
 * @param contGa e' il contatore del numero dei videogiochi
 */
void printFileGamesUser(gamer gamers[], game store[], owned relat[], int relat_len, int contUs, int contGa){
	FILE* loadGamerList;
	char nick[25];
	int i;
	int error = 1;

		while(error){
			system("cls");																//Pulisco lo schermo
			SetColor(18);
			puts("SCRITTURA SU FILE DELLA LIBRERIA DI UN GIOCATORE\n");
			SetColor(11);
			puts("Inserisci il nickname di cui vuoi scrivere la lista dei videogiochi su file: \n");
			SetColor(15);
			fflush(stdin);														//Svuoto il buffer di input
			scanf("%s", nick);													//Acquisisco il nickname per la ricerca
				if(searchUser(gamers, contUs, nick) != -1){						//Controllo che il giocatore esista
					error = 0;													//Imposto gli errori a 0 = ho trovato il giocatore
				}
		}
				if((loadGamerList = fopen("games.csv", "w")) == NULL){
					printf("Impossibile aprire il file 'relat'. \n");
					fflush(stdout);
				}
		  	    else {
		  	    	fprintf(loadGamerList, "Libreria dei videogiochi di %s \n\n",nick);
		  	    	for(i=0; i<relat_len; i++){
		  					if(strcmp(relat[i].iduser, nick ) == 0){

		  						for(int k=0; k<contGa; k++){
		  							if(strcmp(relat[i].idgame, store[k].code) == 0){
		  								fprintf(loadGamerList, "Il codice del gioco e' %s\n Il nome del gioco e' %s\n La casa produttrice del gioco e' %s\n La categoria del gioco e' %s\n Il prezzo del gioco e' %.2f euro\n L'eta' minima di gioco e' %d anni\n\n", store[k].code, store[k].name, store[k].production, store[k].category, store[k].price, store[k].agemin);

		  							}
		  						}
		  					}
		  			}
		  	    	system("cls");
		  	    	SetColor(10);
		  	    	printf("La libreria dei videogiochi di %s e' stata scritta su file\n\n", nick);
		  	    	SetColor(15);
		  	    	system("pause");
		  	    	system("cls");
		  	    }

				fclose(loadGamerList);
		  	    }




/**
 * La procedura consente di cambiare il colore del testo
 *
 * @param Color e' il parametro che richiede un numero che stabilisce il colore
 */
void SetColor(short Color){
HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); // oppure system("COLOR E9");
SetConsoleTextAttribute(hCon,Color);
}
