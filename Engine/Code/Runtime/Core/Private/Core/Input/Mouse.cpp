#include "Input/Mouse.h"
#include "Application.h"
#include "Logging/Logger.h"

namespace
{
	std::map<KeyCode, KeyName> keyNames;
	void SetupKeyNames()
	{
		keyNames[KeyCode::KC_Mouse1] = { KeyCode::KC_Mouse1, "KeyCode::KC_Mouse1" };
		keyNames[KeyCode::KC_Mouse2] = { KeyCode::KC_Mouse2, "KeyCode::KC_Mouse2" };
		keyNames[KeyCode::KC_Mouse3] = { KeyCode::KC_Mouse3, "KeyCode::KC_Mouse3" };
		keyNames[KeyCode::KC_Mouse4] = { KeyCode::KC_Mouse4, "KeyCode::KC_Mouse4" };
		keyNames[KeyCode::KC_Mouse5] = { KeyCode::KC_Mouse5, "KeyCode::KC_Mouse5" };
		keyNames[KeyCode::KC_MouseWheelUp] = { KeyCode::KC_MouseWheelUp, "KeyCode::KC_MouseWheelUp" };
		keyNames[KeyCode::KC_MouseWheelDown] = { KeyCode::KC_MouseWheelDown, "KeyCode::KC_MouseWheelDown" };
		keyNames[KeyCode::KC_MouseX] = { KeyCode::KC_MouseX, "KeyCode::KC_MouseX" };
		keyNames[KeyCode::KC_MouseY] = { KeyCode::KC_MouseY, "KeyCode::KC_MouseY" };
		keyNames[KeyCode::KC_MouseZ] = { KeyCode::KC_MouseZ, "KeyCode::KC_MouseZ" };
		keyNames[KeyCode::KC_MouseXAbsolute] = { KeyCode::KC_MouseXAbsolute, "KeyCode::KC_MouseXAbsolute" };
		keyNames[KeyCode::KC_MouseYAbsolute] = { KeyCode::KC_MouseYAbsolute, "KeyCode::KC_MouseYAbsolute" };
	}
}

Mouse::Mouse()
{
	SetupKeyNames();
}

Mouse::~Mouse()
{
	InputSymbol* symbol = m_inputMap[(KeyCode)KC_MOUSE_RANGE_START];
	delete[] symbol;
}

void Mouse::Initialize(BaseInput* pBaseInput)
{
	pBaseInput->AddDevice(this);
	SetupKeys(pBaseInput);
}

void Mouse::PushInputEvent(InputEvent _event)
{
	//m_events.push_back(_event);
}

const char* Mouse::GetKeyName(KeyCode key) const
{
	return keyNames[key].c_str();
}

InputSymbol* Mouse::GetInputSymbol(KeyCode keyCode)
{
	return m_inputMap[keyCode];
}

void Mouse::Update(BaseInput* pBaseInput)
{
	auto eventList = pBaseInput->GetInputEventsList();
	auto begin = eventList->begin();
	auto end = eventList->end();

	while (begin != end)
	{
		InputEvent& inputEvent = *begin;
		begin++;
		if (keyNames.find(inputEvent.key) == keyNames.end())
		{
			continue;
		}
		if (m_inputMap[inputEvent.key] == nullptr)
		{
			TE_Warning(LogChannel::LC_Core, "Mouse::Update - Invalid KeyCode");
			continue;
		}
		InputSymbol* symbol = m_inputMap[inputEvent.key];
		if (inputEvent.value != symbol->value)
		{
			symbol->AssignTo(inputEvent);

			inputEvent.state = InputState::IS_Changed;
			inputEvent.state |= ((inputEvent.value == 1.0f) ? InputState::IS_Down : InputState::IS_Released);

			if (inputEvent.value == 0.0f && symbol->value == 1.0f)
			{
				inputEvent.state |= InputState::IS_Pressed;

				if (symbol->symbolType == InputSymbol::SymbolType::ST_Button)
				{
					symbol->halfTransitionCount++;
				}
			}
			
			// handle mouse wheel
			if (inputEvent.key == KeyCode::KC_MouseWheelUp || inputEvent.key == KeyCode::KC_MouseWheelDown)
			{
				// nothing done rn
			}
		}

		// update to the latest state of the key symbol
		symbol->value = inputEvent.value;
	}
}

void Mouse::SetupKeys(BaseInput* pBaseInput)
{
	InputSymbol* inputSymbols = new InputSymbol[(uint32)KeyCode::MouseCount];
	for (int symbolIndex = 0; symbolIndex < keyNames.size(); ++symbolIndex)
	{
		KeyCode keyCode = (KeyCode)(KC_MOUSE_RANGE_START + symbolIndex);
		InputSymbol::SymbolType symbolType = (keyCode == KeyCode::KC_MouseWheelUp || 
											  keyCode == KeyCode::KC_MouseWheelDown) ?
			InputSymbol::SymbolType::ST_Axis: InputSymbol::SymbolType::ST_Button;
		inputSymbols[symbolIndex].Create(keyNames[keyCode],
										 keyCode,
										 DI_MOUSE,
										 symbolType,
										 InputDeviceType::IDT_Mouse);
		m_inputMap[keyCode] = &inputSymbols[symbolIndex];
	}
}