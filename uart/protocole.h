
/* ================================= */
/* PROTOCOLE DE TRANSMISSION TEXTE   */
/* ================================= */

#define uart_trame_xy(x,y) asprintf("x=%d\ny=%d\n", x, y)


#define UART_KEYWORD_NEW_XY_ABSOLU "new_xy_absolu"
#define uart_trame_new_xy_absolu(x, y) \
    asprintf("%s\n%s\n", uart_trame_xy(x,y), UART_KEYWORD_NEW_XY_ABSOLU)





#define uart_trame_new_xy_absolu(x, y) \
    "%s\n%s\n", uart_trame_xy(x,y), UART_KEYWORD_NEW_XY_ABSOLU)








//appelées de l'extérieur uniquement pour les tests unitaires
void new_alpha_delta(int alpha, int delta);
void new_xy_relatif(int x, int y);
void new_xy_absolu(int x, int y);
void set_mode_tendu();
void set_mode_courbe();
void new_theta(int theta);
void new_chemin();
