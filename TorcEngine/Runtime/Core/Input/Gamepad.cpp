#include "pch.h"
#include "Gamepad.h"
#include "Core/Application.h"
#include "Platform/PlatformInput.h"

namespace
{
	std::map<KeyCode, KeyName> keyNames;
	void SetupKeyNames()
	{
		keyNames[KeyCode::KC_Gamepad_A] = { KeyCode::KC_Gamepad_A, "KeyCode::KC_Gamepad_A" };
		keyNames[KeyCode::KC_Gamepad_B] = { KeyCode::KC_Gamepad_B, "KeyCode::KC_Gamepad_B" };
		keyNames[KeyCode::KC_Gamepad_X] = { KeyCode::KC_Gamepad_X, "KeyCode::KC_Gamepad_X" };
		keyNames[KeyCode::KC_Gamepad_Y] = { KeyCode::KC_Gamepad_Y, "KeyCode::KC_Gamepad_Y" };
		keyNames[KeyCode::KC_Gamepad_RShoulder] = { KeyCode::KC_Gamepad_RShoulder, "KeyCode::KC_Gamepad_RShoulder" };
		keyNames[KeyCode::KC_Gamepad_LShoulder] = { KeyCode::KC_Gamepad_LShoulder, "KeyCode::KC_Gamepad_LShoulder" };
		keyNames[KeyCode::KC_Gamepad_LTrigger] = { KeyCode::KC_Gamepad_LTrigger, "KeyCode::KC_Gamepad_LTrigger" };
		keyNames[KeyCode::KC_Gamepad_RTrigger] = { KeyCode::KC_Gamepad_RTrigger, "KeyCode::KC_Gamepad_RTrigger" };
		keyNames[KeyCode::KC_Gamepad_DPadUp] = { KeyCode::KC_Gamepad_DPadUp, "KeyCode::KC_Gamepad_DPadUp" };
		keyNames[KeyCode::KC_Gamepad_DPadDown] = { KeyCode::KC_Gamepad_DPadDown, "KeyCode::KC_Gamepad_DPadDown" };
		keyNames[KeyCode::KC_Gamepad_DPadLeft] = { KeyCode::KC_Gamepad_DPadLeft, "KeyCode::KC_Gamepad_DPadLeft" };
		keyNames[KeyCode::KC_Gamepad_DPadRight] = { KeyCode::KC_Gamepad_DPadRight, "KeyCode::KC_Gamepad_DPadRight" };
		keyNames[KeyCode::KC_Gamepad_Menu] = { KeyCode::KC_Gamepad_Menu, "KeyCode::KC_Gamepad_Menu" };
		keyNames[KeyCode::KC_Gamepad_View] = { KeyCode::KC_Gamepad_View, "KeyCode::KC_Gamepad_View" };
		keyNames[KeyCode::KC_Gamepad_LThumb] = { KeyCode::KC_Gamepad_LThumb, "KeyCode::KC_Gamepad_LThumb" };
		keyNames[KeyCode::KC_Gamepad_RThumb] = { KeyCode::KC_Gamepad_RThumb, "KeyCode::KC_Gamepad_RThumb" };
		keyNames[KeyCode::KC_Gamepad_LThumbUp] = { KeyCode::KC_Gamepad_LThumbUp, "KeyCode::KC_Gamepad_LThumbUp" };
		keyNames[KeyCode::KC_Gamepad_LThumbDown] = { KeyCode::KC_Gamepad_LThumbDown, "KeyCode::KC_Gamepad_LThumbDown" };
		keyNames[KeyCode::KC_Gamepad_LThumbRight] = { KeyCode::KC_Gamepad_LThumbRight, "KeyCode::KC_Gamepad_LThumbRight" };
		keyNames[KeyCode::KC_Gamepad_LThumbLeft] = { KeyCode::KC_Gamepad_LThumbLeft, "KeyCode::KC_Gamepad_LThumbLeft" };
		keyNames[KeyCode::KC_Gamepad_RThumbUp] = { KeyCode::KC_Gamepad_RThumbUp, "KeyCode::KC_Gamepad_RThumbUp" };
		keyNames[KeyCode::KC_Gamepad_RThumbDown] = { KeyCode::KC_Gamepad_RThumbDown, "KeyCode::KC_Gamepad_RThumbDown" };
		keyNames[KeyCode::KC_Gamepad_RThumbRight] = { KeyCode::KC_Gamepad_RThumbRight, "KeyCode::KC_Gamepad_RThumbRight" };
		keyNames[KeyCode::KC_Gamepad_RThumbLeft] = { KeyCode::KC_Gamepad_RThumbLeft, "KeyCode::KC_Gamepad_RThumbLeft" };
	}
}

Gamepad::Gamepad(int32 index)
	: m_gamepadIndex(index)
{
	SetupKeyNames();
	m_gamepadState = new GamepadState{};
	m_batteryInfo = new Battery{};
}

