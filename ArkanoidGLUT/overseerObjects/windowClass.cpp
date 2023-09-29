#include <algorithm>
#include <cstdint>
#include <iomanip>
#include "windowClass.h"

Sn_GemContainer::Sn_GemContainer(int xSize, int ySize, int gemSizeX, int gemSizeY) : m_windowX(xSize), m_windowY(ySize), m_gemSizeX(gemSizeX), m_gemSizeY(gemSizeY)
{
    Sn_Vector ballSpeed, ballPos;
    ballSpeed.x = 0.50;
    ballSpeed.y = 0.79;
    
    ballPos.x = 0.0;
    ballPos.y = -0.8;
    
    m_gemSizeX = 0.2;
    m_gemSizeY = 0.1;
    m_carete = new Sn_Carete();
    
	generateGems();
    flingBall(ballPos, ballSpeed);
	generateColorMap();
    m_lastTime = std::clock();
}

Sn_GemContainer::~Sn_GemContainer()
{
    auto size = m_gems.size();
	for (int i = 0; i < size; i++)
	{
		if (m_gems.at(i) != NULL)
			delete m_gems[i];
	}
    delete m_ball;
    delete m_carete;
    
    size = m_bonuses.size();
    for (int i = 0; i < size; i++)
    {
        if (m_bonuses.at(i) != NULL)
            delete m_bonuses[i];
    }
}

void Sn_GemContainer::generateColorMap()
{
	Sn_RGBColor teal = {0, 128, 128};
	Sn_RGBColor crimson = {157, 34, 53};
	Sn_RGBColor purple = {128, 0, 128};
	Sn_RGBColor red = {255, 0, 0};
	Sn_RGBColor blue = {0, 0, 255};
	Sn_RGBColor green = {0, 255, 0};

	m_colorTab.insert(std::make_pair(Sn_ColorIdentifier::tealRGB, teal));
	m_colorTab.insert(std::make_pair(Sn_ColorIdentifier::crimsonRGB, crimson));
	m_colorTab.insert(std::make_pair(Sn_ColorIdentifier::purpleRGB, purple));
	m_colorTab.insert(std::make_pair(Sn_ColorIdentifier::redRGB, red));
	m_colorTab.insert(std::make_pair(Sn_ColorIdentifier::blueRGB, blue));
	m_colorTab.insert(std::make_pair(Sn_ColorIdentifier::greenRGB, green));
}

void Sn_GemContainer::drawGems()
{
	for (int i = 0; i < m_gems.size(); i++)
	{
		if (m_gems[i])
			m_gems[i]->draw(m_colorTab);
	}
    m_ball->draw(m_colorTab);

    m_carete->draw(m_colorTab);
    
    for (auto bonus : m_bonuses)
    {
        bonus->draw(m_colorTab);
    }
}

bool Sn_GemContainer::destructionCheck()
{
    return false;
}

void Sn_GemContainer::generateGems()
{
    std::random_device device;
    m_randomGen.seed(device());
    std::uniform_int_distribution<int> invincibilityChance(0, 100);
    std::uniform_int_distribution<int> bonusChance(0, 100);
    
    for (int i = 0; i < 5; i++)
    {
        for (int a = 0; a < 5; a++)
        {
            auto y = -0.5 + i * 0.3;
            auto x = -0.9 + 0.4 * a;
            auto invincibilityRoll = invincibilityChance(m_randomGen);
            auto bonusRoll = bonusChance(m_randomGen);
            auto gemCreated = new Sn_StandardGem(x, y, m_gemSizeX, m_gemSizeY, Sn_ColorIdentifier::crimsonRGB);
            m_gems.push_back(gemCreated);
            if (invincibilityRoll > 80)
            {
                gemCreated->setIndestructible(true);
                gemCreated->setColor(Sn_ColorIdentifier::tealRGB);
            }
            if (invincibilityRoll < 81 && invincibilityRoll > 75)
                gemCreated->setSpeedUp(true);
            if (bonusRoll >= 80 && bonusRoll <= 83)
                gemCreated->setBonus(Sn_BonusAttribute::bottomOneUse);
            else if (bonusRoll >= 84 && bonusRoll <= 87)
                gemCreated->setBonus(Sn_BonusAttribute::ballSpeedup);
            else if (bonusRoll >= 88 && bonusRoll <= 91)
                gemCreated->setBonus(Sn_BonusAttribute::cartResize);
            else if (bonusRoll >= 92 && bonusRoll <= 95)
                gemCreated->setBonus(Sn_BonusAttribute::stickBall);
            else if (bonusRoll >= 96)
                gemCreated->setBonus(Sn_BonusAttribute::randomProjectoryChange);
        }
    }
}

void Sn_GemContainer::handleMouseClick(int x, int y)
{
	if (m_recentlyReshaped)
		return;

	m_recentlyReshaped = true;
}

void Sn_GemContainer::handleRightMouseClick(int x, int y)
{
	if (m_recentlyReshaped)
		return;
}

int Sn_GemContainer::getXSize()
{
	return m_windowX;
}

