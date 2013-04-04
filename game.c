#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.141592

GLfloat density = 0.8; //set the density to 0.3 which is acctually quite thick
GLfloat fogColor[4] = {0.5, 0.5, 0.5, 1.0}; //set the for color to grey
double playerPos[2] = {0.0, 0.0};
double theta = 0.0;
int keyDown[4] = {0, 0, 0, 0};  // W A S D
int WIDTH=500, HEIGHT=500;
int frame = 0;
int oldXscr;

struct shape
{
    double pos[2];
    int sides;
    double radius;
};

void init (void) {
    glEnable (GL_DEPTH_TEST); //enable the depth testing
    glEnable (GL_FOG); //enable the fog
    glFogi (GL_FOG_MODE, GL_EXP2); //set the fog mode to GL_EXP2
    glFogfv (GL_FOG_COLOR, fogColor); //set the fog color to our color chosen above
    glFogf (GL_FOG_DENSITY, density); //set the density to the value above
    glHint (GL_FOG_HINT, GL_NICEST); // set the fog to look the nicest, may slow down on older cards
    glutIgnoreKeyRepeat(1);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(WIDTH/2, HEIGHT/2);
    oldXscr = WIDTH/2;
    theta = 0.0;
}


void display (void) {
    glutWarpPointer(WIDTH/2, HEIGHT/2);
    glClearColor (1.0,1.0,1.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
         glVertex3f(2.0, -1.0, 0);
         glVertex3f(2.0, 1.0, 0);
         glVertex3f(3.0, 0.0, 0);
    glEnd();
    glFlush();
    glutSwapBuffers();
}

void look()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(playerPos[0], playerPos[1], 0.0, playerPos[0] + cos(theta), playerPos[1] + sin(theta), 0.0, 0.0, 0.0, 1.0);
}

void keyupfunc(unsigned char key, int xscr, int yscr)
{
    if(key == 'w')
        keyDown[0] = 0;
    if(key == 's')
        keyDown[1] = 0;
    if(key == 'a')
        keyDown[2] = 0;
    if(key == 'd')
        keyDown[3] = 0;
}

void keyfunc(unsigned char key, int xscr, int yscr)
{
    if(key == 'q')
        exit(0);

    if(key == 'w')
        keyDown[0] = 1;
    if(key == 's')
        keyDown[1] = 1;
    if(key == 'a')
        keyDown[2] = 1;
    if(key == 'd')
        keyDown[3] = 1;
}

void idle(void)
{
    //printf("KEYS:  %d %d %d %d\n", keyDown[0], keyDown[1], keyDown[2], keyDown[3]);
    //printf("THETA: %f\n", theta);
    //printf("POS:   %f %f\n", playerPos[0], playerPos[1]);
    if(theta > 2*PI)
        theta -= 2*PI;
    if(theta < 0)
        theta += 2*PI;
    double speed = 0.01;
    if(keyDown[0] + keyDown[1] + keyDown[2] + keyDown[3] >= 2)
        speed /= sqrt(2);
    if(keyDown[0])
    {
        playerPos[0] += cos(theta)*speed;
        playerPos[1] += sin(theta)*speed;
    }
    if(keyDown[1])
    {
        playerPos[0] -= cos(theta)*speed;
        playerPos[1] -= sin(theta)*speed;
    }
    if(keyDown[2])
    {
        playerPos[0] -= sin(theta)*speed;
        playerPos[1] += cos(theta)*speed;
    }
    if(keyDown[3])
    {
        playerPos[0] += sin(theta)*speed;
        playerPos[1] -= cos(theta)*speed;
    }
    look();
    glutPostRedisplay();
}

void motion(int xscr, int yscr)
{
    int dx = WIDTH * 0.5 - xscr;
    //int dx = oldXscr - xscr;
    theta += dx/100.0;
    //oldXscr = xscr;
}

void reshape (int w, int h) {
    WIDTH = w;
    HEIGHT = h;
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode (GL_MODELVIEW);
    glutWarpPointer(WIDTH/2, HEIGHT/2);
    theta = 0.0;
}

int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize (WIDTH, HEIGHT);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("A basic OpenGL Window");
    init ();
    glutReshapeFunc (reshape);
    glutDisplayFunc (display);
    glutIdleFunc (idle);
    glutKeyboardFunc(keyfunc);
    glutKeyboardUpFunc(keyupfunc);
    glutPassiveMotionFunc(motion);
    glutMainLoop ();
    return 0;
}
