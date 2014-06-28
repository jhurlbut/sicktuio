#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(120);
	ofSetCircleResolution(64);
	ofSetLogLevel(OF_LOG_VERBOSE);
	//ofSetLogLevel(OF_LOG_NOTICE);
	recording = false;
	// LMS 
	//grabber.setIp("169.254.171.130");

	//TIM
	grabber.setIp("169.254.70.188");
	grabber.setup();
	//player.load("recording.lms");
	
	sick = &grabber;
	
	trackingRegion.set(1200, -800, 1200, 1600);
	
	tracker.setMaximumDistance(100);
	tracker.setPersistence(10);
	tracker.setRegion(trackingRegion);

}

//--------------------------------------------------------------
void ofApp::update(){
	
	sick->update();
	if(sick->isFrameNew()) {
		tracker.update(*sick);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	
	float scale = ofMap(mouseX, 0, ofGetWidth(), 0.05, .2, true);
	
	ofPushMatrix();
	ofTranslate(20, 20);
	ofSetColor(255);
	ofCircle(0, 0, 7);
	ofDrawBitmapString(ofToString(tracker.size()) + " clusters", -4, 4);
	ofPopMatrix();
	
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	
	ofPushMatrix();
	ofScale(scale, scale);
	sick->draw(12, 2400);
	tracker.draw();

	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
		if(key == 'r') {
		recording = !recording;
		if(recording) {
			grabber.startRecording();
		} else {
			grabber.stopRecording("out.lms");
		}
	}
	if(key == '\t') {
		if(sick == &player) {
			sick = &grabber;
		} else {
			sick = &player;
		}
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
