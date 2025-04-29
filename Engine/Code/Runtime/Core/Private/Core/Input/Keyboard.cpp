#include "Input/Keyboard.h"
#include "Application.h"
#include "Logging/Logger.h"

namespace
{
	std::map<KeyCode, KeyName> keyNames;
	void SetupKeyNames()
	{
		keyNames[KeyCode::KC_ArrowUp] = { KeyCode::KC_ArrowUp, "KeyCode::KC_ArrowUp" };
		keyNames[KeyCode::KC_ArrowDown] = { KeyCode::KC_ArrowDown, "KeyCode::KC_ArrowDown" };
		keyNames[KeyCode::KC_ArrowLeft] = { KeyCode::KC_ArrowLeft, "KeyCode::KC_ArrowLeft" };
		keyNames[KeyCode::KC_ArrowRight] = { KeyCode::KC_ArrowRight, "KeyCode::KC_ArrowRight" };
		keyNames[KeyCode::KC_Space] = { KeyCode::KC_Space, "KeyCode::KC_Space" };
		keyNames[KeyCode::KC_BackSpace] = { KeyCode::KC_Space, "KeyCode::KC_BackSpace" };
		keyNames[KeyCode::KC_RShift] = { KeyCode::KC_RShift, "KeyCode::KC_RShift" };
		keyNames[KeyCode::KC_LShift] = { KeyCode::KC_LShift, "KeyCode::KC_LShift" };
		keyNames[KeyCode::KC_RCtrl] = { KeyCode::KC_RCtrl, "KeyCode::KC_RCtrl" };
		keyNames[KeyCode::KC_LCtrl] = { KeyCode::KC_LCtrl, "KeyCode::KC_LCtrl" };
		keyNames[KeyCode::KC_Enter] = { KeyCode::KC_Enter, "KeyCode::KC_Enter" };
		keyNames[KeyCode::KC_Escape] = { KeyCode::KC_Escape, "KeyCode::KC_Escape" };
		keyNames[KeyCode::KC_Semicolon] = { KeyCode::KC_Semicolon, "KeyCode::KC_Semicolon" };
		keyNames[KeyCode::KC_Apostrophe] = { KeyCode::KC_Apostrophe, "KeyCode::KC_Apostrophe" };
		keyNames[KeyCode::KC_Tilde] = { KeyCode::KC_Tilde, "KeyCode::KC_Tilde" };
		keyNames[KeyCode::KC_Backslash] = { KeyCode::KC_Backslash, "KeyCode::KC_Backslash" };
		keyNames[KeyCode::KC_Multiply] = { KeyCode::KC_Multiply, "KeyCode::KC_Multiply" };
		keyNames[KeyCode::KC_Add] = { KeyCode::KC_Add, "KeyCode::KC_Add" };
		keyNames[KeyCode::KC_Separator] = { KeyCode::KC_Separator, "KeyCode::KC_Separator" };
		keyNames[KeyCode::KC_Subtract] = { KeyCode::KC_Subtract, "KeyCode::KC_Subtract" };
		keyNames[KeyCode::KC_Decimal] = { KeyCode::KC_Decimal, "KeyCode::KC_Decimal" };
		keyNames[KeyCode::KC_Divide] = { KeyCode::KC_Divide, "KeyCode::KC_Divide" };
		keyNames[KeyCode::KC_Colon] = { KeyCode::KC_Colon, "KeyCode::KC_Colon" };
		keyNames[KeyCode::KC_Underline] = { KeyCode::KC_Underline, "KeyCode::KC_Underline" };
		keyNames[KeyCode::KC_Print] = { KeyCode::KC_Print, "KeyCode::KC_Print" };
		keyNames[KeyCode::KC_RAlt] = { KeyCode::KC_RAlt, "KeyCode::KC_RAlt" };
		keyNames[KeyCode::KC_LAlt] = { KeyCode::KC_LAlt, "KeyCode::KC_LAlt" };
		keyNames[KeyCode::KC_Pause] = { KeyCode::KC_Pause, "KeyCode::KC_Pause" };
		keyNames[KeyCode::KC_Home] = { KeyCode::KC_Home, "KeyCode::KC_Home" };
		keyNames[KeyCode::KC_PgUp] = { KeyCode::KC_PgUp, "KeyCode::KC_PgUp" };
		keyNames[KeyCode::KC_End] = { KeyCode::KC_End, "KeyCode::KC_End" };
		keyNames[KeyCode::KC_PgDn] = { KeyCode::KC_PgDn, "KeyCode::KC_PgDn" };
		keyNames[KeyCode::KC_Insert] = { KeyCode::KC_Insert, "KeyCode::KC_Insert" };
		keyNames[KeyCode::KC_Delete] = { KeyCode::KC_Delete, "KeyCode::KC_Delete" };
		keyNames[KeyCode::KC_LWin] = { KeyCode::KC_LWin, "KeyCode::KC_LWin" };
		keyNames[KeyCode::KC_RWin] = { KeyCode::KC_RWin, "KeyCode::KC_RWin" };
		keyNames[KeyCode::KC_CapsLock] = { KeyCode::KC_CapsLock, "KeyCode::KC_CapsLock" };
		keyNames[KeyCode::KC_ScrollLock] = { KeyCode::KC_ScrollLock, "KeyCode::KC_ScrollLock" };
		keyNames[KeyCode::KC_NumLock] = { KeyCode::KC_NumLock, "KeyCode::KC_NumLock" };
		keyNames[KeyCode::KC_Tab] = { KeyCode::KC_Tab, "KeyCode::KC_Tab" };
		keyNames[KeyCode::KC_NP_Multiply] = { KeyCode::KC_NP_Multiply, "KeyCode::KC_NP_Multiply" };
		keyNames[KeyCode::KC_NP_Add] = { KeyCode::KC_NP_Add, "KeyCode::KC_NP_Add" };
		keyNames[KeyCode::KC_NP_Subtract] = { KeyCode::KC_NP_Subtract, "KeyCode::KC_NP_Subtract" };
		keyNames[KeyCode::KC_NP_0] = { KeyCode::KC_NP_0, "KeyCode::KC_NP_0" };
		keyNames[KeyCode::KC_NP_1] = { KeyCode::KC_NP_1, "KeyCode::KC_NP_1" };
		keyNames[KeyCode::KC_NP_2] = { KeyCode::KC_NP_2, "KeyCode::KC_NP_2" };
		keyNames[KeyCode::KC_NP_3] = { KeyCode::KC_NP_3, "KeyCode::KC_NP_3" };
		keyNames[KeyCode::KC_NP_4] = { KeyCode::KC_NP_4, "KeyCode::KC_NP_4" };
		keyNames[KeyCode::KC_NP_5] = { KeyCode::KC_NP_5, "KeyCode::KC_NP_5" };
		keyNames[KeyCode::KC_NP_6] = { KeyCode::KC_NP_6, "KeyCode::KC_NP_6" };
		keyNames[KeyCode::KC_NP_7] = { KeyCode::KC_NP_7, "KeyCode::KC_NP_7" };
		keyNames[KeyCode::KC_NP_8] = { KeyCode::KC_NP_8, "KeyCode::KC_NP_8" };
		keyNames[KeyCode::KC_NP_9] = { KeyCode::KC_NP_9, "KeyCode::KC_NP_9" };
		keyNames[KeyCode::KC_NP_Enter] = { KeyCode::KC_NP_Enter, "KeyCode::KC_NP_Enter" };
		keyNames[KeyCode::KC_0] = { KeyCode::KC_0, "KeyCode::KC_0" };
		keyNames[KeyCode::KC_1] = { KeyCode::KC_1, "KeyCode::KC_1" };
		keyNames[KeyCode::KC_2] = { KeyCode::KC_2, "KeyCode::KC_2" };
		keyNames[KeyCode::KC_3] = { KeyCode::KC_3, "KeyCode::KC_3" };
		keyNames[KeyCode::KC_4] = { KeyCode::KC_4, "KeyCode::KC_4" };
		keyNames[KeyCode::KC_5] = { KeyCode::KC_5, "KeyCode::KC_5" };
		keyNames[KeyCode::KC_6] = { KeyCode::KC_6, "KeyCode::KC_6" };
		keyNames[KeyCode::KC_7] = { KeyCode::KC_7, "KeyCode::KC_7" };
		keyNames[KeyCode::KC_8] = { KeyCode::KC_8, "KeyCode::KC_8" };
		keyNames[KeyCode::KC_9] = { KeyCode::KC_9, "KeyCode::KC_9" };
		keyNames[KeyCode::KC_F1] = { KeyCode::KC_F1, "KeyCode::KC_F1" };
		keyNames[KeyCode::KC_F2] = { KeyCode::KC_F2, "KeyCode::KC_F2" };
		keyNames[KeyCode::KC_F3] = { KeyCode::KC_F3, "KeyCode::KC_F3" };
		keyNames[KeyCode::KC_F4] = { KeyCode::KC_F4, "KeyCode::KC_F4" };
		keyNames[KeyCode::KC_F5] = { KeyCode::KC_F5, "KeyCode::KC_F5" };
		keyNames[KeyCode::KC_F6] = { KeyCode::KC_F6, "KeyCode::KC_F6" };
		keyNames[KeyCode::KC_F7] = { KeyCode::KC_F7, "KeyCode::KC_F7" };
		keyNames[KeyCode::KC_F8] = { KeyCode::KC_F8, "KeyCode::KC_F8" };
		keyNames[KeyCode::KC_F9] = { KeyCode::KC_F9, "KeyCode::KC_F9" };
		keyNames[KeyCode::KC_F10] = { KeyCode::KC_F10, "KeyCode::KC_F10" };
		keyNames[KeyCode::KC_F11] = { KeyCode::KC_F11, "KeyCode::KC_F11" };
		keyNames[KeyCode::KC_F12] = { KeyCode::KC_F12, "KeyCode::KC_F12" };
		keyNames[KeyCode::KC_A] = { KeyCode::KC_A, "KeyCode::KC_A" };
		keyNames[KeyCode::KC_B] = { KeyCode::KC_B, "KeyCode::KC_B" };
		keyNames[KeyCode::KC_C] = { KeyCode::KC_C, "KeyCode::KC_C" };
		keyNames[KeyCode::KC_D] = { KeyCode::KC_D, "KeyCode::KC_D" };
		keyNames[KeyCode::KC_E] = { KeyCode::KC_E, "KeyCode::KC_E" };
		keyNames[KeyCode::KC_F] = { KeyCode::KC_F, "KeyCode::KC_F" };
		keyNames[KeyCode::KC_G] = { KeyCode::KC_G, "KeyCode::KC_G" };
		keyNames[KeyCode::KC_H] = { KeyCode::KC_H, "KeyCode::KC_H" };
		keyNames[KeyCode::KC_I] = { KeyCode::KC_I, "KeyCode::KC_I" };
		keyNames[KeyCode::KC_J] = { KeyCode::KC_J, "KeyCode::KC_J" };
		keyNames[KeyCode::KC_K] = { KeyCode::KC_K, "KeyCode::KC_K" };
		keyNames[KeyCode::KC_L] = { KeyCode::KC_L, "KeyCode::KC_L" };
		keyNames[KeyCode::KC_M] = { KeyCode::KC_M, "KeyCode::KC_M" };
		keyNames[KeyCode::KC_N] = { KeyCode::KC_N, "KeyCode::KC_N" };
		keyNames[KeyCode::KC_O] = { KeyCode::KC_O, "KeyCode::KC_O" };
		keyNames[KeyCode::KC_P] = { KeyCode::KC_P, "KeyCode::KC_P" };
		keyNames[KeyCode::KC_Q] = { KeyCode::KC_Q, "KeyCode::KC_Q" };
		keyNames[KeyCode::KC_R] = { KeyCode::KC_R, "KeyCode::KC_R" };
		keyNames[KeyCode::KC_S] = { KeyCode::KC_S, "KeyCode::KC_S" };
		keyNames[KeyCode::KC_T] = { KeyCode::KC_T, "KeyCode::KC_T" };
		keyNames[KeyCode::KC_U] = { KeyCode::KC_U, "KeyCode::KC_U" };
		keyNames[KeyCode::KC_V] = { KeyCode::KC_V, "KeyCode::KC_V" };
		keyNames[KeyCode::KC_W] = { KeyCode::KC_W, "KeyCode::KC_W" };
		keyNames[KeyCode::KC_X] = { KeyCode::KC_X, "KeyCode::KC_X" };
		keyNames[KeyCode::KC_Y] = { KeyCode::KC_Y, "KeyCode::KC_Y" };
		keyNames[KeyCode::KC_Z] = { KeyCode::KC_Z, "KeyCode::KC_Z" };
	}
}

