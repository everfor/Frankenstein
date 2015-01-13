#pragma once

#include "audio_resource.h"

#include <AL/al.h>
#include <AL/alc.h>

class AudioModel
{
	public:
		AudioModel() {};
		virtual ~AudioModel() {};
		void setFormat(ALuint new_format) { format = new_format; };
		ALuint getFormat() { return format; };
		void setSize(ALsizei new_size) { size = new_size; };
		ALsizei getSize() { return size; };
		void setSampleRate(ALsizei new_rate) { sample_rate = new_rate; };
		ALsizei getSampleRate() { return sample_rate; };
		void initializeData(int size) { data = (char*)malloc(size * sizeof(char)); };
		void setData(char* new_data) { data = new_data; };
		char* getData() { return data; };
		void setDuration(float new_duration) { duration = new_duration; };
		float getDuration() { return duration; };
		virtual void loadToAudio(AudioResource* audio) {};
	private:
		ALuint format;
		ALsizei size;
		ALsizei sample_rate;
		float duration;
		char* data;
};

