#ifndef EMISSION_H
#define EMISSION_H

// ================================= //
// PROTOCOLE DE TRANSMISSION BINAIRE //
// ================================= //
//
// Voir l'explication dans reception.h

void uart_send_msg(void *msg, int size_msg);

#endif // EMISSION_H
