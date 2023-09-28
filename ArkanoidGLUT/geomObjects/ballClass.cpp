//
//  ballClass.cpp
//  ArkanoidGLUT
//
//  Created by Никита Шабанов on 26.09.2023.
//

#include "ballClass.hpp"
#include "commonMath.hpp"

Sn_Ball::Sn_Ball()
{
    
}

Sn_Ball::Sn_Ball(const Sn_Vector &position, const Sn_Vector &speed, double radius)
{
    m_xLoc = position.x;
    m_yLoc = position.y;
    
    Sn_Vector speedVector;
    speedVector.x = speed.x;
    speedVector.y = speed.y;
    m_speedVector = speedVector;
    
    m_color = Sn_ColorIdentifier::tealRGB;
    m_radius = radius;
}

void Sn_Ball::draw(const std::map<Sn_ColorIdentifier, Sn_RGBColor> &colorMap)
{
    glBegin(GL_POINTS);
    Sn_RGBColor col = colorMap.at(m_color);
    glColor3f(double(col.redRGB) / 255.0, double(col.greenRGB) / 255.0, double(col.blueRGB) / 255.0);
    setObjectCoords();
    glEnd();
    
    if (m_bottomOneUse)
        drawBottom(colorMap);
}

void Sn_Ball::drawBottom(const std::map<Sn_ColorIdentifier, Sn_RGBColor> &colorMap)
{
    glBegin(GL_POLYGON);
    Sn_RGBColor col = colorMap.at(Sn_ColorIdentifier::blueRGB);
    glColor3f(double(col.redRGB) / 255.0, double(col.greenRGB) / 255.0, double(col.blueRGB) / 255.0);
    glVertex2f(-1.0, -1.0);
    glVertex2f(-1.0, -0.99);
    glVertex2f(1.0, -0.99);
    glVertex2f(1.0, -1.0);
    glEnd();
}

bool Sn_Ball::checkCollision(double elapsedTime)
{
    return false;
}

Sn_ColorIdentifier Sn_Ball::getColor()
{
    return Sn_ColorIdentifier::redRGB;
}

void Sn_Ball::setColor(const Sn_ColorIdentifier& newCol)
{
    
}

bool Sn_Ball::doMovement(double &elapsedTime)
{
    if (elapsedTime <= 0.0)
        return false;
    
    auto nextXLoc = m_speedVector.x * elapsedTime + m_xLoc;
    auto nextYLoc = m_speedVector.y * elapsedTime + m_yLoc;
    
    if (fabs(nextXLoc) < 1.0 - m_radius && fabs(nextYLoc) < 1.0 - m_radius)
    {
        m_xLoc += m_speedVector.x * elapsedTime;
        m_yLoc += m_speedVector.y * elapsedTime;
        
        elapsedTime = 0.0;
    }
    else if (fabs(nextXLoc) == fabs(nextYLoc))
    {
        auto clampedLocX = Sn_CommonMath::clamp(-1.0 + m_radius, 1.0 - m_radius, nextXLoc);
        auto clampedLocY = Sn_CommonMath::clamp(-1.0 + m_radius, 1.0 - m_radius, nextYLoc);
        
        //auto remainingTime = fabs(clampedLocX - m_xLoc) / m_speedVector.x;
        elapsedTime = fabs(clampedLocX - m_xLoc) / fabs(m_speedVector.x);
        m_speedVector.x *= -1;
        m_speedVector.y *= -1;
        
        m_xLoc = clampedLocX;
        m_yLoc = clampedLocY;
    }
    else
    {
        double yIntersectTime, xIntersectTime;
        yIntersectTime = fabs(Sn_CommonMath::signd(m_yLoc) * (1.0 - m_radius) - m_yLoc) / fabs(m_speedVector.y);
        xIntersectTime = fabs(Sn_CommonMath::signd(m_xLoc) * (1.0 - m_radius) - m_xLoc) / fabs(m_speedVector.x);
        
        if (fabs(nextXLoc) < (1.0 - m_radius))
            xIntersectTime = __DBL_MAX__;
        if (fabs(nextYLoc) < (1.0 - m_radius))
            yIntersectTime = __DBL_MAX__;
        
        if (xIntersectTime < yIntersectTime)
        {
            m_xLoc = Sn_CommonMath::signd(m_xLoc) * (1.0 - m_radius);
            m_yLoc += m_speedVector.y * xIntersectTime;
            
            elapsedTime -= xIntersectTime;
            m_speedVector.x *= -1.0;
        }
        else if (yIntersectTime < xIntersectTime)
        {
            m_yLoc = Sn_CommonMath::signd(m_yLoc) * (1.0 - m_radius);
            m_xLoc += m_speedVector.x * yIntersectTime;
            
            elapsedTime -= yIntersectTime;
            m_speedVector.y *= -1.0;
        }
        else
        {
            auto clampedLocX = Sn_CommonMath::clamp(-1.0 + m_radius, 1.0 - m_radius, nextXLoc);
            auto clampedLocY = Sn_CommonMath::clamp(-1.0 + m_radius, 1.0 - m_radius, nextYLoc);
            
            //auto remainingTime = fabs(clampedLocX - m_xLoc) / m_speedVector.x;
            elapsedTime = fabs(clampedLocX - m_xLoc) / fabs(m_speedVector.x);
            m_speedVector.x *= -1.0;
            m_speedVector.y *= -1.0;
            
            m_xLoc = clampedLocX;
            m_yLoc = clampedLocY;
        }
    }
    
    if (m_yLoc == -1.0 + m_radius)
    {
        if (!m_bottomOneUse)
            m_bottomImpacts++;
        else
            m_bottomOneUse = false;
    }
    
    if (elapsedTime > 0.0)
        doMovement(elapsedTime);
    
    return false;
}

