#pragma once

#include <d3d11.h>
#include <wrl.h>

#if defined(FAILED)
#undef FAILED
#endif

#if defined(SUCCEEDED)
#undef SUCCEEDED
#endif

#define SUCCEEDED(hr)   (((HRESULT)(hr)) >= 0)
#define FAILED(hr)      (((HRESULT)(hr)) < 0)
