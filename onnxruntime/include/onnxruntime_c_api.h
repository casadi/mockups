// ABI-faithful trim of ONNX Runtime's onnxruntime_c_api.h (v1.22.0).
//
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
//
// CasADi's plugin builds against this header but at test time runs against the REAL
// libonnxruntime, so OrtApi must be ABI-compatible. OrtApi is dispatched by struct
// offset, so we keep the real member ORDER up to the deepest member the plugin uses
// (index 100) -- used members carry real signatures, the rest are void* filler -- and
// truncate the remaining 217. ORT only ever appends members (see the increasing
// "\since Version" tags upstream), so this 1.22 layout stays valid against any newer
// real library. Verified: offsetof matches the upstream header for all used members.

#ifndef CASADI_MOCKUP_ONNXRUNTIME_C_API_H
#define CASADI_MOCKUP_ONNXRUNTIME_C_API_H

#include <stdint.h>
#include <stddef.h>

// SAL annotations: no-ops, matching the upstream non-MSVC path
#define _In_
#define _In_z_
#define _In_opt_
#define _Inout_
#define _Out_
#define _Outptr_
#define _In_reads_(X)
#define _Inout_updates_all_(X)
#define _Frees_ptr_opt_
#define _Check_return_
#define _Ret_maybenull_
#define ORT_ALL_ARGS_NONNULL
#define ORT_MUST_USE_RESULT

#ifdef _WIN32
#define ORT_API_CALL _stdcall
#define ORT_EXPORT
#else
#define ORT_API_CALL
#define ORT_EXPORT
#endif

#ifdef __cplusplus
#define NO_EXCEPTION noexcept
#else
#define NO_EXCEPTION
#endif

#define ORT_API_VERSION 22

#define ORT_RUNTIME_CLASS(X) \
  struct Ort##X;             \
  typedef struct Ort##X Ort##X

#define ORT_API2_STATUS(NAME, ...) \
  _Check_return_ _Ret_maybenull_ OrtStatusPtr(ORT_API_CALL* NAME)(__VA_ARGS__) NO_EXCEPTION ORT_MUST_USE_RESULT

#define ORT_CLASS_RELEASE(X) void(ORT_API_CALL * Release##X)(_Frees_ptr_opt_ Ort##X * input)

