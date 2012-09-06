#include <GL/glut.h>

void display(void) {
    /* Set background color (white) */
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    /* Set drawing color */
    glColor3d(0, 0, 0);
    /* Tell OpenGL your intentions */
    glBegin(GL_POLYGON);
        /* Set the vertices */
        glVertex2d(-0.5, 0.5);
        glVertex2d(0.5, 0.5);
        glVertex2d(0.5, -0.5);
        glVertex2d(-0.5, -0.5);
        glVertex2d(0.0, 1.0);
    /* Done making polygon */
    glEnd();
    /* Clear screen and draw */
    glutSwapBuffers();
}

void keyfunc(unsigned char key, int xscr, int yscr)
{
    if(key == 'q')
        exit(0);
}

int main(int argc, char **argv)
{
    /* Initialize GLUT */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    /* Window Creation */
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(150, 100);
    glutCreateWindow("Black Window");
    /* When the display needs redrawing... */
    glutDisplayFunc(display);
    glutKeyboardFunc(keyfunc);
    /* Continue until user quits */
    glutMainLoop();
    return 0;
}
