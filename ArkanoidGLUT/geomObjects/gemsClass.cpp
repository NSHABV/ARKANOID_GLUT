#include "gemsClass.h"
#include "commonMath.hpp"
Sn_StandardGem::Sn_StandardGem()
{
}

Sn_StandardGem::Sn_StandardGem(double xLoc, double yLoc, double sizeX, double sizeY, const Sn_ColorIdentifier& col)
{
	m_xLoc = xLoc;
	m_yLoc = yLoc;

	m_sizeX = sizeX;
    m_sizeY = sizeY;
	m_color = col;
    
    m_livesRemaining = 4;
    m_isIndestructible = 0;
}

void Sn_StandardGem::draw(const std::map<Sn_ColorIdentifier, Sn_RGBColor>& colorMap)
{
	glBegin(GL_POLYGON);
	Sn_RGBColor col = colorMap.at(m_color);
	glColor3f(double(col.redRGB) / 255.0, double(col.greenRGB) / 255.0, double(col.blueRGB) / 255.0);
    setObjectCoords();
	glEnd();
}

Sn_ColorIdentifier Sn_StandardGem::getColor()
{
	return m_color;
}

void Sn_StandardGem::setColor(const Sn_ColorIdentifier& newCol)
{
	m_color = newCol;
}

void Sn_StandardGem::setObjectCoords()
{
    glVertex2f(m_xLoc, m_yLoc);
    glVertex2f(m_xLoc, m_yLoc + m_sizeY);
    glVertex2f(m_xLoc + m_sizeX, m_yLoc + m_sizeY);
    glVertex2f(m_xLoc + m_sizeX, m_yLoc);
}

bool Sn_StandardGem::doMovement(double &elapsedTime)
{
    return false;
}

bool Sn_StandardGem::checkCollision(double &elapsedTime, Sn_Ball *ball)
{
    int val = 0;
    val += collisionSideHandling(elapsedTime, ball, Sn_Side::bot);
    val += collisionSideHandling(elapsedTime, ball, Sn_Side::top);
    val += collisionSideHandling(elapsedTime, ball, Sn_Side::left);
    val += collisionSideHandling(elapsedTime, ball, Sn_Side::right);
    
    if (val > 0)
        return true;
    else
        return false;
}

