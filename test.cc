#include <node.h>
#include <string>
// #include <iosteams>

void Hello_World(const v8::FunctionCallbackInfo<v8::Value>& args) {
    // isolate will isolate the whole process in new memory space; so that no other thread can make change onto it at the same time 
    v8::Isolate* isolate = args.GetIsolate();
    v8::String::Utf8Value s(args[0]);

    std::string some_string = "This string has been generated in c++!";

    auto result = v8::String::NewFromUtf8(isolate, some_string.c_str());
    args.GetReturnValue().Set(result);
}

void Write_String(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate* isolate = args.GetIsolate();
    v8::String::Utf8Value s(args[0]);
    std::string str(*s);

    auto result = v8::String::NewFromUtf8(isolate, str.c_str());
    args.GetReturnValue().Set(result);
}

std::string Reverse(std::string& str) {
    std::string newString = ""; 
    for (int i = str.length() - 1; i >= 0; i--) {
      newString += str[i];
    }
    return newString;
}
 

void Reverse_String(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate* isolate = args.GetIsolate();
    v8::String::Utf8Value s(args[0]);
    std::string str(*s);

    std::string reversed = Reverse(str); 

    auto result = v8::String::NewFromUtf8(isolate, reversed.c_str());
    args.GetReturnValue().Set(result);
}

// void Forin_object(const v8::FunctionCallbackInfo<v8::Value>& args) { 
//     std::cout << "this is not javascript console log" << std::
// }


void Initialize(v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "helloWorld", Hello_World);
    NODE_SET_METHOD(exports, "writeString", Write_String);
    NODE_SET_METHOD(exports, "reverseString", Reverse_String);
   // NODE_SET_METHOD(exports, "forinObject", Forin_object);
}

NODE_MODULE(addon, Initialize);