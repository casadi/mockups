/* Mockup ONNX Runtime.
 *
 * Lets CasADi's onnxruntime plugin link and load on platforms where the real
 * ONNX Runtime can't ship (e.g. manylinux2014: the official ORT build needs
 * glibc 2.27 via expf/logf/powf). The plugin references exactly one symbol
 * from libonnxruntime -- OrtGetApiBase -- and reaches everything else through
 * the returned OrtApi function-pointer table.
 *
 * OrtApiBase / OrtGetApiBase is ONNX Runtime's stable, versioned ABI anchor,
 * so only that tiny entry point is declared here (no copy of the full
 * onnxruntime_c_api.h needed). GetApi() returns NULL, so any attempt to
 * actually use the runtime surfaces as a clean CasADi error ("Failed to obtain
 * the ONNX Runtime API") rather than running a fake model.
 */

#include <stdint.h>

struct OrtApi;  /* opaque: the mockup never produces a real API table */

typedef struct OrtApiBase {
  const struct OrtApi* (*GetApi)(uint32_t version);
  const char* (*GetVersionString)(void);
} OrtApiBase;

#if defined(_WIN32)
#define ORT_MOCKUP_EXPORT __declspec(dllexport)
#else
#define ORT_MOCKUP_EXPORT __attribute__((visibility("default")))
#endif

static const struct OrtApi* mockup_GetApi(uint32_t version) {
  (void) version;
  return 0;
}

static const char* mockup_GetVersionString(void) {
  return "mockup";
}

ORT_MOCKUP_EXPORT const OrtApiBase* OrtGetApiBase(void) {
  static const OrtApiBase base = { mockup_GetApi, mockup_GetVersionString };
  return &base;
}
