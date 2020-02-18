#include "AudioSystem.h"
#include <Input/InputManager.h>
#include "Components/AudioComponent.h"

namespace AwesomeEngine
{
	AudioSystem::AudioSystem()
	{
		requireComponent<AudioComponent>();

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

	void AudioSystem::Update(float delta)
	{
		static bool testPlaySound = false;
		for (auto& e : getEntities())
		{
			auto& audio = e.getComponent<AudioComponent>();

			// for test
			if (InputManager::GetInstance().IsKeyPressed(KeyCode::Key::Space))
			{
				if (testPlaySound == false)
				{
					audio.Play(false);
					testPlaySound = true;
				}
			}
			else
			{
				testPlaySound = false;
			}
		}
	}
}