#ifdef __cplusplus
extern "C" {
#endif

ORT_RUNTIME_CLASS(Env);
ORT_RUNTIME_CLASS(Status);
ORT_RUNTIME_CLASS(MemoryInfo);
ORT_RUNTIME_CLASS(Session);
ORT_RUNTIME_CLASS(Value);
ORT_RUNTIME_CLASS(RunOptions);
ORT_RUNTIME_CLASS(SessionOptions);

typedef OrtStatus* OrtStatusPtr;

typedef enum ONNXTensorElementDataType {
  ONNX_TENSOR_ELEMENT_DATA_TYPE_UNDEFINED,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT8,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_INT8,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT16,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_INT16,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_INT32,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_INT64,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_STRING,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_BOOL,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT16,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_DOUBLE,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT32,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT64,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_COMPLEX64,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_COMPLEX128,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_BFLOAT16,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT8E4M3FN,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT8E4M3FNUZ,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT8E5M2,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT8E5M2FNUZ,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT4,
  ONNX_TENSOR_ELEMENT_DATA_TYPE_INT4
} ONNXTensorElementDataType;

typedef enum OrtLoggingLevel {
  ORT_LOGGING_LEVEL_VERBOSE,
  ORT_LOGGING_LEVEL_INFO,
  ORT_LOGGING_LEVEL_WARNING,
  ORT_LOGGING_LEVEL_ERROR,
  ORT_LOGGING_LEVEL_FATAL,
} OrtLoggingLevel;

typedef enum OrtAllocatorType {
  OrtInvalidAllocator = -1,
  OrtDeviceAllocator = 0,
  OrtArenaAllocator = 1
} OrtAllocatorType;

typedef enum OrtMemType {
  OrtMemTypeCPUInput = -2,
  OrtMemTypeCPUOutput = -1,
  OrtMemTypeCPU = OrtMemTypeCPUOutput,
  OrtMemTypeDefault = 0,
} OrtMemType;

struct OrtApiBase {
  const struct OrtApi*(ORT_API_CALL* GetApi)(uint32_t version)NO_EXCEPTION;
  const char*(ORT_API_CALL* GetVersionString)(void)NO_EXCEPTION;
};
typedef struct OrtApiBase OrtApiBase;

ORT_EXPORT const OrtApiBase* ORT_API_CALL OrtGetApiBase(void) NO_EXCEPTION;

// ABI-faithful trim of OrtApi (onnxruntime v1.22.0, ORT_API_VERSION 22). OrtApi is
// dispatched by struct offset, so a plugin built against this and run against the real
// library (the test-time scenario) must see every member at its real index. We therefore
// keep the exact real member ORDER up to the deepest member the plugin uses
// (ReleaseSessionOptions, index 100) and truncate the remaining 217. Members the plugin
// does not call are pointer-sized `void*` filler (a `[N]` run == N function-pointer slots);
// only the 14 used members carry real signatures. Indices in comments are the real offsets.
struct OrtApi {
  void* _gap0[2];  // 0 CreateStatus, 1 GetErrorCode

  const char*(ORT_API_CALL* GetErrorMessage)(_In_ const OrtStatus* status)NO_EXCEPTION ORT_ALL_ARGS_NONNULL;  // 2

  ORT_API2_STATUS(CreateEnv, OrtLoggingLevel log_severity_level, _In_ const char* logid, _Outptr_ OrtEnv** out);  // 3

  void* _gap1[4];  // 4..7

  ORT_API2_STATUS(CreateSessionFromArray, _In_ const OrtEnv* env,
                  _In_ const void* model_data, size_t model_data_length,
                  _In_ const OrtSessionOptions* options, _Outptr_ OrtSession** out);  // 8

  ORT_API2_STATUS(Run, _Inout_ OrtSession* session, _In_opt_ const OrtRunOptions* run_options,
                  _In_reads_(input_len) const char* const* input_names,
                  _In_reads_(input_len) const OrtValue* const* inputs, size_t input_len,
                  _In_reads_(output_names_len) const char* const* output_names, size_t output_names_len,
                  _Inout_updates_all_(output_names_len) OrtValue** outputs);  // 9

  ORT_API2_STATUS(CreateSessionOptions, _Outptr_ OrtSessionOptions** options);  // 10

  void* _gap2[38];  // 11..48

  ORT_API2_STATUS(CreateTensorWithDataAsOrtValue, _In_ const OrtMemoryInfo* info, _Inout_ void* p_data,
                  size_t p_data_len, _In_ const int64_t* shape, size_t shape_len, ONNXTensorElementDataType type,
                  _Outptr_ OrtValue** out);  // 49

  void* _gap3[1];  // 50

  ORT_API2_STATUS(GetTensorMutableData, _In_ OrtValue* value, _Outptr_ void** out);  // 51

  void* _gap4[17];  // 52..68

  ORT_API2_STATUS(CreateCpuMemoryInfo, enum OrtAllocatorType type, enum OrtMemType mem_type,
                  _Outptr_ OrtMemoryInfo** out);  // 69

  void* _gap5[22];  // 70..91

  ORT_CLASS_RELEASE(Env);          // 92
  ORT_CLASS_RELEASE(Status);       // 93
  ORT_CLASS_RELEASE(MemoryInfo);   // 94
  ORT_CLASS_RELEASE(Session);      // 95
  ORT_CLASS_RELEASE(Value);        // 96

  void* _gap6[3];  // 97..99

  ORT_CLASS_RELEASE(SessionOptions);  // 100
};
typedef struct OrtApi OrtApi;

#ifdef __cplusplus
}
#endif

#endif  // CASADI_MOCKUP_ONNXRUNTIME_C_API_H
