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

struct {

	bool operator()(MoMa::Label a, MoMa::Label b) {

		return a.moment.time() < b.moment.time();
	}
} customLess;

void ofApp::setup( void ) {

	addNewTrack("c3d"); // Dynamically add new track
	// registerDragEvent(track("c3d")); // Expose to d&d

	addNewTrack("Track1"); // Dynamically add new track
	// registerDragEvent(track("Track1")); // Expose to d&d

	addNewLabelList("Track1"); // Dynamically add new label list
	registerDragEvent(labelList("Track1")); // Expose to d&d
	track("Track1").setFrameRate(30);
	track("Track1").load(getDataPath() + "kinect2.bones"); 
	track("Track1").load(getDataPath() + "kinect2.nodes");

	ofSetFrameRate(30);
	setFrameRate(30);
	gen_frame = 0;
}
void ofApp::update( void ) {
    
}
void ofApp::scene3d( void ) {
    
	if (track("Track1").nOfFrames() > 0) {

		Frame frame = track("Track1")[getAppTime()];
		ofSetColor(Turquoise);
		setNodeSize(20);
		draw(frame);
	}	

	if (track("c3d").nOfFrames() > 0) {

		Frame frame = track("c3d")[getAppTime()];
		ofSetColor(Red);
		setNodeSize(20);
		draw(frame);
	}
}
void ofApp::scene2d( void ) {
    
	if (track("Track1").nOfFrames() > 0) {

		draw(com.position.elem(2));
	}

	if (track("c3d").nOfFrames() > 0) {

		draw(com_c3d.position.elem(2));
	}
}
void ofApp::annotate( void ) {
    
    
}
void ofApp::keyPressed( int key ) {

	if (key == 'f') {

		cout << "Index: " << getAppIndex() << endl;
		cout << "Time: " << getAppTime() << endl;
	}

	if (key == OF_KEY_UP) {

		for (int i = 0; i < labelList("Track1").size(); i++) {

			if(labelList("Track1")[0].moment.index() < track("Track1").nOfFrames())
				labelList("Track1")[i].moment.setIndex(labelList("Track1")[i].moment.index() + 1);
			cout << labelList("Track1")[0].moment.index() << " " << labelList("Track1")[0].moment.time() << endl;
		}
	}

	if (key == '8') {

		for (int i = 0; i < labelList("Track1").size(); i++) {

			if (labelList("Track1")[0].moment.index() < track("Track1").nOfFrames())
				labelList("Track1")[i].moment.setIndex(labelList("Track1")[i].moment.index() + 20);
			cout << labelList("Track1")[0].moment.index() << " " << labelList("Track1")[0].moment.time() << endl;
		}
	}

	if (key == OF_KEY_DOWN) {

		for (int i = 0; i < labelList("Track1").size(); i++) {

			if (labelList("Track1")[0].moment.index() > 0)
				labelList("Track1")[i].moment.setIndex(labelList("Track1")[i].moment.index() - 1);
			cout << labelList("Track1")[0].moment.index() << " " << labelList("Track1")[0].moment.time() << endl;
		}
	}

	if (key == '2') {

		for (int i = 0; i < labelList("Track1").size(); i++) {

			if (labelList("Track1")[0].moment.index() < track("Track1").nOfFrames())
				labelList("Track1")[i].moment.setIndex(labelList("Track1")[i].moment.index() - 20);
			cout << labelList("Track1")[0].moment.index() << " " << labelList("Track1")[0].moment.time() << endl;
		}
	}

	if (key == 'S') {

		ofFileDialogResult res;
		res = ofSystemSaveDialog("preset.lab", "Saving Labels to File");
		if (res.bSuccess) {

			std::sort(labelList("Track1").begin(), labelList("Track1").end(), customLess);
			labelList("Track1").save(res.filePath);
		}
	}

	if (key == OF_KEY_INSERT) {

		keyPressed('n');
		mousePressed(ofGetMouseX(), ofGetMouseY(), 0);
	}

	if (key == 'G') {

		generate();
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

		if (has_suffix(dragInfo.files[i], ".nodes") || has_suffix(dragInfo.files[i], ".bones")) {
			cout << "nodelist or bonelist!" << endl;
		}

		else if(has_suffix(dragInfo.files[i], ".txt")) {

			mocap_file_name = dragInfo.files[i];
			
			track("Track1").clearData();
			track("Track1").type = FLAT;
			size_t sep = mocap_file_name.find_last_of("\\/");
			size_t dot = mocap_file_name.find_last_of(".");
			track("Track1").setFileName(mocap_file_name.substr(sep + 1, dot - sep - 1));

			TimedFlatParser tflatParser(mocap_file_name, &track("Track1"));
			track("Track1").setFrameRate(30);
			labelList("Track1").clear();
			ofSetFrameRate(30);
			setFrameRate(30);

			cout << "number of frames of this track: " << track("Track1").nOfFrames() << endl;
			cout << "number of nodes of this track: " << track("Track1").nOfNodes() << endl;

			Geometry::placeOnOrigin(track("Track1"), "RAnkle", "LFoot", "RFoot");
			com = Geometry::centerOfMassTrace(track("Track1"));
			setPlayerSize(track("Track1").minTime(), std::max(track("Track1").maxTime(), track("Track1").maxTime()));
		}
		
		else if (has_suffix(dragInfo.files[i], ".c3d") || has_suffix(dragInfo.files[i], ".v3d")) {

			track("c3d").load(dragInfo.files[i]);
			//Geometry::placeOnOrigin(track("c3d"));
			//track("c3d").nodeList->clear();
			//track("c3d").boneList->clear();
			com_c3d = Geometry::centerOfMassTrace(track("c3d"));
			setPlayerSize(track("Track1").minTime(), std::max(track("Track1").maxTime(), track("c3d").maxTime()));
			cout << track("Track1").maxTime() << " " << track("c3d").maxTime() << endl;
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

void ofApp::generate() {

	string line;
	ifstream myfile(mocap_file_name);
	ofstream myfileout("generated.txt");
	if (myfile.is_open()) {

		getline(myfile, line);
		
		int t = stoi(line.substr(0, 8));

		if (myfileout.is_open()) {

			for (int i = gen_frame; i > 0; i--) {

				
				line = line.substr(9);
				line = to_string(t-33*i) + " " + line;
				myfileout << line + "\n";
			}
			myfileout.close();
		}
		myfile.close();
	}
}

void ofApp::save_track(MoMa::Track &tr, string f) {

	ofstream fileout(f);
	if (fileout.is_open()) {

		for (int i = 0; i < tr.nOfFrames(); i++) {

			fileout << to_string(tr.position.time(i)*1000) + " ";

			for (int j = 0; j < tr.nOfNodes(); j++) {

				fileout << to_string(tr.position.getData()(0, j, i)) + " " + 
						   to_string(tr.position.getData()(1, j, i)) + " " + 
						   to_string(tr.position.getData()(2, j, i)) + " ";
			}
			fileout << "\n";
		}
	}
}
