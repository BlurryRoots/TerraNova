#include <string>
#include <iostream>

#include <GL/glew.h>

#include <IGame.h>

#include <TerraNovaGame.h>

TerraNovaGame::TerraNovaGame () {
}

TerraNovaGame::~TerraNovaGame () {
}

void TerraNovaGame::on_initialize () {
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LESS);

	glEnable (GL_CULL_FACE);
	glCullFace (GL_BACK);
	glFrontFace (GL_CCW);

	log ("Starting...");
}

void TerraNovaGame::on_shutdown_request () {
	this->closing_request = true;
}

void TerraNovaGame::on_update (float dt) {

}

void TerraNovaGame::on_render () {
	glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void TerraNovaGame::on_shutdown () {

}

bool TerraNovaGame::has_closing_request () {
	return this->closing_request;
}

void TerraNovaGame::log (std::string msg) {
	std::cout << msg << std::endl;
}
