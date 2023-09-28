//
//  physicsObject.cpp
//  ArkanoidGLUT
//
//  Created by Никита Шабанов on 26.09.2023.
//

#include "physicsObject.hpp"

Sn_PhysicsObject::Sn_PhysicsObject()
{
    
}

void Sn_PhysicsObject::draw(const std::map<Sn_ColorIdentifier, Sn_RGBColor> &colorMap)
{
    glBegin(GL_POLYGON);
    Sn_RGBColor col = colorMap.at(m_color);
    glColor3f(double(col.redRGB) / 255.0, double(col.greenRGB) / 255.0, double(col.blueRGB) / 255.0);
    setObjectCoords();
    glEnd();
}

Sn_ColorIdentifier Sn_PhysicsObject::getColor()
{
    return m_color;
}

void Sn_PhysicsObject::setColor(const Sn_ColorIdentifier& newCol)
{
    m_color = newCol;
}

bool Sn_PhysicsObject::doMovement(double &elapsedTime)
{
    return false;
}

void Sn_PhysicsObject::setObjectCoords()
{
    
}
