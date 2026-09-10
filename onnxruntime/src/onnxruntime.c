/* ONNX Runtime adaptor.
 *
 * CasADi's onnxruntime plugin references exactly one symbol from the runtime --
 * OrtGetApiBase -- and reaches everything else through the returned OrtApi
 * function-pointer table. This adaptor supplies that symbol and forwards it to a
 * real ONNX Runtime opened at run time, so nothing named onnxruntime has to sit on
 * the loader path (Windows ships an ancient onnxruntime.dll in System32 that would
 * otherwise win) and no ONNX Runtime has to be present at link time.
 *
 * ONNX Runtime distributions disagree on file name and layout (MS releases, pip,
 * conda, GPU variants), so there is no search: CASADI_ONNXRUNTIME_LIB must hold the
 * full path of the library. Until it loads, GetApi() returns NULL and the caller
 * surfaces a clean error rather than running a fake model.
 */

#define DLL_IMPLEMENTATION
#include <onnxruntime_c_api.h>

#include <stdio.h>
#include <stdlib.h>

#if defined(_WIN32)
#include <windows.h>
static HMODULE h = NULL;
#else
#include <dlfcn.h>
static void* h = NULL;
#endif

#if defined(_WIN32)
#define ORT_ADAPTOR_EXPORT __declspec(dllexport)
#else
#define ORT_ADAPTOR_EXPORT __attribute__((visibility("default")))
#endif

static const OrtApiBase* (ORT_API_CALL *real_OrtGetApiBase)(void) = NULL;

ORT_ADAPTOR_EXPORT void onnxruntime_adaptor_unload(void) {
  real_OrtGetApiBase = NULL;
  if (h) {
    #if defined(_WIN32)
    FreeLibrary(h);
    #else
    dlclose(h);
    #endif
    h = NULL;
  }
}

ORT_ADAPTOR_EXPORT int onnxruntime_adaptor_load(char* err_msg, unsigned int err_msg_len) {
  const OrtApiBase* base;
  const char* lib;

  if (real_OrtGetApiBase) return 0;

  #if defined(_WIN32)
  const char example[] = "C:\\onnxruntime-win-x64-1.22.0\\lib\\onnxruntime.dll";
  #elif defined(__APPLE__)
  const char example[] = "/opt/onnxruntime/lib/libonnxruntime.dylib";
  #else
  const char example[] = "/opt/onnxruntime/lib/libonnxruntime.so";
  #endif

  lib = getenv("CASADI_ONNXRUNTIME_LIB");
  if (lib == NULL || lib[0] == '\0') {
    snprintf(err_msg, err_msg_len, "The ONNX Runtime adaptor needs an environmental variable "
      "<CASADI_ONNXRUNTIME_LIB> holding the full path of an ONNX Runtime shared library, "
      "e.g. \"%s\".", example);
    return 1;
  }

  #if defined(_WIN32)
  {
    /* Full path only: the search flags cover the dependencies the runtime pulls in
       (its own directory first), not the runtime itself. */
    int n = MultiByteToWideChar(CP_UTF8, 0, lib, -1, NULL, 0);
    wchar_t* libW = n > 0 ? (wchar_t*) malloc(sizeof(wchar_t) * (size_t) n) : NULL;
    if (libW == NULL) {
      snprintf(err_msg, err_msg_len, "Could not decode CASADI_ONNXRUNTIME_LIB ('%s').", lib);
      return 1;
    }
    MultiByteToWideChar(CP_UTF8, 0, lib, -1, libW, n);
    h = LoadLibraryExW(libW, NULL,
      LOAD_LIBRARY_SEARCH_USER_DIRS |
      LOAD_LIBRARY_SEARCH_DEFAULT_DIRS |
      LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);
    free(libW);
    if (h == NULL) {
      snprintf(err_msg, err_msg_len, "Could not load ONNX Runtime '%s' (error %lu).",
        lib, (unsigned long) GetLastError());
      return 1;
    }
  }
  #else
  h = dlopen(lib, RTLD_LAZY | RTLD_LOCAL);
  if (h == NULL) {
    snprintf(err_msg, err_msg_len, "Could not load ONNX Runtime '%s' (%s).", lib, dlerror());
    return 1;
  }
  #endif

  #if defined(_WIN32)
  real_OrtGetApiBase = (const OrtApiBase* (ORT_API_CALL *)(void))
    GetProcAddress(h, "OrtGetApiBase");
  #else
  *(void**) &real_OrtGetApiBase = dlsym(h, "OrtGetApiBase");
  #endif
  if (real_OrtGetApiBase == NULL) {
    snprintf(err_msg, err_msg_len, "Could not find symbol 'OrtGetApiBase' in '%s'; "
      "CASADI_ONNXRUNTIME_LIB should point at an ONNX Runtime shared library.", lib);
    onnxruntime_adaptor_unload();
    return 2;
  }

  /* Reject a runtime too old for the API version the caller was built against
     (the OrtApi table is dispatched by struct offset). */
  base = real_OrtGetApiBase();
  if (base == NULL || base->GetApi(ORT_API_VERSION) == NULL) {
    snprintf(err_msg, err_msg_len, "ONNX Runtime '%s' (version %s) does not offer "
      "API version %d.", lib,
      base && base->GetVersionString ? base->GetVersionString() : "unknown", ORT_API_VERSION);
    onnxruntime_adaptor_unload();
    return 3;
  }

  return 0;
}

/* Unavailable-runtime stand-in: GetApi() returns NULL, which every caller checks. */
static const struct OrtApi* ORT_API_CALL unavailable_GetApi(uint32_t version) {
  (void) version;
  return 0;
}
static const char* ORT_API_CALL unavailable_GetVersionString(void) {
  return "unavailable";
}

ORT_ADAPTOR_EXPORT const OrtApiBase* ORT_API_CALL OrtGetApiBase(void) {
  static const OrtApiBase unavailable = { unavailable_GetApi, unavailable_GetVersionString };
  if (real_OrtGetApiBase == NULL) {
    char err_msg[512];
    if (onnxruntime_adaptor_load(err_msg, sizeof(err_msg))) return &unavailable;
  }
  return real_OrtGetApiBase();
}
