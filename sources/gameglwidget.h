#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QImage>


// Widget dedicated to display the OpenGL game's scene.
// @autor RaphaelChevasson (modification of OpenGL labs' code)
class GameGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    // Constructor
    GameGLWidget(QWidget * parent = nullptr);

protected:
    // Initialisation function
    void initializeGL();

    // Resize function
    void resizeGL(int width, int height);

    // Display function
    void paintGL();

    // Keyboard interractions handling fonction
    void keyPressEvent(QKeyEvent * event);

    // Mouse nterractions handling fonction
    //void mousePressEvent(QMouseEvent * event);
    //void mouseReleaseEvent(QMouseEvent * event);
    //void wheelEvent(QWheelEvent * event);
    //void mouseMoveEvent(QMouseEvent * event);

private:
    // Animation Timer
    float m_TimeElapsed { 0.0f };
    float m_LastTimeElapsed { 0.0f };
    QTimer m_AnimationTimer;
};

#endif // MYGLWIDGET_H
