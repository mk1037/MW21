# Display

## General concept
The `display` is a program for displaying song lyrics with auto scrolling in sync to the music. It is primarily controlled by MIDI events, but controlling by PC keyboard is also possible.

Originally it is a part of [MW21](https://github.com/mk1037/MW21) karaoke, stage prompter, but it can run standalone and be used together with any midi sequencer/DAW.

Text input is a plain-text file. Tokens separated by newline or `|`.

Config file for display is the same as for entire MW21 - [`mw2_config`](https://github.com/mk1037/MW21/blob/main/mw21/configs/default/mw2_config)
It must be placed as  `/tmp/mw2_config`. This path is hardcoded in the `display` binary (as for today).

Three essential note-on events are available among accepted events:

* advance the pointer of highlighted lyrics: note-on nr 1 (the lowest C#) with velocity 1 at channel 4
* jump to the beginning of the lyrics: note-on nr 9 (the lowest A) with velocity 1 at channel 4
* reload lyrics: note-on nr 4 (the lowest E) with velocity 1 at channel 4

More of them you can get from `mw2_config` file.

By using controller nr 20 with values starting from 0 onwards, it is possible to jump directly to particular "group" (basically - paragraph) of the lyrics. This controller can serve as pseudo-transport facility when 'display' is used in tandem with some sequencer. Usually sequencers are sending all recent controllers when placing the playhead (e.g. MusE).

Display can be controlled as well with PC keyboard:

* `o` - open a text file
* `r` - reload a text file
* `Esc` - jump to the beginning of lyrics
* `Space`, `Arrow down`, `Arrow right` - highlight next token
* `Backspace`, `Arrow up`, `Arrow left` - go back
* `Page down` - jump to the next group
* `Page up` - jump to the previous proup
* `z`, `x`, `c` - select theme

//mk1037