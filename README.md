# ssnk - simple snake game

This is a lightweight, text-based implementation of the popular [snake
game][1], written in C.

## Requirements

In order to build ssnk you need [ncurses][2].

## Installation

Edit `config.mk` to match your local setup (ssnk is installed into the
`/usr/local` namespace by default).

Afterwards enter the following command to build and install ssnk (if
necessary as root):

    make clean install

## Running ssnk

After successfully installing the snake game, you can run it:

    ssnk

Navigation is done using the vim-keys. You can quit with 'q'.

[1]: https://en.wikipedia.org/wiki/Snake_(video_game_genre)
[2]: https://www.gnu.org/software/ncurses/ncurses.html
