#pragma once

#include <array>
#include <random>
#include <ctime>
#include "colorStruct.hpp"
#include "gemsClass.h"
#include "ballClass.hpp"
#include "bonusClasses.hpp"

class Sn_GemContainer {
public:
	Sn_GemContainer(int xSize, int ySize, int gemSizeX, int gemSizeY);
	~Sn_GemContainer();

    void drawGems();
    
	int getXSize();
	int getYSize();

	void handleMouseClick(int x, int y);
	void handleRightMouseClick(int x, int y);

	void idleFunc();
    
    void moveLeft();
    void moveRight();
    
    void releaseBall();
    int calcScore();
private:
    void generateBonus(Sn_StandardGem *gem);
    void bonusesProcessing();
    void flingBall(const Sn_Vector &position, const Sn_Vector &speed);
    void generateColorMap();
    
    bool destructionCheck();
    void generateGems();
    
	double m_gemSizeX;
    double m_gemSizeY;

	int m_windowX;
	int m_windowY;

    std::vector<Sn_StandardGem*> m_gems;
    Sn_Ball* m_ball = nullptr;
	std::map<Sn_ColorIdentifier, Sn_RGBColor> m_colorTab;
    
    Sn_Carete *m_carete;
    
    std::vector<Sn_Bonus*> m_bonuses;

	std::mt19937 m_randomGen;
    
	int m_recentlyReshaped = false;
    
    void bonusesProcessing(Sn_BonusAttribute bonus);
    
    std::time_t m_lastTime;
    
    int m_score = 0;
};
