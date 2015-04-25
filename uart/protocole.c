
char* temp_string;
char* to_send_string;

void uart_build_trame_new_xy_absolu(int x, int y) {
    asprintf(temp_string, "x=%d\ny=%d\n", x, y);
    asprintf(to_send_string, "%s\n%s\n",
             temp_string,
             UART_KEYWORD_NEW_XY_ABSOLU);
}
void uart_build_trame_new_xy_relatif(int x, int y) {
    asprintf(temp_string, "x=%d\ny=%d\n", x, y);
    asprintf(to_send_string, "%s\n%s\n",
             temp_string,
             UART_KEYWORD_NEW_XY_RELATIF);
}

void uart_build_trame_new_alpha_delta(int alpha, int delta) {
    asprintf(temp_string, "x=%d\ny=%d\n", x, y);
    asprintf(to_send_string, "%s\n%s\n", temp_string, UART_KEYWORD_NEW_XY_ABSOLU);
}
void uart_build__trame_new_xy_absolu(int x, int y) {
    asprintf(temp_string, "x=%d\ny=%d\n", x, y);
    asprintf(to_send_string, "%s\n%s\n", temp_string, UART_KEYWORD_NEW_XY_ABSOLU);
}
void uart_build_trame_new_xy_absolu(int x, int y) {
    asprintf(temp_string, "x=%d\ny=%d\n", x, y);
    asprintf(to_send_string, "%s\n%s\n", temp_string, UART_KEYWORD_NEW_XY_ABSOLU);
}
void uart_build_trame_new_xy_absolu(int x, int y) {
    asprintf(temp_string, "x=%d\ny=%d\n", x, y);
    asprintf(to_send_string, "%s\n%s\n", temp_string, UART_KEYWORD_NEW_XY_ABSOLU);
}





//appelées de l'extérieur uniquement pour les tests unitaires
void new_alpha_delta(int alpha, int delta);
void new_xy_relatif(int x, int y);
void new_xy_absolu(int x, int y);
void set_mode_tendu();
void set_mode_courbe();
void new_theta(int theta);
void new_chemin();