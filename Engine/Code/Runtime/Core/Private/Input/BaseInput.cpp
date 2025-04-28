#include "Input/BaseInput.h"

#include "Application.h"
#include "Input/PlatformInput.h"
#include "Logging/Logger.h"

static const int32 GetDeviceIndexByKeyCode(KeyCode keyCode)
{
    if (keyCode >= KC_MOUSE_RANGE_START && keyCode < KeyCode::MouseCount)
    {
        return DI_MOUSE;
    }
    else if (keyCode >= KC_KEYBOARD_RANGE_START && keyCode < KeyCode::KeyboardCount)
    {
        return DI_KEYBOARD;
    }
    else if (keyCode >= KC_GAMEPAD_RANGE_START && keyCode < KeyCode::GamepadCount)
    {
        return DI_GAMEPAD;
    }
    return -1;
}

BaseInput::BaseInput()
    : m_modifiers(0)
{}

void BaseInput::Initialize(SystemGlobalEnvironment& env)
{
    env.baseInput = this;
    HandleDeviceChange();
}

void BaseInput::Release()
{
    // TODO(cagri): change this we are assumming gamepad is dynamically allocated
    for (auto& d : m_devices)
    {
        if (d->GetDeviceType() == InputDeviceType::IDT_Gamepad)
        {
            delete d;
        }
    }
}

void BaseInput::AddDevice(IInputDevice* device)
{
    // On input event send input to the corresponding device
    for (IInputDevice* const d : m_devices)
    {
        if (d == device)
        {
            return;
        }
    }
    
    if (m_devices.size() <= device->GetDeviceIndex())
    {
        m_devices.resize(device->GetDeviceIndex() + 1);
    }
    m_devices[device->GetDeviceIndex()] = device;
}

void BaseInput::RemoveDevice(IInputDevice* device)
{
    m_devices.erase(std::remove_if(m_devices.begin(), m_devices.end(),
        [&](const IInputDevice* val) {return val == device; }));
}

Keyboard* BaseInput::GetKeyboardDevice()
{
    return (Keyboard*)m_devices[DI_KEYBOARD];
}

Mouse* BaseInput::GetMouseDevice()
{
    return (Mouse*)m_devices[DI_MOUSE];
}

ModifierKeys BaseInput::ToModifierKey(KeyCode key) const
{
    switch (key)
    {
    case KeyCode::KC_LShift:
    return ModifierKeys::MK_LShift;
    case KeyCode::KC_RShift:
    return ModifierKeys::MK_RShift;
    case KeyCode::KC_LCtrl:
    return ModifierKeys::MK_LCtrl;
    case KeyCode::KC_RCtrl:
    return ModifierKeys::MK_RCtrl;
    case KeyCode::KC_LAlt:
    return ModifierKeys::MK_LAlt;
    case KeyCode::KC_RAlt:
    return ModifierKeys::MK_RAlt;
    case KeyCode::KC_CapsLock:
    return ModifierKeys::MK_CapsLock;
    case KeyCode::KC_ScrollLock:
    return ModifierKeys::MK_ScrollLock;
    case KeyCode::KC_NumLock:
    return ModifierKeys::MK_NumLock;
    default:
    return ModifierKeys::MK_None;
    }
}

void BaseInput::GetProcessedInputs(std::vector<InputEvent>& events)
{}

BaseInput::InputEventListeners* BaseInput::GetListeners()
{
    return &m_listeners;
}

int BaseInput::GetModifiers() const
{
    return m_modifiers;
}

BaseInput::InputEventsList* BaseInput::GetInputEventsList()
{
    return &m_events;
}

void BaseInput::HandleDeviceChange()
{
    PlatformGamepad::HandleDeviceChange();
    struct DeleteIfCondition
    {
        void operator()(IInputDevice*& ptr) const
        {
            delete ptr;
            ptr = NULL;
        }
    };
    auto newEnd = std::remove_if(m_devices.begin(),
                                 m_devices.end(),
                                [](IInputDevice* dev){ return !dev->IsConnected(); });
    std::for_each(newEnd,
                  m_devices.end(), 
                  DeleteIfCondition());
    m_devices.erase(newEnd, m_devices.end());
    GamepadDeviceList* list = PlatformGamepad::GetGamepadDeviceList();
    for (int i = 0; i < list->size(); ++i)
    {
        int gamepadIndex = i + DI_GAMEPAD;
        XInputDevice& xdev = list->at(i);
        xdev.gamepad = new Gamepad(xdev.deviceIndex);
        xdev.gamepad->Initialize(this);
        m_devices.resize(gamepadIndex + 1);
        m_devices[gamepadIndex] = xdev.gamepad;
    }
}

