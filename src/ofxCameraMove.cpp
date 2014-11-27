//
//  ofxCameraMove.cpp
//  emptyExample
//
//  Created by strimbob on 14/08/2013.
//
// 

#include "ofxCameraMove.h"

//--------------------------------------------------------------
ofxCameraMove::ofxCameraMove(){
    isSettingCam = false;// flag to tell if you're positioning a new cam.
    active = false;
    enableSave();
    
}

//--------------------------------------------------------------
void ofxCameraMove::setup(ofEasyCam *_cam,string folder) {
    cam = _cam;
    getNumberOfCamFormXML(folder);
    
    if(target.size()!=0){
    //cout << "viewCount.size(" << target.size() << "), " << "camSpinner:" << ofToString(camSpinner) << ",index:" << ofToString(abs(camSpinner) % target.size()) << endl;
    
    //goto the first cam.
    tweenNow(0, 2.0);
    }

}


//--------------------------------------------------------------
void  ofxCameraMove::getNumberOfCamFormXML(string folder){
    ofDirectory checkDir;
    checkDir.isDirectoryEmpty(folder);
    
    vector<string> xmlPath = loadString(folder);

    camSpinner = 0;// start at zero.
    cameras = xmlPath.size();
    
    
    for(int a = 0;a< xmlPath.size();a++){
        ofQuaternion startQuat;
        ofVec3f startPos;
        ofxXmlSettings XML;
        XML.loadFile(xmlPath[a]);
        
        startPos.set(ofVec3f(XML.getValue("camera:getGlobalPositionX", 0.0),
                             XML.getValue("camera:getGlobalPositionY",0.0),
                             XML.getValue("camera:getGlobalPositionZ",  0.0)));

        float angle =  XML.getValue("camera:angle", 0.0);
        float x =      XML.getValue("camera:x",  0.0);
        float y =      XML.getValue("camera:y",  0.0);
        float z =      XML.getValue("camera:z",  0.0);

        startQuat.makeRotate(angle, x,y,z);
        target.push_back(&camArray[a]);
        target[a]->setGlobalPosition(startPos);
        target[a]->setGlobalOrientation(startQuat);

    }
    if(xmlPath.size() != 0){
            //go to the first cam.
            cutNow(0); //doesn't seem to be working.
    }
}

//--------------------------------------------------------------
vector<string> ofxCameraMove::loadString(string folder){
    vector<string> stringTemp;
    ofDirectory dir;
    dir.listDir(folder);
    dir.sort();
    
    for(int i = 0; i < (int)dir.size(); i++){
        stringTemp.push_back(dir.getPath(i));
        //cout << " loading " << dir.getPath(i) << endl;
    }
    
    return stringTemp;
}


//--------------------------------------------------------------
void ofxCameraMove::loadXML(string file, int i, bool isNew){
    ofQuaternion startQuat;
    ofVec3f startPos;
    ofxXmlSettings XML;
    XML.loadFile(file);
    
    startPos.set(ofVec3f(XML.getValue("camera:getGlobalPositionX", 0.0),
                         XML.getValue("camera:getGlobalPositionY",0.0),
                         XML.getValue("camera:getGlobalPositionZ",  0.0)));
    
    float angle =  XML.getValue("camera:angle", 0.0);
    float x =      XML.getValue("camera:x",  0.0);
    float y =      XML.getValue("camera:y",  0.0);
    float z =      XML.getValue("camera:z",  0.0);
    
    startQuat.makeRotate(angle, x,y,z);
    if(isNew){
        target.push_back(&camArray[i]);
    }
    target[i]->setGlobalPosition(startPos);
    target[i]->setGlobalOrientation(startQuat);
    

}

//--------------------------------------------------------------
void ofxCameraMove::update(){
    Tweener.update();
    if(start != pre){
        float tweenvalue = ofMap (start,0,1,0.,1.,true);
        ofQuaternion tweenedCameraQuaternion;
        tweenedCameraQuaternion.slerp(tweenvalue, startQuat, targetQuat);
        ofVec3f lerpPos;
        lerpPos = startPos + ((targetPos-startPos) * tweenvalue);
        cam->setOrientation(tweenedCameraQuaternion);
        cam->setGlobalPosition(lerpPos);
        pre = start;
    }
    
}

