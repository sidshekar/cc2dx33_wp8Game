
#ifndef __wp8Game__ScrollingBgLayer__
#define __wp8Game__ScrollingBgLayer__

#include <iostream>
#include "ScrollingBg.h"

class ScrollingBgLayer: public Layer
{
public:
    ScrollingBgLayer(float speed);
    ~ScrollingBgLayer();
    
    ScrollingBg* hills;
    ScrollingBg* treesNbush;
	ScrollingBg* ground;
	ScrollingBg* grass;
    
    void update();
    


};

#endif /* defined(__endlessFlyer__ScrollingBgLayer__) */
