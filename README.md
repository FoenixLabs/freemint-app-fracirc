# FracIRC

Standalone FreeMiNT application, maintained for the Foenix A2560Me.

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
