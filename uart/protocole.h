
/* ================================= */
/* PROTOCOLE DE TRANSMISSION TEXTE   */
/* ================================= */

// Envoi de coordonnées
#define UART_KEY_ENVOIE_X "x=%d"
#define UART_KEY_ENVOIE_Y "y=%d"
#define UART_KEY_ENVOIE_ALPHA "alpha=%d"
#define UART_KEY_ENVOIE_DELTA "delta=%d"
#define UART_KEY_ENVOIE_THETA "theta=%d"
void uart_trame_builder_append_envoie_coordonnees(int x, int y);
void uart_trame_builder_append_envoie_alphadelta(int alpha, int delta);
void uart_trame_builder_append_envoie_theta(int theta);

// Envoi d'un point au milieu d'un chemin
#define UART_KEY_POINT_DANS_CHEMIN  "POINT_DANS_CHEMIN"
void uart_trame_builder_append_nouveau_point_dans_chemin();
#define UART_KEY_EXECUTE_LE_CHEMIN  "EXECUTE_LE_CHEMIN"
void uart_trame_builder_append_execute_le_chemin();

// Déplacements classiques
void uart_trame_builder_append_mouvement_xy_absolu();
#define UART_KEY_MV_XY_ABSOLU   "MV_XY_ABSOLU"
#define UART_KEY_MV_XY_RELATIF  "MV_XY_RELATIF"
void uart_trame_builder_append_mouvement_xy_relatif();

// Tour sur soi-même, par exemple
#define UART_KEY_MV_ALPHADELTA  "MV_ALPHADELTA"
void uart_trame_builder_append_mouvement_alphadelta();
#define UART_KEY_MV_ALPHA       "MV_ALPHA"
void uart_trame_builder_append_mouvement_alpha();
#define UART_KEY_MV_DELTA       "MV_DELTA"
void uart_trame_builder_append_mouvement_delta();
#define UART_KEY_MV_THETA       "MV_THETA"
void uart_trame_builder_append_mouvement_theta();

// Modes de déplacement
#define UART_KEY_MODE_TENDU     "MODE_TENDU"
void uart_trame_builder_append_mode_tendu();
#define UART_KEY_MODE_COURBE    "MODE_COURBE"
void uart_trame_builder_append_mode_courbe();

#define UART_KEY_STOP_NORMAL    "STOP_NORMAL"
void uart_trame_builder_append_stop_normal();
#define UART_KEY_STOP_URGENCE   "STOP_URGENCE"
void uart_trame_builder_append_stop_urgence();


//send_position_atteinte

// Utilitaires : (ré)Initialisation du buffer, etc
void uart_trame_builder_init();
char* uart_trame_builder_get_string();

