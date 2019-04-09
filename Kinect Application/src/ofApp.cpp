#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	kinect.initSensor();
	//kinect.initIRStream(640, 480);
	kinect.initColorStream(640, 480, true);
	kinect.initDepthStream(640, 480, true);
	kinect.initSkeletonStream(false); // If true, track just upper part


	sender.setup(HOST, PORT);
	//simple start
	kinect.start();
	ofDisableAlphaBlending(); //Kinect alpha channel is default 0;

	//Loading all the images to use them before
	headImage.loadImage("img/head.png");
	LAimage.loadImage("img/arm_r.jpg");
	RAimage.loadImage("img/arm_l.jpg");
	RHimage.loadImage("img/hand_l.jpg");
	LHimage.loadImage("img/hand_r.jpg");
	Bodyimage.loadImage("img/body.jpg");
	LHipimage.loadImage("img/lap_l.jpg");
	RHipimage.loadImage("img/lap_r.jpg");
	LLimage.loadImage("img/leg_r.jpg");
	RLimage.loadImage("img/leg_l.jpg");
	LFimage.loadImage("img/foot_l.jpg");
	RFimage.loadImage("img/foot_r.jpg");
	velocityL = 0;
	lastwristheightL = 0;
	velocityR = 0;
	lastwristheightR = 0;
	leftstroke = 0;
	rightstroke = 0;

	brazada = 0;
	//Set the stroke time
	timestroke = 0.8;
	salida = 1;
	luigi = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	kinect.update();
	
	//cout << "sending osc messages to Host: " << string(HOST) << "  Port: " << ofToString(PORT) << endl;
	float elapsedTime = ofGetLastFrameTime();
	NuiCameraElevationSetAngle(degree);
	if(kinect.isNewSkeleton()) 
	{
		for( int i = 0; i < kinect.getSkeletons().size(); i++) 
		{
			if (kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HEAD) != kinect.getSkeletons().at(i).end())
			{

				//Accessing to the different bones of the skeleton that Kinect provide us

				SkeletonBone headBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HEAD)->second;
				SkeletonBone neckBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_SHOULDER_CENTER)->second;
				SkeletonBone hipLeftBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HIP_LEFT)->second;
				SkeletonBone hipRightBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HIP_RIGHT)->second;
				SkeletonBone hipBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HIP_CENTER)->second;
				SkeletonBone bodyBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_SPINE)->second;
				SkeletonBone kneeLeftBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_KNEE_LEFT)->second;
				SkeletonBone kneeRightBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_KNEE_RIGHT)->second;
				SkeletonBone shoulderLeftBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_SHOULDER_LEFT)->second;
				SkeletonBone shoulderRightBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_SHOULDER_RIGHT)->second;
				SkeletonBone elbowLeftBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_ELBOW_LEFT)->second;
				SkeletonBone elbowRightBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_ELBOW_RIGHT)->second;
				SkeletonBone ankleLeftBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_ANKLE_LEFT)->second;
				SkeletonBone ankleRightBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_ANKLE_RIGHT)->second;
				SkeletonBone wristLeftBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_WRIST_LEFT)->second;
				SkeletonBone wristRightBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_WRIST_RIGHT)->second;
				SkeletonBone footLeftBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_FOOT_LEFT)->second;
				SkeletonBone footRightBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_FOOT_RIGHT)->second;



				//SKELETON POINT POSITIONS

				//Now we are going to define the x and y points of each point of the skeleton
				//Those points allows us to draw them in the screen, simulating articulations of the body 
				//and also will be useful to have reference points to draw Luigi body parts and scale them

				LSPoint.x = shoulderLeftBone.getScreenPosition().x; LSPoint.y = shoulderLeftBone.getScreenPosition().y;
				RSPoint.x = shoulderRightBone.getScreenPosition().x; RSPoint.y = shoulderRightBone.getScreenPosition().y;
				CSPoint.x = neckBone.getScreenPosition().x; CSPoint.y = neckBone.getScreenPosition().y;
				RWPoint.x = wristRightBone.getScreenPosition().x; RWPoint.y = wristRightBone.getScreenPosition().y;
				LWPoint.x = wristLeftBone.getScreenPosition().x; LWPoint.y = wristLeftBone.getScreenPosition().y;
				LEPoint.x = elbowLeftBone.getScreenPosition().x; LEPoint.y = elbowLeftBone.getScreenPosition().y;
				REPoint.x = elbowRightBone.getScreenPosition().x; REPoint.y = elbowRightBone.getScreenPosition().y;
				SPoint.x = bodyBone.getScreenPosition().x; SPoint.y = bodyBone.getScreenPosition().y;
				HPoint.x = hipBone.getScreenPosition().x; HPoint.y = hipBone.getScreenPosition().y;
				LHPoint.x = hipLeftBone.getScreenPosition().x; LHPoint.y = hipLeftBone.getScreenPosition().y;
				RHPoint.x = hipRightBone.getScreenPosition().x; RHPoint.y = hipRightBone.getScreenPosition().y;
				LKPoint.x = kneeLeftBone.getScreenPosition().x; LKPoint.y = kneeLeftBone.getScreenPosition().y;
				RKPoint.x = kneeRightBone.getScreenPosition().x; RKPoint.y = kneeRightBone.getScreenPosition().y;
				LAPoint.x = ankleLeftBone.getScreenPosition().x; LAPoint.y = ankleLeftBone.getScreenPosition().y;
				RAPoint.x = ankleRightBone.getScreenPosition().x; RAPoint.y = ankleRightBone.getScreenPosition().y;
				headPoint.x = headBone.getScreenPosition().x; headPoint.y = headBone.getScreenPosition().y;
				LFPoint.x = footLeftBone.getScreenPosition().x; LFPoint.y = footLeftBone.getScreenPosition().y;
				RFPoint.x = footRightBone.getScreenPosition().x; RFPoint.y = footRightBone.getScreenPosition().y;

				
				

				if (luigi) {
					//IMAGE POSITION BELOW

					//Using the points above we define the position of each image
					//For instance, for Hips Position, what we do to center the image is, in left hip position and "x" axis,
					//go down to the left hip x position and then we erase the distance between the left hip and the left knee divided 
					//by 2 to have it in the center. By this way we have "x" coordinate stored, where we will draw in this case the hip. 
					//Using the same logic we obtain "y" coordinate and we will use it to centered draw it.
					//All the rest of the parts share the same logic. 

					//Hips Position (to draw lap_r and lap_l)

					LHipPosition.x = LHPoint.x - (LHPoint.x - LKPoint.x) / 2;
					LHipPosition.y = LHPoint.y - (LHPoint.y - LKPoint.y) / 2;

					RHipPosition.x = RHPoint.x - (RHPoint.x - RKPoint.x) / 2;
					RHipPosition.y = RHPoint.y - (RHPoint.y - RKPoint.y) / 2;

					//Arms Position 
					LAPosition.x = LSPoint.x - (LSPoint.x - LEPoint.x) / 2;
					LAPosition.y = LSPoint.y - (LSPoint.y - LEPoint.y) / 2;

					RAPosition.x = RSPoint.x - (RSPoint.x - REPoint.x) / 2;
					RAPosition.y = RSPoint.y - (RSPoint.y - REPoint.y) / 2;

					//Hands
					LHPosition.x = LWPoint.x - (LWPoint.x - LEPoint.x) / 2;
					LHPosition.y = LWPoint.y - (LWPoint.y - LEPoint.y) / 2;

					RHPosition.x = RWPoint.x - (RWPoint.x - REPoint.x) / 2;
					RHPosition.y = RWPoint.y - (RWPoint.y - REPoint.y) / 2;

					//Body Position
					//Here we don't have to do nothing with body "x" position to center the image, as we have already the Spine point as reference
					//We only have to define "y" position: we go down to the hip position and then we go up to the distance between the neck
					//and the hip divided by 2.2 (to fit it better). That is why in this case we sum the 2 "y" points.

					BodyPosition.x = SPoint.x;
					BodyPosition.y = HPoint.y + (CSPoint.y - HPoint.y) / 2.2;

					//Legs
					LLPosition.x = LKPoint.x - (LKPoint.x - LFPoint.x) / 2;
					LLPosition.y = LKPoint.y - (LKPoint.y - LFPoint.y) / 2;

					RLPosition.x = RKPoint.x - (RKPoint.x - RFPoint.x) / 2;
					RLPosition.y = RKPoint.y - (RKPoint.y - RFPoint.y) / 2;



					//ROTATIONS BELOW

					//To rotate each part of the body we simply use the same logic that Head has
					//but taking into acount on which points the rotations has to be for each
					//image and the direction of the rotation.

					//Head
					float dx = CSPoint.x - headPoint.x;
					float dy = CSPoint.y - headPoint.y;
					headRotation = (atan2(dx, dy)*-180 / 3.141592);

					//Hips
					dx = LKPoint.x - LHPoint.x;
					dy = LKPoint.y - LHPoint.y;
					LHipRotation = (atan2(dx, dy)*-180 / 3.141592);

					dx = RKPoint.x - RHPoint.x;
					dy = RKPoint.y - RHPoint.y;
					RHipRotation = (atan2(dx, dy)*-180 / 3.141592);

					//Body
					dx = SPoint.x - CSPoint.x;
					dy = SPoint.y - CSPoint.y;
					BodyRotation = (atan2(dx, dy)*-180 / 3.141592);

					//Arms
					dx = LEPoint.x - LSPoint.x;
					dy = LEPoint.y - LSPoint.y;
					LARotation = (atan2(dx, dy)*-180 / 3.141592);

					dx = REPoint.x - RSPoint.x;
					dy = REPoint.y - RSPoint.y;
					RARotation = (atan2(dx, dy)*-180 / 3.141592);

					//Legs
					dx = LAPoint.x - LKPoint.x;
					dy = LAPoint.y - LKPoint.y;
					LLRotation = (atan2(dx, dy)*-180 / 3.141592);

					dx = RAPoint.x - RKPoint.x;
					dy = RAPoint.y - RKPoint.y;
					RLRotation = (atan2(dx, dy)*-180 / 3.141592);

					//"Hands"
					dx = LWPoint.x - LEPoint.x;
					dy = LWPoint.y - LEPoint.y;
					LHRotation = (atan2(dx, dy)*-180 / 3.141592);

					dx = RWPoint.x - REPoint.x;
					dy = RWPoint.y - REPoint.y;
					RHRotation = (atan2(dx, dy)*-180 / 3.141592);


				}

				velocityL = LWPoint.y - lastwristheightL;
				velocityR = RWPoint.y - lastwristheightR;

				if (salida == 1) {
					brazosjuntos = abs(LWPoint.x - RWPoint.x);
					
					if (brazosjuntos < 19) {
						alturacabezaizq =  headPoint.y - LWPoint.y;
						alturacabezader = headPoint.y - RWPoint.y;
						//cout << "estoy con los brazos juntos" << alturacabezader << alturacabezaizq<< endl;
						if ((alturacabezaizq > 2)&(alturacabezader > 2)) {
							ofxOscMessage start;
							start.setAddress("/startrace");
							start.addIntArg(salida);
							sender.sendMessage(start, true);
							
							cout << "salida " << endl;
							salida = 0;

						}
					}
				}
				

				if (salida == 0) {
					if (leftstroke <= 0) {
						if (velocityL > 40) {
							leftstroke = timestroke;
							ofxOscMessage m;
							m.setAddress("/velocity/left");
							m.addIntArg(velocityL);
							sender.sendMessage(m, true);
							brazada += 1;
							cout << "left arm vel: " << velocityL << endl;
						}
					}
					else {
						leftstroke -= elapsedTime;
					}
					if (rightstroke <= 0) {
						if (velocityR > 40) {
							rightstroke = timestroke;
							ofxOscMessage f;
							f.setAddress("/velocity/right");
							f.addIntArg(velocityR);
							sender.sendMessage(f, true);
							brazada += 1;
							cout << "right arm vel: " << velocityR << endl;
						}
					}
					else {
						rightstroke -= elapsedTime;
					}
					
					lastwristheightL = LWPoint.y;
					lastwristheightR = RWPoint.y;


			/*		ofxOscMessage b;
					b.setAddress("/brazada");
					b.addIntArg(brazada);
					sender.sendMessage(b, true);*/
					ofxOscMessage braz;
					braz.setAddress("/velocity/stroke");
					braz.addIntArg(brazada);
					sender.sendMessage(braz, true);
					//cout << "num brazadas: " << brazada << endl;
					if (brazada == 70) {
						
						salida = 2;
					}
				}
				
				if (salida == 2) {
					ceremoniaizq = headPoint.y - LWPoint.y;
					ceremoniader = headPoint.y - RWPoint.y;
					if ((ceremoniader > 3) && (ceremoniaizq > 3)) {
						ofxOscMessage cerem;
						cerem.setAddress("/ceremony");
						cerem.addIntArg(1);
						sender.sendMessage(cerem, true);
						cout << "rising cup"<< endl;
						salida = 3;
					}
				}
			}
		}
	}
	
}

