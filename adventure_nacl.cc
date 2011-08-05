/// @file adventure_nacl.cc
/// This example demonstrates loading, running and scripting a very simple NaCl
/// module.  To load the NaCl module, the browser first looks for the
/// CreateModule() factory method (at the end of this file).  It calls
/// CreateModule() once to load the module code from your .nexe.  After the
/// .nexe code is loaded, CreateModule() is not called again.
///
/// Once the .nexe code is loaded, the browser than calls the CreateInstance()
/// method on the object returned by CreateModule().  It calls CreateInstance()
/// each time it encounters an <embed> tag that references your NaCl module.
///
/// The browser can talk to your NaCl module via the postMessage() Javascript
/// function.  When you call postMessage() on your NaCl module from the browser,
/// this becomes a call to the HandleMessage() method of your pp::Instance
/// subclass.  You can send messages back to the browser by calling the
/// PostMessage() method on your pp::Instance.  Note that these two methods
/// (postMessage() in Javascript and PostMessage() in C++) are asynchronous.
/// This means they return immediately - there is no waiting for the message
/// to be handled.  This has implications in your program design, particularly
/// when mutating property values that are exposed to both the browser and the
/// NaCl module.

#include <cstdio>
#include <string>
#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"

class AdventureNaclInstance;
AdventureNaclInstance* instance_ = NULL;

extern "C" {
void nacl_main();
}

/// To communicate with the browser, you must override HandleMessage() for
/// receiving messages from the borwser, and use PostMessage() to send messages
/// back to the browser.  Note that this interface is entirely asynchronous.
class AdventureNaclInstance : public pp::Instance {
 public:
  /// The constructor creates the plugin-side instance.
  /// @param[in] instance the handle to the browser-side plugin instance.
  explicit AdventureNaclInstance(PP_Instance instance)
      : pp::Instance(instance),
        input_cb_(NULL),
        a_(NULL), b_(NULL) {
    instance_ = this;
  }
  virtual ~AdventureNaclInstance() {}

  /// Handler for messages coming in from the browser via postMessage().  The
  /// @a var_message can contain anything: a JSON string; a string that encodes
  /// method names and arguments; etc.  For example, you could use
  /// JSON.stringify in the browser to create a message that contains a method
  /// name and some parameters, something like this:
  ///   var json_message = JSON.stringify({ "myMethod" : "3.14159" });
  ///   nacl_module.postMessage(json_message);
  /// On receipt of this message in @a var_message, you could parse the JSON to
  /// retrieve the method name, match it to a function call, and then call it
  /// with the parameter.
  /// @param[in] var_message The message posted by the browser.
  virtual void HandleMessage(const pp::Var& var_message) {
    if (var_message.is_string()) {
      std::string message = var_message.AsString();
      size_t split = message.find_first_of(":");
      std::string command = message.substr(0, split);
      if (command == "start_game") {
        PostConsoleMessage("Starting game...");
        nacl_main();
      } else if (command == "input") {
        PostConsoleMessage((std::string("input: ") + message).c_str());
        std::string input = message.substr(split + 1);

        // Local echo
        PostScreenMessage(input + "\n");

        printf("Calling input cb %p\n", input_cb_);
        if (input_cb_) {
          input_cb_(input.c_str(), a_, b_);
//          SetInputCallback(NULL, NULL, NULL);
        }
      }
    }
  }

  void PostScreenMessage(const std::string& message) {
    PostMessage(pp::Var(std::string("s") + message));
  }
  
  void PostConsoleMessage(const std::string& message) {
    PostMessage(pp::Var(std::string("c") + message));
  }

  void SetInputCallback(int (*input_cb)(const char*, void*, void*),
                        void* a, void* b) {
    printf("Setting input cb %p\n", input_cb);
    input_cb_ = input_cb;
    a_ = a;
    b_ = b;
  }

 private:
  int (*input_cb_)(const char*, void*, void*);
  void* a_;
  void* b_;
};

/// The Module class.  The browser calls the CreateInstance() method to create
/// an instance of your NaCl module on the web page.  The browser creates a new
/// instance for each <embed> tag with type="application/x-nacl".
class AdventureNaclModule : public pp::Module {
 public:
  AdventureNaclModule() : pp::Module() {}
  virtual ~AdventureNaclModule() {}

  virtual pp::Instance* CreateInstance(PP_Instance instance) {
    return new AdventureNaclInstance(instance);
  }
};

namespace pp {

Module* CreateModule() { return new AdventureNaclModule(); }

}  // namespace pp

extern "C" {

void PostScreenMessage(const char* message) {
  instance_->PostScreenMessage(message);
}

void PostConsoleMessage(const char* message) {
  instance_->PostConsoleMessage(message);
}

void WaitForInput(int (*input_cb)(const char*, void*, void*),
                  void* a = NULL, void* b = NULL) {
  instance_->SetInputCallback(input_cb, a, b);
}

}

