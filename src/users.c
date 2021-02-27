#include "users.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"


/**
 * La procedura permette di aggiungere un nuovo giocatore al database,
 * effettua dei controlli sui dati inseriti e ne verifica la validita'.
 *
 * @param gamers e' l'array contenente i dati dei giocatori
 * @param pcontUs e' il contatore del numero dei giocatori
 */
void newUser(gamer gamers[], int *pcontUs){
	   char nickname[25];
	   char email[25];
	   char sex;
	   int valid;
	   int error;

	   system("cls");																//Pulisco lo schermo
	   SetColor(18);
	   puts("INSERIMENTO NUOVO GIOCATORE\n");
	   SetColor(11);
	   puts("Inserisci il nickname del nuovo giocatore <max 25 caratteri> (ricorda: la scelta e' permanente):\n");
	   SetColor(15);
	   do{
		   fflush(stdin);															//Svuoto il buffer di input
		   gets(nickname);
		   	 if(searchUser(gamers, *pcontUs, nickname) != -1){						//Controllo la presenza dell'utente, ritorna -1 se non esiste
		   		  SetColor(12);  													//Imposto il colore rosso al testo
		   		  puts("Nickname gia presente, inserisci un nuovo nickname:\n");
		   		  SetColor(15);	 													//Imposto il colore bianco al testo
		   	 } else strcpy(gamers[*pcontUs].nickname, nickname);					//Copio il nickname inserito nella struct del giocatore
	   }
       while(searchUser(gamers, *pcontUs, nickname) != -1);							//Ripeto finche' si inserisce un nickname non presente nel database

	   	   do{
	   		  error = 0;															//Imposto gli errori a 0
	   		  SetColor(11);
	   		  puts("\nInserisci l'email del giocatore: \n");
	   		  SetColor(15);
	   		  fflush(stdin);														//Svuoto il buffer di input
	   		  scanf("%s", email);													//Acquisisco l'email

	   		   	if(verEmail(email)){												//Controllo che l'e-mail inserita sia valida
	   		   		SetColor(12);
	   		   		puts("Email non valida");
	   		   		SetColor(15);
	   		   		error = 1;														//Se l'e-mail inserita non e' valida, imposto gli errori a 1
	   		   	}

	   		   	if(!error && !(-1 == searchMail(gamers, *pcontUs, email))){			//Controllo errori sull'inserimento dell'email valida e sulla presenza nel database
	   		   		SetColor(12);
	   		   		puts("Email gia presente");
	   		   		SetColor(15);
	   		   		error = 1;														//Se l'e-mail inserita esiste gia', imposto gli errori a 1
	   		   	}
	   		  }
	   		  while(error);															//Ripeto finche' riscontro errori

	   		  strcpy(gamers[*pcontUs].email, email);								//Copio l'email inserita nella struct del giocatore

	   	SetColor(11);
	   	puts("\nInserisci il cognome del giocatore:\n");
	   	SetColor(15);
	   	fflush(stdin);														//Svuoto il buffer di input
		gets(gamers[*pcontUs].surname);										//Acquisisco il cognome del giocatore
		SetColor(11);
		puts("\nInserisci il nome del giocatore:\n");
		SetColor(15);
		fflush(stdin);														//Svuoto il buffer di input
		gets(gamers[*pcontUs].name);										//Acquisisco il nome del giocatore

		do{
			SetColor(11);
			puts("\nInserisci il sesso del giocatore, m o f:\n");
			SetColor(15);
			fflush(stdin);													//Svuoto il buffer di input
			sex = getchar();												//Acquisisco carattere per il sesso
			if(getchar() != '\n'){											//Controllo che il secondo carattere sia l'invio, altrimenti errore inserimento
				sex = '\0';
			}
		}
		while(!((sex == 'm') || (sex == 'f')));								//Ripeto finche' non si inseriscono i caratteri 'm' o 'f'
		gamers[*pcontUs].gender=sex;										//Copio il sesso inserito nella struct del giocatore

		do{
			SetColor(11);
			puts("\nInserisci il credito del giocatore in euro:\n");
			SetColor(15);
			fflush(stdin);													//Svuoto il buffer di input
			valid=scanf("%f", &gamers[*pcontUs].credit);					//Controllo che il valore tornato dalla scanf sia diverso da 1
		}
		while(valid != 1);													//Ripeto finche' il credito inserito è valido

		gamers[*pcontUs].level = 1;											//Imposto il livello del giocatore a 1
		*pcontUs = *pcontUs + 1;											//Incremento il puntatore ad intero che mi indica il numero dei giocatori


		system("cls");														//Pulisco lo schermo
		SetColor(10);
		printf("\nUtente inserito correttamente\n\n\n");
		SetColor(15);
		system("pause");
		system("cls");
}


