/**
 * @file users.h
 *
 * La libreria dispone di alcune funzioni per l'aggiunta di giocatori ad un database,
 * la modifica dei loro dati e altre funzioni per manipolare dei dati.
 *
 * @author Maio Walter
 *
 * @warning Un uso improprio della libreria potrebbe far crashare il programma.
 */

#ifndef USERS_H_
#define USERS_H_


/**
 * Il tipo e' atto a contenere i dati relativi al giocatore che fara' parte della piattaforma.
 */
typedef struct{
		///Conterra' il nickname del giocatore
		char nickname[25];
		///Conterra' l'e-mail del giocatore
		char email[25];
		///Conterra' il cognome del giocatore
		char surname[20];
		///Conterra' il nome del giocatore
		char name[20];
		///Conterra' il sesso del giocatore
		char gender;
		///Conterra' le ore giocate dal giocatore
		int played;
		///Conterra' il livello del giocatore
		int level;
		///Conterra' il credito accumulato del giocatore
		float credit;
} gamer;


/**
 * Il tipo e' atto a contenere i dati di un videogioco che fara' parte della piattaforma.
 */
typedef struct{
		///Conterra' il codice del videogioco
		char code[25];
		///Conterra' il titolo del videogioco
		char name[35];
		///Conterra' il nome della casa produttrice del videogioco
		char production[50];
		///Conterra' la categoria del videogioco
		char category[25];
		///Conterra' il prezzo del videogioco
		float price;
		///Conterra' l'eta' minima per giocare al videogioco
		int agemin;
} game;


/**
 * Il tipo e' atto a contenere una relazione tra un videogioco ed un giocatore.
 */
typedef struct{
	///Conterra' il nome del giocatore di cui esiste una relazione
	char iduser[25];
	///Conterra' il nome del videogioco di cui esiste una relazione
	char idgame[35];
} owned;


/**
 * La procedura aggiunge un giocatore al database.
 *
 * @param[in] gamers e' l'array contenente i dati dei giocatori
 * @param[in] pcontUs e' il contatore del numero dei giocatori
 */
void newUser(gamer gamers[] , int* contUs);


/**
 * La procedura modifica i dati di un giocatore.
 *
 * @param[in] gamers e' l'array contenente i dati dei giocatori
 * @param[in] contUs e' il contatore del numero dei giocatori
 */
void modUser(gamer gamers[], int contUs);


/**La procedura aggiunge credito ad un giocatore.
 *
 * @param[in] gamers e' l'array contenente i dati dei giocatori
 * @param[in] contUs e' il contatore del numero dei giocatori
 */
void addCredit(gamer gamers[], int contUs);


/**
 * La procedura aggiunge ore di gioco ad un giocatore.
 *
 * @param[in] gamers e' l'array contenente i dati dei giocatori
 * @param[in] contUs e' il contatore del numero dei giocatori
 */
void addHours(gamer gamers[], int contUs);


/**
 * La funzione controlla se un giocatore e' presente o no.
 *
 * @param[in] gamers e' l'array contenente i dati dei giocatori
 * @param[in] contUs e' il contatore del numero dei giocatori
 * @param[in] nickname e' il parametro che passo che equivale al nickname per effettuare la verifica, un array di caratteri
 * @return i = la posizione del giocatore nel database se esiste, -1 altrimenti se non esiste il giocatore
 */
int searchUser(gamer gamers[], int contUs, char* nickname);


/**
 * La procedura aggiunge un videogioco ad un giocatore.
 *
 * @param[in] gamers e' l'array contenente i dati dei giocatori
 * @param[in] store e' l'array contenente i videogiochi
 * @param[in] relat e' l'array contenente i possessi dei videogiochi da parte dei giocatori
 * @param[in] relat_len e' una variabile che memorizza quante relazioni <videogioco-giocatore> ci sono
 * @param[in] contUs e' il contatore del numero dei giocatori
 * @param[in] contGa e' il contatore del numero dei videogiochi
 */
void addGame(gamer gamers[], game store[], owned relat[], int* relat_len, int contUs, int contGa);


/**
 * La funzione controlla se e' possibile aggiungere un videogioco al giocatore o no.
 *
 * @param[in] pplayer e' il puntatore al giocatore a cui si desidera aggiungere il videogioco
 * @param[in] app e' il gioco che abbiamo preso in questione
 * @param[in] relat e' l'array contenente i possessi dei videogiochi da parte dei giocatori
 * @param[in] relat_len e' una variabile che memorizza quante relazioni <videogioco-giocatore> ci sono
 * @param[in] priceG e' una variabile che contiene il prezzo del videogioco in questione
 * @return -1 se il giocatore possiede gia' questo videogioco, -2 se il giocatore non ha abbastanza crediti, 0 se l'acquisto e' andato a buon fine
 */
int buyGame(gamer* pplayer, game app, owned relat[], int* relat_len, float priceG);


#endif /* USERS_H_ */
