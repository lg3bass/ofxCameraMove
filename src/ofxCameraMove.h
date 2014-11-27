//
//  ofxCameraMove.h
//  emptyExample
//
//  Created by strimbob on 14/08/2013.
//
//

#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxTweener.h"

#define numberSaveFiles 20 // this is problem want to make is so a can set the array in code can you help!!???

class ofxCameraMove {
	
public:
    ofxCameraMove();
    ~ofxCameraMove();
	void setup(ofEasyCam *_cam,string folder);
    void update();    
    void tweenNow(int cameraNumber,float time);
    void cutNow(int cameraNumber);
    void getNumberOfCamFormXML(string folder);
    void loadXML(string file, int i, bool isNew);
    void keyPressed(ofKeyEventArgs &args);
    void setTweenType(int _tweenType); // not good how to change???
    vector<string> loadString(string path);
    void disableSave();
    void enableSave();
    void newView();
    void updateView(int _idx);
    string saveView(int camNum);
    bool isSettingCam;
    
    void zeroView(float time=2.0);
    void nextView(float time=2.0);
    void prevView(float time=2.0);
    void gotoSelectView(int index, float time=2.0);
    
    void information();
    
    float start;
    float end;
    float pre;
    
    int camSpinner; //neverending spinner of cams
    int cameras;
    int currentIdx;
    vector<int> viewCount;
    
    
private:
    bool active;
    int tweenType;
    
    //Why not a vector?
    ofEasyCam camArray[numberSaveFiles];
    vector<ofEasyCam *> target;
	ofEasyCam *cam;
    ofVec3f startPos;
    ofQuaternion startQuat;
    ofQuaternion targetQuat;
    ofQuaternion whater;
    ofQuaternion targetQu;
    ofVec3f targetPos;

};

