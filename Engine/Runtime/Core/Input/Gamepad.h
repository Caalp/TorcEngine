#pragma once
#include "Core/Input/BaseInput.h"

struct GamepadState;
struct Battery;

class Gamepad : public IInputDevice
{
public:
	Gamepad(int32 index);
	~Gamepad();
	void Initialize(BaseInput* BaseInput) override;
	const char* GetName() const override { return "Gamepad"; }
	InputDeviceId GetID() const override { return DI_GAMEPAD; }
	uint32 GetDeviceIndex() const override { return DI_GAMEPAD + m_gamepadIndex; }
	InputDeviceType GetDeviceType() const { return InputDeviceType::IDT_Gamepad; };
	void PushInputEvent(InputEvent _event) override;
	const char* GetKeyName(KeyCode key) const override;
	virtual InputSymbol* GetInputSymbol(KeyCode keyCode) override;
	void Update(BaseInput* pBaseInput) override;

	virtual bool IsConnected() const { return m_isConnected; }
	virtual void SetConnectionStatus(bool status) { m_isConnected = status; }

private:
	void SetupKeys(BaseInput* pBaseInput);

private:
	std::map<KeyCode, InputSymbol*> m_symbolMap;
	GamepadState* m_gamepadState;
	Battery* m_batteryInfo;
	int32 m_gamepadIndex;
	bool m_isConnected;
};