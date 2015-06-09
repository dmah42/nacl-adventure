# Introduction #

This was developed over the course of about eight hours so it's not the best quality port, but it works.

# Build instructions #

  * First, ensure you have the native client SDK set up from http://code.google.com/p/nativeclient.
  * Next, run make. This will create advtxt\_to\_c that is essential for turning those .txt data files into .c files that should be statically linked into the .nexe. This gets around the file access limitations of Native Client.
  * Finally, run ./scons. This will create optimized and debug .nexe files for 32- and 64-bit targets.
  * To play the game, run a web server and browser to the .html file that is in the source folder.

# TODO #

In priority order.
  * Get Save/Restore working with HTML5 local storage.
  * Do something better with the fatal error/exit(-1) calls.
  * Re-architect from the ground up to be either NaCl specific or platform agnostic.
  * Maybe merge the input and output fields to make something more interactive.