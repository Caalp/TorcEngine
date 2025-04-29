#pragma once
#include "Input/BaseInput.h"

class Keyboard : public IInputDevice
{
public:
	Keyboard();
	~Keyboard();
	const char* GetName() const override { return "Keyboard"; }
	InputDeviceId GetID() const override { return DI_KEYBOARD; }
	uint32 GetDeviceIndex() const override { return 1; };
	InputDeviceType GetDeviceType() const override { return InputDeviceType::IDT_Keyboard;  }
	void PushInputEvent(InputEvent _event) override;
	virtual InputSymbol* GetInputSymbol(KeyCode keyCode) override;
	const char* GetKeyName(KeyCode key) const override;
	void Initialize(BaseInput* BaseInput) override;
	virtual void Update(BaseInput* pBaseInput) override;

	virtual bool IsConnected() const { return m_isConnected; }
	virtual void SetConnectionStatus(bool status) { m_isConnected = status; }
private:
	void SetupKeys(BaseInput* pBaseInput);
private:
	std::map<KeyCode, InputSymbol*> m_inputMap;
	bool m_isConnected;
};