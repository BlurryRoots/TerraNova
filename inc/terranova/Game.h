#ifndef TerraNove_Game_h
#define TerraNove_Game_h

namespace terranova {

struct Application
: public terranova::IGame
, public terranova::IEventHandler {

public:
	Application (void) {
		//
	}

	virtual
	~Application (void) {

	}

	void
	on (terranova::QuitEvent e) {
		this->log ("QuitEvent at " + std::to_string (event.timestamp));
	}

	void
	on_update (float dt) {
		//
	}

	void
	on_render () {
		//
	}

	void
	on_shutdown () {
		//
	}

	void
	log (std::string msg) {
		// log event?
	}

private:
	bool closing_request;

};

}

#endif
