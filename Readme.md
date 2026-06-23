you know how there's like a million different ubisoft emulator projects and each one only supports one specific version of uplay and they all have different config formats and none of them talk to each other

yeah i got tired of maintaining five separate forks so i smashed them together into one thing

right now it covers uplay_r1 (the old one from ac2/farcry3 era), uplay_r2 (newer stuff like valhalla), upc (ubisoft connect), ubiorbit (driver san francisco etc), and dbdata (the denuvo activation thing). each one builds as its own dll from the same source tree so fixes in the core library apply to all of them.

build it like any cmake project:
  cmake -B Build
  cmake --build Build --config Release

drop the right dll + Ubi.ini next to your game exe and it should just work. if it doesn't, check the docs folder or file an issue.

stuff that kinda works: r1 is solid because people have been poking at it the longest. r2 mostly works but some games do weird things with the friend list api that i haven't fully figured out. upc works for the games i've tested but there's probably edge cases. orbit works for driver sf at least. dbdata is the newest and probably the buggiest - some denuvo games need a token file from a legit install that i can't distribute.

stuff that doesn't work yet: the overlay stubs exist but don't actually draw anything (most games don't seem to care), the dockerfile only builds x64 right now, and debug builds are slow enough to cause stutter on single-core systems because logging is chatty.

if you're coming from goldberg, coldapi, lumaplay, or any of the other emulator configs, the tools/ folder has importers that try to convert between formats. they're not perfect but they get you most of the way there.

project is laid out like:
  src/core/ - shared library with all the common stuff (ini parsing, crypto, sockets, protobuf, hooking)
  src/emur1/ src/emur2/ src/emuupc/ src/emuorbit/ src/emudbdata/ - one folder per emulator
  src/shared/ - dll entry point and the factory that picks which emulator to load
  tests/ - unit tests that i should probably write more of
  tools/ - config importers/converters
  examples/ - pre-made Ubi.ini files for specific games

license is mit, do whatever. just don't blame me if it eats your save files.