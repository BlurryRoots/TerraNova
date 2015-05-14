#ifndef DataProcessor_h
#define DataProcessor_h

#include <yanecos/EntityManager.h>

namespace Yanecos {

class DataProcessor {

public:
	DataProcessor (EntityManager &entity_manager)
	: should_update (true)
	, should_render (true)
	, entity_manager (entity_manager) {
		//
	}

	void
	start () {
		this->should_update = true;
	}

	void
	stop () {
		this->should_update = false;
	}

	void
	show () {
		this->should_render = true;
	}

	void
	hide () {
		this->should_render = false;
	}

	void
	update (float dt) {
		if (! this->should_update) {
			return;
		}

		this->on_update (dt);
	}

	void
	render () {
		if (! this->should_render) {
			return;
		}

		this->on_render ();
	}

protected:
	virtual void
	on_update (float dt) = 0;

	virtual void
	on_render () = 0;

	bool should_update;
	bool should_render;

	EntityManager &entity_manager;

};

}

#endif
