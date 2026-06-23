# UUES — Unified Ubisoft Emulator Suite

it is a modular framework that replaces five different ubisoft modules with a single unified emulator. Each emulator builds as its own DLL from the same shared core library, so a fix in `LibUbi` applies to all of them.

**Covers:** Uplay R1 (AC2, Far Cry 3 era), Uplay R2 (Valhalla, newer titles), Ubisoft Connect (UPC), Orbit (Driver: SF), and DbData (ticket/token activation).

---




## Quick Start

1. **Pick the right DLL** for ur game and drop it in the game folder next to the game binaary:

| Emulator | DLL | Targets |
|----------|-----|---------|
| R1 | `uplay_r1_loader.dll` | Assassin's Creed 2/Brotherhood/Revelations, Far Cry 3, Splinter Cell: Blacklist |
| R2 | `uplay_r2_loader.dll` | Assassin's Creed Valhalla/Odyssey/Origins, Far Cry 4/5/6, Watch Dogs 2/Legion |
| UPC | `upc_r1_loader.dll` | Ubisoft Connect titles (The Crew, newer games) |
| Orbit | `ubiorbitapi_r2_loader.dll` | Driver: San Francisco, older Orbit-bound titles |
| DbData | `dbdata.dll` | Games using Denuvo SecureDLC activation |

2. **Drop `Ubi.ini`** next to the DLL. Minimal example:
```ini
[Settings]
UserName=Player
UserId=auto
LogLevel=info
UnlockAllDlc=true
OfflineMode=true
```

3. **Launch the game.** th DLL hooks into the gams import table and serves fake responses so the game thinks Ubisoft services are running.

---

## Ubi.ini Reference

 single `Ubi.ini` drives all five emulators, Each emu only reads the sections it needs.

### [Settings]
| Key | Default | Description |
|-----|---------|-------------|
| `UserName` | `Player` | Display name |
| `UserId` | `auto` | GUID. `auto` generates a random one; specify a fixed GUID for consistency |
| `Email` | `player@local.host` | Email for API calls |
| `Language` | `en-US` | Locale |
| `LogLevel` | `info` | `trace` / `debug` / `info` / `warn` / `error` / `fatal` / `none` |
| `SaveType` | `0` | `0` = AppData, `1` = GameFolder, `2` = Custom (`SavePath` required) |
| `SavePath` | `SAVE_GAMES` | Custom save directory (only when `SaveType=2`) |
| `UnlockAllDlc` | `true` | Unlock every DLC |
| `UnlockAllItems` | `true` | Unlock every inventory item |
| `OfflineMode` | `true` | Skip network calls |
| `LanMode` | `false` | Enable LAN multiplayer stubs |
| `EnableAchievements` | `true` | Spoof achievement API responses |

### [DLC]
DLC IDs, one per line. The emulator tells the game these IDs are owned.
```ini
[DLC]
390001
390002
```

### [Items]
Item IDs, one per line. Same format as DLC.

### [Network]
| Key | Default | Description |
|-----|---------|-------------|
| `ServerUrl` | *(none)* | API endpoint for online mode |
| `ServerPort` | `0` | Server port |
| `PipeName` | *(none)* | Named pipe identifier |
| `ServerIP` | `127.0.0.1` | Used by Orbit emulator |

### [Ticket] — Denuvo Activation
| Key | Default | Description |
|-----|---------|-------------|
| `Ticket` | *(empty)* | Base64-encoded Denuvo ticket |
| `Ownership` | *(empty)* | SecureDLC ownership token |
| `TokenFile` | `Token.ini` | Path to external token file |

### [DbData]
| Key | Default | Description |
|-----|---------|-------------|
| `AppId` | `0` | Game AppId for SecureDLC |
| `UserId` | *(empty)* | Override UserId for Denuvo activation |

### Emulator-specific sections
| Section | Key | Default | Description |
|---------|-----|---------|-------------|
| `[R1]` | `GenerateNewId` | `false` | Create fresh UserId on first launch |
| `[R2]` | `GenerateNewId` | `false` | Create fresh UserId on first launch |
| `[UPC]` | `DemuxPort` | `0` | Demux protocol port |
| `[Orbit]` | `AccountId` | `0` | Orbit account ID |

### [Logging]
| Key | Default | Description |
|-----|---------|-------------|
| `LogFile` | `Uues.log` | Log file path |
| `LogLevel` | `info` | Overrides the per-emulator log level |

