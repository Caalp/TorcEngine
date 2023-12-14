#pragma once
#include "Core/Input/BaseInput.h"

class Mouse : public IInputDevice
{
public:
	Mouse();
	~Mouse();
	void Initialize(BaseInput* BaseInput) override;
	const char* GetName() const override { return "Mouse"; }
	InputDeviceId GetID() const override { return DI_MOUSE; }
	uint32 GetDeviceIndex() const override { return 0; }
	InputDeviceType GetDeviceType() const { return InputDeviceType::IDT_Mouse; };
	void PushInputEvent(InputEvent _event) override;
	const char* GetKeyName(KeyCode key) const override;
	virtual InputSymbol* GetInputSymbol(KeyCode keyCode) override;
	float GetMouseXAbsolute() const { return 0.0f; };
	float GetMouseYAbsolute() const { return 0.0f; };

	float GetMouseXRelative() const { return 0.0f; };
	float GetMouseYRelative() const { return 0.0f; };

	void Update(BaseInput* pBaseInput) override;

	virtual bool IsConnected() const { return m_isConnected; }
	virtual void SetConnectionStatus(bool status) { m_isConnected = status; }

private:
	void SetupKeys(BaseInput* pBaseInput);

private:
	std::map<KeyCode, InputSymbol*> m_inputMap;
	bool m_isConnected;
};