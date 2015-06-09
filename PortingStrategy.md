# Porting Strategy #

There were three key components to getting the code to work under Native Client:
  * Static data
  * stdin/stdout
  * Synchronous calls

## Static data ##
### The problem ###
The original source contains a utility `advent0` that takes the text messages from the .txt files and creates look-up tables that match a message with a byte offset. The runtime then uses these look-up tables to seek through the .txt files and read the message out. This is not feasible under Native Client.

### The solution ###
A new utility was created (`advtxt_to_c`) that converts the .txt files into arrays of c-style strings. These are then statically linked into the executable so that instead of using byte offsets, the runtime can then access the message array directly. This does increase the final executable size, but only by about 64kb. For reference, the total executable size is on the order of 1.2Mb, most of which is Native Client code.

## stdout ##
### The problem ###
The original source relies heavily on `printf`, `fputc`, etc to write to  stdout. Under Native Client these will either end up in the console logs or disappear completely.

### The solution ###
The solution to this was to write a thin wrapper around any console output. At this point, I also split the output into three:
  * screen printing
  * console printing
  * error printing

All of these functions call through to the Native Client module which then calls through to JavaScript methods.

Screen printing is used whenever the output should go to the, well, screen and output is appended to a textarea. Console output is redirected to the JavaScript console, and error messages are added to a special span that shows up red and fades over time. The game is also restarted whenever an error is produced, which is a far better approach than the original `exit(-1)`.

## Synchronous calls ##
### The problem ###
As well as console output, the original source depended on `fgets` for reading user input. This is a synchronous call which has no analogue on the Native Client side. In fact, the whole game was written with an assumption that the game loop would block waiting for user input which, well, doesn't work out all that well when the input never comes.

### The solution ###
`fgets` has been replaced by a call to the Native Client module that registers a callback to be called when the user submits text through the input control on the HTML page. The places that called fgets and assumed a synchronous return therefore had to be split into two functions. In some cases, they had to take in function pointers to call after the input had been received.

The main gameloop, that was essentially a `while (true)` loop, has been replaced by a single call to the `turn` function that contains a single tick of the gameloop. When input is expected and received, a callback is called that once again calls the `turn` function.