/**
 * La procedura permette di modificare i dati riguardanti un utente gia' inserito,
 * esegue dei controlli sui dati inseriti e ne verifica la validita'.
 *
 * @param gamers e' l'array contenente i dati dei giocatori
 * @param contUs e' il contatore del numero dei giocatori
 */
void modUser(gamer gamers[], int contUs){
	   char nick[25];
	   char email[25];
	   char sex;
	   int i;
	   int match;
	   int error;
	   int find = 0;

	    	system("cls");																//Pulisco lo schermo
	   	   	SetColor(18);
	   	    puts("MODIFICA DEI DATI DI UN GIOCATORE\n");
	   	    SetColor(11);
			puts("Inserisci il nickname dell'utente di cui vuoi modificarne i dati: \n");
			SetColor(15);
			fflush(stdin);													//Svuoto il buffer di input
			scanf("%s", nick);												//Acquisisco il nickname per la modifica

	   for(i=0; i<contUs; i++){
		   match = strcmp(nick, gamers[i].nickname);						//Controllo il nickname inserito per verificare l'esistenza di un giocatore
		   	if(match == 0 && find == 0){									//Procedo alla modifica dei dati se esiste il giocatore
		   		system("cls");												//Pulisco lo schermo
		   		SetColor(10);
		   		printf("\nModifica dei dati dell'utente con nickname %s \t\n\n", nick);
		   		SetColor(15);
		   		do{
		   			 error = 0;												//Imposto gli errori a 0
		   			 SetColor(11);
		   			 puts("Inserisci l'email corretta dell'utente: \n");
		   			 SetColor(15);
		   			 fflush(stdin);											//Svuoto il buffer di input
		   			 scanf("%s", email);									//Acquisisco l'email

		   			 if(verEmail(email)){									//Controllo che l'e-mail inserita sia valida
		   				SetColor(12);
		   				puts("Email non valida \n");
		   				SetColor(15);
		   			 	error = 1;											//Se l'e-mail inserita non e' valida, imposto gli errori a 1
		   			 }

		   			 if(!error && !(-1 == searchMail(gamers, contUs, email))){	//Controllo errori sull'inserimento dell'email valida e sulla presenza nel database
		   				SetColor(12);
		   				puts("Email gia presente \n");
		   				SetColor(15);
		   				error = 1;												//Se l'e-mail inserita esiste gia', imposto gli errori a 1
		   			 }
		   		}
		   		while(error);													//Ripeto finche' riscontro errori

		   		strcpy(gamers[i].email, email);							//Copio l'email inserita nella struct del giocatore
		   		SetColor(11);
		   		puts("\nInserisci il cognome corretto dell'utente:\n");
		   		SetColor(15);
		   		fflush(stdin);											//Svuoto il buffer di input
		   		gets(gamers[i].surname);								//Acquisisco il cognome del giocatore
		   		SetColor(11);
		   		puts("\nInserisci il nome corretto dell'utente\n");
		   		SetColor(15);
		   		fflush(stdin);											//Svuoto il buffer di input
		   		gets(gamers[i].name);									//Acquisisco il nome del giocatore

		   		do{
		   			SetColor(11);
		   			puts("\nInserisci il sesso dell'utente, m o f:\n");
		   			SetColor(15);
		   			fflush(stdin);										//Svuoto il buffer di input
		   			sex = getchar();									//Acquisisco carattere per il sesso
		   			if(getchar() != '\n'){								//Controllo che il secondo carattere sia l'invio, altrimenti errore inserimento
		   				sex = '\0';
		   			}
		   		}
		   		while(!((sex== 'f') || (sex== 'm')));					//Ripeto finche' non si inseriscono i caratteri 'm' o 'f'
		   		gamers[i].gender=sex;									//Copio il sesso inserito nella struct del giocatore
		   		find = 1;												//Imposto il flag dell'elemento trovato a 1 per accertarmi che la modifica sia stata fatta
		   		system("cls");											//Pulisco lo schermo
		   		SetColor(10);
		   		printf("\nUtente %s modificato correttamente\n\n\n", nick);
		   		SetColor(15);
		   	 }
		}

	   	   	   if(!find){												//Se il nick non è stato trovato stampo messaggio di errore
	   		   system("cls");											//Pulisco lo schermo
	   		   SetColor(12);
	   		   puts("\nNon esiste alcun utente con il nickname inserito!\n\n");
	   		   SetColor(15);
	   	   	   }
	   		system("pause");
	   		system("cls");
}


