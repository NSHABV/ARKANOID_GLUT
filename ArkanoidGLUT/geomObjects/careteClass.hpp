//
//  careteClass.hpp
//  ArkanoidGLUT
//
//  Created by Никита Шабанов on 24.09.2023.
//

#ifndef careteClass_hpp
#define careteClass_hpp

#include <map>
#include "physicsObject.hpp"
#include "ballClass.hpp"
#include "gemsClass.h"


class Sn_Carete : public Sn_StandardGem
{
public:
    Sn_Carete();
    
    virtual void draw(const std::map<Sn_ColorIdentifier, Sn_RGBColor> &colorMap) override;

    virtual Sn_ColorIdentifier getColor() override;
    virtual void setColor(const Sn_ColorIdentifier& newCol) override;
    
    virtual bool doMovement(double &elapsedTime) override;
    bool doMovement(double &elapsedTime, Sn_Ball *ball);
    
    void resizeCart();
    void setSticky(bool status);
    bool getSticky();
    double getLeftX();
private:
    virtual void setObjectCoords() override;
    double movementBallCollision(Sn_Ball *ball, double mov);
    
    bool m_isSticky = false;
};


#endif /* careteClass_hpp */
