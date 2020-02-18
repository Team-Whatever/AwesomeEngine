#pragma once
#include "Audio.h"
#include <string>

namespace AwesomeEngine
{
	//class AudioSystem;
	class AudioComponent
	{
	public:
		//AudioComponent(AudioSystem *givenAudSystem);
		AudioComponent() = default;
		AudioComponent(std::wstring audioFilePath);
		AudioComponent(const AudioComponent& other);
		AudioComponent operator= (const AudioComponent& other);
		
		void LoadSound(std::wstring filepath);
		void Play(bool isLooping);
		void Stop(bool stopImmediately);
		void Resume();
		void Pause();
		void SetVolume(float volume);

	private:
		std::unique_ptr<DirectX::SoundEffect> m_SoundEffectFile;
		std::unique_ptr<DirectX::SoundEffectInstance> m_SoundEffect;
		//AudioSystem *audSystem;
		float soundVolume;
		std::wstring m_EffectFilePath;
	};
}

