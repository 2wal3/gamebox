/**
 * @file utility.h
 *
 * La libreria dispone di alcune funzioni utili alla manipolazione dei dati di giocatori, videogiochi e file,
 * come modifiche sui dati, ricerche, ordinamenti, stampe su file.
 *
 * @author Maio Walter
 *
 * @warning Un uso improprio della libreria potrebbe far crashare il programma.
 */


#ifndef UTILITY_H_
#define UTILITY_H_

/**
 * Definisco una costante MAX con un valore intero 100
 */
#define MAX 100

/**
 * Definisco il file dei giocatori.
 */
#define FILEUSERS "users.csv"

/**
 * Definisco il file dei videogiochi.
 */
#define FILEGAMES "store.csv"

/**
 * Definisco il file delle relazioni.
 */
#define FILERELAT "relat.csv"

/**
 * Definisco il file della lista dei giochi di un giocatore.
 */
#define FILEGAMELIST "games.csv"


/**
 * La funzione svolge il compito di controllare se un'e-mail e' presente o no nel database
 *
 * @param[in] gamers e' l'array contenente i dati dei giocatori
 * @param[in] contUs e' il contatore del numero dei giocatori
 * @param[in] email e' il parametro che passo per effettuare la verifica, un array di caratteri
 * @return i = la posizione dell'e-mail del giocatore nel database se esiste, -1 altrimenti se non esiste nessun giocatore con quell'e-mail
 */
int searchMail(gamer gamers[], int contUs, char* email);

/**
 * La funzione controlla che l'e-mail inserita sia valida o no
 *
 * @param[in] email che passo per verificare la validita'
 * @return res = 0 se valida, res != 0 altrimenti
 */
int verEmail(char* email);

/**
 * La funzione calcola il possibile incremento del livello
 *
 * @param[in] played e' la variabile che contiene le ore di gioco che si stanno aumentando
 * @param[in] levelOld e' il livello che passo alla funzione al momento della verifica dell'incremento
 * @return levelOld livello incrementato oppure stesso livello di partenza
 */
int levelCheck(int played, int levelOld);

/**
 * La procedura opera un ordinamento decrescente in base al livello dei giocatori
 *
 * @param[in] gamers e' l'array contenente i dati dei giocatori
 * @param[in] contUs e' il contatore del numero dei giocatori
 */
void ordLevel(gamer gamers[], int contUs);

/**
 * La procedura visualizza la lista dei videogiochi posseduti da un giocatore
 *
 * @param[in] gamers e' l'array contenente i dati dei giocatori
 * @param[in] store e' l'array contenente i dati dei videogiochi
 * @param[in] relat e' l'array contenente i possessi dei videogiochi da parte dei giocatori
 * @param[in] relat_len e' una variabile che memorizza quante relazioni <videogioco-giocatore> ci sono
 * @param[in] contUs e' il contatore del numero dei giocatori
 * @param[in] contGa e' il contatore del numero dei videogiochi
 */
void gameListU(gamer gamers[], game store[], owned relat[], int relat_len, int contUs, int contGa);

/**
 * La funzione svolge il compito di controllare se un videogioco e' presente o no nel database
 *
 * @param[in] store e' l'array contenente i dati dei videogiochi
 * @param[in] contGa e' il contatore del numero dei videogiochi
 * @param[in] codeGa  e' il parametro che equivale al codice del gioco che passo per effettuare la verifica, un array di caratteri
 * @return i = la posizione del videogioco nel database se esiste, -1 altrimenti se non esiste nessun videogioco con quel codice
 */
int searchGame(game store[], int contGa, char* codeGa);

/**
 * La procedura si occupa della ricerca di un videogioco nello store
 *
 * @param[in] store e' l'array contenente i dati dei videogiochi
 * @param[in] contGa e' il contatore del numero dei videogiochi
 */
void searchGameStore(game store[], int contGa);

/**
 * La procedura visualizza tutti i dati di un giocatore
 *
 * @param[in] gamers e' l'array contenente i dati dei giocatori
 * @param i e' la posizione del giocatore di cui si vogliono visualizzare i dati
 */
void printUser(gamer gamers[], int i);

/**
 * La procedura visualizza tutti i dati relativi ad un videogioco
 *
 * @param[in] store e' l'array contenente i dati dei videogiochi
 * @param[in] i e' la posizione del videogioco di cui si vogliono visualizzare i dati
 */
void printGame(game store[], int i);

/**
 * La procedura stampa su file tutti i dati dei giocatori
 *
 * @param[in] gamers e' l'array contenente i dati dei giocatori
 * @param[in] contUs e' il contatore del numero dei giocatori
 */
void printFile(gamer gamers[], int contUs);

/**
 * La procedura stampa su file tutte le relazioni <giocatore-videogioco> che sono presenti sul database
 *
 * @param[in] relat e' l'array contenente tutte le relazioni <giocatore-videogioco>
 * @param[in] relat_len e' la dimensione dell'array e quindi il numero delle relazioni presenti
 */
void printFileRelat(owned relat[], int relat_len);

/**
 * La procedura scrive su file la libreria dei videogiochi di un giocatore
 * @param gamers e' l'array contenente i dati dei giocatori
 * @param store e' l'array contenente i dati dei videogiochi
 * @param relat e' l'array contenente tutte le relazioni <giocatore-videogioco>
 * @param relat_len e' la dimensione dell'array e quindi il numero delle relazioni presenti
 * @param contUs e' il contatore del numero dei giocatori
 * @param contGa e' il contatore del numero dei videogiochi
 */
void printFileGamesUser(gamer gamers[], game store[], owned relat[], int relat_len, int contUs, int contGa);

/**
 * La procedura consente di cambiare il colore del testo
 *
 * @param[in] Color e' il parametro che richiede un numero che stabilisce il colore
 */
void SetColor(short);


#endif /* UTILITY_H_ */
