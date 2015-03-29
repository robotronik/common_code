#include "asservissement.h"

void nouvelle_etape(int x, int y) {
    new_xy_absolu(x,y);
}


void bouge_robot_sdl(int x, int y, int alpha_mrad) {
    dessin_init();

    dessine_fond();
    dessine_robot(x, y, alpha_mrad);

    dessin_post();
    //sdl_manage_events(); // On gère les événements qui sont apparus, au cas où
}
