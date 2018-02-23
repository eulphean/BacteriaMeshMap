#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  
  // Load an image.
  image.load("bacteria3.png");
  ofTexture tex = image.getTexture();
  setupMeshPlane();
}

//--------------------------------------------------------------
void ofApp::update(){
  // Update the vertices of the mesh using a sin function.
  offsets.clear();
  for (int i = 0; i < mesh.getVertices().size(); i++) {
    // Jitter offset
    offsets.push_back(glm::vec2(ofRandom(0,5), ofRandom(0,5)));
    
    auto v = mesh.getVertices()[i];
    
    float time = ofGetElapsedTimef();
    float timeScale = 0.5;
    float displacementScale = 1; // This is dependent on time now. Map this to time.
    glm::vec2 offset = offsets[i];

    // Update x and y positions of the vertex by adding noise.
    v.x += (ofSignedNoise(time*i + offset.x) * displacementScale);
    v.y += (ofSignedNoise(time*i + offset.y) * displacementScale);

    mesh.setVertex(i, v);
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetColor(ofColor::white);
  //image.draw(10, 10);
  ofPushMatrix();
    int xTranslate = ofGetWidth()/2 - image.getWidth()/2;
    int yTranslate = ofGetHeight()/2 - image.getHeight()/2;
    ofTranslate(xTranslate, yTranslate);
    image.getTexture().bind();
    mesh.draw();
    image.getTexture().unbind();
  ofPopMatrix();
}

void ofApp::setupMeshPlane() {
  int nCols = 5;
  int nRows = 5;
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
}
