#define _USE_MATH_DEFINES

#include <QApplication>
#include <QDesktopWidget>
#include <GL/glu.h>
#include <QtGui/qopengl.h>
#include <cmath>
#include <random>
#include <QDebug>

#include "myglwidget.h"
#include "objectsmanager.h"
#include "displayedobject.h"
#include "ball.h"

// Declarations des constantes
const unsigned int WIN_WIDTH  = 1600;
const unsigned int WIN_HEIGHT = 900;
const float ASPECT_RATIO      = static_cast<float>(WIN_WIDTH) / WIN_HEIGHT;
const float MAX_DIMENSION     = 50.0f;
// position de la caméra
const float camX = 0;
const float camY = 0;
const float camZ = 10;
// gestion du temps
const float timeSpeed = 1;
// Objet jeu
ObjectsManager *pM;


// Constructeur
MyGLWidget::MyGLWidget(QWidget * parent)
    : QGLWidget(parent)
{
    // Reglage de la taille/position
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    // Connexion du timer
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


// Fonction d'initialisation
void MyGLWidget::initializeGL()
{
    // Reglage de la couleur de fond
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

    // Activation du zbuffer
    glEnable(GL_DEPTH_TEST);

    // Active les textures 2D
    glEnable(GL_TEXTURE_2D);

    // Convertit une image en un format attendu par les fonctions d’OpenGL
    QImage tSoleil  = QGLWidget::convertToGLFormat(QImage(":/textures/res/soleil.jpg" ));
    QImage tMercure = QGLWidget::convertToGLFormat(QImage(":/textures/res/mercure.jpg"));
    QImage tVenus   = QGLWidget::convertToGLFormat(QImage(":/textures/res/venus.jpg"  ));
    QImage tTerre   = QGLWidget::convertToGLFormat(QImage(":/textures/res/terre.jpg"  ));
    // Crée 10 objets texture et leur associe un numéro qu’on stocke
    GLuint* m_tID = new GLuint[10];
    glGenTextures(10, m_tID);

    // Test
    pM = new ObjectsManager();
    Player *pP = new Player();
    new Ball(pM,pP,1,2,3,1,2); // sera dans le constructor de level qui sera dans pG->Start()
    new Ball(pM,pP,1,-2,3,1,-2); // sera dans le constructor de level qui sera dans pG->Start()

    // Reglage de la lampe
    GLfloat ambiantColor[4] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat diffuseColor[4] = {0.7f, 0.7f, 0.7f, 1.0f};
    //GLfloat specularColor[4] = {0.0f, 0.0f, 0.0f, 25.0f};
    GLfloat position[4] = {0.0f, 0.0f, 0.0f, 0.1f}; // le dernier 0 : source positionnée (1 : à l'infini)
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiantColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, specularColor);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    // Activation de la lumiere
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat modelAmbiantColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, modelAmbiantColor); // 0.2, 0.2, 0.2 par défaut
}


// Fonction de redimensionnement
void MyGLWidget::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);

    // Definition de la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(width != 0)
        glOrtho(-MAX_DIMENSION, MAX_DIMENSION,
                -MAX_DIMENSION * height / static_cast<float>(width),
                MAX_DIMENSION * height / static_cast<float>(width),
                -MAX_DIMENSION * 2.0f, MAX_DIMENSION * 2.0f);

    // Definition de la matrice de modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// Fonction d'affichage
void MyGLWidget::paintGL()
{
    // Reinitialisation des tampons
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Definition de la position de la camera
    glLoadIdentity();
    gluLookAt(camX, camY, camZ,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    // Affichage des m_Planetes
    //qDebug() << m_TimeElapsed;
    for (DisplayedObject *o : pM->DisplayedObjects) // access by reference to avoid copying
    {
        o->display();
    }
}


// Fonction de gestion d'interactions clavier
void MyGLWidget::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
        // Activation/Arret de l'animation
        case Qt::Key_Space:
        {
            if(m_AnimationTimer.isActive())
                m_AnimationTimer.stop();
            else
                m_AnimationTimer.start();

            break;
        }

        // Sortie de l'application
        case Qt::Key_Escape:
        {
            exit(0);
        }

        // Cas par defaut
        default:
        {
            // Ignorer l'evenement
            event->ignore();
            return;
        }
    }

    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();
    updateGL();
}
