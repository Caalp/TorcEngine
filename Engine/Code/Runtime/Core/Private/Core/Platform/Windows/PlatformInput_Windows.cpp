#define WIN32_LEAN_AND_MEAN      // Exclude rarely-used stuff from Windows headers
#include <Windows.h>
#include <windowsx.h>

#include "Core/Input/PlatformInput.h"

#include "Core/Platform/Platform.h"
#include "Core/Windowing/WindowBase.h"
#include "Core/Input/BaseInput.h"
#include "Core/Application.h"

#include "Core/Logging/Logger.h"
#include "Core/Common/UtilMacros.h"

#include <iterator>


#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC         ((uint16_t) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE        ((uint16_t) 0x02)
#endif
#ifndef HID_USAGE_GENERIC_KEYBOARD
#define HID_USAGE_GENERIC_KEYBOARD     ((uint16_t) 0x06)
#endif

std::vector<InputEvent> mouseEvents;

class LinearAllocator
{
public:

    ~LinearAllocator()
    {
        Memory::FreeAligned(m_memory);
    }

    void Reserve(size_t sizeInBytes, size_t alignment)
    {
        m_memory = (uint8_t*)Memory::AllocAligned(MemoryTag::MEMORY_TAG_LINEAR_ALLOCATOR, sizeInBytes, alignment);
        m_start = m_memory;
        m_end = m_start + sizeInBytes;
    }

    void Reserve(uint8_t* start, uint8_t* end)
    {
        m_start = start;
        m_end = end;
        m_memory = start;
    }

    uint8_t* Allocate(size_t sizeInBytes)
    {
        if (m_start + sizeInBytes > m_end)
        {
            return nullptr;
        }

        uint8_t* mem = m_start;
        m_start = m_start + sizeInBytes;
        return mem;
    }

    void Free(uint8_t* mem)
    {}

    void Reset()
    {
        m_start = m_memory;
    }

private:
    uint8_t* m_start;
    uint8_t* m_end;
    uint8_t* m_memory;
};

namespace
{
    LinearAllocator allocator;
    std::vector<uint8_t*> inputMessages;