bool Sn_StandardGem::collisionSideHandling(double &elapsedTime, Sn_Ball *ball, Sn_Side heading)
{
    double desiredXCoord, desiredYCoord, timeReq;
    Sn_Vector nextSpeed, nextLoc;
    
    if (elapsedTime == 0.0)
        return false;
    switch (heading) {
        case Sn_Side::bot:
            if (ball->getLoc().y > m_yLoc)
                return false;
            desiredYCoord = m_yLoc - ball->getRadius();
            timeReq = (desiredYCoord - ball->getLoc().y) / ball->getSpeed().y;
            desiredXCoord = Sn_CommonMath::timeElapseCoord(ball->getSpeed().x, ball->getLoc().x, (desiredYCoord - ball->getLoc().y) / ball->getSpeed().y);
            
            if (desiredXCoord == Sn_CommonMath::clamp(m_xLoc, m_xLoc + m_sizeX, desiredXCoord))
            {
                /*
                if (timeReq > elapsedTime || timeReq < 0)
                    break;
                nextSpeed.x = ball->getSpeed().x;
                nextSpeed.y = -1.0 * ball->getSpeed().y;
                ball->setSpeed(nextSpeed);
                elapsedTime -= timeReq;
                return true;
                 */
                Sn_Vector vec;
                vec.x = desiredXCoord;
                vec.y = desiredYCoord;
                if (handleSideReflect(timeReq, ball, elapsedTime, heading, vec))
                    return true;
                else
                    break;
                    
            }
            if (desiredXCoord < m_xLoc && ball->getRadius() >= Sn_CommonMath::distanceToApproachmentVector(ball->getLoc(), getBottomLeftPoint(), ball->getSpeed()))
            {
                //if (timeReq > elapsedTime)
                    //break;
                auto time = Sn_CommonMath::findIntersectPointTime(ball->getLoc(), getBottomLeftPoint(), ball->getRadius(), ball->getSpeed());
                if (time > elapsedTime || time < 0)
                    break;
                else
                {
                    handleReflection(time, getBottomLeftPoint(), ball, elapsedTime);
                    return true;
                }
            }
            if (desiredXCoord > m_xLoc + m_sizeX && ball->getRadius() >= Sn_CommonMath::distanceToApproachmentVector(ball->getLoc(), getBottomRightPoint(), ball->getSpeed()))
            {
                //if (timeReq > elapsedTime)
                    //break;
                auto time = Sn_CommonMath::findIntersectPointTime(ball->getLoc(), getBottomRightPoint(), ball->getRadius(), ball->getSpeed());
                if (time < 0)
                    int dfgdfgdf = 0;
                if (time > elapsedTime || time < 0)
                    break;
                else
                {
                    handleReflection(time, getBottomRightPoint(), ball, elapsedTime);
                    return true;
                }
            }
            break;
        case Sn_Side::top:
            if (ball->getLoc().y < m_yLoc)
                return false;
            desiredYCoord = m_yLoc + m_sizeY + ball->getRadius();
            timeReq = (desiredYCoord - ball->getLoc().y) / ball->getSpeed().y;
            desiredXCoord = Sn_CommonMath::timeElapseCoord(ball->getSpeed().x, ball->getLoc().x, (desiredYCoord - ball->getLoc().y) / ball->getSpeed().y);
            
            if (desiredXCoord == Sn_CommonMath::clamp(m_xLoc, m_xLoc + m_sizeX, desiredXCoord))
            {
                /*
                if (timeReq > elapsedTime || timeReq < 0)
                    break;
                nextSpeed.x = ball->getSpeed().x;
                nextSpeed.y = -1.0 * ball->getSpeed().y;
                ball->setSpeed(nextSpeed);
                elapsedTime -= timeReq;
                return true;
                 */
                Sn_Vector vec;
                vec.x = desiredXCoord;
                vec.y = desiredYCoord;
                if (handleSideReflect(timeReq, ball, elapsedTime, heading, vec))
                    return true;
                else
                    break;
            }
            if (desiredXCoord < m_xLoc && ball->getRadius() >= Sn_CommonMath::distanceToApproachmentVector(ball->getLoc(), getTopLeftPoint(), ball->getSpeed()))
            {
                //if (timeReq > elapsedTime)
                    //break;
                auto time = Sn_CommonMath::findIntersectPointTime(ball->getLoc(), getTopLeftPoint(), ball->getRadius(), ball->getSpeed());
                if (time > elapsedTime || time < 0)
                    break;
                else
                {
                    handleReflection(time, getTopLeftPoint(), ball, elapsedTime);
                    return true;
                }
            }
            if (desiredXCoord > m_xLoc + m_sizeX && ball->getRadius() >= Sn_CommonMath::distanceToApproachmentVector(ball->getLoc(), getTopRightPoint(), ball->getSpeed()))
            {
                //if (timeReq > elapsedTime)
                    //break;
                auto time = Sn_CommonMath::findIntersectPointTime(ball->getLoc(), getTopRightPoint(), ball->getRadius(), ball->getSpeed());
                if (time > elapsedTime || time < 0)
                    break;
                else
                {
                    handleReflection(time, getTopRightPoint(), ball, elapsedTime);
                    return true;
                }
            }
            break;
        case Sn_Side::left:
            if (ball->getLoc().x > m_xLoc)
                return false;
            desiredXCoord = m_xLoc - ball->getRadius();
            timeReq = (desiredXCoord - ball->getLoc().x) / ball->getSpeed().x;
            desiredYCoord = Sn_CommonMath::timeElapseCoord(ball->getSpeed().y, ball->getLoc().y, (desiredXCoord - ball->getLoc().x) / ball->getSpeed().x);
            
            if (desiredYCoord == Sn_CommonMath::clamp(m_yLoc, m_yLoc + m_sizeY, desiredYCoord))
            {
                Sn_Vector vec;
                vec.x = desiredXCoord;
                vec.y = desiredYCoord;
                if (handleSideReflect(timeReq, ball, elapsedTime, heading, vec))
                    return true;
                else
                    break;
            }
            if (desiredYCoord < m_yLoc && ball->getRadius() >= Sn_CommonMath::distanceToApproachmentVector(ball->getLoc(), getBottomLeftPoint(), ball->getSpeed()))
            {
                //if (timeReq > elapsedTime)
                    //break;
                auto time = Sn_CommonMath::findIntersectPointTime(ball->getLoc(), getBottomLeftPoint(), ball->getRadius(), ball->getSpeed());
                if (time > elapsedTime || time < 0)
                    break;
                else
                {
                    handleReflection(time, getBottomLeftPoint(), ball, elapsedTime);
                    return true;
                }
            }
            if (desiredYCoord > m_yLoc + m_sizeY && ball->getRadius() >= Sn_CommonMath::distanceToApproachmentVector(ball->getLoc(), getTopLeftPoint(), ball->getSpeed()))
            {
                //if (timeReq > elapsedTime)
                    //break;
                auto time = Sn_CommonMath::findIntersectPointTime(ball->getLoc(), getTopLeftPoint(), ball->getRadius(), ball->getSpeed());
                if (time > elapsedTime || time < 0)
                    break;
                else
                {
                    handleReflection(time, getTopLeftPoint(), ball, elapsedTime);
                    return true;
                }
            }
            break;
        
        case Sn_Side::right:
            if (ball->getLoc().x < m_xLoc)
                return false;
            desiredXCoord = m_xLoc + m_sizeX + ball->getRadius();
            timeReq = (desiredXCoord - ball->getLoc().x) / ball->getSpeed().x;
            desiredYCoord = Sn_CommonMath::timeElapseCoord(ball->getSpeed().y, ball->getLoc().y, (desiredXCoord - ball->getLoc().x) / ball->getSpeed().x);
            
            if (desiredYCoord == Sn_CommonMath::clamp(m_yLoc, m_yLoc + m_sizeY, desiredYCoord))
            {
                Sn_Vector vec;
                vec.x = desiredXCoord;
                vec.y = desiredYCoord;
                if (handleSideReflect(timeReq, ball, elapsedTime, heading, vec))
                    return true;
                else
                    break;
            }
            if (desiredYCoord < m_yLoc && ball->getRadius() >= Sn_CommonMath::distanceToApproachmentVector(ball->getLoc(), getBottomRightPoint(), ball->getSpeed()))
            {
                //if (timeReq > elapsedTime)
                    //break;
                auto time = Sn_CommonMath::findIntersectPointTime(ball->getLoc(), getBottomRightPoint(), ball->getRadius(), ball->getSpeed());
                if (time > elapsedTime || time < 0)
                    break;
                else
                {
                    handleReflection(time, getBottomRightPoint(), ball, elapsedTime);
                    return true;
                }
            }
            if (desiredYCoord > m_yLoc + m_sizeY && ball->getRadius() >= Sn_CommonMath::distanceToApproachmentVector(ball->getLoc(), getTopRightPoint(), ball->getSpeed()))
            {
                //if (timeReq > elapsedTime)
                    //break;
                auto time = Sn_CommonMath::findIntersectPointTime(ball->getLoc(), getTopRightPoint(), ball->getRadius(), ball->getSpeed());
                if (time > elapsedTime || time < 0)
                    break;
                else
                {
                    handleReflection(time, getTopRightPoint(), ball, elapsedTime);
                    return true;
                }
            }
            break;
        default:
            break;
    }
    
    return false;
}

