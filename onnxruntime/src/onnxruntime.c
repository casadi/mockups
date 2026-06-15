/* Mockup ONNX Runtime.
 *
 * Lets CasADi's onnxruntime plugin link and load on platforms where the real
 * ONNX Runtime can't ship (e.g. manylinux2014: the official ORT build needs
 * glibc 2.27 via expf/logf/powf). The plugin references exactly one symbol
 * from libonnxruntime -- OrtGetApiBase -- and reaches everything else through
 * the returned OrtApi function-pointer table.
 *
 * GetApi() returns NULL, so any attempt to actually use the runtime surfaces
 * as a clean CasADi error ("Failed to obtain the ONNX Runtime API") rather
 * than running a fake model.
 */

#include <onnxruntime_c_api.h>

#if defined(_WIN32)
#define ORT_MOCKUP_EXPORT __declspec(dllexport)
#else
#define ORT_MOCKUP_EXPORT __attribute__((visibility("default")))
#endif

static const struct OrtApi* ORT_API_CALL mockup_GetApi(uint32_t version) {
  (void) version;
  return 0;
}

static const char* ORT_API_CALL mockup_GetVersionString(void) {
  return "mockup";
}

ORT_MOCKUP_EXPORT const OrtApiBase* OrtGetApiBase(void) {
  static const OrtApiBase base = { mockup_GetApi, mockup_GetVersionString };
  return &base;
}
