#include <string>
#include <iostream>

#include <GL/glew.h>

#include <IGame.h>

#include <TerraNovaGame.h>

#include <blurryroots/throwif.h>
#include <ClearColorData.h>

TerraNovaGame::TerraNovaGame ()
: closing_request (false)
, em ()
, csp (em) {
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LESS);

	glEnable (GL_CULL_FACE);
	glCullFace (GL_BACK);
	glFrontFace (GL_CCW);

	log ("Starting...");

	auto eid = this->em.create_entity ();
	THROW_IF (0 == eid,
		"Ne ne!"
	);

	this->em.add_data<ClearColorData> (eid, 0.3f, 0.3f, 0.5f, 1.0f);
}

TerraNovaGame::~TerraNovaGame () {
	//
}

void
TerraNovaGame::on (QuitEvent event) {
	this->closing_request = true;
}


void
TerraNovaGame::on_update (float dt) {
	this->csp.update (dt);
}

void
TerraNovaGame::on_render () {
	this->csp.render ();
}

void
TerraNovaGame::on_shutdown () {
	this->log ("Shutting down...");
}

bool
TerraNovaGame::has_closing_request () {
	return this->closing_request;
}

void
TerraNovaGame::log (std::string msg) {
	std::cout << msg << std::endl;
}
