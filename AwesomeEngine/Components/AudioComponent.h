#pragma once
#include "AudioSystem.h"
#include "Audio.h"

namespace AwesomeEngine
{
	class AudioComponent
	{
	public:
		AudioComponent(AudioSystem *givenAudSystem);
		void LoadSound(std::string filepath);
		void Play(bool isLooping);
		void Stop(bool stopImmediately);
		void Resume();
		void Pause();
		void SetVolume(float volume);

	private:
		std::unique_ptr<DirectX::SoundEffect> m_SoundEffectFile;
		std::unique_ptr<DirectX::SoundEffectInstance> m_SoundEffect;
		AudioSystem *audSystem;
		float soundVolume;
	};
}

