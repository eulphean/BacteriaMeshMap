// Author: Amay Kataria
// Date: 02/22/2018

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  
  // Load an image.
  image.load("bacteria3.png");
  ofTexture tex = image.getTexture();
  setupMeshPlane();
  
  enableInteractivity = false;
}

//--------------------------------------------------------------
void ofApp::update(){
  // Update the vertices of the mesh using a sin function.
  offsets.clear();
  for (int i = 0; i < mesh.getVertices().size(); i++) {
    // Jitter offset
    offsets.push_back(glm::vec2(ofRandom(0,5), ofRandom(0,5)));
    // Use the original mesh to get distances.
    auto v = meshCopy.getVertices()[i];
    
    if (enableInteractivity) {
      addInteractivity(v, i);
    } else {
      // Add jitter to each vertex.
      addJitter(v, i);
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetColor(ofColor::white);
  ofPushMatrix();
    int xTranslate = ofGetWidth()/2 - image.getWidth()/2;
    int yTranslate = ofGetHeight()/2 - image.getHeight()/2;
    ofTranslate(xTranslate, yTranslate);
    image.getTexture().bind();
    mesh.draw();
    image.getTexture().unbind();
  ofPopMatrix();
}

//
void ofApp::keyPressed(int key) {
  if (key == 'i') {
    enableInteractivity = !enableInteractivity;
    // Restore the original mesh. 
    mesh = meshCopy;
  }
}

// Use TRIANGLE mode to setup a mesh.
void ofApp::setupMeshPlane() {
  mesh.setMode(OF_PRIMITIVE_TRIANGLES);
  
  int nCols = 15;
  int nRows = 15;
  int w = image.getWidth();
  int h = image.getHeight();
  
  // Setup a 5 x 5 mesh.
  for (int y = 0; y < nCols; y++) {
    for (int x = 0; x < nRows; x++) {
      float ix = w * x / (nCols - 1);
      float iy = h * y / (nRows - 1);
      mesh.addVertex({ix, iy, 0});
      mesh.addTexCoord(glm::vec2(ix, iy));
    }
  }
  
  // We don't draw the last row / col (nRows - 1 and nCols - 1) because it was
    // taken care of by the row above and column to the left.
    for (int y = 0; y < nRows - 1; y++)
    {
        for (int x = 0; x < nCols - 1; x++)
        {
            // Draw T0
            // P0
            mesh.addIndex((y + 0) * nCols + (x + 0));
            // P1
            mesh.addIndex((y + 0) * nCols + (x + 1));
            // P2
            mesh.addIndex((y + 1) * nCols + (x + 0));

            // Draw T1
            // P1
            mesh.addIndex((y + 0) * nCols + (x + 1));
            // P3
            mesh.addIndex((y + 1) * nCols + (x + 1));
            // P2
            mesh.addIndex((y + 1) * nCols + (x + 0));
        }
    }
  
    // Doing this does a deep copy of the mesh.
    // Save a copy to restore the mesh when not interacting. 
    meshCopy = mesh;
}

void ofApp::addInteractivity(glm::vec2 v, int idx) {
    // Compensate for the translation in the draw function.
    int xTranslate = ofGetWidth()/2 - image.getWidth()/2;
    int yTranslate = ofGetHeight()/2 - image.getWidth()/2;
  
    // Get current mouse position.
    glm::vec2 mousePos = glm::vec2(mouseX - xTranslate, mouseY - yTranslate);

    // Get distanceVector of this vertex from the position.
    glm::vec2 distance = mousePos - v;
  
    // Normalize distance vector.
    glm::vec2 normal = glm::normalize(distance);
  
    // Calculate length of distance vector.
    int distanceToMouse = glm::length(distance);
  
    // Closer the vertex is, more distortion. Farther the vertex, less is the distortion.
    int displacement = ofMap(distanceToMouse, 0, 400, 20, 0, true);
  
    // Get the new vertex in the direction of the normal vector.
    glm::vec2 newVertex = v + displacement * normal;
  
    // Set the new vertex to the mesh.
    mesh.setVertex(idx, {newVertex.x, newVertex.y, 0});
}

void ofApp::addJitter(glm::vec2 v, int idx) {
    float time = ofGetElapsedTimef();
    float timeScale = 0.5;
    float displacementScale = 1; // This is dependent on time now. Map this to time.
    glm::vec2 offset = offsets[idx];

    // Update x and y positions of the vertex by adding noise.
    v.x += (ofSignedNoise(time*idx + offset.x) * displacementScale);
    v.y += (ofSignedNoise(time*idx + offset.y) * displacementScale);

    mesh.setVertex(idx, {v.x, v.y, 0});
}
