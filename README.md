# SCREENSHOTS

!https://github.com/pony-montana/simple-dwl-desktop/blob/main/20240819_17h21m57s_grim.png
!https://github.com/pony-montana/simple-dwl-desktop/blob/main/20240819_17h22m09s_grim.png
!https://github.com/pony-montana/simple-dwl-desktop/blob/main/20240819_17h23m39s_grim.png

# A SIMPLE KISS DESKTOP BASED ON DWL.

dwl is a dwm clone based on wayland protocols, in particular on wlroots library.

This DE, after being properly setted-up, has these feature on my machine:
- clickable status bar with 9 desktops + information status as battery level, audio volume and date&time;
- support enabled for xwayland.
- clipboard unified across programs, in particular the function in the .zshrc that makes the "copy-pasting in the terminals" to use wl-clipboard.
- reproducing images in the terminal with ranger + foot + imagemagick(sixel).
- some choices are specific for my machine: a thinkpad x200 with uk keyboard running gentoo and (obviously) wayland. I don't use pipewire on this machine/setup, but just pure alsa.
- a beautiful wallpaper, the Tower of Babel of Pieter Bruegel. I picked it from www.wikipedia.org.

# REPOSITORY MAP

The programs you are here for are here as standalone folders. I put them in .local/src/ on my machine.

You will find dotfiles in /config. They need to be put in $HOME/.config in order to work.

A pseudo-complete list of program I use is in /packagelist.txt

The original tower of babel everyone is searching that I stole from the museum of Wi Kipedia is in /bg

# ATTENTION

!!! I putted the original readme in the respective folder so you can read all the informations you need to build programs.

If reading readmes you feel you want to dive more into these programs, please go to the respective upstreams. In the end, do what you want but I'm not responsible for nothing here, I'm just sharing free code.

# PROGRAM LIST

You find the pseudo-complete list in /packagelist.txt

You can find some alternatives in https://github.com/natpen/awesome-wayland

# REFERENCE

The upstream repos and the people I stolen code from:
https://github.com/LukeSmithxyz/voidrice
https://codeberg.org/dwl/dwl
https://codeberg.org/sewn
