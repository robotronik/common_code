#ifndef PROTOCOLE_UART_H
#define PROTOCOLE_UART_H

/* ================================= */
/* PROTOCOLE DE TRANSMISSION TEXTE   */
/* ================================= */

// Envoi de coordonnées
#define UART_KEY_X "x="
#define UART_KEY_Y "y="
#define UART_KEY_ALPHA "alpha="
#define UART_KEY_DELTA "delta="
#define UART_KEY_THETA "theta="

// Gestion des chemins de points
#define UART_KEY_POINT_DANS_CHEMIN  "POINT_DANS_CHEMIN"
#define UART_KEY_EXECUTE_LE_CHEMIN  "EXECUTE_LE_CHEMIN"

// Déplacements classiques
#define UART_KEY_MV_XY_ABSOLU   "MV_XY_ABSOLU"
#define UART_KEY_MV_XY_RELATIF  "MV_XY_RELATIF"

// Tour sur soi-même, par exemple
#define UART_KEY_MV_ALPHADELTA  "MV_ALPHADELTA"
#define UART_KEY_MV_ALPHA       "MV_ALPHA"
#define UART_KEY_MV_DELTA       "MV_DELTA"
#define UART_KEY_MV_THETA       "MV_THETA"

// Modes de déplacement
#define UART_KEY_MODE_TENDU     "MODE_TENDU"
#define UART_KEY_MODE_COURBE    "MODE_COURBE"

#define UART_KEY_STOP_NORMAL    "STOP_NORMAL"
#define UART_KEY_STOP_URGENCE   "STOP_URGENCE"

#define UART_KEY_CALIBRATION    "CALIBRATION"
#define UART_KEY_WERE_ARE_YOU   "WERE_ARE_YOU"
#define UART_KEY_I_AM_HERE      "I_AM_HERE"
#define UART_KEY_FINISHED_I_AM_BORED "FINISHED_I_AM_BORED"

#endif //PROTOCOLE_UART_H
