
/* ================================= */
/* PROTOCOLE DE TRANSMISSION TEXTE   */
/* ================================= */

// Envoi de coordonnées
#define UART_KEY_X "x=%d"
#define UART_KEY_Y "y=%d"
#define UART_KEY_ALPHA "alpha=%d"
#define UART_KEY_DELTA "delta=%d"
#define UART_KEY_THETA "theta=%d"

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


//*************** Fonctions d'envoi

// Utilitaires : (ré)Initialisation du buffer, etc
void uart_trame_builder_init();
char* uart_trame_builder_get_string();

// Envoi de coordonnées
void uart_trame_builder_append_coordonnees(int x, int y);
void uart_trame_builder_append_alphadelta(int alpha, int delta);
void uart_trame_builder_append_theta(int theta);

// Gestion des chemins de points
void uart_trame_builder_append_nouveau_point_dans_chemin();
void uart_trame_builder_append_execute_le_chemin();

// Déplacements classiques
void uart_trame_builder_append_mouvement_xy_absolu();
void uart_trame_builder_append_mouvement_xy_relatif();

// Tour sur soi-même, par exemple
void uart_trame_builder_append_mouvement_alphadelta();
void uart_trame_builder_append_mouvement_alpha();
void uart_trame_builder_append_mouvement_delta();
void uart_trame_builder_append_mouvement_theta();

// Modes de déplacement
void uart_trame_builder_append_mode_tendu();
void uart_trame_builder_append_mode_courbe();
void uart_trame_builder_append_stop_normal();
void uart_trame_builder_append_stop_urgence();


// "Feedback" de l'asser à la stratégie
void uart_trame_builder_append_position_atteinte();


//*************** API de réception :
/* Les fonctions sont déclarées ici MAIS à implémenter en tant que callbacks
 * dans chaque projet.
 * On peut bien sûr implémenter des fonctions vides, si on ne veut pas
 * gérer certains messages ! ;)

 (Quoi, moi, influencé par le java ? Noooooooon…)
 */

// Réception de coordonnées
void uart_received_coordonnees(int x, int y);
void uart_received_alphadelta(int alpha, int delta);
void uart_received_theta(int theta);

// Gestion des chemins de points
void uart_received_nouveau_point_dans_chemin();
void uart_received_execute_le_chemin();

// Déplacements classiques
void uart_received_mouvement_xy_absolu();
void uart_received_mouvement_xy_relatif();

// Tour sur soi-même, par exemple
void uart_received_mouvement_alphadelta();
void uart_received_mouvement_alpha();
void uart_received_mouvement_delta();
void uart_received_mouvement_theta();

// Modes de déplacement
void uart_received_mode_tendu();
void uart_received_mode_courbe();
void uart_received_stop_normal();
void uart_received_stop_urgence();


// "Feedback" de l'asser à la stratégie
void uart_received_position_atteinte();

