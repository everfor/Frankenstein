#pragma once

#include "audio_source_resource.h"
#include "audio.h"

#include <glm/glm.hpp>

class AudioSource
{
	public:
		AudioSource(bool is_background = false, ALboolean should_loop = AL_FALSE);
		virtual ~AudioSource();
		AudioSourceResource* getResource() { return resource; };
		bool isBackground() { return is_background; };
		bool shouldPlay() { return should_play; };
		void enablePlay() { should_play = true; };
		ALboolean shouldLoop() { return should_loop; };
		void setLoop(ALboolean new_should) { should_loop = new_should; };
		void setPosition(glm::vec3& new_pos) { pos = new_pos; };
		void setPosition(float x, float y, float z) { pos = glm::vec3(x, y, z); };
		void setAudio(Audio* new_audio) { audio = new_audio; enablePlay(); };
		void play();
	private:
		bool is_background;
		bool should_play;
		ALboolean should_loop;
		glm::vec3 pos;
		AudioSourceResource *resource;
		Audio *audio;
};

