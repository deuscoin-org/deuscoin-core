
Debian
====================
This directory contains files used to package deuscoind/deuscoin-qt
for Debian-based Linux systems. If you compile deuscoind/deuscoin-qt yourself, there are some useful files here.

## deuscoin: URI support ##


deuscoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install deuscoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your deuscoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/deuscoin128.png` to `/usr/share/pixmaps`

deuscoin-qt.protocol (KDE)

