//
//  textDrawer.cpp
//  manifesto
//
//  Created by Kenneth Lim on 04/05/2016.
//
//

#include "textDrawer.h"

void textDrawer::setup(){
    // A two dimentional vector for storing the text in manifestoWords
    // in the form of manifestoWords[line number][word number]
    manifestoText = ofBufferFromFile("manifesto.txt");
    manifestoLines = ofSplitString(manifestoText, "\n");
    for (auto& line: manifestoLines){
        vector<string> wordsInLine = ofSplitString(line, " ");
        
        vector< tuple<string, fontStates, bool> > manifestoWordTuple;
        for (auto& word: wordsInLine){
            manifestoWordTuple.push_back(make_tuple(word, H4, false));
        }

        manifestoWords.push_back(manifestoWordTuple);
    }
    
    fontH1.load("verdana.ttf", 48, true, true);
    fontH2.load("verdana.ttf", 24, true, true);
    fontH3.load("verdana.ttf", 18, true, true);
    fontH4.load("verdana.ttf", 14, true, true);
}



void textDrawer::update(float fontVolume){
    // With manifestoPointer we get the current word that we will render next.
    // Then we set its font size and set the render boolean to true so it renders in draw().
    // This should be where we control how often a new word is drawn.
    if(fontVolume > 15){
        get<1>(manifestoWords[manifestoPointer.first][manifestoPointer.second]) = H1;
    }else if(fontVolume > 10 && fontVolume <= 15){
        get<1>(manifestoWords[manifestoPointer.first][manifestoPointer.second]) = H2;
    }else if(fontVolume > 5 && fontVolume <= 10){
        get<1>(manifestoWords[manifestoPointer.first][manifestoPointer.second]) = H3;
    }else{
        get<1>(manifestoWords[manifestoPointer.first][manifestoPointer.second]) = H4;
    }
    get<2>(manifestoWords[manifestoPointer.first][manifestoPointer.second]) = true;
    
    if(!(manifestoPointer.first == manifestoWords.size()-1)){
        // increment the pointer
        if(manifestoPointer.second == manifestoWords[manifestoPointer.first].size()-1){
            manifestoPointer.first++;
            manifestoPointer.second = 0;

            if(textHeight > ofGetHeight()-140) {
                multiplier++;
            }
        }else{
            manifestoPointer.second++;
        }
    }
}


void textDrawer::draw(){
    ofSetColor(225);
    ofRectangle rect;
    float textWidth;
    textHeight = 0;

    ofPushMatrix();
    ofTranslate(0, -70 * multiplier);
    // for every line
    for (auto& line: manifestoWords){
        auto indexLine = &line - &manifestoWords[0];
        // for every word
        for (auto& word: line){
            auto indexWord = &word - &line[0];
            // if the word should be rendered
            if (get<2>(word) == true){
                // find out how big the word should be rendered
                switch(get<1>(word)){
                    // render the word and find out how big its bounding box is
                    case H1:
                        rect = fontH1.getStringBoundingBox(get<0>(word), 0, 0);
                        fontH1.drawString(get<0>(word), textWidth, textHeight);
                        break;
                    case H2:
                        rect = fontH2.getStringBoundingBox(get<0>(word), 0, 0);
                        fontH2.drawString(get<0>(word), textWidth, textHeight);
                        break;
                    case H3:
                        rect = fontH3.getStringBoundingBox(get<0>(word), 0, 0);
                        fontH3.drawString(get<0>(word), textWidth, textHeight);
                        break;
                    case H4:
                        rect = fontH4.getStringBoundingBox(get<0>(word), 0, 0);
                        fontH4.drawString(get<0>(word), textWidth, textHeight);
                        break;
                }
                
                // increase the existing width of the line of text once every word is drawn and spacing
                textWidth += rect.width + 15;
            }else{
                // Stop looping if there isn't anything more to render
                break;
            }
        }

        // the last line have fully rendered
        // reset the textWidth and increse the textHeight to go to the next line
        textWidth = 0;
        textHeight += 70;

        if(!(indexLine+1 == manifestoWords.size()) && !get<2>(manifestoWords[indexLine+1][0])){
            break;
        }
    }
    ofPopMatrix();
}






