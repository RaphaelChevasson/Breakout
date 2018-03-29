#include "satellite.h"
#include "QImage.h"
#include <QGLWidget>
#include <QFile>

Satellite::Satellite(std::string name, float distanceFromCenter, float radius, const QColor & color, float rotationPeriod, float revolutionPeriod, Planet* planeteAssociee)
    : m_PlaneteAssociée(planeteAssociee)
{
    Planet(name, distanceFromCenter, radius, color, rotationPeriod, revolutionPeriod);
    // Creation de la quadrique
    m_Body = gluNewQuadric();
}


Satellite::~Satellite()
{
    // Destruction de la quadrique
    gluDeleteQuadric(m_Body);
}

void Satellite::Display(const float timeInDays)
{
    glPushMatrix();

    glEnable(GL_LIGHTING);

    // TRANSFORMATION POUR POSITIONNER LA PLANETE ASSOCIEE AUTOUR DU SOLEIL
    // Transformation pour la periode de revolution
    glRotatef(360.0f * m_PlaneteAssociee->GetRevolutionPeriodInDays() / 365.256f, 0.0f, 0.0f, 1.0f);

    glTranslatef(13.0f, 0, 0);

    // Transformation pour la periode de rotation
    glRotatef(360.0f * timeInDays /  1.0f, 0.0f, 0.0f, 1.0f);

    // TRANSFORMATION POUR POSITIONNER LE SATTELITE AUTOUR DE LA PLANETE ASSOCIEE
    // Transformation pour la periode de revolution
    glRotatef(360.0f * timeInDays / m_PlaneteAssociee->GetRevolutionPeriodInDays(), 0.0f, 0.0f, 1.0f);

    glTranslatef(m_DistanceFromCenter, 0, 0);

    // Transformation pour la periode de rotation
    glRotatef(360.0f * timeInDays / m_PlaneteAssociee->GetRotationPeriodInDays(), 0.0f, 0.0f, 1.0f);

    // Couleur de l'objet
    GLfloat color[] = {(float)m_Color.redF(), (float)m_Color.greenF(), (float)m_Color.blueF(), 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

    GLfloat emissionColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionColor);

    gluSphere(m_Body, m_Radius, 32, 32);

    glPopMatrix();
}
