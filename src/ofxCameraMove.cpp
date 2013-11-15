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
    
ofAddListener(ofEvents().keyPressed, this, &ofxCameraMove::keyPressed);
    
}

//--------------------------------------------------------------
vector<string> ofxCameraMove::loadString(string path){
    
    vector<string> stringTemp;
    ofDirectory dir;
    dir.listDir(path);
    dir.sort();
    
    for(int i = 0; i < (int)dir.size(); i++){
        stringTemp.push_back(dir.getPath(i));
        
    }
    
    return stringTemp;
    
}
//--------------------------------------------------------------
void  ofxCameraMove::getNumberOfCamFormXML(){
    
    vector<string> xmlPath = loadString("xml");

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

            cutNow(0);
    }
}

//--------------------------------------------------------------
void ofxCameraMove::setup(ofEasyCam *_cam) {
    cam = _cam;    
    getNumberOfCamFormXML();

}

//--------------------------------------------------------------
void ofxCameraMove::tweenNow(int cameraNumber,float time) {

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
    Tweener.addTween(start, end, time,&ofxTransitions::easeOutExpo);
    
}
//--------------------------------------------------------------
void ofxCameraMove::cutNow(int cameraNumber){
    if(cameraNumber<target.size()){
    cam->setGlobalOrientation(target[cameraNumber]->getOrientationQuat());
    cam->setGlobalPosition(target[cameraNumber]->getGlobalPosition());
    }
    
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
void ofxCameraMove::keyPressed(ofKeyEventArgs &args) {

    cout << "listion " << " " << args.key << endl;
    ofxXmlSettings XML;
    
    if(args.key =='1'){
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
            XML.saveFile("xml/camera1.xml");
        }
    
    if(args.key =='2'){
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
        XML.saveFile("xml/camera2.xml");
    }
    
    
    if(args.key =='3'){
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
        XML.saveFile("xml/camera3.xml");
    }
    
}

//--------------------------------------------------------------
ofxCameraMove::~ofxCameraMove(){
    ofRemoveListener(ofEvents().keyPressed, this, &ofxCameraMove::keyPressed);
}





