#pragma once

#include <map>
#include "physicsObject.hpp"
#include "ballClass.hpp"

class Sn_StandardGem : public Sn_PhysicsObject {
public:
	Sn_StandardGem();
	Sn_StandardGem(double xLoc, double yLoc, double sizeX, double sizeY, const Sn_ColorIdentifier &col);

	virtual void draw(const std::map<Sn_ColorIdentifier, Sn_RGBColor> &colorMap) override;

    bool checkCollision(double &elapsedTime, Sn_Ball *ball);

    virtual Sn_ColorIdentifier getColor() override;
    virtual void setColor(const Sn_ColorIdentifier& newCol) override;
    
    virtual bool doMovement(double &elapsedTime) override;
    
    bool collisionSideHandling(double &elapsedTime, Sn_Ball *ball, Sn_Side heading);
    void loseLife();
    
    Sn_Vector getBottomLeftPoint();
    Sn_Vector getTopLeftPoint();
    Sn_Vector getBottomRightPoint();
    Sn_Vector getTopRightPoint();
    
    void setIndestructible(bool stat);
    int getLives();
    Sn_BonusAttribute getBonusType();
    void setBonus(Sn_BonusAttribute bonus);
protected:
    virtual void setObjectCoords() override;
    void handleReflection(double time, const Sn_Vector &pointCoords, Sn_Ball *ball, double &elapsedTime);
    bool handleSideReflect(double timeReq, Sn_Ball *ball, double &elapsedTime, Sn_Side side, const Sn_Vector &vecLoc);
    
    int m_livesRemaining;
    bool m_isIndestructible;
    Sn_BonusAttribute m_bonusAttr;
};
