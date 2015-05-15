#ifndef TerraNova_UserEvent_h
#define TerraNova_UserEvent_h

namespace terranova {

struct UserEvent {
	uint32_t type;
	uint32_t timestamp;

	void* data;
};

}

#endif
