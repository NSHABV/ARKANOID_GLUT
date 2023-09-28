//
//  bonusClass.hpp
//  ArkanoidGLUT
//
//  Created by Никита Шабанов on 28.09.2023.
//

#ifndef bonusClass_hpp
#define bonusClass_hpp

#include <stdio.h>
#include "careteClass.hpp"

class Sn_Bonus : public Sn_PhysicsObject
{
public:
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

#endif /* bonusClass_hpp */
