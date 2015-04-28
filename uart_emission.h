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
