#include "cartographie.h"

int x_actuelle = 300;
int y_actuelle = 1000;

void nouvelle_etape(int x, int y) {
    pathfinding_init();
    pathfinding_start(x_actuelle, y_actuelle, x, y);
    x_actuelle = x;
    y_actuelle = y;
}