void BaseInput::SetModifier(int modifiers)
{
    m_modifiers |= modifiers;
}

void BaseInput::ClearModifier(int modifier)
{
    m_modifiers &= ~modifier;
}

bool BaseInput::IsKeyDown(KeyCode keyCode)
{
    int32 idx = GetDeviceIndexByKeyCode(keyCode);
    if (idx == -1 || m_devices.size() <= idx)
    {
        return false;
    }
    InputSymbol* symbol = m_devices[idx]->GetInputSymbol(keyCode);
    return (symbol->value == 1.0f);

    /*if (m_eventsMap.count(keyCode))
    {
        InputEvent* inputEvent = m_eventsMap[keyCode];
        return (inputEvent->value == 1.0f);
    }
    return false;*/
}

bool BaseInput::IsKeyUp(KeyCode keyCode)
{
    int32 idx = GetDeviceIndexByKeyCode(keyCode);
    if (idx == -1 || m_devices.size() <= idx)
    {
        return false;
    }
    InputSymbol* symbol = m_devices[idx]->GetInputSymbol(keyCode);
    return (symbol->value == 0.0f);
   /* if (m_eventsMap.count(keyCode))
    {
        InputEvent* inputEvent = m_eventsMap[keyCode];
        return (inputEvent->value == 0.0f);
    }
    return false;*/
}

bool BaseInput::IsModifierKey(KeyCode key) const
{
    if (key == KeyCode::KC_LCtrl || key == KeyCode::KC_RCtrl
        || key == KeyCode::KC_LAlt || key == KeyCode::KC_RAlt ||
        key == KeyCode::KC_LShift || key == KeyCode::KC_RShift ||
        key == KeyCode::KC_CapsLock || key == KeyCode::KC_ScrollLock || key == KeyCode::KC_NumLock)
    {
        return true;
    }
    return false;
}

bool BaseInput::IsKeyToggledOn(KeyCode key) const
{
    return IsModifierKey(key) && ((int)ToModifierKey(key) & m_modifiers);
}

bool BaseInput::RegisterListener(IInputEventListener* pListener, const char* czName)
{
    InputEventListeners::iterator begin = m_listeners.begin();
    InputEventListeners::iterator end = m_listeners.end();
    for (auto i = begin; i != end; i++)
    {
        if ((*i) == pListener)
        {
            return false;
        }
    }
    m_listeners.emplace_back(std::move(pListener));
    return true;
}

bool BaseInput::RemoveListener(IInputEventListener* pListener)
{
    InputEventListeners::iterator begin = m_listeners.begin();
    InputEventListeners::iterator end = m_listeners.end();
    for (auto i = begin; i != end; i++)
    {
        if ((*i) == pListener)
        {
            m_listeners.erase(i);
            return true;
        }
    }
    return false;
}

void BaseInput::OnInputEvent(InputEvent inputEvent)
{}

void BaseInput::Update()
{
    m_events.clear();
    m_eventsMap.clear();
    // Get events from platform layer which only contains data about current state of a button 
    // if event is ever occured this frame
    gEnv->platformInput->GetInputEvents(m_events);

    // TODO(cagri): we can dispatch only section of the array that concerns a device
    // and dispatch it on a seperate thread similar thing can be done when calling listeners
    for (IInputDevice* device : m_devices)
    {
        // device gets the events list from the baseinput and operates on the list of events that
        // is for them and fills out event structure that can be passed to the listeners later
        device->Update(this);
    }

    for (auto& e : m_events)
    {
        m_eventsMap[e.key] = &e;
        for (auto& l : m_listeners)
        {
            l->OnInputEvent(e);
        }
    }
}

// TODO(cagri): move debug device into its own file
DebugDevice::DebugDevice()
{}

void DebugDevice::Initialize(BaseInput* pBaseInput)
{
    pBaseInput->RegisterListener(this, "DebugDevice");
}

bool DebugDevice::OnInputEvent(InputEvent inputEvent)
{
    char msg[256];

    IInputDevice* dev = gEnv->application->GetBaseInput()->m_devices[inputEvent.deviceIndex];
    sprintf_s(msg, "InputEvent: idx: %d, name: %s, key: %s, key_state: %d, modifier: %d, value=%f\n", 
              inputEvent.deviceIndex, 
              dev->GetName(), 
              dev->GetKeyName(inputEvent.key),
              inputEvent.state, gEnv->application->GetBaseInput()->GetModifiers(),
              inputEvent.value);
    gEnv->logger->Log(msg, LogChannel::LC_Core, LogSeverity::LS_Info);
    return true;
}