#ifndef IGame_h
#define IGame_h

struct IGame {

	virtual
	~IGame () {}

	virtual void
	on_initialize () = 0;

	virtual void
	on_update (float dt) = 0;

	virtual void
	on_render () = 0;

	virtual void
	on_shutdown_request () = 0;

	virtual bool
	has_closing_request () = 0;

	virtual void
	on_shutdown () = 0;

};

#endif
