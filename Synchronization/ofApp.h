/**
 *
 *  @file ofApp.h
 *  @brief MotionMachine header file for empty example
 *  @copyright Numediart Institute, UMONS (c) 2015
 *
 */
#pragma once
#include "MoMa.h"
#include "MoMaUI.h"
#include "ofMain.h"
#include "tracksView.h"
#include "mmGeometry.h"
#include "mmTimedFlatparser.h"

class ofApp : public MoMa::SceneApp {
  public:
    
    void setup( void );
    void update( void );
    
    void scene3d( void );
    void scene2d( void );
    void annotate( void );
    
    void keyPressed( int key );
    void keyReleased( int key );
    
    void mousePressed( int x, int y, int button );
    void mouseReleased( int x, int y, int button );
    void mouseDragged( int x, int y, int button );
    void mouseMoved( int x, int y );
    
    void windowResized( int w, int h );
    void dragEvent( ofDragInfo dragInfo );
    void gotMessage( ofMessage msg );
	bool has_suffix(const std::string &str, const std::string &suffix);
	inline bool exists(const std::string& name);

	string mocap_file_name;

	MoMa::Trace com, com_c3d;

	// duplicate first frame multiple times if the txt file starts before c3d one, taking into account the timestamps.
	void generate();
	void save_track(MoMa::Track &tr, string f);

	int gen_frame;
};
