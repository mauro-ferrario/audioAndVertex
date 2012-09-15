#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    backgroundColor = 0;
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofBackground(backgroundColor);
    
    lineColor = backgroundColor;
    lineColor.invert();
    lineColor.a = 10;
    
    invertColor = 0;
    target = 0;
    
    spring = .01;
    friction = .95;
    force = 1;
    lineDistance = 5;
    activeDefaultMovement = false;
    activeAudioReaction = true;
    volumLevelInvertColor = .9;
    
    liquidnessCoeff = 100;
    amplitudeCoeff = .1;
    speedDampenCoeff = .5;
    
    this->loadModel("sphere.dae");
    this->setupAudio();
    this->initGUI();
}

void testApp::initGUI()
{
    gui = new ofxUICanvas(); 
    gui->setFont("GUI/MEMORIA_.ttf");
    gui->setFontSize(OFX_UI_FONT_SMALL, 4);
    gui->addWidgetDown(new ofxUILabel("Arrow up and down for change shape", OFX_UI_FONT_SMALL )); 
    gui->addWidgetDown(new ofxUILabel("Press 'g' to hide/show GUI", OFX_UI_FONT_SMALL )); 
    gui->addWidgetDown(new ofxUILabel("Press 'f' to enter in fullscreen mode", OFX_UI_FONT_SMALL )); 
    
    
    gui->addWidgetDown(new ofxUISpacer(0, 0, 100, 1));
	gui->addWidgetDown(new ofxUILabel("Movement", OFX_UI_FONT_SMALL )); 
    gui->addWidgetDown(new ofxUISlider(310, 20, 100, 10, 0.00, 1.00, .01, "Spring"));
    gui->addWidgetDown(new ofxUISlider(310, 60, 100, 10, 0.00, 1.00, .95, "Friction"));
    
    gui->addWidgetDown(new ofxUISpacer(0, 0, 100, 1));
    gui->addWidgetDown(new ofxUIToggle(810, 20, 10, 10, false, "Default movement"));
    gui->addWidgetDown(new ofxUISlider(310, 20, 100, 10, 0.00, 200.00, 100, "Liquidness coeff"));
    gui->addWidgetDown(new ofxUISlider(310, 60, 100, 10, 0.00, 1.00, .10, "Amplitude coeff"));
    gui->addWidgetDown(new ofxUISlider(310, 60, 100, 10, 0.00, 1.00, .5, "Speed dampen coeff"));
    gui->addWidgetDown(new ofxUISpacer(0, 0, 100, 1));
    gui->addWidgetDown(new ofxUIToggle(810, 20, 10, 10, true, "Audio reaction"));
    gui->addWidgetDown(new ofxUISlider(310, 100, 100, 10, 0.0, 10.0, 1.0, "Repulsion force"));

    gui->addWidgetDown(new ofxUISpacer(0, 0, 100, 1));
    gui->addWidgetDown(new ofxUILabel("Effects", OFX_UI_FONT_SMALL )); 
    gui->addWidgetDown(new ofxUISlider(310, 20, 100, 10, 0.00, 1.00, .90, "Volume level reverse color"));
    gui->addWidgetDown(new ofxUISlider(310, 20, 100, 10, 0, 100, 50, "Distance line"));
    gui->addWidgetDown(new ofxUIToggle(810, 20, 10, 10, false, "Invert color"));
    gui->addWidgetDown(new ofxUIFPS(OFX_UI_FONT_SMALL)); 
    
    
    ofColor fillColor;
    
    fillColor.r = 255;
    fillColor.g = 255;
    fillColor.b = 0;
    fillColor.a = 200;
    
    gui->setColorBack(fillColor);
    
    fillColor.r = 227;
    fillColor.g = 59;
    fillColor.b = 2;
    
    gui->setWidgetColor(OFX_UI_WIDGET_COLOR_FILL, fillColor);
    gui->setWidgetColor(OFX_UI_WIDGET_COLOR_FILL_HIGHLIGHT, fillColor);
    
    fillColor.r = 50;
    fillColor.g = 50;
    fillColor.b = 50;
    gui->setWidgetColor(OFX_UI_WIDGET_COLOR_BACK, fillColor);
    gui->setWidgetColor(OFX_UI_WIDGET_COLOR_OUTLINE, fillColor);
    
    fillColor.r = 255;
    fillColor.g = 255;
    fillColor.b = 255;
    fillColor.a = 0;
    
    gui->setWidgetColor(OFX_UI_WIDGET_COLOR_OUTLINE_HIGHLIGHT, fillColor);
//  gui->loadSettings("GUI/guiSettings.xml");
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
}

void testApp::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	
    if(name == "Spring")
	{
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
       spring = slider->getScaledValue();          
	}
    if(name == "Friction")
	{
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        friction = slider->getScaledValue();          
	}
    if(name == "Repulsion force")
	{
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        force = slider->getScaledValue();          
	}
    if(name == "Distance line")
	{
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        lineDistance = slider->getScaledValue();          
	}
    if(name == "Default movement")
	{
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
		activeDefaultMovement = toggle->getValue();
	}
    if(name == "Audio reaction")
	{
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
		activeAudioReaction = toggle->getValue();
	}
    if(name == "Invert color")
    {
        backgroundColor.invert();
        lineColor.invert();
    }
    if(name == "Volume level reverse color")
	{
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        volumLevelInvertColor = slider->getScaledValue();          
	}
    if(name == "Liquidness coeff")
	{
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        liquidnessCoeff = slider->getScaledValue();          
	}
    if(name == "Amplitude coeff")
	{
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        amplitudeCoeff = slider->getScaledValue();          
	}
    if(name == "Speed dampen coeff")
	{
        ofxUISlider *slider = (ofxUISlider *) e.widget; 
        speedDampenCoeff = slider->getScaledValue();          
	}
}

