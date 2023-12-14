#include "pch.h"

#include "Platform/PlatformInput.h"
#include "Core/Input/BaseInput.h"
#include "Core/Input/Gamepad.h"
#include <Xinput.h>

#pragma comment(lib, "Xinput.lib")

#define MAX_ZONE_VALUE 32767

namespace
{
    std::vector<XInputDevice> devices;

    void ApplyCircularDeadZone(float x, float y, unsigned int deadZone, float& outX, float& outY)
    {
        
        float lx = x;
        float ly = y;

        float magnitude = sqrt(lx * lx + ly * ly);
        float normalizedMagnitude = 0.0f;
        float nx = (lx == 0.0f ) ? 0.0f : lx / magnitude;
        float ny = (ly == 0.0f) ? 0.0f:  ly / magnitude;
        if (magnitude > deadZone)
        {
            if (magnitude > MAX_ZONE_VALUE)
            {
                magnitude = MAX_ZONE_VALUE;
            }
            magnitude -= deadZone;
            normalizedMagnitude = magnitude / (MAX_ZONE_VALUE - deadZone);
        }
        else
        {
            magnitude = 0.0f;
            normalizedMagnitude = 0.0f;
        }
        outX = normalizedMagnitude * nx;
        outY = normalizedMagnitude * ny;
    }
}

int PlatformGamepad::Initialize(Gamepad* gamepad)
{
    XINPUT_STATE state;
    int deviceCount = -1;
    for (int i = 0; i < XUSER_MAX_COUNT; i++)
    {
        uint32_t ret = XInputGetState(i, &state);
        if (ret == ERROR_SUCCESS)
        {
            deviceCount++;
            XInputDevice device;
            device.deviceIndex = i;
            device.lastStatePacketNumber = 0;
            device.isConnected = true;
            device.gamepad = gamepad;
            devices.push_back(device);
        }
    }

    return deviceCount;
}

bool PlatformGamepad::HasStateChanged(int idx)
{
    XINPUT_STATE state;
    uint32_t ret = XInputGetState(idx, &state);
    if (ret == ERROR_DEVICE_NOT_CONNECTED)
    {
        for (auto& dev : devices)
        {
            if (dev.deviceIndex == idx && dev.isConnected == false)
            {
                return false;
            }
        }
        LOG_ERROR(LogChannel::LC_Core, "XInput Device is not connected at %d", idx);
        return true;
    }

    if (ret == ERROR_SUCCESS)
    {
        if (devices[idx].lastStatePacketNumber == state.dwPacketNumber)
        {
            devices[idx].hasStateChanged = false;
            return false;
        }
        devices[idx].hasStateChanged = true;
        return true;
    }
    return false;
}

void PlatformGamepad::SetFeedback(uint16_t leftMotorSpeed, uint16_t rightMotorSpeed, int idx)
{
    XINPUT_VIBRATION vibration;

    vibration.wLeftMotorSpeed = leftMotorSpeed;
    vibration.wRightMotorSpeed = rightMotorSpeed;

    uint32_t ret = XInputSetState(idx, &vibration);
    if (ret != ERROR_SUCCESS)
    {
        LOG_ERROR(LogChannel::LC_Core, "Error occured while setting gamepad feedback %d", idx);      
    }
}

void PlatformGamepad::Enable(bool enable)
{
	XInputEnable(enable);
	for (auto& dev : devices)
	{
		dev.enabled = enable;
	}
}

