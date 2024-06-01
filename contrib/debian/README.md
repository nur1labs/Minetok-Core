
Debian
====================
This directory contains files used to package mubdid/mubdi-qt
for Debian-based Linux systems. If you compile mubdid/mubdi-qt yourself, there are some useful files here.

## MuBdI: URI support ##


mubdi-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install mubdi-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your mubdi-qt binary to `/usr/bin`
and the `../../share/pixmaps/mubdi128.png` to `/usr/share/pixmaps`

mubdi-qt.protocol (KDE)

