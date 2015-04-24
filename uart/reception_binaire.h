#ifndef RECEPTION_H
#define RECEPTION_H

#include "inttypes.h"

/* ================================= */
/* PROTOCOLE DE TRANSMISSION BINAIRE */
/* ================================= */

/* STRUCTURE D'UNE TRAME
 *
 * La structure d'une trame est la suivante :
 * les [données], terminée par un '0'
 * le [crc] sur 1 octet
 * un caractère de terminaison nul (0)
 *
 * Remarques :
 *      si les données contiennent un '0', il faut envoyer "\0"
 *      si les données contiennent un '\', il faut envoyer "\\"
 *      NB: cela s'applique également pour le crc
 */

/* BUFFER
 *
 * Le buffer utilisé pour stoqué la trame doit faire
 * [taille du message] + 1 octet qui sera le caractère null
 */

/* CRC
 *
 * Le crc est calculé de la manière suivante :
 * C'est un xor entre [taille] et chacun des octets de [données]
 */

/* EXEMPLE
 *
 * On veut transmettre les données suivantes "ab:cd:ef:0\" (sans les
 * guillemets, et 0 est le caractère nul (pas le chiffre ascii)).
 *
 * La trame transmise sera donc (en hexa) :
 * 61 62 3A 64 65 3A 66 67 3A 5C 00 5C 5C 61 00
 * NB :
 *  61 = 'a'
 *  62 = 'b'
 *  3A = ':'
 *  61 = 'c'
 *  62 = 'd'
 *  3A = ':'
 *  61 = 'e'
 *  62 = 'f'
 *  3A = ':'
 *  5C puis 00 = le caractère nul
 *  5C puis 5C = '\'
 *  61 est le crc ( 'a' ^ 'b' ^ ':' ^ 'c' ^ 'd' ^ ':' ^ 'e' ^ 'f' ^ ':' ^
 *  '\' ^ '0' ^ '\' ^ '\' );
 *  00 est le caractère de fin
 */

/* BUFFER MULTIPLES
 *
 * Comme la structure g_communication ne s'occupe pas de reserver l'espace
 * alloué par le buffer, il donc très simple d'utiliser plusieurs buffer.
 * Exemple :
 *
 * int main(void)
 * {
 *     uint8_t buf1[10], buf2[10];
 *
 *     g_communication.state = PRET;
 *     g_communication.used_size = 0;
 *     g_communication.data_size = 10;
 *
 *     g_communication.data = buf1; // Dans un premier temps on utilise buf1
 *
 *     // initialisation des interruption
 *     uart_interrupt = lire_uart; // pseudo code
 *     interrupt_enable = true;
 *
 *     // On attend de recevoir des données
 *     while(g_communication.state != RECU);
 *
 *     // buf1 est plein, maintenant, on utilise buf2
 *     g_communication.data = buf2;
 *     g_communication.state = PRET;
 *
 *     // On peut faire un travail sur buf1, pendant que buf2 se remplis…
 *
 *     // On attend de recevoir des données
 *     while(g_communication.state != RECU);
 *
 *     // À ce state buf1 et buf2 contiennent les données
 * }
 */

/* RESET
 *
 * À tout moment on peut s'assurer que la réception est bien en attente,
 * il faut envoyer la trame suivante (en hexa)
 * 00 00
 *
 * Cela permet dans tout les cas de s'assurer qu'on à envoyé une fin de trame,
 * dans le cas où le dernier caractère envoyé était '\'
 */

enum transission_state_t {
    ERREUR,         // Trame reçu, contenant des erreurs
    PRET,           // En attente d'une nouvelle trame
    EN_RECEPTION,   // Réception actuellement en cours
    RECU,           // Trame entièrement reçu, sans erreur
};

struct g_communication_t {
    /* État de la transmission courante
     * À initialiser à PRET
     */
    enum transission_state_t state;

    /* taille actuellement réservée dans le buffer data en octet
     * À initialiser à 0
     */
    uint8_t used_size;

    /* taille du buffer data en octet
     * À initialiser correctement :)
     */
    uint8_t data_size;

    /* adresse du buffer contenant les données
     * Doit être initialisé avec une adresse valide
     */
    uint8_t *data;
};

/* Contient les données de la trame en cour de reception
 */
extern struct g_communication_t g_communication;

/** Lit un octet en provenance de l'UART
 */
void lire_uart();

#endif // RECEPTION_H
