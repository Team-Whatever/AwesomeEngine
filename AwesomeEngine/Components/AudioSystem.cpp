#include "AudioSystem.h"

namespace AwesomeEngine
{
	AudioSystem::AudioSystem()
	{
		DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AudioEngine_Default;
		m_audEngine = std::make_unique<DirectX::AudioEngine>(eflags);
	}

	void AudioSystem::SuspendAudio()
	{
		m_audEngine->Suspend();
	}

	void AudioSystem::ResumeAudio()
	{
		m_audEngine->Resume();
	}
}
