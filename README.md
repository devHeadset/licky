# Licky

A simple C++ tool that fetches and displays song lyrics.

## Overview

Licky is a straightforward command-line utility for retrieving and displaying song lyrics. It's designed to be simple to use while providing clean output formatting options.

## Usage

The basic syntax is simple - just provide the artist and song name:

```bash
./licky --artist "Frank Sinatra" --song "Strangers in the Night"
```

This will output the lyrics directly to your terminal.

### Pretty Output

By default, Licky outputs lyrics in a basic format. However, you can use the `--prettify` (or `-p`) flag to enable ncurses-based formatting for a more appealing display:

```bash
./licky --artist "Frank Sinatra" --song "Strangers in the Night" --prettify
```

## Limitations

Please note that the API currently used by Licky is quite basic, which means:
- Some songs may be missing portions of their lyrics
- Not all songs may be available in the database

These limitations are planned to be addressed in future updates.

## Compiling from Source

If you prefer to compile Licky yourself rather than using the pre-compiled binary, you'll need the following dependencies:

### Dependencies

- `ncurses-devel`
- `curl-devel` 
- `clicky` (custom library)

### Installation on Fedora

For ncurses and curl:

```bash
sudo dnf install -y ncurses-devel curl-devel
```

For the `clicky` library, you'll need to build it manually. Instructions are available at: https://auth-xyz.github.io/clicky

## TODO

- [ ] Change to a better API
- [ ] Either add an existing algorithm for lyrics matching or create one
- [ ] Add sync functionality with ncspot

## Future Plans

While Licky was originally designed as a simple tool, several enhancements are planned:
- Better API integration for more complete lyrics
- Music player synchronization (specifically with ncspot)
- Improved lyrics matching capabilities

---