void PlatformGamepad::GetBatteryInfo(Battery* battery, int idx)
{
    XINPUT_BATTERY_INFORMATION batteryInformation;
    uint32_t ret = XInputGetBatteryInformation(idx, BATTERY_DEVTYPE_GAMEPAD, &batteryInformation);

    if (ret != ERROR_SUCCESS)
    {
        LOG_WARN(LogChannel::LC_Core, "XInput failed to retrieve battery information for device at %d", idx);
        return;
    }

    switch (batteryInformation.BatteryType)
    {
    case BATTERY_TYPE_DISCONNECTED:
        (*battery).type = Battery::BatteryType::DISCONNECTED;
        break;
    case BATTERY_TYPE_WIRED:
        (*battery).type = Battery::BatteryType::WIRED;
        break;
    case BATTERY_TYPE_ALKALINE:
        (*battery).type = Battery::BatteryType::ALKALINE;
        break;
    case BATTERY_TYPE_NIMH:
        (*battery).type = Battery::BatteryType::NIMH;
        break;
    case BATTERY_TYPE_UNKNOWN:
        (*battery).type = Battery::BatteryType::UNKNOWN;
        break;
    default:
        break;
    }

    switch (batteryInformation.BatteryLevel)
    {
    case BATTERY_LEVEL_EMPTY:
        (*battery).level = Battery::BatteryLevel::EMPTY;
        break;
    case BATTERY_LEVEL_LOW:
        (*battery).level = Battery::BatteryLevel::LOW;
        break;
    case BATTERY_LEVEL_MEDIUM:
        (*battery).level = Battery::BatteryLevel::MEDIUM;
        break;
    case BATTERY_LEVEL_FULL:
        (*battery).level = Battery::BatteryLevel::FULL;
        break;
    default:
        break;
    }
}

bool PlatformGamepad::IsConnected(int idx)
{
    for (auto& dev : devices)
    {
        if (dev.deviceIndex == idx)
        {
            return dev.isConnected;
        }
    }

    // device is disconnected and potentially deleted from list
    return false;
}

