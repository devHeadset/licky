#include <curl/curl.h>
#include <ncurses.h>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class licky {
public:
  // helper function, since "Frank Sinatra" wouldn't work, but "Frank-Sinatra" will. 
  static std::string cleanString(const std::string &input) {
    std::string result = input;
    for (char &c : result) {
      if (c == ' ')
        c = '-';
    }
    return result;
  }

  static json fetchLyrics(const std::string &artist, const std::string &song) {
    std::string url = "https://api.lyrics.ovh/v1/" + cleanString(artist) + "/" +
                      cleanString(song);
    CURL *curl = curl_easy_init();
    std::string response;
    json jsonData;

    if (curl) {
      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
      CURLcode res = curl_easy_perform(curl);
      curl_easy_cleanup(curl);

      if (res == CURLE_OK) {
        try {
          jsonData = json::parse(response);
        } catch (json::parse_error &e) {
          jsonData["error"] = "Failed to parse JSON";
        }
      } else {
        jsonData["error"] = "Request failed";
      }
    }
    return jsonData;
  }

  static void prettifyLyrics(const std::string &artist, const std::string &song,
                             const std::string &lyrics) {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    mousemask(ALL_MOUSE_EVENTS, nullptr);

    int row, col;
    getmaxyx(stdscr, row, col);

    clear();
    std::string title = artist + " - " + song;
    int title_x = (col - title.size()) / 2;
    mvprintw(2, title_x, "%s", title.c_str());

    refresh();

    int win_height = row - 6;
    int win_width = col - 10;
    int win_y = 4;
    int win_x = (col - win_width) / 2;
    WINDOW *win = newwin(win_height, win_width, win_y, win_x);

    box(win, 0, 0);
    scrollok(win, TRUE);

    std::vector<std::string> lines;
    std::istringstream stream(lyrics);
    std::string line;

    while (std::getline(stream, line)) {
      lines.push_back(line);
    }

    int total_lines = lines.size();
    int top_line = 0;

    int ch;
    while (true) {
      werase(win);
      box(win, 0, 0);

      for (int i = 0; i < win_height - 2 && top_line + i < total_lines; ++i) {
        std::string l = lines[top_line + i];
        int x = (win_width - l.size()) / 2;
        if (x < 1)
          x = 1;
        mvwprintw(win, i + 1, x, "%s", l.c_str());
      }

      wrefresh(win);

      ch = getch();
      if (ch == 'q')
        break;
      if (ch == KEY_UP && top_line > 0)
        top_line--;
      if (ch == KEY_DOWN && top_line < total_lines - (win_height - 2))
        top_line++;
      if (ch == KEY_MOUSE) {
        MEVENT event;
        if (getmouse(&event) == OK) {
          if (event.bstate & BUTTON4_PRESSED && top_line > 0)
            top_line--; // Scroll up
          if (event.bstate & BUTTON5_PRESSED &&
              top_line < total_lines - (win_height - 2))
            top_line++; // Scroll down
        }
      }
    }

    endwin();
  }

private:
  // Callback function to write response data
  static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                              std::string *output) {
    size_t totalSize = size * nmemb;
    output->append((char *)contents, totalSize);
    return totalSize;
  }
};
