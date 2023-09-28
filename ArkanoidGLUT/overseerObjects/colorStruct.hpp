//
//  colorMap.hpp
//  ArkanoidGLUT
//
//  Created by Никита Шабанов on 26.09.2023.
//

#ifndef colorMap_hpp
#define colorMap_hpp

#include <map>

enum Sn_BonusAttribute {
    nobonus,
    cartResize,
    ballSpeedup,
    stickBall,
    bottomOneUse,
    randomProjectoryChange
};

enum Sn_ColorIdentifier {
    redRGB,
    blueRGB,
    greenRGB,
    tealRGB,
    crimsonRGB,
    purpleRGB
};

struct Sn_RGBColor {
    int redRGB;
    int greenRGB;
    int blueRGB;
};

#endif /* colorMap_hpp */
