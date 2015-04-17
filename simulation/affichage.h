// Convertir les milliradians en degrés pour l'affichage
#define MRAD2DEGRES 0.0572957795131
// Dimensions
// Le facteur de zoom (mm par pixel)
#define ZOOM_FACTOR 5

#define PLATEAU_HEIGHT 2000
#define PLATEAU_WIDTH 3000

#define ROBOT_HEIGHT 250
#define ROBOT_WIDTH  230

#define POINT_SIZE 40
#define PRECISION_CERCLE 8

#define IMAGE_PLATEAU "../common_code/simulation/plateau.png"

// SDL basic functions
int init_sdl_screen();
// To be called very often
int sdl_manage_events();
int quit_sdl_screen();

// Drawing functions
void dessine_fond();

void bouge_robot_sdl(int x, int y, int alpha);

void dessine_obstacle_rond(int cx, int cy, int r);
void dessine_obstacle_ligne(int x1, int y1, int x2, int y2);

void dessine_point_passage_carto(int x, int y, int type);

void dessin_init();
void dessin_post();

void new_xy_absolu(int, int);
