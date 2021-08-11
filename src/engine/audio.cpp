/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Luca Tagliavini #971133
  07/27/2021

  audio.cpp: implements the logic for audio-playing using the `aplay` and
  `afplay` system tools
*/

#include "audio.hpp"
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

char Engine::Audio::tool[256] = "not_fetched";
int Engine::Audio::pid = -1;
bool *Engine::Audio::playing = nullptr;

// check is the system has a program available in the $PATH and in case
// return a zero error code and puts the path in the second argument
bool has_tool(const char *tool, char path[256]) {
  char which_cmd[256] = "which ";
  strcat(which_cmd, tool);
  auto f = popen(which_cmd, "r");
  if (f == nullptr)
    return false;

  // read the command output into the path argument
  fgets(path, 256, f);
  // remove trailing \n in file path
  int i = strlen(path) - 1;
  if (i > 0) {
    path[i] = '\0';
  }
  return !pclose(f);
}

// since our target systems are Linux and Darwin, we know for a fact that the
// `which` command is available, and can therefore use that (its return code) to
// check if the required tools are available
void Engine::Audio::fetch_tool() {
  // check for aplay
  char tool_path[256];
  if (has_tool("aplay", tool_path) || has_tool("afplay", tool_path))
    strcpy(tool, tool_path);
  else
    strcpy(tool, "none");
}

Engine::Audio::Error Engine::Audio::play(const char *fp) {
  if (strcmp(tool, "not_fetched") == 0)
    fetch_tool();

  if (strcmp(tool, "none") == 0)
    return Error::no_tool;

  // check if we have read permission on the given file at fp
  if (access(fp, R_OK) != 0)
    return Error::invalid_file;

  if(status() == State::playing)
    stop();

  // keep shared memory across threads with mman functions
  // see man mmap, man munmap and https://stackoverflow.com/a/13274800
  playing = (bool *)mmap(nullptr, sizeof *playing, PROT_READ | PROT_WRITE,
                         MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  *playing = true;
  pid = fork();
  if (pid < 0)
    return Error::no_thread;
  else if (pid == 0) {
    // open /dev/null and pipe this thread's output to it
    int dn = open("/dev/null", O_WRONLY);
    dup2(dn, 1);
    dup2(dn, 2);
    close(dn);

    int ppid = -1;
    while (*playing) {
      if ((usleep(1000000 / 30) == EINTR))
        break; // stop if usleep blocks

      // if we don't have any aplay instance start a new one
      int status = -1;
      if (ppid != -1)
        waitpid(ppid, &status, WNOHANG);

      if (ppid == -1 || WIFEXITED(status) || WIFSTOPPED(status) ||
          WIFSIGNALED(status)) {
        ppid = fork();
        if (ppid < 0)
          exit(-1);
        else if (ppid == 0)
          exit(execlp(tool, tool, fp, nullptr));
      }
    }
    // stop the aplay instance if we got one
    if (ppid != -1)
      kill(ppid, SIGINT);

    exit(0);
  } else
    return Error::none;
}

Engine::Audio::State Engine::Audio::status() {
  return (playing != nullptr && *playing) ? State::playing : State::stopped;
}

// quit NOT gracefully, we just want the audio to stop immediately
void Engine::Audio::stop() {
  if (status() == State::playing) {
    *playing = false;
    wait(nullptr);

    // cleanup
    if(playing != nullptr)
      munmap(playing, sizeof *playing);
    playing = nullptr;
    pid = -1;
  }
}