void testApp::setupAudio()
{
    int bufferSize = 256;
	
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
    
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
}

void testApp::loadModel(string ind)
{
    model.loadModel(ind);
    ofVboMesh mesh = model.getMesh(0);
    verts = mesh.getVertices();
    targetVertex = mesh.getVertices();
    
    for(int a = 0; a < verts.size(); a++)
        vectors.push_back(0);
}

//--------------------------------------------------------------
void testApp::update(){
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
    if(scaledVol >= volumLevelInvertColor && invertColor <= 0)
    {
        invertColor = 20;
        backgroundColor.invert();
        lineColor.invert();
    }   
    
    for(int i = 0; i < verts.size(); i++)
    {            
        float liquidness = cos(vectors[i].x) * liquidnessCoeff;
        float amplitude =  amplitudeCoeff;
        float speedDampen = cos(vectors[i].z) * speedDampenCoeff;		
        
        if(activeDefaultMovement)
        {
            vectors[i].x += ofSignedNoise(verts[i].x/liquidness, verts[i].y/liquidness,verts[i].z/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
            vectors[i].y += ofSignedNoise(verts[i].z/liquidness, verts[i].x/liquidness,verts[i].y/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
            vectors[i].z += ofSignedNoise(verts[i].y/liquidness, verts[i].z/liquidness,verts[i].x/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
        }
            
        if(activeAudioReaction)
        {
            ofVec3f currentVertex;
            if(i < verts.size() * .5)
            {
                if(verts[i].x > 0)
                    vectors[i].x += left[ofMap(i, 0, verts.size() * .5, 0, 255)] * force;
                else
                    vectors[i].x -= left[ofMap(i, 0, verts.size() * .5, 0, 255)] * force;
                
                if(verts[i].y > 0)
                    vectors[i].y += left[ofMap(i, 0, verts.size() * .5, 0, 255)] * force;
                else
                    vectors[i].y -= left[ofMap(i, 0, verts.size() * .5, 0, 255)] * force;
                
                if(verts[i].z > 0)
                    vectors[i].z += left[ofMap(i, 0, verts.size() * .5, 0, 255)] * force;
                else
                    vectors[i].z -= left[ofMap(i, 0, verts.size() * .5, 0, 255)] * force;
            }
            else 
            {
                if(verts[i].x > 0)
                    vectors[i].x += right[ofMap(i, (verts.size() * .5) + 1, verts.size() - 1, 0, 255)] * force;
                else
                    vectors[i].x -= right[ofMap(i, (verts.size() * .5) + 1, verts.size() - 1, 0, 255)] * force;
                
                if(verts[i].y > 0)
                    vectors[i].y += right[ofMap(i, (verts.size() * .5) + 1, verts.size() - 1, 0, 255)] * force;
                else
                    vectors[i].y -= right[ofMap(i, (verts.size() * .5) + 1, verts.size() - 1, 0, 255)] * force;
                
                if(verts[i].z > 0)
                    vectors[i].z += right[ofMap(i, (verts.size() * .5) + 1, verts.size() - 1, 0, 255)] * force;
                else
                    vectors[i].z -= right[ofMap(i, (verts.size() * .5) + 1, verts.size() - 1, 0, 255)] * force;
            }
        }
        
        ofVec3f distance = targetVertex[i] - verts[i];
        ofVec3f acceleration = distance * spring;
        vectors[i] += acceleration;
        vectors[i] *= friction;
        verts[i] += vectors[i];        
    }    
    invertColor--;
}

void testApp::audioIn(float * input, int bufferSize, int nChannels){	
	float curVol = 0.0;
	int numCounted = 0;	
	for (int i = 0; i < bufferSize; i++){
		left[i]		=  abs(input[i*2]*0.5);
		right[i]	= abs(input[i*2+1]*0.5);
        
		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	curVol /= (float)numCounted;
	curVol = sqrt( curVol );
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
}

//--------------------------------------------------------------
void testApp::draw(){   
    ofBackground(backgroundColor); 
    cam.begin();    
    ofSetColor(lineColor);
    for(int i = 0; i < verts.size(); i++)
    {
        ofVec3f cur = verts[i];
        for(int a = 0; a < i; a++)
        {
            float distance = verts[a].distance(cur);
            if(distance < lineDistance)
                ofLine(cur, verts[a]);
        }
    }
    cam.end();    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    if(key == 'f')
        ofToggleFullscreen();
    if(key == 'g')
        gui->toggleVisible();
    
    if(key == OF_KEY_UP || key == OF_KEY_DOWN)
    {
        if(key == OF_KEY_UP)
        {
            target++;   
            if(target == 3) target = 0;
        }
        else {
            target--;
            if(target == -1) target = 2;
        }
        
        if(target == 0)
        {
            ofVboMesh mesh = model.getMesh(0);
            vector<ofVec3f> originalVertex = mesh.getVertices();
            for(int a = 0; a < verts.size(); a++)
                targetVertex[a] = originalVertex[a];
        }
        
        if(target == 1)
        {
            for(int a = 0; a < verts.size(); a++)
            {
                targetVertex[a].x = ofMap(a, 0, verts.size(), -2000, 2000);
                targetVertex[a].y = ofMap(a, 0, verts.size(), -300, 300);
                targetVertex[a].z = ofMap(a, 0, verts.size(), -300, 300);
            } 
        }
        
        if(target == 2)
        {
            for(int a = 0; a < verts.size(); a++)
            {
                targetVertex[a].x = cos(a) * 100;
                targetVertex[a].y = sin(a) * 100;
                targetVertex[a].z = sin(a) * ofRandom(0, 100);
            } 
        }
    }
}