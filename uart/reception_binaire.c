#include "string.h"
#include "stdbool.h"
#include "stdio.h"

#include "../common.h"

#include "reception_binaire.h"
#include "uart_hardware.h"

struct g_communication_t g_communication;

void lire_uart()
{
    // code de correction d'erreur de la trame en cours
    static int8_t crc;
    // Vrai si le caractère courant est à échaper
    static bool escape_char = false;

    debug(1, "STATE : %d\n", g_communication.state);

    // Contient le dernier caractère reçu.
    // L'écriture dans le buffer g_communication.data est différé, car le crc
    // ne doit pas être inclus dans g_communication.data, et le seul moyen de
    // savoir que l'on est dans en train de recevoir le crc est de connaitre le
    // caractère suivant (le \0).
    static uint8_t last_char;

    // lecture des données en provenance de l'uart
    uint8_t uart_buff = get_uart();
    debug(1, "data : ");
    debug_byte(uart_buff);

    switch (g_communication.state) {
        case PRET:

            debug(1, "RECEPTION (debut)\n");

            // initialisation
            g_communication.used_size = 0;
            crc = 0;
            escape_char = false;

        // Le cas PRET continue dans EN_RECEPTION (pas de break volontairement)
        case EN_RECEPTION:

            // fin de trame
            if (uart_buff=='\0' && !escape_char) {
                debug(1, "FIN DE TRAME\n");
                // À ce stade, si la reception s'est bien passé, alors on viens
                // de recevoir le crc
                if (crc == 0) {
                    g_communication.state = RECU;
                } else {
                    debug(1, "CRC ERREUR\n");
                    debug_byte(crc);
                    debug_byte(uart_buff);
                    debug_byte(last_char);
                    debug(1, "\n");
                    g_communication.state = ERREUR;
                }
                break;
            }

            // On s'assure que la trame n'est pas trop grande
            if (g_communication.used_size >= g_communication.data_size) {
                debug(1, "ERREUR : trame trop grande\n");
                debug(1, "%d au lieu de %d\n", g_communication.used_size,
                        g_communication.data_size);
                g_communication.state = ERREUR;
                break;
            }

            // gestion du crc
            crc ^= uart_buff;

            // caractère d'échapement
            if (uart_buff == '\\' && !escape_char) {
                debug(1, "CARACTÈRE ÉCHAPÉ\n");
                escape_char = true;
                break;
            }

            // c'est pas très beau, mais je n'ai pas trouvé le moyen de faire mieux
            if (g_communication.state == PRET) {
                g_communication.state = EN_RECEPTION;
            } else {
                // On écrit le caractère précédant dans le buffer
                g_communication.data[g_communication.used_size] = last_char;
                g_communication.used_size++;
            }

            last_char = uart_buff;
            escape_char = false;
            break;

        case ERREUR:
        case RECU:
        default:
            // On ignore les données tant que le système n'est pas pret à les recevoir
            debug(1, "ERREUR : %d\n", g_communication.state);
            break;
    }

    debug(1, "STATE FIN : %d\n", g_communication.state);
}

