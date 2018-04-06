/**
 *
 *  @file ofApp.cpp
 *  @brief MotionMachine source file for empty example
 *  @copyright Numediart Institute, UMONS (c) 2015
 *
 */
#include "ofApp.h"
using namespace std;
using namespace arma;
using namespace MoMa;


void ofApp::setup( void ) {

	addNewTrack("c3d"); // Dynamically add new track

	addNewTrack("Track1"); // Dynamically add new track

	addNewLabelList("Track1"); // Dynamically add new label list
	registerDragEvent(labelList("Track1")); // Expose to automatic drag and drop
	track("Track1").load(getDataPath() + "resources/kinect2.bones");
	track("Track1").load(getDataPath() + "resources/kinect2.nodes");

	//ofSetFrameRate(30);
	//setFrameRate(30);
}
void ofApp::update( void ) {
    
}
void ofApp::scene3d( void ) {
    
    //Draw kinect track
	if (track("Track1").nOfFrames() > 0) {

		Frame frame = track("Track1")[getAppTime()];
		ofSetColor(Turquoise);
		setNodeSize(20);
		draw(frame);
	}	

    //Draw qualisys track
	if (track("c3d").nOfFrames() > 0) {

		Frame frame = track("c3d")[getAppTime()];
		ofSetColor(Red);
		setNodeSize(20);
		draw(frame);
	}
}
void ofApp::scene2d( void ) {
    
    //Draw kinect track COM
	if (track("Track1").nOfFrames() > 0) {

        draw(com);//draw only Z-axis
	}

    //Draw Qualisys track COM
	if (track("c3d").nOfFrames() > 0) {

        draw(com_c3d);
	}
}
void ofApp::annotate( void ) {
    
    
}
void ofApp::keyPressed( int key ) {

	if (key == 'f') {

		cout << "Index: " << getAppIndex() << endl;
		cout << "Time: " << getAppTime() << endl;
	}
}
void ofApp::keyReleased( int key ) {
    
}
void ofApp::mousePressed( int x, int y, int button ) {
    
}
void ofApp::mouseReleased( int x, int y, int button ) {
    
}
void ofApp::mouseDragged( int x, int y, int button ) {
    
    
}
void ofApp::mouseMoved( int x, int y ) {

}

void ofApp::windowResized( int w, int h ) {
    

}

void ofApp::dragEvent( ofDragInfo dragInfo ) {

	for (int i = 0; i < dragInfo.files.size(); i++) {

        //Load kinect or qualisys data files
        string filename = dragInfo.files[i];
        size_t dot = filename.find_last_of(".");
        string extension = filename.substr(dot + 1, filename.size() - dot - 1);
        transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

		if(extension ==  "txt") {			

			TimedFlatParser tflatParser(filename, &track("Track1"));
            //Place on origin at beginning
			Geometry::placeOnOrigin(track("Track1"), "RAnkle", "LFoot", "RFoot");
            //Compute center of mass (average of all markers)
			com = Geometry::centerOfMassTrace(track("Track1"));

            //Set player size
            setPlayerSize(0.0, std::max(track("Track1").maxTime(), track("c3d").maxTime()));
            if (track("c3d").nOfFrames() <= 0)
                setPlayerSize(0.0, track("Track1").maxTime());
		}		

		else if (extension == "c3d" || extension == "v3d" || extension == "tsv") {

			track("c3d").load(filename);
            //Place on origin at beginning
            Geometry::placeOnOrigin(track("c3d"), "R_FCC", "L_FM1", "R_FM1");
            //Compute center of mass (average of all markers)
			com_c3d = Geometry::centerOfMassTrace(track("c3d"));

            //Set player size
            setPlayerSize(0.0, std::max(track("Track1").maxTime(), track("c3d").maxTime()));
            if (track("Track1").nOfFrames() <= 0)
                setPlayerSize(0.0, track("c3d").maxTime());
		}
	}
}

void ofApp::gotMessage( ofMessage msg ) {
    
    
}

bool ofApp::has_suffix(const std::string &str, const std::string &suffix)
{
	return str.size() >= suffix.size() &&
		str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}