    KeyCode ToKeyCode(uint32 vkCode, uint32 scanKeyCode, int flag, int& outModifiers)
    {
        switch (vkCode)
        {
        case VK_UP:
            return KeyCode::KC_ArrowUp;
        case VK_DOWN:
            return KeyCode::KC_ArrowDown;
        case VK_LEFT:
            return KeyCode::KC_ArrowLeft;
        case VK_RIGHT:
            return KeyCode::KC_ArrowRight;
        case VK_ESCAPE:
            return KeyCode::KC_Escape;
        case VK_NUMPAD0:
            return KeyCode::KC_NP_0;
        case VK_NUMPAD1:
            return KeyCode::KC_NP_1;
        case VK_NUMPAD2:
            return KeyCode::KC_NP_2;
        case VK_NUMPAD3:
            return KeyCode::KC_NP_3;
        case VK_NUMPAD4:
            return KeyCode::KC_NP_4;
        case VK_NUMPAD5:
            return KeyCode::KC_NP_5;
        case VK_NUMPAD6:
            return KeyCode::KC_NP_6;
        case VK_NUMPAD7:
            return KeyCode::KC_NP_7;
        case VK_NUMPAD8:
            return KeyCode::KC_NP_8;
        case VK_NUMPAD9:
            return KeyCode::KC_NP_9;
        case VK_MULTIPLY:
            return KeyCode::KC_Multiply;
        case VK_ADD:
            return KeyCode::KC_Add;
        case VK_SEPARATOR:
            return KeyCode::KC_Separator;
        case VK_SUBTRACT:
            return KeyCode::KC_Subtract;
        case VK_DECIMAL:
            return KeyCode::KC_Decimal;
        case VK_DIVIDE:
            return KeyCode::KC_Divide;
        case VK_TAB:
            return KeyCode::KC_Tab;
        case VK_F1:
            return KeyCode::KC_F1;
        case VK_F2:
            return KeyCode::KC_F2;
        case VK_F3:
            return KeyCode::KC_F3;
        case VK_F4:
            return KeyCode::KC_F4;
        case VK_F5:
            return KeyCode::KC_F5;
        case VK_F6:
            return KeyCode::KC_F6;
        case VK_F7:
            return KeyCode::KC_F7;
        case VK_F8:
            return KeyCode::KC_F8;
        case VK_F9:
            return KeyCode::KC_F9;
        case VK_F10:
            return KeyCode::KC_F10;
        case VK_F11:
            return KeyCode::KC_F11;
        case VK_F12:
            return KeyCode::KC_F12;
        case 0x41: // A
            return KeyCode::KC_A;
        case 0x42:
            return KeyCode::KC_B;
        case 0x43:
            return KeyCode::KC_C;
        case 0x44:
            return KeyCode::KC_D;
        case 0x45:
            return KeyCode::KC_E;
        case 0x46:
            return KeyCode::KC_F;
        case 0x47:
            return KeyCode::KC_G;
        case 0x48:
            return KeyCode::KC_H;
        case 0x49:
            return KeyCode::KC_I;
        case 0x4A:
            return KeyCode::KC_J;
        case 0x4B:
            return KeyCode::KC_K;
        case 0x4C:
            return KeyCode::KC_L;
        case 0x4D:
            return KeyCode::KC_M;
        case 0x4E:
            return KeyCode::KC_N;
        case 0x4F:
            return KeyCode::KC_O;
        case 0x50:
            return KeyCode::KC_P;
        case 0x51:
            return KeyCode::KC_Q;
        case 0x52:
            return KeyCode::KC_R;
        case 0x53:
            return KeyCode::KC_S;
        case 0x54:
            return KeyCode::KC_T;
        case 0x55:
            return KeyCode::KC_U;
        case 0x56:
            return KeyCode::KC_V;
        case 0x57:
            return KeyCode::KC_W;
        case 0x58:
            return KeyCode::KC_X;
        case 0x59:
            return KeyCode::KC_Y;
        case 0x5A: // Z
            return KeyCode::KC_Z;
        case 0x30: // 0
            return KeyCode::KC_0;
        case 0x31:
            return KeyCode::KC_1;
        case 0x32:
            return KeyCode::KC_2;
        case 0x33:
            return KeyCode::KC_3;
        case 0x34:
            return KeyCode::KC_4;
        case 0x35:
            return KeyCode::KC_5;
        case 0x36:
            return KeyCode::KC_6;
        case 0x37:
            return KeyCode::KC_7;
        case 0x38:
            return KeyCode::KC_8;
        case 0x39: // 9
            return KeyCode::KC_9;
        case VK_PRIOR:
            return KeyCode::KC_PgUp;
        case VK_NEXT:
            return KeyCode::KC_PgDn;
        case VK_END:
            return KeyCode::KC_End;
        case VK_HOME:
            return KeyCode::KC_Home;
        case VK_PRINT:
            return KeyCode::KC_Print;
        case VK_INSERT:
            return KeyCode::KC_Insert;
        case VK_DELETE:
            return KeyCode::KC_Delete;
        case VK_LWIN:
            outModifiers |= (int)ModifierKeys::MK_LWin;
            return KeyCode::KC_LWin;
        case VK_RWIN:
            outModifiers |= (int)ModifierKeys::MK_RWin;
            return KeyCode::KC_RWin;
        case VK_NUMLOCK:
            outModifiers |= (int)ModifierKeys::MK_NumLock;
            return KeyCode::KC_NumLock;
        case VK_SCROLL:
            outModifiers |= (int)ModifierKeys::MK_ScrollLock;
            return KeyCode::KC_ScrollLock;
        case VK_CAPITAL:
            outModifiers |= (int)ModifierKeys::MK_CapsLock;
            return KeyCode::KC_CapsLock;
        case VK_BACK:
            return KeyCode::KC_BackSpace;
        case VK_SHIFT:
        {
            uint32 vkc = MapVirtualKey(scanKeyCode, MAPVK_VSC_TO_VK_EX);
            if (vkc == VK_RSHIFT)
            {
                outModifiers |= (int)ModifierKeys::MK_RShift;
                return KeyCode::KC_RShift;
            }
            outModifiers |= (int)ModifierKeys::MK_LShift;
            return KeyCode::KC_LShift;
        }
        case VK_RETURN:
            return KeyCode::KC_Enter;
        case VK_MENU:
        {
            if (flag & RI_KEY_E0)
            {
                outModifiers |= (int)ModifierKeys::MK_RAlt;
                return KeyCode::KC_RAlt;
            }
            outModifiers |= (int)ModifierKeys::MK_LAlt;
            return KeyCode::KC_LAlt;
        }           
        case VK_CONTROL:
        {
            if (flag & RI_KEY_E0)
            {
                outModifiers |= (int)ModifierKeys::MK_RCtrl;
                return KeyCode::KC_RCtrl;
            }
            outModifiers |= (int)ModifierKeys::MK_LCtrl;
            return KeyCode::KC_LCtrl;
        }

        // Mouse Keys
        case VK_LBUTTON:
            return KeyCode::KC_Mouse1;
        case VK_RBUTTON:
            return KeyCode::KC_Mouse2;
        case VK_MBUTTON:
            return KeyCode::KC_Mouse3;
        case VK_XBUTTON1:
            return KeyCode::KC_Mouse4;
        case VK_XBUTTON2:
            return KeyCode::KC_Mouse5;
        default:
            break;
        }

        return KeyCode::KC_Unknown;
    }

