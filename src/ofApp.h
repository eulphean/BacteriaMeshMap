#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
  
    const int radius = 400; 
  
    ofMesh mesh;
    ofImage image;
  
    vector<glm::vec2> offsets;
};
