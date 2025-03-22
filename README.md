# MW21 - Music Workstation

## What is MW21
This program is a simple karaoke / stage-prompter application for singers and amateur music bands.

It's written for linux operating system. For now it should integrate with little effort on debian-based systems with `XFCE` desktop.

In fact - it's a bundle of few applications communicating mostly via `alsa` midi and plain inter-process communications (signals).
It is is controlled mostly via some physical MIDI device (keyboard, pad, launcher, whatever ...) or application e.g. `vkeybd` for Linux.

It also integrates through php/shell scripts with `apache2` server. It offers simple web-based playlist for playback music through e.g. breaks during your performance. It's convenient for controlling music player with your mobile phone staying connected in LAN.

## Concept
The basic idea behind is simultaneous playback of an audio file (wav or mp3) and a midi file (with adjustable `delay` of audio __following__ midi). Midi events emitted from the midi player are forwarded to the `display` program which increases pointer of the highlighted text. It works really well :-)

## Implementation
Window library is `gtkmm-3.0`
Playback backend is `VLC` (well-known multimedia player). This system supports playback of wav and mp3 files.
Text rendering is implemented with `freetype2` library.
MIDI sequencing - `pmidi` (command line midi player).
Scripts for placing windows is `wmctrl` - it relies on `X11`

## Data format
Creating text to be displayed is easy. Those are regular plain-text files. Synchronized with your music is a separate thing. It's not a piece of cake and basic MIDI-sequencer experience is needed. Note C#-0 with velocity 1 at channel 4 is increasing the pointer. Note A-0 on the same channel/velocity re-winds text to the beginning. Some documentation on this - planned to be provided soon.

## Installation
For today - the only way to install is to compile it on your own. Suitable packages for e.g. `linux-lite-7.2` are:

    apt-get install -y build-essential \
      pkg-config \
      libgtkmm-3.0-dev \
      libasound2-dev \
      libfreetype-dev \
      git \
      wmctrl \
      vlc \
      bc \
      pmidi \
      a2jmidid \
      gmidimonitor \
      vkeybd \
      apache2 \
      libapache2-mod-php \
      mc \
      meld

Being in `mw21/` you can do:

    MW2_DIR=$(pwd) ; \
    cd $MW2_DIR/chooser/ ; make ; \
    cd $MW2_DIR/display/ ; make ; \
    cd $MW2_DIR/g_proxy/ ; make ; \
    cd $MW2_DIR/modeline/ ; make ; \
    cd $MW2_DIR/remote/ ; make ; \
    cd $MW2_DIR/ ## MAKE_ALL - to build

    MW2_DIR=$(pwd) ; \
    cd $MW2_DIR/chooser/ ; make clean ; \
    cd $MW2_DIR/display/ ; make clean ; \
    cd $MW2_DIR/g_proxy/ ; make clean ; \
    cd $MW2_DIR/modeline/ ; make clean ; \
    cd $MW2_DIR/remote/ ; make clean ; \
    cd $MW2_DIR/ ## MAKE_CLEAN - to clean

Apache must be run as regular user (not `www-data` user). It's definitely __not_recommended__ for real web servers (publicly-available), but for this application (running only for few hours in local network) it should be fine.

Please remember to publish `mw21/web` diretory via your `apache2` web server.

Several adjusts have to be done in config files (`config/default/mw2_config`, `config/default/config.php`, `config/default/specific_variables.sh` ). Especially - replacing `USERNAME` to your linux account name.

## Data setup
Also suitable file must be placed in songs directory of the structure below:

    songs_files/
    `-- bank_3/
        |-- delay/
        |-- midi/
        |-- text/
        `-- waves/

to be scanned correctly via `modeline` program.
Collection of files to be played during breaks must be placed in some directory with prefixes:

    0000_abcxyz.mp3
    0001_abcxyz.mp3
    .
    .
    .
    xxx9_abcxyz.mp3

The total number must be divisible by 10 e.g. 10, 20, 30, 70, 150 etc...
Prefix must be 4-digits with leading zeros. Only ASCII, no-spaces allowed.

Script to start the system is run_mw21.sh in web directory

Detailed installation procedure is average-complex and not documented for now. I hope to provide more documentation soon.


Have fun!

mk1037

