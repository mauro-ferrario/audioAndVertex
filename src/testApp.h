#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxUI.h"

#define PORT 9997

class testApp : public ofBaseApp{
	public:
		void                    setup();
		void                    update();
		void                    draw();
		void                    keyPressed(int key);
		void                    keyReleased(int key);
        void                    audioIn(float * input, int bufferSize, int nChannels);     
        void                    loadModel(string ind);
        void                    setupAudio();
        void                    guiEvent(ofxUIEventArgs &e);
        void                    initGUI();
        
        ofxUICanvas*            gui;
        ofxAssimpModelLoader    model;
        ofEasyCam               cam;
	
        vector <float>          left;
        vector <float>          right;
    
        float                   smoothedVol;
        float                   scaledVol;    
        ofSoundStream           soundStream;
    
        ofColor                 backgroundColor;
        ofColor                 lineColor;

        float                   volumLevelInvertColor;
        int                     invertColor;
        int                     target;
    
        vector<ofVec3f>         verts;
        vector<ofVec3f>         targetVertex;
        vector<ofVec3f>         vectors;
    
        float                   spring;
        float                   friction;
        float                   force;
        float                   lineDistance;
        float                   liquidnessCoeff;
        float                   amplitudeCoeff;
        float                   speedDampenCoeff;
        bool                    activeDefaultMovement;
        bool                    activeAudioReaction;
};
