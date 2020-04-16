
#include<GL/glew.h>
#include<stdlib.h>
#include<math.h>
#include<vector>
#include "loader.h"

int WINDOW_HEIGHT=800;
int WINDOW_WIDTH=800;
bool ispressed[256]={0};
float xpos=5.0f, ypos=5.0f,zpos=5.0f;
float xrot=0.0f, yrot=0.0f ,zrot=0.0f;
float factor=0.02f;

void keyOperations (void) {
    if (ispressed['a']) xpos-= factor;//translation along x-axis
    if (ispressed['d']) xpos+= factor;
    if (ispressed['w']) ypos-= factor;//translation along y-axis
    if (ispressed['s']) ypos+= factor;
    if (ispressed['e']) zpos-= factor;//translation along z-axis
    if (ispressed['q']) zpos+= factor;
        
    if (ispressed['l']) yrot+= factor;//rotation along y axis
    if (ispressed['j']) yrot-= factor;
    if (ispressed['i']) xrot+= factor;//rotation along x axis
    if (ispressed['k']) xrot-= factor;
    if (ispressed['o']) zrot+= factor;//rotation along z axis
    if (ispressed['u']) zrot-= factor;

    if (ispressed['c']) factor-=0.004f;//reseting the factor
    if (ispressed['v']) factor+=0.004f;

    if (ispressed['x']) exit(0);
}


void render(){
    Loader load("owmoon.obj","owmoon.mtl");
    std::vector<std::vector<GLfloat>> vertex = load.getVertex();

    for(int j=1;j<load.numOfObjects();j++){
        object obj = load.getObj(j);
        
        std::vector<GLfloat> v = load.getValue(obj.material);
        glColor4f(v[0],v[1],v[2],1.0f);

        for(int i=0;i<obj.faceVertex.size();i++){
            glBegin(GL_QUADS);
                glVertex3f(vertex[obj.faceVertex[i][0]][0],vertex[obj.faceVertex[i][0]][1],vertex[obj.faceVertex[i][0]][2]);
                glVertex3f(vertex[obj.faceVertex[i][1]][0],vertex[obj.faceVertex[i][1]][1],vertex[obj.faceVertex[i][1]][2]);
                glVertex3f(vertex[obj.faceVertex[i][2]][0],vertex[obj.faceVertex[i][2]][1],vertex[obj.faceVertex[i][2]][2]);
                glVertex3f(vertex[obj.faceVertex[i][3]][0],vertex[obj.faceVertex[i][3]][1],vertex[obj.faceVertex[i][3]][2]);
            glEnd();
        }
    }
    //insert a teapot if time remains
}


void camera(){
    glRotatef(xrot,1.0,0.0,0.0);
    glRotatef(yrot,0.0,1.0,0.0);
    glRotatef(zrot,0.0,0.0,1.0);
    glTranslatef(-xpos,-ypos,-zpos);
}

void display(void){
    keyOperations();

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    camera();

    render();

    glutSwapBuffers();
}

void reshape(int width,int height){
    //resizing the viewport
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    
    glMatrixMode(GL_PROJECTION);
        //reloading identity matrix and reseting perspective
        glLoadIdentity();
        gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyDown (unsigned char key, int x, int y) {  
    ispressed[key] = true;  
} 
void keyUp (unsigned char key, int x, int y) {  
    ispressed[key] = false;
}


int main(int argc, char **argv){

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE);
    glutInitWindowSize (WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH )- WINDOW_WIDTH)/ 2, (glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2 );
    glutCreateWindow ("3D Scene");

    glutDisplayFunc(display);
    glutIdleFunc(display);

    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);

    glutMainLoop();
}