//
//  bonusClasses.hpp
//  ArkanoidGLUT
//
//  Created by Никита Шабанов on 28.09.2023.
//

#ifndef bonusClasses_hpp
#define bonusClasses_hpp

#include <stdio.h>
#include "careteClass.hpp"

class Sn_Bonus : public Sn_PhysicsObject
{
public:
    Sn_Bonus();
    Sn_Bonus(double xLoc, double yLoc);
    virtual bool doMovement(double &elapsedTime) override;
    
    virtual bool bonusCollision(Sn_Carete *carete, double elapsedTime);
    virtual Sn_BonusAttribute getBonusAttribute();
    
    virtual bool isGone();
private:
    virtual void setObjectCoords() override;
};

class Sn_CartResizeBonus : public Sn_Bonus
{
public:
    Sn_CartResizeBonus(double xLoc, double yLoc);
    
    virtual Sn_BonusAttribute getBonusAttribute() override;
};

class Sn_BallSpeedUpBonus : public Sn_Bonus
{
public:
    Sn_BallSpeedUpBonus(double xLoc, double yLoc);
    
    virtual Sn_BonusAttribute getBonusAttribute() override;
};

class Sn_StickBonus : public Sn_Bonus
{
public:
    Sn_StickBonus(double xLoc, double yLoc);
    
    virtual Sn_BonusAttribute getBonusAttribute() override;
};

class Sn_BottomOneBonus : public Sn_Bonus
{
public:
    Sn_BottomOneBonus(double xLoc, double yLoc);
    
    virtual Sn_BonusAttribute getBonusAttribute() override;
};

class Sn_RandomProjectoryChange : public Sn_Bonus
{
public:
    Sn_RandomProjectoryChange(double xLoc, double yLoc);
    
    virtual Sn_BonusAttribute getBonusAttribute() override;
};


#endif /* bonusClasses_hpp */
