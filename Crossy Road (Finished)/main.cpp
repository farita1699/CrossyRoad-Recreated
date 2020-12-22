/*
Performance Task. Road crossing.
Jerry Wan
2020/1/17

This program will attempt to re-create the popular arcade video game ¡®Crossy Road¡¯ created by Hipster Whale. The game will have the user control a playable character in a 3D world. The character is able to move in four directions: left, right, forward and backward. The objective of the game is for the character to reach the end of the 10x100 world without colliding into other mobile objects(eg.cars). The 3D world will have borders to restrict the player¡¯s movement. It will also contain obstacles to enhance the difficulties of the game(eg. Tree, boulder). The character will die and the game will end when collision with mobile objects occur.
*/


#include <windows.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

//declaration of player¡¯s x,y,z position
static GLfloat object_x = 2.75;
static GLfloat object_y = 0.25;
static GLfloat object_z = -0.25;

//declaration of camera¡¯s x,y,z position
static GLfloat camera_x = 3.25; //2.75
static GLfloat camera_y = 3; //3
static GLfloat camera_z = 2; //2

//declaration of eye¡¯s(location in which the camera looks at) x,y,z position
static GLfloat eye_x = 2.75;
static GLfloat eye_y = 0;
static GLfloat eye_z = -0.25;

//for storing different colors
struct ground
{
    GLfloat red;
    GLfloat green;
    GLfloat blue;
};

std::vector <ground> color(4);

//for setting the position of various obstacles, blocks, and mobile objects
struct point
{
    GLfloat x;
    GLfloat z;
};

std::vector <point> tree;
std::vector <point> boulder;
std::vector <point> grass;
std::vector <point> road;
std::vector <point> car;

//variables for storing the number of various obstacles, blocks, and mobile objects
static int treecount = 0;
static int bouldercount = 0;
static int grasscount = 0;
static int roadcount = 0;
static int carCount = 0;

static int rGen; //random car generating variable
static int counter = 0;

//3 different speeds for mobile objects
std::vector <GLfloat> speed1;
std::vector <GLfloat> speed2;
std::vector <GLfloat> speed3;




