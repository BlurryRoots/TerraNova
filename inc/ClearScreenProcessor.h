#ifndef ClearScreenProcessor_h
#define ClearScreenProcessor_h

#include <SDL.h>
#include <GL/glew.h>

#include <blurryroots/superclass.h>

#include <yanecos/DataProcessor.h>
#include <ClearColorData.h>

class ClearScreenProcessor
: public Yanecos::DataProcessor {

DECLARE_SUPER_CLASS (Yanecos::DataProcessor);

public:
	ClearScreenProcessor (Yanecos::EntityManager &entity_manager)
	: __super (entity_manager)
	, color_speed (0.8f) {
		//
	}

protected:
	void
	on_update (float dt) override {
		for (auto eid : this->entity_manager.get_entities_with<ClearColorData> ()) {
			auto color = this->entity_manager.get_entity_data<ClearColorData> (eid);
			color->r = color->r > 1.0f
				? 0.0f
				: color->r + dt * this->color_speed
				;
		}
	}

	void
	on_render () override {
		for (auto eid : this->entity_manager.get_entities_with<ClearColorData> ()) {
			auto color = this->entity_manager.get_entity_data<ClearColorData> (eid);
			glClearColor (color->r, color->g, color->b, color->a);
		}

		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

private:
	float color_speed;

};

#endif
