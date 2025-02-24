#include <clicky/clicky.hpp>
#include <iostream>

#include "../libs/licky.h"

int main(int argc, char *argv[]) {
  clicky cli;
  licky lyric;

  cli.add_argument("artist", "a", "The 'main' author of the song", true);
  cli.add_argument("song", "s", "the name of the music", true);

  cli.add_options(
      {{"verbose", "vb", "displays a more verbose output", false},
       {"prettify", "pr", "uses ncurses to render the json response", false}});

  cli.parse(argc, argv);

  try {
    std::string artist;
    std::string song;
    std::string lrc;

    artist = cli.get_argument("artist");
    song = cli.get_argument("song");

    json res = lyric.fetchLyrics(artist, song);
    
    if (res.contains("lyrics")) {
      lrc = res["lyrics"].get<std::string>();
    } else {
      lrc = "[e] : not found";
    }

    if (cli.has_option("prettify")) {
      lyric.prettifyLyrics(artist, song, lrc);
    } else {
      std::cout << lrc << std::endl;
    }

  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}
