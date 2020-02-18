#include "InputManager.h"


namespace AwesomeEngine
{
	InputManager::InputManager()
	{

	}


	void InputManager::OnKeyDown(KeyCode::Key code)
	{
		mKeyMapper[(int)code] = true;
	}

	void InputManager::OnKeyUp(KeyCode::Key code)
	{
		mKeyMapper[(int)code] = false;
	}

	bool InputManager::IsKeyPressed(KeyCode::Key code)
	{
		return mKeyMapper[(int)code];
	}

	bool InputManager::IsKeyReleased(KeyCode::Key code)
	{
		return !mKeyMapper[(int)code];
	}


}