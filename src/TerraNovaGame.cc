#include <string>
#include <iostream>

#include <GL/glew.h>

#include <terranova/IGame.h>
#include <terranova/events/MouseButtonEvent.h>
#include <terranova/events/QuitEvent.h>
#include <terranova/events/UserEvent.h>
#include <terranova/FileReader.h>

#include <TerraNovaGame.h>

#include <blurryroots/throwif.h>
#include <ClearColorData.h>

TerraNovaGame::TerraNovaGame (void)
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

	// create basic shader program
	auto vs = terranova::VertexShader (
		terranova::FileReader ("shaders/es/basic.vert").to_string ()
	);
	auto fs = terranova::FragmentShader (
		terranova::FileReader ("shaders/es/basic.frag").to_string ()
	);
	this->shader_program = terranova::ShaderProgramBuilder ()
		.add_shader (vs)
		.add_shader (fs)
		.bind_attribute ("vertex_position", 0)
		.bind_attribute ("vertex_uv", 1)
		.bind_attribute ("vertex_normal", 2)
		.link ()
		;

	this->texture_loader.load ("textures/ground.lines.png",
		"ground", 0
	);
	this->mesh_loader.load ("models/ground.obj",
		this->shader_program,
		"ground"
	);

	auto eid = this->em.create_entity ();
	THROW_IF (0 == eid,
		"Ne ne!"
	);

	this->em.add_data<ClearColorData> (eid,
		0.3f, 0.3f, 0.5f, 1.0f
	);
}

TerraNovaGame::~TerraNovaGame (void) {
	this->mesh_loader.dispose ();
	this->texture_loader.dispose ();
}

void
TerraNovaGame::on (terranova::MouseButtonEvent event) {
	this->log ("MouseButtonEvent at ("
		+ std::to_string (event.x) + ":"
		+ std::to_string (event.y) + ")");
}

void
TerraNovaGame::on (terranova::QuitEvent event) {
	this->log ("QuitEvent at " + std::to_string (event.timestamp));
	this->closing_request = true;
}

void
TerraNovaGame::on (terranova::UserEvent event) {
	this->log ("UserEvent at " + std::to_string (event.timestamp));
	this->log ("Should I delete the pointer here?");
}

void
TerraNovaGame::on_update (float dt) {
	//this->csp.update (dt);
}

void
TerraNovaGame::on_render (void) {
	this->csp.render ();

	this->shader_program.use ();

	this->camera_processor.on_render (this->shader_program);

	// ambient light
	this->shader_program.set_uniform_i ("complex_attenuation",
		static_cast<int> (0)
	);
	this->shader_program.set_uniform_vec3 ("ambient_light",
		glm::vec3 (0.08, 0.08, 0.2)
	);

	// point light
	auto light_color = glm::vec3 (1.0, 0.8, 1.0);
	auto light_intensity = 0.8;
	auto light_radius = 2.0;
	auto light_pos_mat = terranova::Transform ().to_translation ();
	this->shader_program.set_uniform_vec4 ("point_light_color",
		glm::vec4 (light_color, light_intensity)
	);
	this->shader_program.set_uniform_vec4 ("point_light",
		glm::vec4 (
			terranova::Transform::to_position (light_pos_mat),
			light_radius
		)
	);

	auto texture_key = std::string ("ground");
	auto mesh = this->mesh_loader.get ("ground");

	this->texture_loader.bind (texture_key);
	glBindVertexArray (mesh->vertex_array_object);

	terranova::Transform transform;
	// calculate and forward mesh transform
	this->shader_program.set_uniform_mat4 ("m",
		transform.to_matrix ()
	);

	int size;
	glGetBufferParameteriv (
		GL_ELEMENT_ARRAY_BUFFER,
		GL_BUFFER_SIZE,
		&size
	);
	THROW_IF (0 >= size,
		"Invalid element buffer!"
	);

	// draw all the triangles!
	int element_count = size
		/ sizeof (mesh->shapes[0].mesh.indices.at (0))
		;
	int real_element_count = mesh->shapes[0].mesh.indices.size ();
	THROW_IF (element_count != real_element_count,
		"Unequal element_count ", std::to_string (element_count),
		" vs ", std::to_string (real_element_count)
	);
	glDrawElements (GL_TRIANGLES, element_count, GL_UNSIGNED_INT, 0);

	glBindVertexArray (0);
	texture_loader.unbind (texture_key);
}

void
TerraNovaGame::on_shutdown (void) {
	this->log ("Shutting down...");
	this->log (this->em.serialize ());
}

bool
TerraNovaGame::has_closing_request (void) {
	return this->closing_request;
}

void
TerraNovaGame::log (std::string msg) {
	std::cout << msg << std::endl;
}