void Sn_StandardGem::handleReflection(double time, const Sn_Vector &pointCoords, Sn_Ball *ball, double &elapsedTime)
{
    Sn_Vector nextLoc, centreVec;
    auto realXCoord = ball->getLoc().x + ball->getSpeed().x * time;
    auto realYCoord = ball->getLoc().y + ball->getSpeed().y * time;
    nextLoc.x = realXCoord;
    nextLoc.y = realYCoord;
    centreVec.x = realXCoord - pointCoords.x;
    centreVec.y = realYCoord - pointCoords.y;
    auto normal = Sn_CommonMath::getNormal(centreVec);
    auto nextSpeed = Sn_CommonMath::refractionVector(normal, ball->getSpeed());
    ball->setSpeed(nextSpeed);
    elapsedTime -= time;
    ball->setLoc(nextLoc);
}

bool Sn_StandardGem::handleSideReflect(double timeReq, Sn_Ball *ball, double &elapsedTime, Sn_Side side, const Sn_Vector &vecLoc)
{
    Sn_Vector nextSpeed;
    if (timeReq > elapsedTime || timeReq < 0)
        return false;
    if (side == Sn_Side::top || side == Sn_Side::bot)
        nextSpeed.y = -1.0 * ball->getSpeed().y;
    else
        nextSpeed.y = ball->getSpeed().y;
    
    if (side == Sn_Side::left || side == Sn_Side::right)
        nextSpeed.x = -1.0 * ball->getSpeed().x;
    else
        nextSpeed.x = ball->getSpeed().x;
    
    ball->setSpeed(nextSpeed);
    ball->setLoc(vecLoc);
    elapsedTime -= timeReq;
    return true;
}

Sn_Vector Sn_StandardGem::getBottomLeftPoint()
{
    Sn_Vector val;
    val.x = m_xLoc;
    val.y = m_yLoc;
    return val;
}

Sn_Vector Sn_StandardGem::getTopLeftPoint()
{
    Sn_Vector val;
    val.x = m_xLoc;
    val.y = m_yLoc + m_sizeY;
    return val;
}

Sn_Vector Sn_StandardGem::getBottomRightPoint()
{
    Sn_Vector val;
    val.x = m_xLoc + m_sizeX;
    val.y = m_yLoc;
    return val;
}

Sn_Vector Sn_StandardGem::getTopRightPoint()
{
    Sn_Vector val;
    val.x = m_xLoc + m_sizeX;
    val.y = m_yLoc + m_sizeY;
    return val;
}

void Sn_StandardGem::loseLife()
{
    if (m_isIndestructible)
        return;
    m_livesRemaining--;
}

int Sn_StandardGem::getLives()
{
    return m_livesRemaining;
}

void Sn_StandardGem::setIndestructible(bool stat)
{
    m_isIndestructible = stat;
}

void Sn_StandardGem::setBonus(Sn_BonusAttribute bonus)
{
    m_bonusAttr = bonus;
}

Sn_BonusAttribute Sn_StandardGem::getBonusType()
{
    return m_bonusAttr;
}

void Sn_StandardGem::setSpeedUp(bool status)
{
    m_speedupBall = status;
}

bool Sn_StandardGem::getSpeedUp()
{
    return m_speedupBall;
}