/**La procedura svolge l'operazione di aggiunta dei crediti verso un giocatore,
 * verifica gli eventuali inserimenti validi e stampa un messaggio di corretto inserimento.
 *
 * @param gamers e' l'array contenente i dati dei giocatori
 * @param contUs e' il contatore del numero dei giocatori
 */
void addCredit(gamer gamers[], int contUs){
	 char nick[25];
	 int i;
	 int match;
	 int valid;
	 int find = 0;
	 float newcredit = 0;

	 	   system("cls");															//Pulisco lo schermo
	 	   SetColor(18);
	 	   puts("AGGIUNTA DEL CREDITO AD UN GIOCATORE\n");
	 	   SetColor(11);
		   puts("Inserisci il nickname su cui vuoi aggiungere del credito: \n");
		   SetColor(15);
		   fflush(stdin);															//Svuoto il buffer di input
		   scanf("%s", nick);														//Acquisisco il nickname per la modifica dei crediti


	   for(i=0; i<contUs; i++){
	   		   match = strcmp(nick, gamers[i].nickname);						//Controllo il nickname inserito per verificare l'esistenza di un giocatore
	   		   			if(match == 0 && find == 0){							//Procedo alla modifica dei crediti se esiste il giocatore
	   		   				system("cls");										//Pulisco lo schermo
	   		   				do{
	   		   					system("cls");
	   		   					SetColor(10);
	   		   					printf("\nInserisci il credito da aggiungere per l'utente %s:\n\n", gamers[i].nickname);
	   		   					SetColor(15);
	   		   					fflush(stdin);									//Svuoto il buffer di input
	   		   					valid=scanf("%f", &newcredit);		//Controllo inserimento, valid = 1 INSERIMENTO CORRETTO, valid = 0 INSERIMENTO ERRATO
	   		   				} while(valid != 1);

	   		   					gamers[i].credit = gamers[i].credit + newcredit;	//Aggiorno il credito del giocatore
	   		   					find = 1;					//Imposto il flag dell'elemento trovato a 1 per accertarmi che la modifica sia stata fatta

	   		   				system("cls");					//Pulisco lo schermo
	   		   				SetColor(10);
	   		   				puts("\nCredito aggiunto correttamente!\n\n");
	   		   				SetColor(15);
	   		   			}
	   	}
	   	  if(!find){													//Se il nick non è stato trovato stampo messaggio di errore
	   	   	  system("cls");											//Pulisco lo schermo
	   	   	  SetColor(12);
	   	   	  puts("\nNon esiste alcun utente con il nickname inserito!\n\n");
	   	   	  SetColor(15);
	   	  }
			system("pause");
			system("cls");
}


/**
 * La procedura svolge l'operazione di aggiunta delle ore di gioco verso un giocatore,
 * le ore di gioco sono sotto forma di numero intero, e hanno implicitamente la correlazione
 * con altri dati del giocatore quali il livello ed il credito, infatti si utilizza la funzione x^2
 * per stabilire ogni quante ore bisogna aumentare il livello del giocatore e si aggiungono dei crediti
 * dal valore di 0.05 euro per ogni ora che il giocatore trascorre sulla piattaforma.
 *
 * @param gamers e' l'array contenente i dati dei giocatori
 * @param contUs e' il contatore del numero dei giocatori
 */