Gamepad::~Gamepad()
{
	InputSymbol* symbol = m_symbolMap[(KeyCode)KC_GAMEPAD_RANGE_START];
	delete[] symbol;
	delete m_gamepadState;
	delete m_batteryInfo;
}

void Gamepad::Initialize(BaseInput* pBaseInput)
{
	pBaseInput->AddDevice(this);
	SetupKeys(pBaseInput);
}

void Gamepad::PushInputEvent(InputEvent _event)
{}

const char* Gamepad::GetKeyName(KeyCode key) const
{
	return keyNames[key].c_str();
}

InputSymbol* Gamepad::GetInputSymbol(KeyCode keyCode)
{
	return m_symbolMap[keyCode];
}

void Gamepad::Update(BaseInput* pBaseInput)
{
	bool hasNewState = PlatformGamepad::GetState(m_gamepadState, m_gamepadIndex);
	if (hasNewState)
	{
		// TODO(cagri): instead of getting a pointer to the list just define a function that pushes events
		auto inputEventList = pBaseInput->GetInputEventsList();
		for (int keyIndex = 0; 
			 keyIndex < KeyCode::GamepadCount % KC_GAMEPAD_RANGE_START;
			 keyIndex++)
		{
			bool buttonState = m_gamepadState->buttons & (1 << keyIndex);
			InputSymbol* symbol = m_symbolMap[(KeyCode)(KC_GAMEPAD_RANGE_START + keyIndex)];
			if (buttonState)
			{
				InputEvent inputEvent;
				symbol->AssignTo(inputEvent);
				if (symbol->symbolType == InputSymbol::ST_Axis)
				{
					if (symbol->key == KeyCode::KC_Gamepad_LTrigger)
					{
						inputEvent.value = m_gamepadState->leftTrigger;
					}
					else if (symbol->key == KeyCode::KC_Gamepad_RTrigger)
					{
						inputEvent.value = m_gamepadState->rightTrigger;
					}
					else if (symbol->key == KeyCode::KC_Gamepad_LThumbUp || 
							 symbol->key == KeyCode::KC_Gamepad_LThumbDown)
					{
						inputEvent.value = m_gamepadState->thumbLY;
					}
					else if (symbol->key == KeyCode::KC_Gamepad_LThumbLeft ||
							 symbol->key == KeyCode::KC_Gamepad_LThumbRight)
					{
						inputEvent.value = m_gamepadState->thumbLX;
					}
					else if (symbol->key == KeyCode::KC_Gamepad_RThumbUp || 
							 symbol->key == KeyCode::KC_Gamepad_RThumbDown)
					{
						inputEvent.value = m_gamepadState->thumbRY;
					}
					else if (symbol->key == KeyCode::KC_Gamepad_RThumbLeft || 
							 symbol->key == KeyCode::KC_Gamepad_RThumbRight)
					{
						inputEvent.value = m_gamepadState->thumbRX;
					}
				}
				else
				{
					inputEvent.value = 1.0f;
				}
				symbol->value = inputEvent.value;
				inputEventList->push_back(inputEvent);
			}
			else
			{
				float oldValue = symbol->value;
				symbol->value = 0.0f;
				if (symbol->symbolType == InputSymbol::ST_Button && oldValue == 1.0f)
				{
					InputEvent inputEvent{};
					symbol->AssignTo(inputEvent);
					inputEventList->push_back(inputEvent);
				}
			}
		}
	}
}

void Gamepad::SetupKeys(BaseInput* pBaseInput)
{
	InputSymbol* inputSymbols = new InputSymbol[(uint32)KeyCode::GamepadCount];
	for (int symbolIndex = 0; symbolIndex < keyNames.size(); ++symbolIndex)
	{
		KeyCode keyCode = (KeyCode)(KC_GAMEPAD_RANGE_START + symbolIndex);
		InputSymbol::SymbolType symbolType = (keyCode == KeyCode::KC_Gamepad_LTrigger ||
											  keyCode == KeyCode::KC_Gamepad_RTrigger ||
											  keyCode == KeyCode::KC_Gamepad_LThumbUp ||
											  keyCode == KeyCode::KC_Gamepad_LThumbDown ||
											  keyCode == KeyCode::KC_Gamepad_LThumbRight ||
											  keyCode == KeyCode::KC_Gamepad_LThumbLeft ||
											  keyCode == KeyCode::KC_Gamepad_RThumbUp ||
											  keyCode == KeyCode::KC_Gamepad_RThumbDown ||
											  keyCode == KeyCode::KC_Gamepad_RThumbRight ||
											  keyCode == KeyCode::KC_Gamepad_RThumbLeft) ?
			InputSymbol::SymbolType::ST_Axis: InputSymbol::SymbolType::ST_Button;
		inputSymbols[symbolIndex].Create(keyNames[keyCode],
										 keyCode,
										 DI_GAMEPAD,
										 symbolType,
										 InputDeviceType::IDT_Gamepad);
		m_symbolMap[keyCode] = &inputSymbols[symbolIndex];
	}
}