#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void setupMeshPlane();
  
    const int radius = 400; 
  
    // Mesh
    ofMesh mesh;
    ofImage image;
  
    vector<glm::vec2> offsets;
};
