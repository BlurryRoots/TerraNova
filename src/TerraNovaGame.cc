#include <string>
#include <iostream>

#include <GL/glew.h>

#include <IGame.h>

#include <TerraNovaGame.h>

#include <blurryroots/throwif.h>
#include <ClearColorData.h>

TerraNovaGame::TerraNovaGame () {
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
TerraNovaGame::on_shutdown_request () {
	this->closing_request = true;
}

#include <SDL.h>
void
TerraNovaGame::on_update (float dt) {
	auto s = std::string ("dt: ") + std::to_string (dt);
	SDL_Log (s.c_str ());
	static const float color_speed = 1.0f;

	for (auto eid : this->em.get_entities_with<ClearColorData> ()) {
		auto color = this->em.get_entity_data<ClearColorData> (eid);
		color->r = color->r > 1.0f
			? 0.0f
			: color->r + dt * color_speed
			;
	}
}

void
TerraNovaGame::on_render () {
	for (auto eid : this->em.get_entities_with<ClearColorData> ()) {
		auto color = this->em.get_entity_data<ClearColorData> (eid);
		glClearColor (color->r, color->g, color->b, color->a);
	}

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
TerraNovaGame::on_shutdown () {
	//
}

bool
TerraNovaGame::has_closing_request () {
	return this->closing_request;
}

void
TerraNovaGame::log (std::string msg) {
	std::cout << msg << std::endl;
}