int Sn_GemContainer::getYSize()
{
	return m_windowY;
}

void Sn_GemContainer::idleFunc()
{
    auto nextTime = std::clock();
    auto timeDiff = nextTime - m_lastTime;
    double timeElapsedBonus = double(timeDiff) / double(CLOCKS_PER_SEC);
    auto ball = m_ball;
    
    double timeElapsed = double(timeDiff) / double(CLOCKS_PER_SEC);
    for (auto gemIter = m_gems.begin(); gemIter != m_gems.end();)
    {
        auto gem = *gemIter;
        if (!gem)
            continue;
        auto result = gem->checkCollision(timeElapsed, ball);
        if (result)
        {
            m_score++;
            gem->loseLife();
            if (gem->getSpeedUp())
                m_ball->ballSpeedUp();
        }
        if (timeElapsed < 0.0)
            timeElapsed = 0;
        if (gem->getLives() < 1)
        {
            generateBonus(gem);
            delete gem;
            gemIter = m_gems.erase(gemIter);
        }
        else
            gemIter++;
    }
    auto collisionResult = m_carete->checkCollision(timeElapsed, ball);
    if (m_carete->getSticky() && collisionResult)
    {
        Sn_Vector speed;
        speed.x = 0.0;
        speed.y = 0.0;
        ball->setStuck(true);
        ball->archiveSpeed(true);
    }
    
    ball->doMovement(timeElapsed);
    
    for (auto bonusIter = m_bonuses.begin(); bonusIter != m_bonuses.end();)
    {
        auto bonus = *bonusIter;
        if (bonus->isGone())
        {
            delete bonus;
            bonusIter = m_bonuses.erase(bonusIter);
            continue;
        }
        auto result = bonus->bonusCollision(m_carete, timeElapsedBonus);
        if (result)
        {
            bonusesProcessing(bonus->getBonusAttribute());
            delete bonus;
            bonusIter = m_bonuses.erase(bonusIter);
            continue;
        }
        else
            bonusIter++;
    }
    
    m_lastTime = nextTime;
}

void Sn_GemContainer::flingBall(const Sn_Vector &position, const Sn_Vector &speed)
{
    Sn_Ball* ball = new Sn_Ball(position, speed, 0.05);
    if (m_ball)
        delete m_ball;
    m_ball = ball;
}

void Sn_GemContainer::moveLeft()
{
    double mov = -0.1;
    m_carete->doMovement(mov, m_ball);
}

void Sn_GemContainer::moveRight()
{
    double mov = 0.1;
    m_carete->doMovement(mov, m_ball);
}

void Sn_GemContainer::bonusesProcessing(Sn_BonusAttribute bonus)
{
    std::random_device device;
    m_randomGen.seed(device());
    std::uniform_real_distribution<double> angleRange(0, 360.0);
    
    switch (bonus) {
        case Sn_BonusAttribute::nobonus:
            break;
        case Sn_BonusAttribute::cartResize:
            m_carete->resizeCart();
            break;
        case Sn_BonusAttribute::ballSpeedup:
            m_ball->ballSpeedUp();
            break;
        case Sn_BonusAttribute::stickBall:
            m_carete->setSticky(true);
            break;
        case Sn_BonusAttribute::bottomOneUse:
            m_ball->setBottomOneUse(true);
            break;
        case Sn_BonusAttribute::randomProjectoryChange:
            m_ball->setTrajectory(angleRange(m_randomGen));
            break;
        default:
            break;
    }
}

void Sn_GemContainer::releaseBall()
{
    if (m_ball->isStuck())
    {
        m_ball->archiveSpeed(false);
        m_ball->setStuck(false);
        double tSpeed = 0.0001;
        m_ball->doMovement(tSpeed);
        m_carete->setSticky(false);
    }
}

int Sn_GemContainer::calcScore()
{
    return m_score - m_ball->getBottomImpacts();
}

void Sn_GemContainer::generateBonus(Sn_StandardGem *gem)
{
    double bonusX = gem->getBottomLeftPoint().x + m_gemSizeX / 2.0;
    double bonusY = gem->getBottomLeftPoint().y;
    
    auto bonusType = gem->getBonusType();
    switch (bonusType) {
        case Sn_BonusAttribute::nobonus:
            break;
        case Sn_BonusAttribute::cartResize:
            m_bonuses.push_back(new Sn_CartResizeBonus(bonusX, bonusY));
            break;
        case Sn_BonusAttribute::ballSpeedup:
            m_bonuses.push_back(new Sn_BallSpeedUpBonus(bonusX, bonusY));
            break;
        case Sn_BonusAttribute::stickBall:
            m_bonuses.push_back(new Sn_StickBonus(bonusX, bonusY));
            break;
        case Sn_BonusAttribute::bottomOneUse:
            m_bonuses.push_back(new Sn_BottomOneBonus(bonusX, bonusY));
            break;
        case Sn_BonusAttribute::randomProjectoryChange:
            m_bonuses.push_back(new Sn_RandomProjectoryChange(bonusX, bonusY));
            break;
        default:
            break;
    }
}
