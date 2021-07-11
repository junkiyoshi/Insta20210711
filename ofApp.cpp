#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetLineWidth(2);

	this->fbo.allocate(ofGetWidth(), ofGetHeight());
	this->count = 125;
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->fbo.begin();
	ofClear(0);
	ofSetColor(0);

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	for (int k = 0; k < 3; k++) {

		auto deg = ofGetFrameNum() + k * 120;

		auto location = glm::vec2(230 * cos(deg * DEG_TO_RAD), 230 * sin(deg * DEG_TO_RAD));
		auto next = glm::vec2(230 * cos((deg + 1) * DEG_TO_RAD), 230 * sin((deg + 1) *DEG_TO_RAD));

		this->draw_arrow(location, next, 200, ofColor(0), ofColor(0));
	}

	this->fbo.end();
	this->fbo.readToPixels(this->pix);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->arrow_list.clear();

	while (this->arrow_list .size() < this->count) {

		int x = ofRandom(ofGetWidth());
		int y = ofRandom(ofGetHeight());

		ofColor pix_color = this->pix.getColor(x, y);
		if (pix_color != ofColor(0)) {

			continue;
		}

		ofColor color;
		color.setHsb(ofRandom(255), 255, 255);
		glm::vec2 point = glm::vec2(x, y);
		float radius = ofRandom(8, 18);

		bool flag = true;
		for (int i = 0; i < this->arrow_list.size(); i++) {

			if (glm::distance(point, this->arrow_list[i].first) < this->arrow_list[i].second + radius) {

				flag = false;
				break;
			}
		}

		if (flag) {

			this->arrow_list.push_back(make_pair(point, radius));
		}
	}

	for (int arrow_index = 0; arrow_index < this->arrow_list.size(); arrow_index++) {

		glm::vec2 location = this->arrow_list[arrow_index].first;
		float radius = this->arrow_list[arrow_index].second;

		auto noise_angle = ofMap(ofNoise(glm::vec3(location * 0.005, ofGetFrameNum() * 0.001)), 0, 1, 0, PI);
		this->draw_arrow(location, location + glm::vec2(cos(noise_angle), sin(noise_angle)), radius * 1.2, ofColor(39), ofColor(255));
	}

	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 target, float size, ofColor fill_color, ofColor no_fill_color) {

	auto angle = std::atan2(target.y - location.y, target.x - location.x);

	ofSetColor(fill_color);
	ofFill();
	ofBeginShape();
	ofVertex(location + glm::vec2(size * cos(angle), size * sin(angle)));
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)));
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)));
	ofEndShape();

	ofBeginShape();
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25);
	ofEndShape();

	ofSetColor(no_fill_color);
	ofNoFill();
	ofBeginShape();
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)));
	ofVertex(location + glm::vec2(size * cos(angle), size * sin(angle)));
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)));
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25);
	ofEndShape();

	ofBeginShape();
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25);
	ofEndShape();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}