void display() //displays most of the objects
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(camera_x, camera_y, camera_z, eye_x, eye_y, eye_z, 0, 1, 0);

    // Draw a white torus of outer radius 3, inner radius 0.5 with 15 stacks
    // and 30 slices.
    glColor3f(1.0, 1.0, 1.0);

    for (int i = 0; i < grasscount; i++)
    {
        glColor3f(color[0].red,color[0].green,color[0].blue);
        glPushMatrix();
        glTranslatef(grass[i].x,-0.25,grass[i].z);
        glutSolidCube(0.5);
        glPopMatrix();
    }

    for (int i = 0; i < roadcount; i++)
    {
        glColor3f(color[3].red,color[3].green,color[3].blue);
        glPushMatrix();
        glTranslatef(road[i].x,-0.35,road[i].z);
        glutSolidCube(0.5);
        glPopMatrix();
        glColor3f(1,1,0);
        glPushMatrix();
        glTranslatef(road[i].x,-0.35+0.05,road[i].z);
        glutSolidCube(0.1);
        glPopMatrix();
    }

    //player
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(object_x,object_y-0.075,object_z-0.06);
    glutSolidCube(0.2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(object_x,object_y + 0.12,object_z-0.06);
    glutSolidCube(0.2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(object_x,object_y-0.075,object_z+0.1);
    glutSolidCube(0.2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(object_x-0.1,object_y-0.075,object_z+0.01);
    glutSolidCube(0.13);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(object_x+0.1,object_y-0.075,object_z+0.01);
    glutSolidCube(0.13);
    glPopMatrix();
    glColor3f(1, 1, 0);
    glPushMatrix();
    glTranslatef(object_x+0.07,object_y-0.225,object_z+0.01);
    glutSolidCube(0.05);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(object_x-0.07,object_y-0.225,object_z+0.01);
    glutSolidCube(0.05);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(object_x+0.07,object_y-0.2,object_z+0.01);
    glutSolidCube(0.05);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(object_x-0.07,object_y-0.2,object_z+0.01);
    glutSolidCube(0.05);
    glPopMatrix();
    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(object_x-0.1,object_y+0.2,object_z-0.14);
    glutSolidCube(0.05);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(object_x+0.1,object_y+0.2,object_z-0.14);
    glutSolidCube(0.05);
    glPopMatrix();
    glColor3f(1, 1, 0);
    glPushMatrix();
    glTranslatef(object_x,object_y+0.12,object_z-0.16);
    glutSolidCube(0.08);
    glPopMatrix();

    //tree
    for (int i = 0; i < treecount; i++)
    {
        glColor3f(color[0].red,color[0].green,color[0].blue);
        glPushMatrix();
        glTranslatef(tree[i].x,-0.25,tree[i].z);
        glutSolidCube(0.5);
        glPopMatrix();
        glColor3f(0, 1, 0);
        glPushMatrix();
        glTranslatef(tree[i].x,0.05,tree[i].z);
        glutSolidCube(0.1);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(tree[i].x,0.15,tree[i].z);
        glutSolidCube (0.1);
        glPopMatrix();
        glPushMatrix();
        glTranslated(tree[i].x,0.2,tree[i].z);
        glRotated(90,-500,0.2,tree[i].z);
        glutSolidCone(0.3,1,32,32);
        glPopMatrix();
    }
    //boulder
    for (int i = 0; i < bouldercount; i++)
    {
        glColor3f(color[0].red,color[0].green,color[0].blue);
        glPushMatrix();
        glTranslatef(boulder[i].x,-0.25,boulder[i].z);
        glutSolidCube(0.5);
        glPopMatrix();
        glColor3f(0,0,0);
        glPushMatrix();
        glTranslatef(boulder[i].x,0.2,boulder[i].z);
        glutSolidCube (0.4);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(boulder[i].x+0.1,0.2-0.05,boulder[i].z+0.1);
        glutSolidCube (0.3);
        glPopMatrix();
    }

    //car
    for (int i = 0; i < carCount; i++)
    {
        glColor3f(1,1,1);
        glPushMatrix();
        glTranslatef(car[i].x,0.2,car[i].z);
        glutSolidCube (0.4);
        glPopMatrix();
    }


    glColor3f(1, 1, 1);
    glPushMatrix();
    glRasterPos2f(-1,1);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'S');
    glRasterPos2f(-0.9,1);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'T');
    glRasterPos2f(-0.8,1);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');
    glRasterPos2f(-0.7,1);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'R');
    glRasterPos2f(-0.6,1);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'T');
    glPopMatrix();

    glutSwapBuffers();
    glFlush();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        object_z = object_z - 0.5;
        camera_z = camera_z - 0.5;
        eye_z = eye_z - 0.5;

        for (int i = 0; i < treecount; i++)
        {
            if (object_z == tree[i].z && object_x == tree[i].x)
            {
                object_z = object_z + 0.5;
                camera_z = camera_z + 0.5;
                eye_z = eye_z + 0.5;
            }
        }
        for (int i = 0; i < bouldercount; i++)
        {
            if (object_z == boulder[i].z && object_x == boulder[i].x)
            {
                object_z = object_z + 0.5;
                camera_z = camera_z + 0.5;
                eye_z = eye_z + 0.5;
            }
        }

        break;

    case 'a':
        object_x = object_x - 0.5;
        camera_x = camera_x - 0.5;
        eye_x = eye_x - 0.5;

        for (int i = 0; i < treecount; i++)
        {
            if (object_z == tree[i].z && object_x == tree[i].x)
            {
                object_x = object_x + 0.5;
                camera_x = camera_x + 0.5;
                eye_x = eye_x + 0.5;
            }
        }
        for (int i = 0; i < bouldercount; i++)
        {
            if (object_z == boulder[i].z && object_x == boulder[i].x)
            {
                object_x = object_x + 0.5;
                camera_x = camera_x + 0.5;
                eye_x = eye_x + 0.5;
            }
        }

        if (object_x == -0.25)
            {
                object_x = object_x + 0.5;
                camera_x = camera_x + 0.5;
                eye_x = eye_x + 0.5;
            }

        break;

    case 's':
        object_z = object_z + 0.5;
        camera_z = camera_z + 0.5;
        eye_z = eye_z + 0.5;

        for (int i = 0; i < treecount; i++)
        {
            if (object_z == tree[i].z && object_x == tree[i].x)
            {
                object_z = object_z - 0.5;
                camera_z = camera_z - 0.5;
                eye_z = eye_z - 0.5;
            }
        }
        for (int i = 0; i < bouldercount; i++)
        {
            if (object_z == boulder[i].z && object_x == boulder[i].x)
            {
                object_z = object_z - 0.5;
                camera_z = camera_z - 0.5;
                eye_z = eye_z - 0.5;
            }
        }

        if (object_z == 0.25)
            {
                object_z = object_z - 0.5;
                camera_z = camera_z - 0.5;
                eye_z = eye_z - 0.5;
            }

        break;

    case 'd':
        object_x = object_x + 0.5;
        camera_x = camera_x + 0.5;
        eye_x = eye_x + 0.5;

        for (int i = 0; i < treecount; i++)
        {
            if (object_z == tree[i].z && object_x == tree[i].x)
            {
                object_x = object_x - 0.5;
                camera_x = camera_x - 0.5;
                eye_x = eye_x - 0.5;
            }
        }
        for (int i = 0; i < bouldercount; i++)
        {
            if (object_z == boulder[i].z && object_x == boulder[i].x)
            {
                object_x = object_x - 0.5;
                camera_x = camera_x - 0.5;
                eye_x = eye_x - 0.5;
            }
        }

        if (object_x == 5.25)
            {
                object_x = object_x - 0.5;
                camera_x = camera_x - 0.5;
                eye_x = eye_x - 0.5;
            }

        break;

    case 'j':
        camera_z = camera_z - 0.5;
        break;

    case 'k':
        camera_z = camera_z + 0.5;
        break;

    case 'n':
        camera_x = camera_x - 0.5;
        break;

    case 'm':
        camera_x = camera_x + 0.5;
        break;
    }

    glutPostRedisplay();
}

