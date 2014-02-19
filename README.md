ofxCameraMove
=====================================

Introduction
------------
C++ openFrameworks addon for moving easycam easyly


Licence
-------


Installation
------------
Copy to your openFrameworks/addons folder.


Dependencies
------------
folder of xml to live in(data/xml/)
ofxTweener
ofxXmlSettings

Compatibility
------------
openFrameworks 008 


Known issues
------------
Ofeasycam must be define start lunch.

MacOS:
Dial back the deployment target to 10.8 for ofxtweener to work. 
https://github.com/openframeworks/openFrameworks/pull/2764

Version history
------------
v_0_0_4
added camera continous rotator
press 'n' for new camera.
press 's' to save current view.
press ',' and '.' to cycle through cameras.
press 'q,w,e,r' to tween directly to view.

v_0_0_3
added enableSave and disableSave
change to 6 cameras

v_0_0_2
added string folder to setup
added check dir on startUp
added tweenType // not good must change when go more time but at else it backward compat

v_0_0_1
birth




