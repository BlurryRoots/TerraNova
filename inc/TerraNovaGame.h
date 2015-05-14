#ifndef TerraNovaGame_h
#define TerraNovaGame_h

#include <string>

#include <IGame.h>
#include <yanecos/EntityManager.h>
#include <ClearScreenProcessor.h>

class TerraNovaGame
: public IGame {

public:
	TerraNovaGame ();

	virtual
	~TerraNovaGame ();

	void
	on_shutdown_request ();

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
