#ifndef TerraNovaGame_h
#define TerraNovaGame_h

#include <string>

#include <terranova/IGame.h>
#include <terranova/IEventHandler.h>

#include <yanecos/EntityManager.h>
#include <ClearScreenProcessor.h>

class TerraNovaGame
: public terranova::IGame
, public terranova::IEventHandler {

public:
	TerraNovaGame ();

	virtual
	~TerraNovaGame ();

	void
	on (terranova::QuitEvent e);

	void
	on (terranova::UserEvent e);

	void
	on (terranova::MouseButtonEvent e);

	void
	on_update (float dt);

	void
	on_render ();

	void
	on_shutdown ();

	bool
	has_closing_request ();

	void
	log (std::string msg);

private:
	bool closing_request;

	Yanecos::EntityManager em;
	ClearScreenProcessor csp;

};

#endif
