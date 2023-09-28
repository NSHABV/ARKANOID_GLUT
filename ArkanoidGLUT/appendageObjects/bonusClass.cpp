//
//  bonusClass.cpp
//  ArkanoidGLUT
//
//  Created by Никита Шабанов on 28.09.2023.
//

#include "bonusClass.hpp"

Sn_Bonus::Sn_Bonus(double xLoc, double yLoc)
{
    m_xLoc = xLoc;
    m_yLoc = yLoc;
    m_sizeX = 0.02;
    m_sizeY = 0.02;
    
    Sn_Vector speedVec;
    speedVec.x = 0.0;
    speedVec.y = 0.05;
    
    m_speedVector = speedVec;
}

bool Sn_Bonus::doMovement(double &elapsedTime)
{
    m_yLoc += m_speedVector.y * elapsedTime;
    m_xLoc += m_speedVector.x * elapsedTime;
    return false;
}
    
Sn_BonusAttribute Sn_Bonus::getBonusAttribute()
{
    return Sn_BonusAttribute::nobonus;
}

bool Sn_Bonus::isGone()
{
    if (m_yLoc <= -1.0)
        return true;
    return false;
}

bool Sn_Bonus::bonusCollision(Sn_Carete *carete, double elapsedTime)
{
    double futureY = m_yLoc + elapsedTime * m_speedVector.y;
    double futureX = m_xLoc + elapsedTime * m_speedVector.x;
    
    double yBoundary = carete->getTopLeftPoint().y;
    double xBoundaryLeft = carete->getTopLeftPoint().x;
    double xBoundaryRight = carete->getTopRightPoint().x;
    
    if (futureY > yBoundary)
    {
        doMovement(elapsedTime);
        return false;
    }
    else
    {
        if (futureX + m_sizeX >= xBoundaryLeft || futureX <= xBoundaryRight)
            return true;
        else
        {
            doMovement(elapsedTime);
            return false;
        }
    }
}

void Sn_Bonus::setObjectCoords()
{
    glVertex2f(m_xLoc, m_yLoc);
    glVertex2f(m_xLoc, m_yLoc + m_sizeY);
    glVertex2f(m_xLoc + m_sizeX, m_yLoc + m_sizeY);
    glVertex2f(m_xLoc + m_sizeX, m_yLoc);
}
