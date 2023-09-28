//
//  commonMath.hpp
//  ArkanoidGLUT
//
//  Created by Никита Шабанов on 27.09.2023.
//

#ifndef commonMath_hpp
#define commonMath_hpp

#include <stdio.h>
#include <map>

struct Sn_Vector
{
    double x;
    double y;
};

class Sn_CommonMath {
public:
    Sn_CommonMath();
    
    static double clamp(double min, double max, double val)
    {
        if (val > max)
            return max;
        else if (val < min)
            return min;
        else
            return val;
    }
    
    static double signd(double val)
    {
        if (val > 0.0)
            return 1.0;
        else if (val < 0.0)
            return -1.0;
        else
            return 0.0;
    }
    
    static double findP(const Sn_Vector &pointBeginning, const Sn_Vector &movVec)
    {
        double t;
        //if (pointBeginning.y < 0)
            t = -1.0 * pointBeginning.y / movVec.y;
        //else
            //t = pointBeginning.y / movVec.y;
        
        return pointBeginning.x + movVec.x * t;
    }
    
    static double findIntersectPointTime(const Sn_Vector &pointBeginning, const Sn_Vector &centreCircle, double radius, const Sn_Vector &movVec)
    {
        //double p = pointBeginning.x - movVec.x * pointBeginning.y / movVec.y;
        double p = Sn_CommonMath::findP(pointBeginning, movVec);
        
        double constant = centreCircle.x * centreCircle.x + centreCircle.y * centreCircle.y - radius * radius - 2.0 * p * centreCircle.x + p * p;
        double ctangAlpha = movVec.x / movVec.y;
        
        double b = 2.0 * p * ctangAlpha - 2.0 * centreCircle.x * ctangAlpha - 2.0 * centreCircle.y;
        double a = 1.0 + ctangAlpha * ctangAlpha;
        double discr = b * b - 4 * a * constant;
        if (discr < 0.0)
            return -1.0;
        
        double val1 = -1.0 * b + sqrt(discr);
        val1 /= 2.0 * a;
        double val2 = -1.0 * b - sqrt(discr);
        val2 /= 2.0 * a;
        
        double time1 = val1 - pointBeginning.y;
        time1 /= movVec.y;
        double time2 = val2 - pointBeginning.y;
        time2 /= movVec.y;
        
        auto realTime = std::min(time1, time2);
        
        return realTime;
    }
    
    static double distanceToApproachmentVector(const Sn_Vector &pointBeginning, const Sn_Vector &centreCircle, const Sn_Vector &movVec)
    {
        double top = movVec.y * centreCircle.x - movVec.x * centreCircle.y;
        top += (pointBeginning.x + movVec.x) * pointBeginning.y;
        top -= (pointBeginning.y + movVec.y) * pointBeginning.x;
        top = fabs(top);
        
        double bot = sqrt(movVec.y * movVec.y + movVec.x * movVec.x);
        
        return top / bot;
    }
    
    static double timeToApproachementCoordinate(double speedAxis, double coordAxis, double curLoc)
    {
        return (coordAxis - curLoc) / speedAxis;
    }
    
    static double timeElapseCoord(double speedAxis, double coordAxis, double time)
    {
        return coordAxis + speedAxis * time;
    }
    
    static double scalarMultiplication(const Sn_Vector &vec, const Sn_Vector &other)
    {
        return vec.x * other.x + vec.y * other.y;
    }
    
    static Sn_Vector refractionVector(const Sn_Vector &normal, const Sn_Vector &origVec)
    {
        Sn_Vector vectr;
        vectr.x = origVec.x - 2 * scalarMultiplication(origVec, normal) * normal.x;
        vectr.y = origVec.y - 2 * scalarMultiplication(origVec, normal) * normal.y;
        
        return vectr;
    }
    
    static Sn_Vector getNormal(const Sn_Vector &vec)
    {
        Sn_Vector val;
        double size = sqrt(vec.x * vec.x + vec.y * vec.y);
        val.x = vec.x / size;
        val.y = vec.y / size;
        return val;
    }
};

#endif /* commonMath_hpp */
