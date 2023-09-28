//
//  careteClass.cpp
//  ArkanoidGLUT
//
//  Created by Никита Шабанов on 24.09.2023.
//

#include "careteClass.hpp"

Sn_Carete::Sn_Carete()
{
    m_xLoc = -0.2;
    m_yLoc = -1.0;
    m_sizeY = 0.03;
    m_sizeX = 0.2;
    
    m_speedVector.x = 0.5;
    m_speedVector.y = 0.0;
}

void Sn_Carete::draw(const std::map<Sn_ColorIdentifier, Sn_RGBColor> &colorMap)
{
    glBegin(GL_POLYGON);
    Sn_RGBColor col = colorMap.at(m_color);
    glColor3f(double(col.redRGB) / 255.0, double(col.greenRGB) / 255.0, double(col.blueRGB) / 255.0);
    setObjectCoords();
    glEnd();
}

Sn_ColorIdentifier Sn_Carete::getColor()
{
    return m_color;
}

void Sn_Carete::setColor(const Sn_ColorIdentifier& newCol)
{
    m_color = newCol;
}

bool Sn_Carete::doMovement(double &elapsedTime)
{
    m_xLoc += m_speedVector.x * elapsedTime;
    m_yLoc += m_speedVector.y * elapsedTime;
    
    m_yLoc = Sn_CommonMath::clamp(-1.0, 1.0 - m_sizeY, m_yLoc);
    
    if (m_xLoc == Sn_CommonMath::clamp(-1.0, 1.0 - m_sizeX, m_xLoc))
        return true;
    else
    {
        m_xLoc = Sn_CommonMath::clamp(-1.0, 1.0 - m_sizeX, m_xLoc);
        return false;
    }
    
    return false;
}

bool Sn_Carete::doMovement(double &elapsedTime, Sn_Ball *ball)
{
    if (!ball)
        return false;
    
    if (ball->isStuck())
    {
        double mov;
        double xSharedLeft = std::min(m_xLoc, ball->getLoc().x - ball->getRadius());
        double xSharedRight = std::max(m_xLoc + m_sizeX, ball->getLoc().x + ball->getRadius());
        double sharedSize = xSharedRight - xSharedLeft;
        
        double movLeft = xSharedLeft + m_speedVector.x * elapsedTime;
        movLeft = Sn_CommonMath::clamp(-1.0, 1.0 - sharedSize, movLeft);
        double movRight = xSharedRight + m_speedVector.x * elapsedTime;
        movRight = Sn_CommonMath::clamp(-1.0 + sharedSize, 1.0, movRight);
        if (elapsedTime < 0.0)
            mov = -1.0 * std::min(xSharedLeft - movLeft, xSharedRight - movRight);
        else
            mov = std::min(movLeft - xSharedLeft, movRight - xSharedRight);
        m_yLoc += m_speedVector.y * elapsedTime;
        
        m_yLoc = Sn_CommonMath::clamp(-1.0, 1.0 - m_sizeY, m_yLoc);
        m_xLoc += mov;
        ball->doStuckMovement(mov);
        
        return true;
    }
    else
    {
        if (elapsedTime * m_speedVector.x != movementBallCollision(ball, m_speedVector.x * elapsedTime))
            return false;
        
        m_xLoc += m_speedVector.x * elapsedTime;
        m_yLoc += m_speedVector.y * elapsedTime;
        
        m_yLoc = Sn_CommonMath::clamp(-1.0, 1.0 - m_sizeY, m_yLoc);
        
        if (m_xLoc == Sn_CommonMath::clamp(-1.0, 1.0 - m_sizeX, m_xLoc))
            return true;
        else
        {
            m_xLoc = Sn_CommonMath::clamp(-1.0, 1.0 - m_sizeX, m_xLoc);
            return false;
        }
        
        return false;
    }
}

void Sn_Carete::setObjectCoords()
{
    glVertex2f(m_xLoc, m_yLoc);
    glVertex2f(m_xLoc, m_yLoc + m_sizeY);
    glVertex2f(m_xLoc + m_sizeX, m_yLoc + m_sizeY);
    glVertex2f(m_xLoc + m_sizeX, m_yLoc);
}

double Sn_Carete::movementBallCollision(Sn_Ball *ball, double mov)
{
    double ballY = ball->getLoc().y;
    double ballX = ball->getLoc().x;
    if (ballY <= m_yLoc + m_sizeY && ballX < m_xLoc)
    {
        double impactDist = ballX - m_xLoc;
        if (impactDist < mov)
            return mov;
        else
            return impactDist * 0.99;
    }
    else if (ballY <= m_yLoc + m_sizeY && ballX > m_xLoc + m_sizeX)
    {
        double impactDist = ballX - m_xLoc - m_sizeX;
        if (impactDist > mov)
            return mov;
        else
            return impactDist * 0.99;
    }
    else if (ballY > m_yLoc + m_sizeY && ballY < m_yLoc + m_sizeY + ball->getRadius())
    {
        double y0 = m_yLoc + m_sizeY;
        double b = -2.0 * ballX;
        double c = ballX * ballX + ballY * ballY + y0 * y0 - 2.0 * y0 * ballY - ball->getRadius() * ball->getRadius();
        double discr = b * b - 4.0 * c;
        
        if (discr < 0.0)
            return mov;
        
        double val;
        if (mov > 0.0)
        {
            val = (-1.0 * b - sqrt(discr)) / 2.0;
            return (val - m_xLoc - m_sizeX) * 0.99;
        }
        else
        {
            val = (-1.0 * b + sqrt(discr)) / 2.0;
            return (val - m_xLoc) * 0.99;
        }
    }
    
    return mov;
}

void Sn_Carete::resizeCart()
{
    m_sizeX += 0.03;
}

void Sn_Carete::setSticky(bool status)
{
    m_isSticky = status;
}

bool Sn_Carete::getSticky()
{
    return m_isSticky;
}

double Sn_Carete::getLeftX()
{
    return m_xLoc;
}