// Sets up global attributes like clear color and drawing color, and sets up
// the desired projection and modelview matrices.
void init()
{

    // Set the current clear color to black and the current drawing color to
    // white.
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);

    // Set the camera lens to have a 60 degree (vertical) field of view, an
    // aspect ratio of 4/3, and have everything closer than 1 unit to the
    // camera and greater than 40 units distant clipped away.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 4.0/3.0, 1, 40);

    // Position camera at (4, 6, 5) looking at (0, 0, 0) with the vector
    // <0, 1, 0> pointing upward.
    glMatrixMode(GL_MODELVIEW);
    //colors for the ground
    //light green
    color[0].red = 0.196078;
    color[0].green = 0.8;
    color[0].blue = 0.196078;
    //medium green
    color[1].red = 0.419608;
    color[1].green = 0.556863;
    color[1].blue = 0.137255;
    //dark green
    color[2].red = 0.184314;
    color[2].green = 0.309804;
    color[2].blue = 0.184314;
    //dark slate grey
    color[3].red = 0.184314;
    color[3].green = 0.309804;
    color[3].blue = 0.309804;

    ifstream InFile("Map.txt"); // just a text file
    if (InFile.fail())
    {
        cout << "File not found"<<endl;
    }
    else
    {
        string line;
        int h,v;
        getline(InFile,line); //get horizontal number of cubes in the map
        h = stoi(line);
        getline(InFile,line); //get vertical number of cubes in the map
        v = stoi(line);

        GLfloat layout[v][h];
        int fileLine = 100;

        while(getline(InFile,line))
        {
            for (int i = 0; i < line.length(); i++)
            {
                char c = line.at(i);
                if (c == '.')
                {
                    point temp;
                    grasscount++;
                    temp.x = (1+i)* 0.5 - 0.25;
                    temp.z = -(fileLine * 0.5 - 0.25);
                    grass.push_back(temp);
                }
                else if (c == '/')
                {
                    point temp;
                    roadcount++;
                    temp.x = (1+i)* 0.5 - 0.25;
                    temp.z = -(fileLine * 0.5 - 0.25);
                    road.push_back(temp);
                    rGen = rand()%3;
                    if (rGen == 0)
                    {
                        carCount++;
                        temp.x = (1+i)* 0.5 - 0.25;
                        temp.z = -(fileLine * 0.5 - 0.25);
                        car.push_back(temp);
                    }

                }
                else if (c == 't')
                {
                    point temp;
                    treecount++;
                    temp.x = (1+i)* 0.5 - 0.25;
                    temp.z = -(fileLine * 0.5 - 0.25);
                    tree.push_back(temp);
                }
                else if (c == 'o')
                {
                    point temp;
                    bouldercount++;
                    temp.x = (1+i)* 0.5 - 0.25;
                    temp.z = -(fileLine * 0.5 - 0.25);
                    boulder.push_back(temp);
                }
            }
            fileLine--;
        }
    }

    for (int i = 0; i < carCount; i++)
    {
        if (i < carCount/3)
        {
            speed3.push_back(0.03);
        }
        else if (i >= carCount/3 && i < 2*carCount/3)
        {
            speed2.push_back(0.02);
        }
        else if (i >= 2*carCount/3)
        {
            speed1.push_back(0.01);
        }
    }

    const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

    const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[] = { 100.0f };

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

}

void timer(int v)
{
    for (int i = 0; i < carCount; i++)
    {
        if (i < carCount/3)
        {
            car[i].x += speed3[i];
            if (car[i].x < 0.25 || car[i].x > 4.75)
            {
                speed3[i] = speed3[i] * -1;
            }
        }
        else if (i >= carCount/3 && i < 2*carCount/3)
        {
            car[i].x += speed2[i-carCount/3];
            if (car[i].x < 0.25 || car[i].x > 4.75)
            {
                speed2[i-carCount/3] = speed2[i-carCount/3] * -1;
            }
        }
        else if (i >= 2*carCount/3)
        {
            car[i].x += speed1[i-2*carCount/3];
            if (car[i].x < 0.25 || car[i].x > 4.75)
            {
                speed1[i-2*carCount/3] = speed1[i-2*carCount/3] * -1;
            }
        }
        //lose condition
        if (object_z == car[i].z && object_x >= car[i].x-0.4 && object_x <= car[i].x+0.4)
        {
            cout<<"You lost!"<<endl;
            exit(0);
        }

        glutPostRedisplay();
    }
    //win condition
    if (object_z == -50.25){
        cout<<"You win!"<<endl;
        exit(0);
    }


    glutTimerFunc(1000/60, timer, v);
}


// Initializes GLUT, the display mode, and main window; registers callbacks;
// does application initialization; enters the main event loop.
int main(int argc, char** argv)
{
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(800, 600);
    glutCreateWindow("A Simple Torus");
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutTimerFunc(100, timer, 0);

    init();
    glutMainLoop();

    return EXIT_SUCCESS;
}