Keyboard::Keyboard() 
{
	SetupKeyNames();
}

Keyboard::~Keyboard()
{
	InputSymbol* symbol = m_inputMap[(KeyCode)KC_KEYBOARD_RANGE_START];
	delete[] symbol;
}

void Keyboard::PushInputEvent(InputEvent inputEvent)
{}

InputSymbol* Keyboard::GetInputSymbol(KeyCode keyCode)
{
	return m_inputMap[keyCode];
}

const char* Keyboard::GetKeyName(KeyCode key) const
{
	return keyNames[key].c_str();
}

void Keyboard::Initialize(BaseInput* pBaseInput)
{
	pBaseInput->AddDevice(this);
	SetupKeys(pBaseInput);
}

void Keyboard::Update(BaseInput* pBaseInput)
{
	auto eventList = pBaseInput->GetInputEventsList();
	auto begin = eventList->begin();
	auto end = eventList->end();
	while(begin != end)
	{
		InputEvent& inputEvent = *begin;
		begin++;
		if (keyNames.find(inputEvent.key) == keyNames.end())
		{
			continue;
		}

		if (m_inputMap[inputEvent.key] == nullptr)
		{
			TE_Warning(LogChannel::LC_Core, "Keyboard::Update - Invalid KeyCode");
			continue;
		}

		// process modifier key
		InputSymbol* symbol = m_inputMap[inputEvent.key];
		if (symbol->symbolType == InputSymbol::ST_Button)
		{
			symbol->AssignTo(inputEvent);
			if ((inputEvent.value == 0.0f && symbol->value == 1.0f) ||
				(inputEvent.value == 1.0f && symbol->value == 0.0f))
			{
				inputEvent.state |= InputState::IS_Changed;
				symbol->halfTransitionCount++;
			}
			if (inputEvent.value == 0.0f && symbol->value == 1.0f)
			{
				inputEvent.state |= InputState::IS_Pressed | IS_Released;
			}
			else if (inputEvent.value == 1.0f && symbol->value == 0.0f)
			{
				inputEvent.state |= InputState::IS_Down;
			}
			else
			{
				inputEvent.state &= ~InputState::IS_Changed;
			}
			symbol->value = inputEvent.value;
		}
		else if (symbol->symbolType == InputSymbol::ST_Toggle)
		{
			symbol->AssignTo(inputEvent);
			if ((inputEvent.value == 0.0f && symbol->value == 1.0f) || 
				(inputEvent.value == 1.0f && symbol->value == 0.0f))
			{
				symbol->halfTransitionCount++;
				inputEvent.state |= InputState::IS_Changed;
			}

			if (pBaseInput->IsModifierKey(inputEvent.key))
			{
				ModifierKeys mk = pBaseInput->ToModifierKey(inputEvent.key);
				if (symbol->halfTransitionCount % 4 == 1)
				{
					pBaseInput->SetModifier((int)mk);
					inputEvent.state |= InputState::IS_Down;
				}
				else if (symbol->halfTransitionCount % 4 == 3)
				{
					pBaseInput->ClearModifier((int)mk);
					inputEvent.state |= InputState::IS_Down;
				}
				else
				{
					inputEvent.state |= InputState::IS_Released | InputState::IS_Pressed;
				}
			}
			symbol->value = inputEvent.value;		
		}
	}
}

void Keyboard::SetupKeys(BaseInput* pBaseInput)
{
	InputSymbol* inputSymbols = new InputSymbol[(uint32)KeyCode::KeyboardCount];
	for (int symbolIndex = 0; symbolIndex < keyNames.size(); ++symbolIndex)
	{
		KeyCode keyCode = (KeyCode)(KC_KEYBOARD_RANGE_START + symbolIndex);
		InputSymbol::SymbolType symbolType = (!pBaseInput->IsModifierKey(keyCode)) ?
			InputSymbol::SymbolType::ST_Button : InputSymbol::SymbolType::ST_Toggle;
		inputSymbols[symbolIndex].Create(keyNames[keyCode],
										 keyCode,
										 DI_KEYBOARD,
										 symbolType,
										 InputDeviceType::IDT_Keyboard);
		m_inputMap[keyCode] = &inputSymbols[symbolIndex];
	}
}