bool PlatformGamepad::GetState(GamepadState* pState, int idx)
{
    XINPUT_STATE state;
    uint32_t ret = XInputGetState(idx, &state);
    if (ret != ERROR_SUCCESS)
    {
        return false;
    }

    XInputDevice* dev = &devices[idx];

    // state is not changed
    if (dev->lastStatePacketNumber == state.dwPacketNumber)
    {
        dev->hasStateChanged = false;
    }

    bool gamepadDPadUp = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
    bool gamepadDPadDown = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
    bool gamepadDPadLeft = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
    bool gamepadDPadRight = state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
    bool gamepadStart = state.Gamepad.wButtons & XINPUT_GAMEPAD_START;
    bool gamepadBack = state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
    bool gamepadLThumb = state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
    bool gamepadRThumb = state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
    bool gamepadLShoulder = state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
    bool gamepadRShoulder = state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
    bool gamepadA = state.Gamepad.wButtons & XINPUT_GAMEPAD_A;
    bool gamepadB = state.Gamepad.wButtons & XINPUT_GAMEPAD_B;
    bool gamepadX = state.Gamepad.wButtons & XINPUT_GAMEPAD_X;
    bool gamepadY = state.Gamepad.wButtons & XINPUT_GAMEPAD_Y;

    pState->buttons = 0;
    pState->buttons |= ((int32)gamepadDPadUp << (KeyCode::KC_Gamepad_DPadUp) % KC_GAMEPAD_RANGE_START);
    pState->buttons |= ((int32)gamepadDPadDown << (KeyCode::KC_Gamepad_DPadDown) % KC_GAMEPAD_RANGE_START);
    pState->buttons |= ((int32)gamepadDPadLeft << (KeyCode::KC_Gamepad_DPadLeft) % KC_GAMEPAD_RANGE_START);
    pState->buttons |= ((int32)gamepadDPadRight << (KeyCode::KC_Gamepad_DPadRight) % KC_GAMEPAD_RANGE_START);
    pState->buttons |= ((int32)gamepadStart << (KeyCode::KC_Gamepad_Menu) % KC_GAMEPAD_RANGE_START);
    pState->buttons |= ((int32)gamepadBack << (KeyCode::KC_Gamepad_View) % KC_GAMEPAD_RANGE_START);
    pState->buttons |= ((int32)gamepadLThumb << (KeyCode::KC_Gamepad_LThumb) % KC_GAMEPAD_RANGE_START);
    pState->buttons |= ((int32)gamepadRThumb << (KeyCode::KC_Gamepad_RThumb) % KC_GAMEPAD_RANGE_START);
    pState->buttons |= ((int32)gamepadLShoulder << (KeyCode::KC_Gamepad_LShoulder) % KC_GAMEPAD_RANGE_START);
    pState->buttons |= ((int32)gamepadRShoulder << (KeyCode::KC_Gamepad_RShoulder) % KC_GAMEPAD_RANGE_START);
    pState->buttons |= ((int32)gamepadA << (KeyCode::KC_Gamepad_A) % KC_GAMEPAD_RANGE_START);
    pState->buttons |= ((int32)gamepadB << (KeyCode::KC_Gamepad_B) % KC_GAMEPAD_RANGE_START);
    pState->buttons |= ((int32)gamepadX << (KeyCode::KC_Gamepad_X) % KC_GAMEPAD_RANGE_START);
    pState->buttons |= ((int32)gamepadY << (KeyCode::KC_Gamepad_Y) % KC_GAMEPAD_RANGE_START);

    SHORT thumbLX = state.Gamepad.sThumbLX;
    SHORT thumbLY = state.Gamepad.sThumbLY;
    SHORT thumbRX = state.Gamepad.sThumbRX;
    SHORT thumbRY = state.Gamepad.sThumbRY;

    float tLX = 0;
    float tLY = 0;
    float rLX = 0;
    float rLY = 0;
    ApplyCircularDeadZone(thumbLX, thumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, tLX, tLY);
    ApplyCircularDeadZone(thumbRX, thumbRY, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, rLX, rLY);

    BYTE leftTrigger = state.Gamepad.bLeftTrigger;
    BYTE rightTrigger = state.Gamepad.bRightTrigger;

    if (tLX != 0)
    {
        pState->buttons |= ((tLX < 0) ?
            (1 << (KeyCode::KC_Gamepad_LThumbLeft) % KC_GAMEPAD_RANGE_START) :
            (1 << (KeyCode::KC_Gamepad_LThumbRight) % KC_GAMEPAD_RANGE_START));
    }
    if (tLY != 0)
    {
		pState->buttons |= (tLY < 0) ?
			(1 << (KeyCode::KC_Gamepad_LThumbDown) % KC_GAMEPAD_RANGE_START) :
			(1 << (KeyCode::KC_Gamepad_LThumbUp) % KC_GAMEPAD_RANGE_START);
    }
    if (rLX != 0)
    {
		pState->buttons |= (rLX < 0) ?
			(1 << (KeyCode::KC_Gamepad_RThumbLeft) % KC_GAMEPAD_RANGE_START) :
			(1 << (KeyCode::KC_Gamepad_RThumbRight) % KC_GAMEPAD_RANGE_START);
    }
    if (rLY != 0)
    {
        pState->buttons |= (rLY < 0) ?
            (1 << (KeyCode::KC_Gamepad_RThumbDown) % KC_GAMEPAD_RANGE_START) :
            (1 << (KeyCode::KC_Gamepad_RThumbUp) % KC_GAMEPAD_RANGE_START);
    }
    pState->buttons |= (leftTrigger != 0) ?
        (1 << (KeyCode::KC_Gamepad_LTrigger) % KC_GAMEPAD_RANGE_START) : 0;
    pState->buttons |= (rightTrigger != 0) ?
        (1 << (KeyCode::KC_Gamepad_RTrigger) % KC_GAMEPAD_RANGE_START) : 0;

    pState->thumbLX = tLX;
    pState->thumbLY = tLY;
    pState->thumbRX = rLX;
    pState->thumbRY = rLY;
    pState->leftTrigger = leftTrigger;
    pState->rightTrigger = rightTrigger;

    return true;
}

void PlatformGamepad::HandleDeviceChange()
{
    // remove any device that is not currently connected
    auto newEnd = std::remove_if(devices.begin(), devices.end(), [](XInputDevice dev){
            XINPUT_STATE state;
            uint32_t ret = XInputGetState(dev.deviceIndex, &state);
            if (dev.isConnected == true && ret != ERROR_SUCCESS)
            {
                dev.gamepad->SetConnectionStatus(false);
                LOG_INFO(LogChannel::LC_Platform, "Gamepad is disconnected at index %d", dev.deviceIndex);
                return true;
            }
        return false;
        });

    devices.erase(newEnd, devices.end());

    for (int i = 0; i < XUSER_MAX_COUNT; ++i)
    {
        XINPUT_STATE state;
        uint32_t ret = XInputGetState(i, &state);
        if (ret == ERROR_SUCCESS && devices.size() <= i)
        {
            devices.resize(i + 1);
            XInputDevice device{};
            device.deviceIndex = i;
            device.isConnected = true;
            devices[i] = device;
            LOG_INFO(LogChannel::LC_Platform, "Gamepad is connected at index %d", i);
        }
    }
}

GamepadDeviceList* PlatformGamepad::GetGamepadDeviceList()
{
    return &devices;
}