#ifndef SATELLITE_H
#define SATELLITE_H

#include <GL/glu.h>
#include <QColor>
#include <QtGui/qopengl.h>
#include <planet.h>

// Classe dediee pour la gestion d'un satellite (lune)
class Satellite : public Planet
{
public:
    // Constructeur avec parametres
    Satellite(std::string name, float distanceFromCenter, float radius, const QColor & color, float rotationPeriod, float revolutionPeriod);

    // Destructeur
    virtual ~Satellite();

    // Methode d'affichage
    void Display(const float timeInDays);

    // Acces a un objet
   const std::string & GetName();

private:
    Planet* m_PlaneteAssociee = nullptr;
};

#endif // SATELLITE_H

