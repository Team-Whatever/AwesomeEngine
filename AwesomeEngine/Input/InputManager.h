#pragma once
#include "KeyCodes.h"

namespace AwesomeEngine
{
	class InputManager
	{
		explicit InputManager();
	public:
		static InputManager& GetInstance()
		{
			static InputManager instance;
			return instance;
		}

	public:
		void OnKeyDown(KeyCode::Key code);
		void OnKeyUp(KeyCode::Key code);
		bool IsKeyPressed(KeyCode::Key code);
		bool IsKeyReleased(KeyCode::Key code);
			

	private:
		bool mKeyMapper[256];

	};
}
