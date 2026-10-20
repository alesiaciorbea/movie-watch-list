# Movie Watch List

Desktop app in C++ with Qt, made for the Object-Oriented Programming course at Babeș-Bolyai University (year 1, spring 2026).

## Features

- At start you choose where the movies are stored (a text file or an SQLite database) and the format of the watch list file (CSV or HTML).
- Admin mode: add, remove and update movies, with multi-level undo/redo (buttons or Ctrl+Z / Ctrl+Y).
- User mode: browse the movies of a genre (or all of them), and the trailer of each movie opens in the browser. Movies can be added to a personal watch list; when you remove one, you can like it, which adds a like to the movie.
- The watch list is shown in a table (a custom `QAbstractTableModel` with Title, Genre, Year and Likes) and saved as a CSV or HTML file.
- A bar chart shows how many movies there are in each genre (drawn with `QPainter`).

## Design

- Layers: domain (`Movie`, `MovieValidator`), repository, controller, GUI.
- `SqliteRepository` extends the text-file `Repository`, so the rest of the app does not depend on the storage.
- Undo/redo uses the Command pattern: `ActionAdd`, `ActionRemove` and `ActionUpdate` implement `Action` (`executeUndo` / `executeRedo`).
- `CSVWatchlist` and `HTMLWatchlist` extend `FileWatchlist` and write the watch list in their format.

## Build

Visual Studio with the Qt VS Tools extension and Qt 6 (Widgets): open `a10.slnx` and run. SQLite is included as source (`sqlite3.c`, `sqlite3.h`, public domain, from sqlite.org).

The CSV file opens in Notepad and the HTML file in the default browser, using Windows commands, so that part works on Windows only.

## What I would improve

- The SQLite queries are built by joining strings, so a title with an apostrophe (for example "Schindler's List") breaks them. Prepared statements (`sqlite3_prepare_v2`) would fix this.
