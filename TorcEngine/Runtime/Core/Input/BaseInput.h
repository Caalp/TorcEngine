#pragma once

#define DI_MOUSE 0
#define DI_KEYBOARD 1
#define DI_GAMEPAD 2

#define KC_KEYBOARD_RANGE_START 0
#define KC_MOUSE_RANGE_START 256
#define KC_GAMEPAD_RANGE_START 512

typedef uint32_t InputDeviceId;

enum KeyCode : uint32
{
	KC_ArrowUp = KC_KEYBOARD_RANGE_START,
	KC_ArrowDown,
	KC_ArrowLeft,
	KC_ArrowRight,
	KC_Space,
	KC_BackSpace,
	KC_RShift,
	KC_LShift,
	KC_RCtrl,
	KC_LCtrl,
	KC_Enter,
	KC_Escape,
	KC_Semicolon,
	KC_Apostrophe,
	KC_Tilde,
	KC_Backslash,
	KC_Multiply,
	KC_Add,
	KC_Separator,
	KC_Subtract,
	KC_Decimal,
	KC_Divide,
	KC_Colon,
	KC_Underline,
	KC_Print,
	KC_RAlt,
	KC_LAlt,
	KC_Pause,
	KC_Home,
	KC_PgUp,
	KC_End,
	KC_PgDn,
	KC_Insert,
	KC_Delete,
	KC_LWin,
	KC_RWin,
	KC_CapsLock,
	KC_ScrollLock,
	KC_NumLock,
	KC_Tab,
	KC_NP_Multiply,
	KC_NP_Add,
	KC_NP_Subtract,
	KC_NP_0,
	KC_NP_1,
	KC_NP_2,
	KC_NP_3,
	KC_NP_4,
	KC_NP_5,
	KC_NP_6,
	KC_NP_7,
	KC_NP_8,
	KC_NP_9,
	KC_NP_Enter,
	KC_0,
	KC_1,
	KC_2,
	KC_3,
	KC_4,
	KC_5,
	KC_6,
	KC_7,
	KC_8,
	KC_9,
	KC_F1,
	KC_F2,
	KC_F3,
	KC_F4,
	KC_F5,
	KC_F6,
	KC_F7,
	KC_F8,
	KC_F9,
	KC_F10,
	KC_F11,
	KC_F12,
	KC_A,
	KC_B,
	KC_C,
	KC_D,
	KC_E,
	KC_F,
	KC_G,
	KC_H,
	KC_I,
	KC_J,
	KC_K,
	KC_L,
	KC_M,
	KC_N,
	KC_O,
	KC_P,
	KC_Q,
	KC_R,
	KC_S,
	KC_T,
	KC_U,
	KC_V,
	KC_W,
	KC_X,
	KC_Y,
	KC_Z,
	KeyboardCount,
	
	KC_Mouse1 = KC_MOUSE_RANGE_START,
	KC_Mouse2,
	KC_Mouse3,
	KC_Mouse4,
	KC_Mouse5,
	KC_MouseWheelUp,
	KC_MouseWheelDown,
	KC_MouseX,
	KC_MouseY,
	KC_MouseZ,
	KC_MouseXAbsolute,
	KC_MouseYAbsolute,
	KC_MouseLast,
	MouseCount,
	
	KC_Gamepad_A = KC_GAMEPAD_RANGE_START,
	KC_Gamepad_B,
	KC_Gamepad_X,
	KC_Gamepad_Y,
	KC_Gamepad_RShoulder,
	KC_Gamepad_LShoulder,
	KC_Gamepad_LTrigger,
	KC_Gamepad_RTrigger,
	KC_Gamepad_DPadUp,
	KC_Gamepad_DPadDown,
	KC_Gamepad_DPadLeft,
	KC_Gamepad_DPadRight,
	KC_Gamepad_Menu, // start button in 360 controller
	KC_Gamepad_View, // back button for other controllers
	KC_Gamepad_LThumb,
	KC_Gamepad_RThumb,
	KC_Gamepad_LThumbUp,
	KC_Gamepad_LThumbDown,
	KC_Gamepad_LThumbRight,
	KC_Gamepad_LThumbLeft,
	KC_Gamepad_RThumbUp,
	KC_Gamepad_RThumbDown,
	KC_Gamepad_RThumbRight,
	KC_Gamepad_RThumbLeft,
	GamepadCount,

	KC_Unknown = 0xffffffff
};

enum class InputDeviceType : uint8
{
	IDT_Mouse,
	IDT_Keyboard,
	IDT_Gamepad,
	IDT_Unknown
};

enum InputState : uint8
{
	IS_Unknown	= 0,
	IS_Pressed	= (1 << 0), // key is pressed
	IS_Released = (1 << 1), // key was down before and now it is up
	IS_Down		= (1 << 2), // key is currently being held down
	IS_Changed	= (1 << 3)	// state of the key is changed
};

enum class ModifierKeys
{
	MK_None			= 0,
	MK_RAlt			= (1 << 0),
	MK_LAlt			= (1 << 1),
	MK_RCtrl		= (1 << 2),
	MK_LCtrl		= (1 << 3),
	MK_LWin			= (1 << 4),
	MK_RWin			= (1 << 5),
	MK_RShift		= (1 << 6),
	MK_LShift		= (1 << 7),
	MK_NumLock		= (1 << 8),
	MK_CapsLock		= (1 << 9),
	MK_ScrollLock	= (1 << 10),

