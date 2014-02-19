#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    
    saveCam.setup(&cam,"xml"); // add you ofeasycam and the folder where the xmls are
    //saveCam.enableSave(); // by defaul the listion is on you can actival with enableSave;
    //saveCam.disableSave(); // or disable key save wtih this
    
    saveCam.isSettingCam = false;//flag to display the press 'n' to save message.
    
}

//--------------------------------------------------------------
void testApp::update(){
    saveCam.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    cam.begin();
    ofRect(20, 20, 20, 20);
    cam.end();
    
    ofDrawBitmapString("Press 'q,w,e,r' to jump tween between cameras.\nPress 'n' for a new camera.\npress 's' to save cam positon to xml\nPress ',.' to continously cycle through cameras.\nYou'll need 'data/xml' folder.\n", 300,280);
    
    saveCam.information();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    
    if(key == 'q'){
        saveCam.tweenNow(0, 2); // first int is what camera to tween to , secound int is time
    }
    if(key == 'w'){
        saveCam.tweenNow(1, 3);
    }
    if(key == 'e'){
        saveCam.tweenNow(2, 2);
    }
    if(key == 'r'){
        saveCam.tweenNow(3, 2);
    }
    if(key == 't'){
        saveCam.tweenNow(4, 2);
    }
    if(key == 'b'){
        saveCam.cutNow((int)ofRandom(5));
    }
    
    //previous cam
    if(key == ','){
        saveCam.prevView();
    }
    
    //next cam
    if(key == '.'){
        saveCam.nextView(4.0);
    }
    
    //save view
    if(key == 's'){
        saveCam.updateView(-1);//-1= current view
    }
    
    //new cam view.
    if(key == 'n'){
        saveCam.newView();
    }
    
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    saveCam.isSettingCam = true;
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
	
}
