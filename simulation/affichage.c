#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SOIL/SOIL.h>
#include <math.h>

#include "../debug.h"

#include "../../asservissement/trajectoire.h"

#include "affichage.h"

SDL_Event evenements;
GLuint texturePlateau;

SDL_Rect position_robot;

int init_sdl_screen() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        return quit_sdl_screen(1);

    SDL_WM_SetCaption("SDL : Une simulation du robot !", NULL);

    if (SDL_SetVideoMode(PLATEAU_WIDTH/ZOOM_FACTOR+1, PLATEAU_HEIGHT/ZOOM_FACTOR+1, 32, SDL_OPENGL) == 0)
        return quit_sdl_screen(1);

    // Changer de repère : repère orthogonal avec origine bas-gauche
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, PLATEAU_WIDTH, 0, PLATEAU_HEIGHT);

    // Texture : plateau de jeu
    texturePlateau = SOIL_load_OGL_texture(IMAGE_PLATEAU,
        SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    debug(_VERBOSE_, "SOIL messages : '%s' (%s)\n", SOIL_last_result(), IMAGE_PLATEAU);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, texturePlateau);
    return 0;
}

int sdl_manage_events() {
    SDL_PollEvent(&evenements);
    switch(evenements.type) {
        case SDL_QUIT:
            return 1;
        case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEMOTION: // Clic de la souris
            if (evenements.button.button == SDL_BUTTON_LEFT) {
                debug(_VERBOSE_, "%d %d\n", evenements.button.x*ZOOM_FACTOR, PLATEAU_HEIGHT - evenements.button.y*ZOOM_FACTOR);
                set_trajectoire_xy_absolu(evenements.button.x*ZOOM_FACTOR, PLATEAU_HEIGHT - evenements.button.y*ZOOM_FACTOR);
            }
        default:
            return 0;
    }
}

int quit_sdl_screen(int erreur) {
    if (erreur != 0) {
        debug(_ERROR_, "Erreur lors de la creation de la fenetre : ,%s",SDL_GetError());
    }

    SDL_Quit();
    return -1;
}


void dessin_post() {
    glFlush();
    SDL_GL_SwapBuffers(); // Mise à jour de l'écran
}

void dessine_fond() {
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        glColor3ub(255,255,255);
        glTexCoord2d (0, 0); glVertex2d(0,              0);
        glTexCoord2d (0, 1); glVertex2d(0,              PLATEAU_HEIGHT);
        glTexCoord2d (1, 1); glVertex2d(PLATEAU_WIDTH,  PLATEAU_HEIGHT);
        glTexCoord2d (1, 0); glVertex2d(PLATEAU_WIDTH,  0);
    glEnd();
}

void dessine_robot() {
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        glColor3ub(0,0,255);
        glVertex2d(-ROBOT_WIDTH/2, -ROBOT_HEIGHT/2);
        glVertex2d(-ROBOT_WIDTH/2, +ROBOT_HEIGHT/2);
        glVertex2d(+ROBOT_WIDTH/2, +ROBOT_HEIGHT/2);
        glVertex2d(+ROBOT_WIDTH/2, -ROBOT_HEIGHT/2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glColor3ub(0,0,255);
        glVertex2d(-ROBOT_WIDTH/2, -ROBOT_HEIGHT/2);
        glVertex2d(+ROBOT_WIDTH/2, -ROBOT_HEIGHT/2);
        glColor3ub(255,0,200);
        glVertex2d(0, ROBOT_HEIGHT/2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glColor3ub(0,0,255);
        glVertex2d(-ROBOT_WIDTH/2, -ROBOT_HEIGHT/2);
        glVertex2d(+ROBOT_WIDTH/2, -ROBOT_HEIGHT/2);
        //glColor3ub(0,0,0);
        glVertex2d(0, 0);
    glEnd();
}

void bouge_robot_sdl(int x, int y, int alpha) {
    float alpha_deg = alpha * MRAD2DEGRES;
    debug(_VERBOSE_, "x = %d, y = %d, alpha = %f\n", x, y, alpha_deg);
    // Remplissage de la surface avec du noir
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    dessine_fond();
    glTranslated(x, y, 0);
    glRotatef(alpha_deg, 0, 0, 1);
    dessine_robot();
    dessin_post();
}

void dessine_obstacle_rond(int cx, int cy, int r){
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    float theta = 2 * 3.1415926 / (float)(PRECISION_CERCLE);
    float c = cosf(theta);//precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = r;//we start at angle = 0
    float y = 0;

    glBegin(GL_LINE_LOOP);
    int ii;
    for( ii = 0; ii < PRECISION_CERCLE; ii++) {
        glVertex2f(x + cx, y + cy);//output vertex

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
    dessin_post();
}
void dessine_obstacle_ligne(int x1, int y1,int x2, int y2) {
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    glColor3ub(255,0,0);

    glDisable(GL_TEXTURE_2D);
    glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
    glEnd();
    dessin_post();
}

void dessine_point_passage_carto(int x, int y, int type) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(x, y, 0);

    switch (type) {
        case 0: // Point ouvert
            glColor3ub(0,128,128);
            break;
        case 1: // Point visité
            glColor3ub(0,255,255);
            break;
        case 2: // Point de passage réel
            glColor3ub(255,0,0);
            break;
        case 3: // Point borne
            glColor3ub(0,255,0);
            break;
        default:
            glColor3ub(0,0,0);
    }


    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        glVertex2d(-POINT_SIZE/2, -POINT_SIZE/2);
        glVertex2d(-POINT_SIZE/2, +POINT_SIZE/2);
        glVertex2d(+POINT_SIZE/2, +POINT_SIZE/2);
        glVertex2d(+POINT_SIZE/2, -POINT_SIZE/2);
    glEnd();
    dessin_post();
}

