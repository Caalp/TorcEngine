#pragma once
#include "Core/System/ISystem.h"

// NOTE(cagri): this is redefinition of values defined in BaseInput.h
#define DI_MOUSE 0
#define DI_KEYBOARD 1

struct InputEvent;
struct GamepadState;
class Gamepad;

enum KeyCode : uint32;
struct Battery
{
	enum class BatteryType
	{
		DISCONNECTED,
		WIRED,
		ALKALINE,
		NIMH,
		UNKNOWN,
	};
	
	enum class BatteryLevel
	{
		EMPTY,
		LOW,
		MEDIUM,
		FULL,
	};

	BatteryType type;
	BatteryLevel level;
};

struct GamepadState
{
	uint32  buttons;
	float thumbLX;
	float thumbLY;
	float thumbRX;
	float thumbRY;
	uint8  leftTrigger;
	uint8  rightTrigger;
};

struct XInputDevice
{
	int32 deviceIndex;
	bool isConnected;
	uint32 lastStatePacketNumber;
	bool hasStateChanged;
	bool enabled;
	Gamepad* gamepad;
};

typedef std::vector<XInputDevice> GamepadDeviceList;

namespace PlatformGamepad
{
	// enumerates and initalizes gamepads and returns number of
	// gamepads initialized
	int Initialize(Gamepad* gamepad);

	// Checks the state of gamepad for given idx if its state changed
	// since last update
	bool HasStateChanged(int idx);

	// Sets motor rumble effects for given controller
	void SetFeedback(uint16_t leftMotorSpeed, uint16_t rightMotorSpeed, int idx);

	// if enable is false, stop sending state changes
	void Enable(bool enable);

	// initializes battery struct with battery information for device at index idx
	void GetBatteryInfo(Battery* battery, int idx);

	bool IsConnected(int idx);

	bool GetState(GamepadState* state, int idx);

	void HandleDeviceChange();

	GamepadDeviceList* GetGamepadDeviceList();

};

class PlatformInput : public IWindowEventListener
{
public:
	~PlatformInput() = default;
	void Initialize(SystemGlobalEnvironment& env, WindowBase* targetWindow);
	void Release();
	void GetInputEvents(std::vector<InputEvent>& events);
	virtual bool OnWindowEvent(TORC_HWND hWnd, uint32 msg, uint64 wparam, uint64 lparam) override;
};