Sn_Vector Sn_Ball::getSpeed()
{
    return m_speedVector;
}

double Sn_Ball::getRadius()
{
    return m_radius;
}

Sn_Vector Sn_Ball::getLoc()
{
    Sn_Vector loc;
    loc.x = m_xLoc;
    loc.y = m_yLoc;
    return loc;
}

void Sn_Ball::setObjectCoords()
{
    for (double angle = 0.0; angle <= (2.0 * M_PI); angle += 0.01)
    {
        double x = m_xLoc + m_radius * sin(angle);
        double y = m_yLoc + m_radius * cos(angle);
        glVertex2d(x, y);
    }
}

void Sn_Ball::setSpeed(const Sn_Vector &vec)
{
    m_speedVector.x = vec.x;
    m_speedVector.y = vec.y;
}

void Sn_Ball::archiveSpeed(bool active)
{
    if (active)
    {
        Sn_Vector speed;
        speed.x = 0.0;
        speed.y = 0.0;
        m_formerSpeed = m_speedVector;
        m_speedVector = speed;
    }
    else
    {
        Sn_Vector temp = m_speedVector;
        m_speedVector = m_formerSpeed;
        m_formerSpeed = temp;
    }
}

void Sn_Ball::setLoc(const Sn_Vector &vec)
{
    m_xLoc = vec.x;
    m_yLoc = vec.y;
}

void Sn_Ball::ballSpeedUp()
{
    m_speedVector.x *= 1.1;
    m_speedVector.y *= 1.1;
}

void Sn_Ball::setTrajectory(double angleAlpha)
{
    double vecLen = m_speedVector.x * m_speedVector.x + m_speedVector.y * m_speedVector.y;
    
    angleAlpha = Sn_CommonMath::clamp(0.0, 360.0, angleAlpha);
    double angleRadians = angleAlpha / 2.0 / M_PI;
    
    m_speedVector.x = vecLen * cos(angleRadians);
    m_speedVector.y = vecLen * sin(angleRadians);
}

void Sn_Ball::setBottomOneUse(bool set)
{
    m_bottomOneUse = set;
}

void Sn_Ball::setStuck(bool status)
{
    m_stuck = status;
}

bool Sn_Ball::isStuck()
{
    return m_stuck;
}

void Sn_Ball::doStuckMovement(double movement)
{
    m_xLoc += movement;
}

int Sn_Ball::getBottomImpacts()
{
    return m_bottomImpacts;
}