void addHours(gamer gamers[], int contUs){
	char nick[25];
	int pos;
	int valid;
	int find = 0;
	int newhours = 0;

		system("cls");										//Pulisco lo schermo
		SetColor(18);
		puts("AGGIUNTA DELLE ORE DI GIOCO AD UN GIOCATORE\n");
		SetColor(11);
	   	puts("Inserisci il nickname su cui vuoi aggiungere ore di gioco: \n");
	   	SetColor(15);
	   	fflush(stdin);										//Svuoto il buffer di input
	   	scanf("%s", nick);									//Acquisisco il nickname per l'aggiunta delle ore al giocatore

	   	   pos = searchUser(gamers, contUs, nick);			//Memorizzo la posizione dell'utente in questione

	   	      if((pos != -1) && (find == 0)){				//Procedo alla modifica delle ore se esiste il giocatore
	   	   		  system("cls");							//Pulisco lo schermo
	   	   		  do{
	   	   			  system("cls");
	   	   			  SetColor(10);
	   	   			  printf("\nInserisci le ore da aggiungere all'utente %s:\n\n", gamers[pos].nickname);
	   	   			  SetColor(15);
	   	   			  fflush(stdin);						//Svuoto il buffer di input
	   	   		   	  valid=scanf("%d", &newhours);			//Controllo inserimento, valid = 1 INSERIMENTO CORRETTO, valid = 0 INSERIMENTO ERRATO
	   	   		  } while (valid != 1);						//Ripeto finche' il numero inserito è valido

	   	   		   		gamers[pos].played = gamers[pos].played + newhours;		//Aggiorno le ore del giocatore

	   	   		   		system("cls");											//Pulisco lo schermo
	   	   		   		SetColor(10);
	   	   		   		puts("\nOre aggiunte correttamente!\n\n");
	   	   		   		SetColor(15);

	   	   		   		gamers[pos].level = levelCheck(gamers[pos].played, gamers[pos].level);	//Aggiorno il livello se possibile, altrimenti rimane invariato

	   	   		   		for(int i=0; i<newhours; i++){
	   	   		   			gamers[pos].credit = gamers[pos].credit + 0.05;				//Aggiorno il credito del giocatore in base alle ore inserite
	   	   		   		}
	   	   		   }

	   	   		  if(pos == -1){										//Se il nick non è stato trovato stampo messaggio di errore
	   	   			  system("cls");									//Pulisco lo schermo
	   	   			  SetColor(12);
	   	   			  puts("\nNon esiste alcun utente con il nickname inserito!\n\n");
	   	   			  SetColor(15);
	   	   		  }
	   			system("pause");
	   			system("cls");
}


/**
 * La funzione svolge il compito di controllare se un giocatore e' presente o no nel database.
 *
 * @param gamers e' l'array contenente i dati dei giocatori
 * @param contUs e' il contatore del numero dei giocatori
 * @param nickname e' il parametro che passo che equivale al nickname per effettuare la verifica, un array di caratteri
 * @return i = la posizione del giocatore nel database se esiste, -1 altrimenti se non esiste nessun giocatore con quel nickname
 */
int searchUser(gamer gamers[], int contUs, char* nickname){
	int i, match;

	for(i=0; i<contUs; i++){
		match = strcmp(nickname, gamers[i].nickname);		//Se match = 0 corrispondenza trovata, match != 0 giocatore non trovato
		if(match == 0){
			return i;										//Ritorno la posizione del giocatore trovato
		}
	}
	return -1;												//Ritorno un valore di errore
}


/**
 * La procedura svolge il compito di aggiunta di un gioco verso un giocatore,
 * effettua dei controlli sugli inserimenti e offre la possibilita' di visionare la lista
 * dei giochi attualmente presenti nello store. La procedura si interfaccia con la funzione 'buyGame' per
 * gestire la possibilita' di aggiunta del videogioco in base al prezzo del videogioco e ai crediti del giocatore,
 * se non e' possibile aggiungere il gioco verra' mostrato un messaggio di errore.
 *
 * @param gamers e' l'array contenente i dati dei giocatori
 * @param store e' l'array contenente i videogiochi
 * @param relat e' l'array contenente i possessi dei videogiochi da parte dei giocatori
 * @param relat_len e' una variabile che memorizza quante relazioni <videogioco-giocatore> ci sono
 * @param contUs e' il contatore del numero dei giocatori
 * @param contGa e' il contatore del numero dei videogiochi
 */
