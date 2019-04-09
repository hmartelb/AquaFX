#pragma once

#include "ofMain.h"
#include "ofxKinectCommonBridge.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


		ofxOscSender sender;

		ofxKinectCommonBridge kinect;

		//To load and store images
		ofImage headImage, LAimage, RAimage, LHimage,RHimage, Bodyimage,LLimage,RLimage,LHipimage,RHipimage,LFimage,RFimage;

		//Points where the image will be centered
		ofPoint LAPosition,RAPosition,LHPosition,RHPosition,BodyPosition,LLPosition,RLPosition,LHipPosition,RHipPosition,LFPosition,RFPosition, neckPosition;

		//Points of the skeleton (not the positions where the center of the image will be
		ofPoint LSPoint, RSPoint, CSPoint, RWPoint, LWPoint, LEPoint, REPoint, SPoint, HPoint, LHPoint, RHPoint, LKPoint, RKPoint, LAPoint, RAPoint, LFPoint, RFPoint, headPoint;

		int brazada, salida, degree;

		float headRotation,LARotation,RARotation,LHRotation,RHRotation,BodyRotation,LLRotation,RLRotation,LHipRotation,RHipRotation,LFRotation,RFRotation;

		float leftstroke, rightstroke, timestroke;

		bool luigi;

		float velocityL, velocityR, lastwristheightL, lastwristheightR, alturacabezaizq, alturacabezader, brazosjuntos, ceremoniaizq, ceremoniader;
};