Lines starting with `;` or `#` are comments.

---

## Activation / Tickets / Tokens

Some newergames require a valid ticket and token chain before startng. The DbData emulator handles this with two approaches:

### Automatic ticket generation
Set `UnlockAllDlc=true` in `[Settings]` and the emulator generates a signed ticket internally using its built in RSA key. Most sgames work this way without extra file

### External token file
Some games verify the token against platform data n reject auto gen tokens. For these titles, point `TokenFile` in `[Ticket]` to a `Token.ini` with tokens extracted from a legitimate install:

```ini
[Ticket]
TokenFile=Token.ini
```

The `Token.ini` file contains the Denuvo token data (activation and ownership tokens). These tokens are tied to hardware and cannot be shared between machines. You extract them from your own legal copy using tools like the ones in `Tools/`.

### SecureDLC ownership
The `[Ticket]` section also supports `Ownership` — a base64-encoded signed ownership blob that SecureDLC endpoints validate. If present, the emulator returns it to the game.

---

## Building from Source

Requires *CMake 3.20+** and a C++20 compiler.

```bash
git clone https://github.com/the-lust/ubi-emu.git
cd ubi-emu
cmake -B Build
cmake --build Build --config Release
```

Output DLLs appear under `Build/Bin/{R1,R2,UPC,Orbit,DbData}/`.

**Build presets** — see `Docs/Building/` for per-compiler guides:
- **MSVC** `cmake -B Build -G "Visual Studio 17 2022" -A x64`
- **MinGW** `cmake -B Build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release`
- **Clang** `cmake -B Build -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++`

**Options:**
- `-DBUILD_TESTS=ON` — build an run tests, `ctest` from build dir
- `-DBUILD_TOOLS=ON` — build config converters and utilities
- `-DENABLE_LOGGING=ON` — enable logging subsystem

---

## Project Layout

```
UUES/
├── Src/
│   ├── Core/         Shared library: INI, Crypto, Net, Proto, Hook, Log, Platform, Config, Storage, Threading
│   ├── EmuR1/        Uplay R1 emulator
│   ├── EmuR2/        Uplay R2 emulator
│   ├── EmuUPC/       Ubisoft Connect emulator
│   ├── EmuOrbit/     Orbit DRM emulator
│   ├── EmuDbData/    Denuvo ticket/token emulator
│   ├── Shared/       DLL entry point and EmulatorFactory
│   └── Tests/        Unit tests (Core, R1, R2, UPC, Orbit, DbData, Integration)
├── Tools/            Config importers, ExportValidator, GameIdResolver
├── Examples/         Pre-made Ubi.ini files for specific games
├── Docs/
│   ├── Config/       Ubi.ini reference
│   ├── Api/          Namespace overview
│   └── Building/     Build guides (MSVC, MinGW, Clang)
├── Dockerfile        Linux x64 cross-build
└── CMakeLists.txt    Root build file
```

---

## Project Status

| Emulator | Status | Notes |
|----------|--------|-------|
| **R1** | Most tested. Covers all known uplay_r1 exports |
| **R2** | Friend list API has edge cases |
| **UPC** | Demux protocol works for tested titles |
| **Orbit** | Tested with Driver: SF. LAN untested |
| **DbData** | Ticket/token emulation works (somee may be bugge dlike steam/ubi version app id for watch dogs 2)|

**CI:** MSVC, MinGW, and Clang — all three build and pass tests.

---

## Credits

MANY THANKS TO MY BSF AND BRO :3 [Andreh](https://github.com/NotAndreh)

This project stands on the shoulders of the game-emulation community. It was built after researching **69+ existing projects**, including but not limited to:

- **Goldberg Emulator** — the gold standard for Steam emulation; inspired the EmuR1/R2 design
- **ColdAPI** — Ubisoft Connect emulator that pioneered much of the UPC Demux protocol work
- **LumaPlay** — another Ubisoft emulator with solid Uplay R1 coverage
- **denuvosanctuary/ubi-dbdata** — reference implementation for Denuvo SecureDLC ticket/token handling
- **Various uplay_r1 and uplay_r2 wrappers** from the open-source scene, each tackling specific games

Thanks to veryone who documented Ubisofts internals, protocol buffers, and API endpoints over the years. without that collective effort none of this would exist.

---

## License

MIT — do whatever you want with it. See `License.txt`. Don't blame us if it eats your save files. ;)
