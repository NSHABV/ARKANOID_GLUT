//
//  physicsObject.hpp
//  ArkanoidGLUT
//
//  Created by Никита Шабанов on 26.09.2023.
//

#ifndef physicsObject_hpp
#define physicsObject_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "colorStruct.hpp"
#include "commonMath.hpp"

enum Sn_Side
{
    left,
    right,
    top,
    bot
};

class Sn_PhysicsObject {
public:
    Sn_PhysicsObject();

    virtual void draw(const std::map<Sn_ColorIdentifier, Sn_RGBColor> &colorMap);

    virtual Sn_ColorIdentifier getColor();
    virtual void setColor(const Sn_ColorIdentifier& newCol);
    
    virtual bool doMovement(double &elapsedTime);
protected:
    virtual void setObjectCoords();
    
    double m_xLoc;
    double m_yLoc;

    double m_sizeX;
    double m_sizeY;
    
    Sn_ColorIdentifier m_color;
    Sn_Vector m_speedVector;
};


#endif /* physicsObject_hpp */
