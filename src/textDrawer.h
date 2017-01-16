//
//  textDrawer.hpp
//  manifesto
//
//  Created by Kenneth Lim on 04/05/2016.
//
//

#pragma once

#include "ofMain.h"
#include <tuple>

class textDrawer {
public:
    void setup();
    void update(float fontVolume);
    void draw();
    enum fontStates {H1, H2, H3, H4};
    
private:
    ofBuffer manifestoText;
    vector<string> manifestoLines;
    vector< vector< tuple<string, fontStates, bool> > > manifestoWords;
    vector<fontStates> manifestoStates;
    pair<int, int> manifestoPointer = make_pair(0, 0);
    
    
    fontStates currFontState;
    
    float fontSize;
    ofTrueTypeFont fontH1;
    ofTrueTypeFont fontH2;
    ofTrueTypeFont fontH3;
    ofTrueTypeFont fontH4;
    
    float multiplier = 0;
    float textHeight;
};
