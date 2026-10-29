# FracIRC experimental source build

Imported from the supplied fracirc_src.zip into components/fracirc.
The original archive and Git import bundle are retained in the release sources
cache, independently of Downloads. No prebuilt FracIRC executable is used.

Launch D:/APPS/FRACIRC/FRACIRC.PRG. It uses the existing GlueSTiK/MiNTNet service.
Ctrl-O opens the connection dialog with irc.libera.chat:6667 and nickname FnxFrac.
Auto-join is off. Change the nickname to your own before connecting. Alt-Q exits;
Ctrl-Q disconnects. Use Options for server/user settings. The GCC port uses a
bounded text FRACIRC.INF; preserve it when updating. Legacy DAT files from the
original archive are not compatible and are not installed.

Port work includes GCC/MiNTlib/GEMlib bindings, explicit 16-bit GEM values,
GCC-compatible STiK calls, replacement of the incomplete dialog initializer,
rectangular fills for the fVDI driver, bounded text preferences, and fixes to
uninitialized window state and missing function arguments.

This remains an experimental port of an incomplete historic source release.
Advanced DCC file transfer, FracTALK, sounds and large IRC channels are unvalidated.
Current preference persistence covers identity, server/port and directory fields;
additional display options retain their built-in defaults after restart.
No X11, STinG drivers or WDIALOG.PRG are installed. No modern TLS support is claimed.

Build/stage: python3 scripts/fracirc.py. Original author: Tim Putnam; original
notices and documentation are preserved in the component source and sources folder.

IRC command fixes normalize outgoing lines to CRLF, accept `/list` without a
filter, parse server prefixes and fragmented input safely, and answer PING
keepalives. Use `/join #channel` and `/nick nickname` (up to nine characters).
Channel names support up to 200 characters, with bounded window status text.

Hardware validation against the private InspIRCd server confirmed `/list`,
`/join #general-discussions`, and `/nick FnxTest` using the source-built client.

The right-hand user panel uses a 200-pixel area with readable default colours
and VDI font spacing. NAMES refreshes replace the roster without duplicates;
nickname changes preserve status prefixes, and leave/quit events remove users.
The roster holds up to 128 entries. Scrolling larger rosters is not implemented.

Joined-channel navigation: the middle sidebar lists all joined channels on the
current connection. Click a channel to select the message target and its user
list. Each joined channel has a separate 150-line chat history. The selected
channel has a > marker; small windows offer Prev/Next pages. Server-assigned
auto-joins are retained.

The Open connection dialog has an optional masked NickServ password (up to 64
non-space printable characters). After IRC registration, FracIRC sends
PRIVMSG NickServ :identify <password> once, without echoing the secret locally.
A sent notice is not proof of successful identification; NickServ supplies the
result. Blank skips identification. No TLS support has been added.

Connect after editing the password to accept it, then use File > Save setup or
Ctrl-S to save the default FRACIRC.INF. Passwords are stored as plain text in
that file because they must be sent to NickServ. Saved passwords load masked
on the next connection. Do not include personal preferences in shared drives.

Channel selection restores that channel's history and scroll position. Incoming
channel traffic is retained while another channel is selected. The Server entry
keeps the initial connection log accessible. Ctrl-L clears the selected chat
area and its stored history, preserving other channels. Histories are in memory
and reset when a channel is left or the program exits.

The window's vertical scrollbar follows the selected history: its thumb reflects
the visible fraction of stored lines. Drag the thumb, use the arrow buttons, or
click above/below the thumb to move a page. Histories shorter than the view show
a full-size thumb. Each channel restores its own position. New lines keep the
view at the latest line when at the bottom, or preserve the reading position
when scrolled back (until the oldest lines leave the 150-line ring). Ctrl-L
resets the selected scrollbar along with the history.
