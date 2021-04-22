# not-so-sound-project
Testing some programming patterns in plain old C.

The program is build in a way that it can be used as launcher
for multiple smaller projects.

Currently implemented projects:

* Syna, sound generation trough mathematics


# Dependencies

- std - current version is dependent on c standard library
- pragma once - pragma once is used instead of header guards,
  so compiler and preprocessor used need to handle it correctly
- [PortAudio](http://portaudio.com) is used as abstraction for
  sound devices and platform audio functionality. PortAudio used
  in development is build and linked with ALSA, but should work
  with other underlaying sound interfaces as well.