void addGame(gamer gamers[], game store[], owned relat[], int *relat_len, int contUs, int contGa){
	char nick[25];
	char codeGa[25];
	char list[5];
	int posU, posG;
	int error_a = 0;
	int error_b = 0;
	float priceG;

	strcpy(list, "list");											//Copio nell'array di caratteri, la stringa <list>

		while(!error_a){
			system("cls");																//Pulisco lo schermo
		    SetColor(18);
		    puts("AGGIUNTA DI UN VIDEOGIOCO AD UN GIOCATORE\n");
		    SetColor(11);
			puts("Inserisci il nickname valido su cui vuoi aggiungere il gioco: \n");
			SetColor(15);
			fflush(stdin);											//Svuoto il buffer di input
			scanf("%s", nick);										//Acquisisco il nickname per l'aggiunta del videogioco

				if(searchUser(gamers, contUs, nick) != -1){			//Controllo che il nickname esista, ritorna -1 se non esiste, la posizione altrimenti
					error_a = 1;			//Imposto un errore per ciclare l'inserimento del nickname nel caso in cui fosse stato inserito errato
					posU = searchUser(gamers, contUs, nick);		//Memorizzo la posizione del giocatore trovato
			}
		}

		while(!error_b){
																	//Pulisco lo schermo
			SetColor(11);
			puts("\nInserisci il codice del gioco che vuoi aggiungere, se non lo conosci digita < list > per visualizzare la lista: \n");
			SetColor(15);
			fflush(stdin);											//Svuoto il buffer di input
			scanf("%s", codeGa);									//Acquisisco il codice del videogioco

				if((strcmp(codeGa, list)) == 0){					//Controllo se l'utente ha richiesto la visualizzazione della lista dei giochi
					system("cls");									//Pulisco lo schermo
					SetColor(18);
					puts("\t\tLista dei giochi presenti sulla piattaforma:\n");
					SetColor(15);
						for (int i=0; i<contGa; i++){				//Scansiono l'array dei videogiochi
							printGame(store, i);					//Visualizzo la lista del videogioco presente
						}
				}
					if(searchGame(store, contGa, codeGa) != -1){	//Controllo che il gioco esista, ritorna -1 se non esiste, la posizione altrimenti
						error_b = 1;				//Imposto un errore per ciclare l'inserimento del codice del gioco nel caso in cui fosse errato inserimento
						posG = searchGame(store, contGa, codeGa);	//Memorizzo la posizione del videogioco
						priceG = store[posG].price;					//Memorizzo il prezzo del videogioco
					}
		}

		if(buyGame(&gamers[posU], store[posG], relat, relat_len, priceG) == -1){	//Se 'buyGame' = -1 il giocatore ha gia' il videogioco
			SetColor(12);
			printf("\nIl giocatore possiede gia' questo gioco! \n\n\n");
			SetColor(15);
		}else if(buyGame(&gamers[posU], store[posG], relat, relat_len, priceG) == -2){ //Se 'buyGame' = -2 il giocatore non ha crediti per l'acquisto
			system("cls");
			SetColor(12);
			printf("\nIl gioco %s non puo' essere aggiunto perche' il giocatore non ha abbastanza crediti!\n", store[posG].name);
			SetColor(15);
			printf("Il gioco costa %.2f euro\n", priceG);
			printf("Il giocatore possiede %.2f euro\n\n\n", gamers[posU].credit);
		}else{																		//Visualizzo messaggio corretto inserimento del videogioco
			SetColor(10);
			printf("\nIl gioco e' stato aggiunto!\n\n\n");
			SetColor(15);
		}
		system("pause");
		system("cls");
}


/**
 * La funzione svolge il compito di controllare se un determinato giocatore ha la possibilita'
 * di acquistare un videogioco dallo store, effettua dei controlli sul prezzo del gioco
 * e sui crediti posseduti dal giocatore e se e' possibile effettuare l'acquisto aggiunge
 * all'array delle relazioni la coppia <videogioco-giocatore>, altrimenti ritorna valori di errore.
 *
 * @param pplayer e' il puntatore al giocatore a cui si desidera aggiungere il videogioco
 * @param app e' il gioco che abbiamo preso in questione
 * @param relat e' l'array contenente i possessi dei videogiochi da parte dei giocatori
 * @param relat_len e' una variabile che memorizza quante relazioni <videogioco-giocatore> ci sono
 * @param priceG e' una variabile che contiene il prezzo del videogioco in questione
 * @return -1 se il giocatore possiede gia' questo videogioco, -2 se il giocatore non ha abbastanza crediti, 0 se l'acquisto e' andato a buon fine
 */
int buyGame(gamer* pplayer, game app, owned relat[], int* relat_len, float priceG){
	owned new;										//Creo una struttura temporanea per il confronto
	int i;

	strcpy(new.iduser, pplayer->nickname);			//Copio il nickname del giocatore nella nuova struttura temporanea
	strcpy(new.idgame, app.code);					//Copio il codice del gioco nella nuova struttura temporanea

	for(i=0; i<*(relat_len); i++){
			if( !( (strcmp(relat[i].iduser, new.iduser)) || (strcmp(relat[i].idgame, new.idgame)) ) ){	//Controllo che il giocatore non possieda gia' il gioco
				return -1;					//Ritorno -1 se è verificata la condizione, vado avanti altrimenti
			}
	}
		if(pplayer->credit < priceG){		//Controllo che il giocatore abbia i crediti necessari per l'acquisto del gioco
			return -2;						//Ritorno -2 se è verificata la condizione, vado avanti altrimenti
		}

	relat[*relat_len] = new;				//Aggiungo la struttura 'new' all'array 'relat' che possiede le relazioni
	pplayer->credit = pplayer->credit - priceG;		//Sottraggo il credito dell'utente in base al prezzo del gioco acquistato
	*relat_len = *relat_len + 1;					//Incremento il puntatore che mi indica il numero delle relazioni
	return 0;										//Ritorno 0 se l'operazione e' andata a buon fine
}
