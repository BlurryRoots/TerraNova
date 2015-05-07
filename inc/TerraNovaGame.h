#include <string>

#include <IGame.h>

#ifndef TerraNovaGame_h
#define TerraNovaGame_h

class TerraNovaGame
: public IGame {

public:
	TerraNovaGame ();

	virtual
	~TerraNovaGame ();

	void
	on_initialize ();

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

};

#endif
