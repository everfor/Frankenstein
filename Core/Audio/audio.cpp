#include "audio.h"
#include "audio_engine.h"
#include "core_engine.h"

Audio::Audio(const std::string& file_name) : engine(NULL)
{
	resource = AudioResource::_get_resource(std::string(file_name));
}

Audio::~Audio()
{
}

void Audio::setEngine(CoreEngine *core)
{
	engine = core->getAudioEngine();
}

void Audio::play(glm::vec3& source_pos, bool loop)
{
	engine->playAudio(this, source_pos, loop);
}
