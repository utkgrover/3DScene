//add keyboard input and stuff that can be done with keyboard input

#include<GL/glew.h>
#include<stdlib.h>
#include<math.h>
#include "loader.h"

int WINDOW_HEIGHT=500;
int WINDOW_WIDTH=500;
bool ispressed[256]={0};
GLfloat zoomed = -5.0f;
GLfloat scale = 1.0f;
GLfloat xRot=0.0f;
GLfloat yRot=0.0f;


float xpos=0,ypos=0,zpos=-5.0f;


void keyPressOperation(){
    if(ispressed['z']){
        //zoom
        // zoomed+=0.5f;
        // glTranslatef(0.0f, 0.0f, zoomed);
    }
    if(ispressed['d']){
        scale+=0.02f;
    }
    if(ispressed['a']){
        scale-=0.02f;
    }
    if(ispressed['l']){
        xRot+=1.0f;
    }
    if(ispressed['j']){
        xRot-=1.0f;
    }
    if(ispressed['i']){
        yRot+=1.0f;
    }
    if(ispressed['k']){
        yRot-=1.0f;
    }
    if(ispressed['q']){
        exit(0);
    }

}


void render(){
    Loader load("scene1_v2.obj");
    std::vector<std::vector<GLfloat>> vertex = load.getVertex();

    // glColor3f(1.0f,1.0f,1.0f);

    for(int j=0;j<load.numOfObjects();j++){
        object obj = load.getObj(j);
        for(int i=0;i<obj.faceVertex.size();i++){
            glBegin(GL_QUADS);
                glVertex3f(vertex[obj.faceVertex[i][0]][0],vertex[obj.faceVertex[i][0]][1],vertex[obj.faceVertex[i][0]][2]);
                glVertex3f(vertex[obj.faceVertex[i][1]][0],vertex[obj.faceVertex[i][1]][1],vertex[obj.faceVertex[i][1]][2]);
                glVertex3f(vertex[obj.faceVertex[i][2]][0],vertex[obj.faceVertex[i][2]][1],vertex[obj.faceVertex[i][2]][2]);
                glVertex3f(vertex[obj.faceVertex[i][3]][0],vertex[obj.faceVertex[i][3]][1],vertex[obj.faceVertex[i][3]][2]);
            glEnd();
        }
    }
    
}

//dummy render functions 
void render1(){
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
        glVertex3f(1,-1,0);
        glVertex3f(2,2,0);
        glVertex3f(3,-3,0);
        glVertex3f(4,4,0);
    glEnd();
}
void renderPrimitive (void) {  
    glBegin(GL_QUADS); // Start drawing a quad primitive  
    
    glVertex3f(-1.0f, -1.0f, 0.0f); // The bottom left corner  
    glVertex3f(-1.0f, 1.0f, 0.0f); // The top left corner  
    glVertex3f(1.0f, 1.0f, 0.0f); // The top right corner  
    glVertex3f(1.0f, -1.0f, 0.0f); // The bottom right corner  
    
    glEnd();  
}


void display(void){
    glClearColor(0.0f,0.0f,0.0f,1.0f);  //sets background colour to black


    keyPressOperation();
    //clearing previos data out
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);

    //camera commands
    glScalef(scale,scale,scale);
    glRotatef(xRot,1.0,0.0,0.0);
    glRotatef(yRot,0.0,1.0,0.0);

    render();

    //flushes buffers to screen
    // glFlush();
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