//--------------------------------------------------------------
void ofApp::draw()
{
	kinect.draw(0,0);
	kinect.drawDepth(640, 0);
	

	if(kinect.isNewSkeleton()) 
	{
		for( int i = 0; i < kinect.getSkeletons().size(); i++) 
		{
			if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HEAD) != kinect.getSkeletons().at(i).end())
			{
				kinect.drawSkeleton(i);
				ofEnableAlphaBlending();
				ofSetRectMode(OF_RECTMODE_CENTER);
				
				//In order to reescale the images each if we approach or if we go away or even if
				//we bend (affecting for instance body width size) we use it the euclidian distance 
				//between the points where the images are
				if (luigi) {
					//Body
					ofPushMatrix();
					ofTranslate(BodyPosition);
					ofRotate(BodyRotation);
					Bodyimage.draw(0, 0, abs(LSPoint.x - RSPoint.x), sqrt(pow(CSPoint.y - HPoint.y, 2) + pow(CSPoint.x - HPoint.x, 2)));
					ofPopMatrix();


					//Legs
					ofPushMatrix();
					ofTranslate(LLPosition);
					ofRotate(LLRotation);
					LLimage.draw(0, 0, abs(LSPoint.x - CSPoint.x) / 1, sqrt(pow(LKPoint.y - LFPoint.y, 2) + pow(LKPoint.x - LFPoint.x, 2)));
					ofPopMatrix();

					ofPushMatrix();
					ofTranslate(RLPosition);
					ofRotate(RLRotation);
					RLimage.draw(0, 0, abs(LSPoint.x - CSPoint.x) / 1, sqrt(pow(RKPoint.y - RFPoint.y, 2) + pow(RKPoint.x - RFPoint.x, 2)));
					ofPopMatrix();

					//Hips
					ofPushMatrix();
					ofTranslate(LHipPosition);
					ofRotate(LHipRotation);
					LHipimage.draw(0, 0, abs(LSPoint.x - CSPoint.x) / 1.2, sqrt(pow(LHPoint.y - LKPoint.y, 2) + pow(LHPoint.x - LKPoint.x, 2)));
					ofPopMatrix();

					ofPushMatrix();
					ofTranslate(RHipPosition);
					ofRotate(RHipRotation);
					RHipimage.draw(0, 0, abs(RSPoint.x - CSPoint.x) / 1.2, sqrt(pow(RHPoint.y - RKPoint.y, 2) + pow(RHPoint.x - RKPoint.x, 2)));
					ofPopMatrix();


					//Arms
					ofPushMatrix();
					ofTranslate(LAPosition);
					ofRotate(LARotation);
					LAimage.draw(0, 0, abs(LSPoint.x - CSPoint.x) / 1.5, sqrt(pow(LSPoint.y - LEPoint.y, 2) + pow(LSPoint.x - LEPoint.x, 2)));
					ofPopMatrix();

					ofPushMatrix();
					ofTranslate(RAPosition);
					ofRotate(RARotation);
					RAimage.draw(0, 0, abs(RSPoint.x - CSPoint.x) / 1.5, sqrt(pow(RSPoint.y - REPoint.y, 2) + pow(RSPoint.x - REPoint.x, 2)));
					ofPopMatrix();


					//Head
					ofPushMatrix();
					ofTranslate(headPoint);
					ofRotate(headRotation);
					headImage.draw(0, 0, abs(LSPoint.x - RSPoint.x) / 1.5, abs(CSPoint.y - headPoint.y) * 2);
					ofPopMatrix();

					//"Hands"
					ofPushMatrix();
					ofTranslate(LHPosition);
					ofRotate(LHRotation);
					LHimage.draw(0, 0, abs(LSPoint.x - CSPoint.x) / 1.5, sqrt(pow(LEPoint.y - LWPoint.y, 2) + pow(LEPoint.x - LWPoint.x, 2)));
					ofPopMatrix();

					ofPushMatrix();
					ofTranslate(RHPosition);
					ofRotate(RHRotation);
					RHimage.draw(0, 0, abs(LSPoint.x - CSPoint.x) / 1.5, sqrt(pow(REPoint.y - RWPoint.y, 2) + pow(REPoint.x - RWPoint.x, 2)));
					ofPopMatrix();
				}
				ofSetRectMode(OF_RECTMODE_CORNER);
				
				ofDisableAlphaBlending();
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'l':
		luigi = true;
		break;
	case 'n':
		luigi = false;
		break;
	case 'r':
		salida = 1;
		break;
	case '+':
		if (degree>=+27) {

		}
		else {
			degree++;
			cout << degree << endl;
		}
		break;
	case '-':		
		if (degree<=-27) {

		}
		else {
			degree--;
			cout << degree << endl;
		}
		break;
	case '1':
		salida = 1;
		break;
	case '2':
		salida = 0;
		break;
	case '3':
		salida = 2;
		break;
	case '4':
		salida = 4;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}