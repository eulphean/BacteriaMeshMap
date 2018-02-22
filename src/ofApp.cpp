#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  
  // Load an image.
  image.load("bacteria3.png");
  ofTexture tex = image.getTexture();
  
  // Setup a circular mesh. We'll just have 4 points.
  mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
  
  float x = radius * cos(ofDegToRad(45));
  float y = radius * sin(ofDegToRad(45));
  mesh.addVertex({x, y, 0});
  mesh.addTexCoord(glm::vec2(image.getWidth(), image.getHeight()));
  
  x = radius * cos(ofDegToRad(135));
  y = radius * sin(ofDegToRad(135));
  mesh.addVertex({x, y, 0});
  mesh.addTexCoord(glm::vec2(0, image.getHeight()));
  
  x = radius * cos(ofDegToRad(225));
  y = radius * sin(ofDegToRad(225));
  mesh.addVertex({x, y, 0});
  mesh.addTexCoord(glm::vec2(0, 0));
  
  x = radius * cos(ofDegToRad(315));
  y = radius * sin(ofDegToRad(315));
  mesh.addVertex({x, y, 0});
  mesh.addTexCoord(glm::vec2(0, image.getHeight()));
}

//--------------------------------------------------------------
void ofApp::update(){
  // Update the vertices of the mesh using a sin function.
  offsets.clear();
  for (int i = 0; i < mesh.getVertices().size(); i++) {
    // Jitter offset
    offsets.push_back(glm::vec2(ofRandom(0,10), ofRandom(0,10)));
    
    auto v = mesh.getVertices()[i];
    
    float time = ofGetElapsedTimef();
    float timeScale = 2.0;
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
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    image.getTexture().bind();
    mesh.drawFaces();
    image.getTexture().unbind();
//    for (auto v : mesh.getVertices()) {
//      ofSetColor(ofColor::red);
//      ofDrawCircle(v.x, v.y, 10);
//    }
  ofPopMatrix();
}
