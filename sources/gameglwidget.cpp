#define _USE_MATH_DEFINES

#include <QApplication>
#include <QDesktopWidget>
#include <GL/glu.h>
#include <QtGui/qopengl.h>
#include <cmath>
#include <random>
#include <QDebug>

#include "gameglwidget.h"
#include "objectsmanager.h"
#include "displayedobject.h"
#include "animatedobject.h"
#include "collidingobject.h"
#include "player.h"
#include "ball.h"
#include "limitwall.h"
#include "deathwall.h"


// Constants declaration :
// screen shape
const unsigned int WIN_WIDTH  = 1600;
const unsigned int WIN_HEIGHT = 900;
const float ASPECT_RATIO      = static_cast<float>(WIN_WIDTH) / WIN_HEIGHT;
const float MAX_DIMENSION     = 50.0f;
// camera position
const float camX = 0;
const float camY = 0;
const float camZ = 10;
// time handling
const float timeSpeed = 1;

// Variables declaration :
// game objects
ObjectsManager *pM;
// display options
bool displayHitboxes = false;


// Constructor
GameGLWidget::GameGLWidget(QWidget * parent)
    : QGLWidget(parent)
{
    // Widget size and position setup
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    // Timer setup
    connect(&m_AnimationTimer,  &QTimer::timeout, [&] {
        m_TimeElapsed += timeSpeed / 100.0f;

        // Annimation
        for (AnimatedObject *o : pM->AnimatedObjects) // access by reference to avoid copying
        {
            o->animate(m_TimeElapsed, m_TimeElapsed - m_LastTimeElapsed);
        }

        // Display
        updateGL();

        m_LastTimeElapsed = m_TimeElapsed;
    });

    m_AnimationTimer.setInterval(10);
    m_AnimationTimer.start();
}


// Initialisation function
void GameGLWidget::initializeGL()
{
    // Background color setup
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

    // Activate zbuffer
    glEnable(GL_DEPTH_TEST);

    // Activate textures
    glEnable(GL_TEXTURE_2D);

    // TODO: Import textures (see example bellow)
    //   // Convert an image into the format expected by OpenGL's functions
    //   QImage tSoleil  = QGLWidget::convertToGLFormat(QImage(":/textures/res/soleil.jpg" ));
    //   // Create 10 object textures and bind them with a number that we store
    //   GLuint* m_tID = new GLuint[10];
    //   glGenTextures(10, m_tID);

    // Lighting setup
    GLfloat ambiantColor[4] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat diffuseColor[4] = {0.7f, 0.7f, 0.7f, 1.0f};
    //GLfloat specularColor[4] = {0.0f, 0.0f, 0.0f, 25.0f};
    GLfloat position[4] = {0.0f, 0.0f, 0.0f, 0.1f}; // le dernier 0 : source positionnée (1 : à l'infini)
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiantColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, specularColor);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    // Activate lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat modelAmbiantColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, modelAmbiantColor); // 0.2, 0.2, 0.2 par défaut


    // Test of a basic level setup

    pM = new ObjectsManager();
    Player *pP = new Player();

    new Ball(pM,pP,1,2,3,3,7); // TODO: this will be in Level's constructor, and Level will be created in pG->Start()
    new Ball(pM,pP,1,-2,3,4,-8); // TODO: this will be in Level's constructor, and Level will be created in pG->Start()
    new LimitWall(pM, -20, -20, -20,  20); // left limit wall  // TODO: this will be in Level's constructor, and Level will be created in pG->Start()
    new LimitWall(pM, -20,  20,  20,  20); // up limit wall    // TODO: this will be in Level's constructor, and Level will be created in pG->Start()
    new LimitWall(pM,  20,  20,  20, -20); // right limit wall // TODO: this will be in Level's constructor, and Level will be created in pG->Start()
    new DeathWall(pM,  20, -20, -20, -20); // down limit wall  // TODO: this will be in Level's constructor, and Level will be created in pG->Start()

    // End of the basic level setup
}


// Resize function
void GameGLWidget::resizeGL(int width, int height)
{
    // Viewport setup (display zone)
    glViewport(0, 0, width, height);

    // Projection matrice setup
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(width != 0)
        glOrtho(-MAX_DIMENSION, MAX_DIMENSION,
                -MAX_DIMENSION * height / static_cast<float>(width),
                MAX_DIMENSION * height / static_cast<float>(width),
                -MAX_DIMENSION * 2.0f, MAX_DIMENSION * 2.0f);

    // Modelview matrice setup
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// Display function
void GameGLWidget::paintGL()
{
    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Define camerra position
    glLoadIdentity();
    gluLookAt(camX, camY, camZ,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    // Draw all DisplayedObjects :
    for (DisplayedObject *o : pM->DisplayedObjects) // access by reference to avoid copying
    {
        // Save current matrix and color
        glPushMatrix();
        glPushAttrib(GL_CURRENT_BIT | GL_LIGHTING_BIT);

        // Display the object
        o->display();

        // Restore current matrix and color
        glPopMatrix();
        glPopAttrib();
    }

    if(displayHitboxes)
    {
        // Draw all CollidingObjects' hitboxes :

        // make points larger
        glPointSize(4);

        // disable lighting to permit full color control
        glDisable(GL_LIGHTING);

        for (CollidingObject *o : pM->CollidingObjects) // access by reference to avoid copying
        {
            // Save current matrix and color
            glPushMatrix();
            glPushAttrib(GL_CURRENT_BIT);

            // Display the hitbox
            o->drawHitbox();

            // Restore current matrix and color
            glPopMatrix();
            glPopAttrib();
        }

        // turn back lighting
        glEnable(GL_LIGHTING);
    }


    // Flush drawing commands
    glFlush();

    //qDebug() << m_TimeElapsed; // test; TODO: remove this
}


// Keyboard interractions handling fonction
void GameGLWidget::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
        // Pause/resume animation (space)
        case Qt::Key_Space:
        {
            if(m_AnimationTimer.isActive())
                m_AnimationTimer.stop();
            else
                m_AnimationTimer.start();

            break;
        }

        // Closing application (escape)
        case Qt::Key_Escape:
        {
            exit(0);
        }

        // Display/hide hitboxes (F2)
        case Qt::Key_F2:
        {
            displayHitboxes = !displayHitboxes;
            glFlush();
            break;
        }

        // Other inputs
        default:
        {
            // Ignore the event
            event->ignore();
            return;
        }
    }

    // Accept the event and update the scene
    event->accept();
    updateGL();
}
