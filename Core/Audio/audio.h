#pragma once

#include "audio_resource.h"

#include <glm/glm.hpp>
#include <memory>

class CoreEngine;
class AudioEngine;

class Audio
{
	public:
		Audio(const std::string& file_name);
		virtual ~Audio();
		AudioResource* getResource() { return resource; };
		void setEngine(CoreEngine* core);
		void play(glm::vec3& source_pos = glm::vec3(), bool loop = false);
	private:
		AudioResource *resource;
		AudioEngine *engine;
};

