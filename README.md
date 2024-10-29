![Logo](images/logo50.png)

Arxiv RSS Reader is a simple dedicated arXiv RSS feed parser and reader. Built using QT5, it's designed to be light-weight and thus has only basic features, including:

- single feed capability
- display both HTML and PDF links from the arXiv listing
- customizable update frequencies
- basic sorting 

This application was built in my free time, so it is an ongoing process. Please feel free to suggest additional functionality and report bugs.

## Dependencies

The program was built using

- QT5
- linux build essentials
- C++ standard libraries

You can download the normal dependencies using
- Fedora: `dnf install qt5-qtbase-devel`
- Ubuntu: `apt-get install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools`

## Installation

The first step is to install the source code. Henceforth, Fedora will be used as the example installation OS.

- `cd` into a directory of your choice for cloning the code, then run `git clone https://github.com/ShaunFell/arXiv_RSS_Reader.git`
- execute `qmake-qt5 -o Makefile arXiv-RSS-Reader.pro` then `make`. You can also run `make -j<n>` where `<n>` is the number of threads you would like the `make` program to use. 
- Finally, execute `make install` to install the program.

The default installation directory of the executable is `$HOME/.bin`. The desktop file is copied to `$HOME/.local/share/applications`. If you would like to move the desktop file to the system directory, you can execute `sudo desktop-file-install ~/.local/share/applications/arxiv-rss-reader.desktop`.

Thats it! The program should be installed in the correct directory and you should see the program appear in your list of applications. If you have build and/or installation issues, please feel free to reach out to me.

## Usage

### Changing the Feed
You can change the feed by navigating to Settings -> Preferences -> Feed URL. Enter your custom arXiv Feed URL (see [the docs](https://info.arxiv.org/help/api/basics.html)) and hit save. For example, you can enter `http://export.arxiv.org/api/query?search_query=all:electron`, hit save, then refresh and the feed will be populated in the left window.

### Changing the update frequency.
As long as the program is running, the feed will update at a default frequency of 1 hour. You can change this by navigating to Settings -> Preferences -> Update Frequency (minutes). There, change the update frequency in minutes to what you would like and hit save. The feed will now update at your given frequency.

### Sorting the output.
By default, the feed is sorted by the date the papers were last updated. You can also change the sorting to publication date, alphabetical order by title (A -> Z), and reverse alphabetical order by title (Z -> A). If you would like additional sorting possiblities, please let me know.

### Article View
When you click on an article in the left pane, the following information will be populated in the right pane:
- Article title
- List of authors
- abstract
- Publication date and last update date
- link to the arXiv article
- link to the articles pdf


## Uninstallation
To remove the program and associated files, simply execute `make uninstall` where you previously ran `make install` (probably the repo's base directory).