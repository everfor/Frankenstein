#include "audio.h"
#include "audio_engine.h"
#include "core_engine.h"

Audio::Audio(std::string& file_name) : engine(NULL)
{
	resource = AudioResource::_get_resource(file_name);
}

Audio::~Audio()
{
}

void Audio::setEngine(CoreEngine *core)
{
	engine = core->getAudioEngine();
	core->getAudioEngine()->addAudio(this);
}

void Audio::play(glm::vec3& source_pos, bool loop)
{
	engine->playAudio(this, source_pos, loop);
}
