#ifndef TEXT_EMISSION_H
#define TEXT_EMISSION_H

/**
 * Cette fonction envoie du texte. Sur micro-controleur, elle utilise l'uart,
 * sur pc printf.
 *
 * Elle doit être implémenté dans les fichiers `hardware` des architectures
 * respectives.
 *
 * L'interface est exactement la même que celle de printf.
 */
void send_text(const char *format, ...);


#endif /* TEXT_EMISSION_H */