    KeyCode RawMouseToKeyCode(uint16 code, float& outValue)
    {
        switch (code)
        {
        case RI_MOUSE_BUTTON_1_DOWN:
            outValue = 1.0f;
            return KeyCode::KC_Mouse1;
        case RI_MOUSE_BUTTON_1_UP:
            outValue = 0.0f;
            return KeyCode::KC_Mouse1;
        case RI_MOUSE_BUTTON_2_DOWN:
            outValue = 1.0f;
            return KeyCode::KC_Mouse2;
        case RI_MOUSE_BUTTON_2_UP:
            outValue = 0.0f;
            return KeyCode::KC_Mouse2;
        case RI_MOUSE_BUTTON_3_DOWN:
            outValue = 1.0f;
            return KeyCode::KC_Mouse3;
        case RI_MOUSE_BUTTON_3_UP:
            outValue = 0.0f;
            return KeyCode::KC_Mouse3;
        case RI_MOUSE_BUTTON_4_DOWN:
            outValue = 1.0f;
            return KeyCode::KC_Mouse4;
        case RI_MOUSE_BUTTON_4_UP:
            outValue = 0.0f;
            return KeyCode::KC_Mouse4;
        case RI_MOUSE_BUTTON_5_DOWN:
            outValue = 1.0f;
            return KeyCode::KC_Mouse5;
        case RI_MOUSE_BUTTON_5_UP:
            outValue = 0.0f;
            return KeyCode::KC_Mouse5;
        default:
            break;
        }
        return KeyCode::KC_Unknown;
    }
   
    void ProcessRawInputMessage(UINT_PTR lparam)
    {
        uint32_t size;
        uint32_t ret;
        ret = GetRawInputData((HRAWINPUT)lparam, RID_INPUT, NULL, &size, sizeof(RAWINPUTHEADER));

        uint8_t* mem = (uint8_t*)allocator.Allocate(size);

        // allocator is full
        if (mem == nullptr)
        {
            // process or discard messages
            inputMessages.clear();
            allocator.Reset();
        }

        if (ret == 0 && size != 0)
        {
            ret = GetRawInputData((HRAWINPUT)lparam, RID_INPUT, mem, &size, sizeof(RAWINPUTHEADER));
            inputMessages.push_back(mem);
        }
    }

