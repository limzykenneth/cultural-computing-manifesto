#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetCircleResolution(80);
    ofBackground(54, 54, 54);

    // 0 output channels,
    // 2 input channels
    // 44100 samples per second
    // 256 samples per buffer
    // 4 num buffers (latency)
    
    //if you want to set a different device id
    // soundStream.setDeviceID(1); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
    ofSoundStreamListDevices();
    
    int bufferSize = 256;
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(ofGetWidth()-20, 0.0);
    
    bufferCounter	= 0;
    drawCounter		= 0;
    smoothedVol     = 0.0;
    scaledVol		= 0.0;
    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);

    // setup object
    manifesto.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    //lets scale the vol up to a 0-1 range
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
    //lets record the volume into an array
    volHistory.push_back( scaledVol );
    
    //if we are bigger than the size we want to record - lets drop the oldest value
    // Potential memory leak here...
    if( volHistory.size() >= ofGetWidth()-20 ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }

    // Update the object info
    // When to update? Also control scaledVol to control the size input
    float fontVolume = scaledVol * 150;
    if(ofGetFrameNum()%24 == 0 && fontVolume > 15){
//        manifesto.update(fontVolume);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    float graphMaxHeight = ofGetHeight()-20;
    float graphMaxWidth = ofGetWidth()-20;
    
    ofNoFill();
    
    // draw the average volume: (Circle)
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(10, 10, 0);

    if(debugMode){
        ofSetColor(225);
        ofDrawBitmapString("Scaled average vol (0-100): " + ofToString(scaledVol * 100.0, 0), 4, 18);
        ofDrawRectangle(0, 0, graphMaxWidth, graphMaxHeight);
        
        ofDrawBitmapString("FPS: " + ofToString(floor(ofGetFrameRate())), ofGetWidth() - 200, 30);
        ofDrawBitmapString("Frame: " + ofToString(ofGetFrameNum()), ofGetWidth() - 200, 50);

        ofSetColor(245, 58, 135, 100);
        ofFill();
        ofDrawCircle(graphMaxWidth/2, graphMaxHeight/2, scaledVol * 400.0f);
    

        //lets draw the volume history as a graph
        ofBeginShape();
        for (unsigned int i = 0; i < volHistory.size(); i++){
            if( i == 0 ) ofVertex(i, graphMaxHeight);
            
            ofVertex(i, graphMaxHeight - volHistory[i] * graphMaxHeight/2);
            
            if( i == volHistory.size() - 1 ) ofVertex(i, graphMaxHeight);
        }
        ofEndShape(false);
    }
    
    // Draw the text
    ofTranslate(20, 60, 0);
//    manifesto.draw();
    
    ofPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
}

void ofApp::audioOut(float * input, int bufferSize, int nChannels){

//    float curVol = 0.0;
//
//    // samples are "interleaved"
//    int numCounted = 0;
//
//    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
//    for (int i = 0; i < bufferSize; i++){
//        left[i]		= input[i*2]*0.5;
//        right[i]	= input[i*2+1]*0.5;
//
//        curVol += left[i] * left[i];
//        curVol += right[i] * right[i];
//        numCounted+=2;
//    }
//
//    //this is how we get the mean of rms :)
//    curVol /= (float)numCounted;
//
//    // this is how we get the root of rms :)
//    curVol = sqrt( curVol );
//
//    smoothedVol *= 0.93;
//    smoothedVol += 0.07 * curVol;
//
//    bufferCounter++;
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    if( key == 's' ){
        soundStream.start();
    }
    
    if( key == 'e' ){
        soundStream.stop();
    }

    if(key == 'd'){
        debugMode = !debugMode;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    volHistory.assign(ofGetWidth()-20, 0.0);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