//--------------------------------------------------------------
void ofxCameraMove::information(){
    //message stuff
    ofDrawBitmapString("Continuous Rotator:"+ ofToString(camSpinner),10,10);
    ofDrawBitmapString("<vector> ViewCount:"+ ofToString(target.size()),10,22);
    ofDrawBitmapString("Currently Selected:"+ ofToString(currentIdx),10,34);
    
    //notify if you are positioning Cam and need to save.
    if(isSettingCam){
        ofDrawBitmapString("Press 'n' to add a new camera.", 10, ofGetHeight()-20);
    }
}


//--------------------------------------------------------------
void ofxCameraMove::tweenNow(int cameraNumber,float time) {
    if(target.size()!=0){
        if(cameraNumber < target.size()){
            startPos.set(cam->getGlobalPosition());
            whater = cam->getOrientationQuat() ;
            float angle;
            float xa;
            float ya;
            float za;
            whater.getRotate(angle, xa,ya,za);
            startQuat.makeRotate(angle, xa,ya,za);
            targetPos.set(target[cameraNumber]->getGlobalPosition());
            targetQu = target[cameraNumber]->getOrientationQuat() ;
            
            float angleEnd;
            float x;
            float y;
            float z;
            targetQu.getRotate(angleEnd, x,y,z);
            targetQuat.makeRotate(angleEnd, x,y,z);
            start = 0;
            end = 1;
            if(tweenType == 0){
            Tweener.addTween(start, end, time,&ofxTransitions::easeOutExpo);
            }
            if(tweenType == 1){
              Tweener.addTween(start, end, time,&ofxTransitions::easeInOutExpo);
                
            }
        }
    }

}
//--------------------------------------------------------------
void ofxCameraMove::cutNow(int cameraNumber){
    if(cameraNumber<target.size()){
    cam->setGlobalOrientation(target[cameraNumber]->getOrientationQuat());
    cam->setGlobalPosition(target[cameraNumber]->getGlobalPosition());
    }
} 

//--------------------------------------------------------------
void ofxCameraMove::keyPressed(ofKeyEventArgs &args) {

    //20140621 TAKEN OUT - accidentally hitting this and messing things up.
    //Perhaps I take this out later.
    /*
    if(args.key =='1'){
        updateView(0);
    }
    if(args.key =='2'){
        updateView(1);
    }
    if(args.key =='3'){
        updateView(2);
    }
    if(args.key =='4'){
        updateView(3);
    }
    if(args.key =='5'){
        updateView(4);
    }
    if(args.key =='6'){
        updateView(5);
    }
    if(args.key =='7'){
        updateView(6);
    }
    if(args.key =='8'){
        updateView(7);
    }
    if(args.key =='9'){
        updateView(8);
    }
     */
}

//--------------------------------------------------------------
void ofxCameraMove::newView(){

    string newFile = saveView(target.size());

    //load new xml
    loadXML(newFile, target.size(), true);
    
    //keeping track of how many cameras
    ++cameras;
    
    //set the indexes
    camSpinner = target.size()-1;
    currentIdx = target.size()-1;//reset to base cam.

    //cout << "NEW Camera View: " + ofToString(target.size()) << endl;
    //cout << "viewCount.size(" << target.size() << "), " << "camSpinner:" << ofToString(camSpinner) << ",index:" << ofToString(target.size()-1) << endl;
    
    isSettingCam = false;// turn off on-screen reminder to save.
}

