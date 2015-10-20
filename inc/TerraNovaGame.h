#ifndef TerraNovaGame_h
#define TerraNovaGame_h

#include <string>

#include <terranova/IGame.h>
#include <terranova/IEventHandler.h>
#include <terranova/ShaderProgram.h>
#include <terranova/VertexShader.h>
#include <terranova/FragmentShader.h>
#include <terranova/Mesh.h>
#include <terranova/MeshLoader.h>
#include <terranova/MeshRenderer.h>
#include <terranova/TextureLoader.h>

#include <yanecos/EntityManager.h>
#include <ClearScreenProcessor.h>
#include <CameraProcessor.h>

class TerraNovaGame
: public terranova::IGame
, public terranova::IEventHandler {

public:
	TerraNovaGame (void);

	virtual
	~TerraNovaGame (void);

	void
	on (terranova::QuitEvent e);

	void
	on (terranova::UserEvent e);

	void
	on (terranova::MouseButtonEvent e);

	void
	on_update (float dt);

	void
	on_render (void);

	void
	on_shutdown (void);

	bool
	has_closing_request (void);

	void
	log (std::string msg);

private:
	bool closing_request;

	terranova::ShaderProgram shader_program;
	terranova::model::MeshLoader mesh_loader;
	terranova::model::MeshRenderer mesh_renderer;
	terranova::TextureLoader texture_loader;

	Yanecos::EntityManager em;
	ClearScreenProcessor csp;
	CameraProcessor camera_processor;

};

#endif
