#include <QApplication>
#include <QLayout>
#include <QLabel>
#include <ctime>
#include "gameglwidget.h"
#include "detectmotion.h"

int main(int argc, char *argv[])
{
    // Initialise Random Numer generator
    srand(time(nullptr));

    // Create QT application
    QApplication app(argc, argv);

    QWidget window;

    // Create OpenGL (for 3D game scene) and Label (for camera display) widgets
    QLabel *pCameraLabel = new QLabel;
    DetectMotion::init(pCameraLabel);

    GameGLWidget *glWidget = new GameGLWidget();

    // Add them to the main window
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(pCameraLabel);
    layout->addWidget(glWidget);
    window.setLayout(layout);

    //camWidget->computeDetection();

    //camWidget.show();
    //glWidget.show();
    window.show();

    // Execute QT application
    return app.exec();
}
