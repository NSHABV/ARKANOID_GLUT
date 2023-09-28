//
//  ballClass.hpp
//  ArkanoidGLUT
//
//  Created by Никита Шабанов on 26.09.2023.
//

#ifndef ballClass_hpp
#define ballClass_hpp

#include <stdio.h>
#include "physicsObject.hpp"


class Sn_Ball : public Sn_PhysicsObject
{
public:
    Sn_Ball();
    Sn_Ball(const Sn_Vector &position, const Sn_Vector &speed, double radius);
    
    virtual void draw(const std::map<Sn_ColorIdentifier, Sn_RGBColor> &colorMap) override;

    bool checkCollision(double elapsedTime);

    virtual Sn_ColorIdentifier getColor() override;
    virtual void setColor(const Sn_ColorIdentifier& newCol) override;
    
    virtual bool doMovement(double &elapsedTime) override;
    
    Sn_Vector getSpeed();
    Sn_Vector getLoc();
    double getRadius();
    void setSpeed(const Sn_Vector &vec);
    void setLoc(const Sn_Vector &vec);
    void ballSpeedUp();
    void setTrajectory(double angleAlpha);
    void setBottomOneUse(bool set);
    
    void setStuck(bool status);
    bool isStuck();
    
    void doStuckMovement(double movement);
    void archiveSpeed(bool active);
    int getBottomImpacts();
private:
    virtual void setObjectCoords() override;
    void drawBottom(const std::map<Sn_ColorIdentifier, Sn_RGBColor> &colorMap);
    double m_radius;
    
    int m_bottomImpacts = 0;
    
    bool m_bottomOneUse = false;
    bool m_stuck = false;
    
    Sn_Vector m_formerSpeed;
};

#endif /* ballClass_hpp */
