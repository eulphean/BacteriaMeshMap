// Author: Amay Kataria
// Date: 02/22/2018

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
  
    // Helper methods.
    void setupMeshPlane();
    void addInteractivity(glm::vec2 v, int idx);
    void addJitter(glm::vec2 v, int idx);
    void meshDivisionUpdated(int &divisions);
  
    // Events.
    void keyPressed(int key);
  
    // Mesh
    ofMesh mesh;
    ofMesh meshCopy; // Keep a copy of the original mesh so we can reset the mesh when
    // we don't want to interact with the mesh. 
    ofImage image;
  
    // Interaction.
    bool enableInteractivity;
    
    // Jitter
    vector<glm::vec2> offsets;
  
    // GUI.
    ofxIntSlider meshDivisions;
    ofxIntSlider attraction;
    ofxIntSlider repulsion;
    ofxPanel gui; 
};