//--------------------------------------------------------------
void ofxCameraMove::updateView(int _idx){
    if(target.size()!=0){
        
        if(_idx == -1){
            string newFile = saveView(currentIdx);
            //update existing xml
            loadXML(newFile, currentIdx, false);
            
            //set the indexes
            camSpinner = currentIdx;
            
            //cout << "viewCount.size(" << target.size() << "), " << "camSpinner:" << ofToString(camSpinner) << ",index:" << ofToString(currentIdx) << endl;
        } else {
            if(_idx < target.size()){
                string newFile = saveView(_idx);
                loadXML(newFile, _idx, false);
            }
        }

    }
}


//--------------------------------------------------------------
string ofxCameraMove::saveView(int camNum){

    ofxXmlSettings XML;

    ofQuaternion startQuat;
    ofQuaternion targetQuat;
    ofVec3f startPos;
    ofVec3f targetPos;
    ofQuaternion whater;
    startPos.set(cam->getGlobalPosition());
    whater = cam->getOrientationQuat() ;
    float angle;
    float xb;
    float yb;
    float zb;
    whater.getRotate(angle, xb,yb,zb);
    startQuat.makeRotate(angle, xb,yb,zb);
    XML.setValue("camera:angle", angle);
    XML.setValue("camera:x",  xb);
    XML.setValue("camera:y",  yb);
    XML.setValue("camera:z",  zb);
    XML.setValue("camera:getGlobalPositionX",  cam->getGlobalPosition().x);
    XML.setValue("camera:getGlobalPositionY",  cam->getGlobalPosition().y);
    XML.setValue("camera:getGlobalPositionZ",  cam->getGlobalPosition().z);
    XML.saveFile("xml/camera" + ofToString(camNum) + ".xml");

    return "xml/camera" + ofToString(camNum) + ".xml";

    //cout << "saved to xml/camera" + ofToString(camNum) + ".xml" << endl;
    
}

//RESET the view to 0
//--------------------------------------------------------------
void ofxCameraMove::zeroView(float time){
    if(target.size()!=0){
        camSpinner = 0;
        currentIdx = 0;
        cout << "viewCount.size(" << target.size() << "), " << "camSpinner:" << ofToString(camSpinner) << ",index:" << ofToString(abs(camSpinner) % target.size()) << endl;
        tweenNow(currentIdx, time);
        isSettingCam = false;
    }
}


//--------------------------------------------------------------
void ofxCameraMove::nextView(float time){
    if(target.size()!=0){
        ++camSpinner;
        cout << "viewCount.size(" << target.size() << "), " << "camSpinner:" << ofToString(camSpinner) << ",index:" << ofToString(abs(camSpinner) % target.size()) << endl;
        currentIdx = abs(camSpinner) % target.size();
        tweenNow(currentIdx, time);
        isSettingCam = false;
    }
}

//--------------------------------------------------------------
void ofxCameraMove::gotoSelectView(int index, float time){
    if(target.size()!=0){
        if(index < target.size()){
            currentIdx = index;
            tweenNow(currentIdx, time);
            isSettingCam = false;
        } else {
            cout << "there are only " << target.size() << " cameras." << endl;
        }
    }
}

//--------------------------------------------------------------
void ofxCameraMove::prevView(float time){
    if(target.size()!=0){
        --camSpinner;
        cout << "viewCount.size(" << target.size() << "), " << "camSpinner:" << ofToString(camSpinner) << ",index:" << ofToString(abs(camSpinner) % target.size()) << endl;
        currentIdx = abs(camSpinner) % target.size();
        tweenNow(currentIdx, time);
        isSettingCam = false;
    }
}

//--------------------------------------------------------------
void ofxCameraMove::setTweenType(int _tweenType){
    tweenType = _tweenType;
    
    
}
void ofxCameraMove::enableSave(){
    if(!active){
    ofAddListener(ofEvents().keyPressed, this, &ofxCameraMove::keyPressed);
        active = false;
    }
    
}

void ofxCameraMove::disableSave(){
        if(!active){
       ofRemoveListener(ofEvents().keyPressed, this, &ofxCameraMove::keyPressed);
            active = true;
        }
}


//--------------------------------------------------------------
ofxCameraMove::~ofxCameraMove(){
    disableSave();
}





