AdventureNaclModule = null;  // Global application object.
statusText = 'NO-STATUS';

// When the NaCl module has loaded, hook up an event listener to handle
// messages coming from it via PPB_Messaging.PostMessage() (in C) or
// pp::Instance.PostMessage() (in C++), and indicate success.
function moduleDidLoad() {
  AdventureNaclModule = document.getElementById('adventure_nacl');
  AdventureNaclModule.addEventListener('message', handleMessage, false);
  updateStatus('SUCCESS');

  document.getElementById('input').focus();
  AdventureNaclModule.postMessage('start_game');
}

// The 'message' event handler.  This handler is fired when the NaCl module
// posts a message to the browser by calling PPB_Messaging.PostMessage()
// (in C) or pp::Instance.PostMessage() (in C++).  This implementation
// appends the message data to the output div.
function handleMessage(message_event) {
  console.dir(message_event);
  var type = message_event.data[0];
  var message = message_event.data.slice(1);
  switch(type) {
    case 'c':
      console.log(message);
      break;
    case 's':
      appendOutput(message);
      break;
    default:
      console.debug('unknown event type ' + type + ' for message ' +
          message);
      break;
  }
}

function postInput() {
  var input = document.getElementById('input');
  AdventureNaclModule.postMessage('input:' + input.value);
  input.value = '';
}

// If the page loads before the Native Client module loads, then set the
// status message indicating that the module is still loading.  Otherwise,
// do not change the status message.
function pageDidLoad() {
  if (AdventureNaclModule == null) {
    updateStatus('LOADING...');
  } else {
    // It's possible that the Native Client module onload event fired
    // before the page's onload event.  In this case, the status message
    // will reflect 'SUCCESS', but won't be displayed.  This call will
    // display the current message.
    updateStatus();
  }
}

// Set the global status message.  If the element with id 'statusField'
// exists, then set its HTML to the status message as well.
// opt_message The message test.  If this is null or undefined, then
// attempt to set the element with id 'statusField' to the value of
// |statusText|.
function updateStatus(opt_message) {
  if (opt_message)
    statusText = opt_message;
  console.log("Status: " + statusText);
}

function appendOutput(message) {
  var output = document.getElementById('output');
  output.value += message;
  output.scrollTop = output.scrollHeight;
}