	MK_Ctrl			= (MK_LCtrl | MK_RCtrl),
	MK_Alt			= (MK_LAlt | MK_RAlt),
	MK_Win			= (MK_LWin | MK_RWin),
	MK_Shift		= (MK_LShift | MK_RShift)
};

struct KeyName
{
	const char* name;
	KeyCode code;

	KeyName() = default;
	KeyName(KeyCode _code, const char* _name)
		: name(_name)
		, code(_code)
	{}

	bool operator==(KeyName rhs) { return !strcmp(name, rhs.name); }
	bool operator==(KeyCode rhs) { return code == rhs; }
	const char* c_str() const { return name; }
};

struct InputEvent
{
	uint32 state; // state of the input 
	KeyCode key; // code of the key
	struct InputSymbol* symbol;

	/*
	* Value associated with the key, this value will contain information regarding state of the button
	* 0 if key is up 1 if is down, if button is trigger it will have value from 0.0f to 1.0f etc.
	*/
	float value; // value assocaited with the key 
	InputDeviceType deviceType;
	uint8 deviceIndex;
	int modifiers; // info about modifiers if any being held

	InputEvent()
		: state(InputState::IS_Unknown)
		, key(KeyCode::KC_Unknown)
		, value(0.0f)
		, deviceType(InputDeviceType::IDT_Unknown)
		, deviceIndex(0u)
		, modifiers(0)
	{}
};

struct InputSymbol
{
	enum SymbolType
	{
		ST_Button,
		ST_Toggle,
		ST_Axis // Analog
	};

	void AssignTo(InputEvent& event)
	{
		event.deviceIndex = deviceIndex;
		event.deviceType = deviceType;
		event.key = key;
		event.symbol = this;
		event.state = 0;
	}

	void Create(KeyName Name, KeyCode Key, uint8 DeviceIndex, SymbolType SymbolType,
				InputDeviceType DeviceType)
	{
		name = Name;
		key = Key;
		deviceIndex = DeviceIndex;
		symbolType = SymbolType;
		deviceType = DeviceType;
		halfTransitionCount = 0;
		value = 0.0f;
	}

	KeyName name;
	KeyCode key;
	uint8 deviceIndex;
	SymbolType symbolType;
	InputDeviceType deviceType;
	int32 halfTransitionCount;
	float value;
};

class IInputDevice
{
public:
	virtual ~IInputDevice() = default;
	virtual void Initialize(BaseInput* BaseInput) = 0;
	virtual const char* GetName() const = 0;
	virtual InputDeviceId GetID() const = 0;
	virtual uint32 GetDeviceIndex() const = 0;
	virtual InputDeviceType GetDeviceType() const = 0;
	virtual void PushInputEvent(InputEvent _event) = 0;
	virtual const char* GetKeyName(KeyCode key) const = 0;
	virtual InputSymbol* GetInputSymbol(KeyCode keyCode) = 0;
	virtual bool IsConnected() const = 0;
	virtual void SetConnectionStatus(bool status) = 0;
	virtual void Update(BaseInput*) = 0;
};

class Keyboard;
class Mouse;

class BaseInput : public IInputEventDispatcher
{
	friend class DebugDevice;
	typedef std::vector<IInputDevice*> InputDevices;
	typedef std::vector<IInputEventListener*> InputEventListeners;
	typedef std::vector<InputEvent> InputEventsList;
	typedef std::map<KeyCode, InputEvent*> InputEventsMap;

public:
	BaseInput();
	void Initialize(SystemGlobalEnvironment& env);
	void Release();
	void AddDevice(IInputDevice* device);
	void RemoveDevice(IInputDevice* device);
	Keyboard* GetKeyboardDevice();
	Mouse* GetMouseDevice();
	ModifierKeys ToModifierKey(KeyCode key) const;
	void GetProcessedInputs(std::vector<InputEvent>& events);
	InputEventListeners* GetListeners();
	int GetModifiers() const;
	InputEventsList* GetInputEventsList();
	void HandleDeviceChange();
	void SetModifier(int modifier);
	void ClearModifier(int modifier);
	bool IsKeyDown(KeyCode keyCode);
	bool IsKeyUp(KeyCode keyCode);
	bool IsModifierKey(KeyCode key) const;
	bool IsKeyToggledOn(KeyCode key) const;

	virtual bool RegisterListener(IInputEventListener* pListener, const char* szName) override;
	virtual bool RemoveListener(IInputEventListener* pListener) override;
	virtual void OnInputEvent(InputEvent event) override;
	virtual void Update() override;
private:
	InputDevices m_devices;
	InputEventListeners m_listeners;
	IInputDevice* m_debugDevice;
	int m_modifiers;
	InputEventsList m_events;
	InputEventsMap m_eventsMap;
};

class DebugDevice : public IInputEventListener
{
public:
	DebugDevice();
	void Initialize(BaseInput* pBaseInput);
	virtual bool OnInputEvent(InputEvent inputEvent) override;
};