/*
  university of bologna
  first cicle degree in computer science
  00819 - programmazione

  luca tagliavini #971133
  07/27/2021

  audio.hpp: provides a platform-independent way to play audio across `aplay` on
  linux and `afplay` on darwin
*/

#ifndef ENGINE_AUDIO_HPP
#define ENGINE_AUDIO_HPP

namespace Engine {

// Audio keeps track of the available tools on the system to play audio and
// exposes two methods: `play` and `stop` to allow the game loop to control the
// sound playing status. All media files played must be encoded in the `wav`
// format, as it's the only one supported by both `aplay` and `afplay`
class Audio {
private:
  static char *tool;

public:
  // searches for the best tool to use to play audio. Choises are:
  // - aplay (on Linux, for ALSA - Advanced Linux Sound Architecture)
  // - afplay (on Darwin, aka OSX/MacOS)
  // this function is mainly for internal use, but is kept public as it can
  // be called in advance to play any software to avoid the delay (and thread
  // blocking) caused by the use of this procedure
  static void fetch_tool();

  // play plays the given wav file using one of the available system tools
  static int play(const char *fp);

  // stop stops the current playing audio file
  static void stop();
};

} // namespace Engine

#endif // ENGINE_AUDIO_HPP
