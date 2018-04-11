#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QImage>


// Classe dediee a l'affichage d'une scene OpenGL
class MyGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    // Constructeur
    MyGLWidget(QWidget * parent = nullptr);

protected:
    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

    // Fonction de gestion d'interactions clavier
    void keyPressEvent(QKeyEvent * event);

    // Fonctions de gestion d'interactions souris
    //void mousePressEvent(QMouseEvent * event);
    //void mouseReleaseEvent(QMouseEvent * event);
    //void wheelEvent(QWheelEvent * event);
    //void mouseMoveEvent(QMouseEvent * event);

private:
    // Timer d'animation
    float m_TimeElapsed { 0.0f };
    float m_LastTimeElapsed { 0.0f };
    QTimer m_AnimationTimer;
};

#endif // MYGLWIDGET_H