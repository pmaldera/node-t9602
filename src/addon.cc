#include <napi.h>
#include "t9602.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return T9602::Init(env, exports);
}

NODE_API_MODULE(addon, InitAll)