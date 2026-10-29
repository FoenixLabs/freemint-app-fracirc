# FracIRC

Standalone FreeMiNT application, maintained for the Foenix A2560Me.

## Enhancements to the original FracIRC

The original application is by Tim Putnam. This version preserves its GEM
interface and adds the following porting work, fixes and features:

- **Modern FreeMiNT build:** GCC, MiNTlib and GEMlib support, explicit GEM-sized
  values, compatibility replacements for the original compiler, and a 68060
  build that does not require an FPU. Uses XaAES's native windowed dialogs.
- **MiNTNet connectivity through GlueSTiK:** repaired transport bindings and
  receive handling, including fragmented/coalesced input, bounded line buffering,
  normalized CRLF output and correct PING replies. No separate STinG network
  stack or X11 server is required; GlueSTiK remains a runtime dependency.
- **IRC command and channel fixes:** repaired `/list`, `/join` and `/nick`
  handling; support for channel names up to 200 characters; retained server
  autojoins; and consistent removal on PART or KICK.
- **Joined-channel sidebar:** lists Server and the joined channels, marks the
  selected view, switches the destination and transcript on click, and provides
  pagination when the window is too short to show every channel.
- **Repaired user sidebar:** readable colours and font-based positioning,
  accurate NAMES refresh, status-prefix handling, duplicate prevention, nickname
  updates, user removal and bounded storage for up to 128 users per channel.
- **Separate conversation histories:** each channel and server view retains its
  own 150-line in-memory transcript. Background channel traffic and local echoes
  are routed to the appropriate history. Switching views restores the transcript.
- **Working history scrollbar:** proportional thumb size for the selected
  history, thumb dragging, line arrows, page clicks and resize updates. Each view
  remembers its position, and incoming messages preserve the reading position
  while scrolled back. **Ctrl-L** clears only the selected transcript/history.
- **Optional NickServ identification:** a masked password field queues
  `/msg NickServ identify <password>` after successful registration, without
  echoing the secret into the chat transcript. Leaving it blank skips identification.
- **Saved settings:** bounded text preferences, saved NickServ password loading,
  and **Ctrl-S** to save the default configuration. Saved passwords are plaintext
  because they must be sent to NickServ; protect the settings file.
- **Rendering and stability fixes:** repaired fVDI-compatible rectangle fills,
  clipping and redraw behaviour, minimum window dimensions, bounded text handling,
  and correct event routing to the window receiving scrollbar events.
- **Regression coverage:** host tests exercise IRC framing, preferences, password
  editing/masking, channel selection, user rosters, history isolation and scrollbar
  calculations. These tests are included in this repository and run in GitHub Actions.

History is kept in memory rather than persisted across application restarts.
DCC, FracTALK and legacy sound features remain experimental; their presence in
the original source does not imply they have been validated in this port.

## Build

Requires Python 3, `m68k-atari-mint-gcc`, a built MiNTlib tree with
`include/` and `build/m68020/`, and GEMlib with `.lib68020-60/`.
These dependencies are supplied explicitly; no system-workspace checkout is required.

```sh
python3 build.py --mintlib /path/to/mintlib --gemlib /path/to/gemlib
```

Outputs are written to `build/`. Use `--output` to change the location and
`--cc` to select a compiler or compiler wrapper. Builds target 68060 without
FPU instructions. For FracIRC, install `fracirc2.rsc` beside `FRACIRC.PRG` as
`FRACIRC2.RSC`.

## Tests

Host regression tests need Python 3 and a host C compiler; ServiceManager's
account transaction test also requires libcrypt development files.

```sh
for test in tests/*.py; do python3 "$test" || exit; done
```

## Installation and integration

See [USAGE.md](USAGE.md) for runtime instructions and known limitations.
The [system workspace](https://github.com/FoenixLabs/freemint-agent-workspace)
handles drive installation, startup scripts, hardware dependencies, and desktop shortcuts.
This repository owns application sources, builds, and application unit tests.

## License and provenance

Original Tim Putnam notices are preserved. The supplied source archive did not specify a new license; this extraction does not relicense the upstream code. See IMPORT.md.
