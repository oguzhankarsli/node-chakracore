// Copyright Microsoft. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and / or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#include "v8.h"
#include "jsrtutils.h"

namespace v8 {

using jsrt::IsolateShim;

Local<Value> NumberObject::New(Isolate * isolate, double value) {
  JsValueRef numberObjectConstructor = IsolateShim::FromIsolate(isolate)
                        ->GetCurrentContextShim()->GetNumberObjectConstructor();
  JsValueRef newNumberObjectRef;
  JsValueRef numberRef;
  if (JsDoubleToNumber(value, &numberRef) != JsNoError) {
    return Local<Value>();
  }

  JsValueRef args[] = { nullptr, numberRef };

  if (JsConstructObject(numberObjectConstructor,
                        args,
                        _countof(args),
                        &newNumberObjectRef) != JsNoError) {
    return Local<Value>();
  }

  return Local<NumberObject>::New(
    static_cast<NumberObject*>(newNumberObjectRef));
}

NumberObject *NumberObject::Cast(v8::Value *obj) {
  if (!obj->IsNumberObject()) {
    // CHAKRA-TODO: what should we return in this case?
    // just exit and print?
    return nullptr;
  }

  return static_cast<NumberObject*>(obj);
}

}  // namespace v8