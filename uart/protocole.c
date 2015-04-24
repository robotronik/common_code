

char* la_variable_que_l_uart_a_construit;

void uart_new_xy_absolu(int x, int y) {
    asprintf(la_variable_que_l_uart_a_construit, "x=%d\ny=%d\n", x, y);
    asprintf(la_variable_que_l_uart_a_construit, "%s\n%s\n", la_variable_que_l_uart_a_construit, UART_KEYWORD_NEW_XY_ABSOLU);

}

