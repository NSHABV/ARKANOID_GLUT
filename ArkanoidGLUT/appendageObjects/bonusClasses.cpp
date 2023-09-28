//
//  bonusClasses.cpp
//  ArkanoidGLUT
//
//  Created by Никита Шабанов on 28.09.2023.
//

#include "bonusClasses.hpp"

Sn_Bonus::Sn_Bonus()
{
    
}

Sn_Bonus::Sn_Bonus(double xLoc, double yLoc)
{
    m_xLoc = xLoc;
    m_yLoc = yLoc;
    m_sizeX = 0.02;
    m_sizeY = 0.02;
    
    Sn_Vector speedVec;
    speedVec.x = 0.0;
    speedVec.y = -0.3;
    
    m_color = Sn_ColorIdentifier::greenRGB;
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
        if (futureX + m_sizeX >= xBoundaryLeft && futureX <= xBoundaryRight)
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

Sn_CartResizeBonus::Sn_CartResizeBonus(double xLoc, double yLoc)
{
    m_xLoc = xLoc;
    m_yLoc = yLoc;
    m_sizeX = 0.02;
    m_sizeY = 0.02;
    
    Sn_Vector speedVec;
    speedVec.x = 0.0;
    speedVec.y = -0.3;
    
    m_color = Sn_ColorIdentifier::greenRGB;
    m_speedVector = speedVec;
}
    
Sn_BallSpeedUpBonus::Sn_BallSpeedUpBonus(double xLoc, double yLoc)
{
    m_xLoc = xLoc;
    m_yLoc = yLoc;
    m_sizeX = 0.02;
    m_sizeY = 0.02;
    
    Sn_Vector speedVec;
    speedVec.x = 0.0;
    speedVec.y = -0.3;
    
    m_color = Sn_ColorIdentifier::greenRGB;
    m_speedVector = speedVec;
}
    
Sn_StickBonus::Sn_StickBonus(double xLoc, double yLoc)
{
    m_xLoc = xLoc;
    m_yLoc = yLoc;
    m_sizeX = 0.02;
    m_sizeY = 0.02;
    
    Sn_Vector speedVec;
    speedVec.x = 0.0;
    speedVec.y = -0.3;
    
    m_color = Sn_ColorIdentifier::greenRGB;
    m_speedVector = speedVec;
}
    
Sn_BottomOneBonus::Sn_BottomOneBonus(double xLoc, double yLoc)
{
    m_xLoc = xLoc;
    m_yLoc = yLoc;
    m_sizeX = 0.02;
    m_sizeY = 0.02;
    
    Sn_Vector speedVec;
    speedVec.x = 0.0;
    speedVec.y = -0.3;
    
    m_color = Sn_ColorIdentifier::greenRGB;
    m_speedVector = speedVec;
}
    
Sn_RandomProjectoryChange::Sn_RandomProjectoryChange(double xLoc, double yLoc)
{
    m_xLoc = xLoc;
    m_yLoc = yLoc;
    m_sizeX = 0.02;
    m_sizeY = 0.02;
    
    Sn_Vector speedVec;
    speedVec.x = 0.0;
    speedVec.y = -0.3;
    
    m_color = Sn_ColorIdentifier::greenRGB;
    m_speedVector = speedVec;
}


Sn_BonusAttribute Sn_CartResizeBonus::getBonusAttribute()
{
    return Sn_BonusAttribute::cartResize;
}
Sn_BonusAttribute Sn_BallSpeedUpBonus::getBonusAttribute()
{
    return Sn_BonusAttribute::ballSpeedup;
}
Sn_BonusAttribute Sn_StickBonus::getBonusAttribute()
{
    return Sn_BonusAttribute::stickBall;
}
Sn_BonusAttribute Sn_BottomOneBonus::getBonusAttribute()
{
    return Sn_BonusAttribute::bottomOneUse;
}
Sn_BonusAttribute Sn_RandomProjectoryChange::getBonusAttribute()
{
    return Sn_BonusAttribute::randomProjectoryChange;
}