    void ToInputEvent(std::vector<InputEvent>& inputEvents)
    {
        for (uint8* msg : inputMessages)
        {
            if (msg == nullptr)
            {
                continue;
            }

            RAWINPUT rawInput = *(RAWINPUT*)msg;

            if (rawInput.header.dwType == RIM_TYPEMOUSE)
            {
                RAWMOUSE rawMouse = rawInput.data.mouse;
               
                //InputEvent inputEvent2{};
                
               
                if (rawMouse.usButtonFlags == RI_MOUSE_WHEEL)
                {
                    InputEvent inputEvent{};
                    inputEvent.deviceType = InputDeviceType::IDT_Mouse;
                    inputEvent.value = (int16_t)rawMouse.usButtonData;
                    inputEvent.key = ((int16_t)rawMouse.usButtonData < 0) ? 
                        KeyCode::KC_MouseWheelDown : KeyCode::KC_MouseWheelUp;
                    inputEvents.push_back(inputEvent);                   
                }
                if (rawMouse.usButtonFlags > 0)
                {
                    InputEvent inputEvent{};
                    inputEvent.deviceType = InputDeviceType::IDT_Mouse;
                    inputEvent.value = (int16_t)rawMouse.usButtonData;
                    inputEvent.key = RawMouseToKeyCode(rawMouse.usButtonFlags, inputEvent.value);
                    inputEvents.push_back(inputEvent);
                }                

                //if (rawMouse.usFlags == MOUSE_MOVE_RELATIVE && (float)rawMouse.lLastX != 0.0f && (float)rawMouse.lLastY != 0.0f)
                //{
                //    //inputEvent2.key = KeyCode::KC_MouseX;
                //    //inputEvent2.value = (float)rawMouse.lLastX;

                //   /* inputEvent3.key = KeyCode::KC_MouseY;
                //    inputEvent3.value = (float)rawMouse.lLastY;*/

                //    //inputEvents.push_back(inputEvent2);
                //    //inputEvents.push_back(inputEvent3);
                //    TE_Info(LogChannel::LC_Platform, "MOUSE_MOVE_RELATIVE EVENT!");
                //}
                //else if (rawMouse.usFlags & MOUSE_MOVE_ABSOLUTE)
                //{
                //    /*inputEvent2.key = KeyCode::KC_MouseXAbsolute;
                //    inputEvent2.value = (float)rawMouse.lLastX;*/

                // /*   inputEvent3.key = KeyCode::KC_MouseYAbsolute;
                //    inputEvent3.value = (float)rawMouse.lLastY;*/

                //    //inputEvents.push_back(inputEvent2);
                //    //inputEvents.push_back(inputEvent3);
                //    TE_Info(LogChannel::LC_Platform, "MOUSE_MOVE_ABSOLUTE EVENT!");
                //}

                if (rawMouse.usFlags & MOUSE_VIRTUAL_DESKTOP)
                { 
                    TE_Info(LogChannel::LC_Platform, "VIRTUAL DESKTOP MOUSE EVENT!");
                }
            }
            else if (rawInput.header.dwType == RIM_TYPEKEYBOARD)
            {
                InputEvent inputEvent;
                RAWKEYBOARD rawKeyboard = rawInput.data.keyboard;
                inputEvent.deviceType = InputDeviceType::IDT_Keyboard;
                inputEvent.key = ToKeyCode(rawKeyboard.VKey, rawKeyboard.MakeCode, 
                                           rawKeyboard.Flags, inputEvent.modifiers);
                inputEvent.value = (float)!(rawKeyboard.Flags & RI_KEY_BREAK);
                inputEvents.push_back(inputEvent);
            }           
        }
    }
}

void PlatformInput::Initialize(SystemGlobalEnvironment& env, WindowBase* targetWindow)
{
    RAWINPUTDEVICE Rid[2] = {};

    // Register mouse:
    Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
    Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
    Rid[0].dwFlags = RIDEV_INPUTSINK;
    Rid[0].hwndTarget = (HWND)targetWindow->GetWindowHandle();

    // Register keyboard:
    Rid[1].usUsagePage = HID_USAGE_PAGE_GENERIC;
    Rid[1].usUsage = HID_USAGE_GENERIC_KEYBOARD;
    Rid[1].dwFlags = RIDEV_INPUTSINK;
    Rid[1].hwndTarget = (HWND)targetWindow->GetWindowHandle();

    if (RegisterRawInputDevices(Rid, arraysize(Rid), sizeof(Rid[0])) == FALSE)
    {
        TE_Error(LogChannel::LC_Platform, "Registering input devices failed.");
    }

    allocator.Reserve(512 * 512, 8);
    env.platformInput = this;
    env.application->RegisterWindowEventListener(this, "PlatformInput");
}

void PlatformInput::Release()
{}

void PlatformInput::GetInputEvents(std::vector<InputEvent>& events)
{
    std::transform(mouseEvents.begin(), mouseEvents.end(), std::back_insert_iterator(events), [](InputEvent& ie){ return ie; });
    ToInputEvent(events);

    inputMessages.clear();
    allocator.Reset();
}

bool PlatformInput::OnWindowEvent(TORC_HWND hWnd, uint32 msg, uint64 wparam, uint64 lparam)
{
    mouseEvents.clear();
	switch (msg)
	{
	case WM_INPUT:
	    ProcessRawInputMessage(lparam);
	break;
	case WM_MOUSEMOVE:
	{
		InputEvent _eventX;
		InputEvent _eventY;
		int x = GET_X_LPARAM(lparam);
		int y = GET_Y_LPARAM(lparam);
		_eventX.deviceIndex = 0;
		_eventX.key = KeyCode::KC_MouseXAbsolute;
		_eventX.value = (float)x;
		_eventX.deviceType = InputDeviceType::IDT_Mouse;

		_eventY.deviceIndex = 0;
		_eventY.key = KeyCode::KC_MouseYAbsolute;
		_eventY.value = (float)y;
		_eventY.deviceType = InputDeviceType::IDT_Mouse;

        mouseEvents.push_back(_eventX);
        mouseEvents.push_back(_eventY);
	}
	break;
	default:
	break;
	}
    return true;
}