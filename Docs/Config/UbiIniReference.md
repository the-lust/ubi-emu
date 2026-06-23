Ubi.ini is the single config file shared by all five UUES emulators. You drop it in your game directory. Under the Settings section you set your UserName (defaults to Player), a UserId that is a GUID and auto-generated if you leave it blank, an Email defaulting to player@local.host, and Language like en-US. LogLevel accepts trace, debug, info, warn, error, fatal, or none with info being the default. DebugMode is a bool that turns on verbose logging when true. SaveType uses 0 for AppData, 1 for GameFolder, or 2 for Custom, and when you pick 2 you also set SavePath which defaults to SAVE_GAMES. UnlockAllDlc and UnlockAllItems are both bools that default to true, same for OfflineMode, LanMode, and EnableAchievements which handles achievement spoofing.

The DLC section takes DLC IDs one per line, same format you might remember from Goldberg or uplay_r2.ini. Items works the same way with item IDs one per line.

Network has your ServerUrl for when you are running online, a ServerPort defaulting to 0, a PipeName for named pipes, and ServerIP which defaults to 127.0.0.1 and is used by the Orbit emulator.

Ticket holds Denuvo ticket data. Ticket is a base64 string for the ticket itself, Ownership is a SecureDLC ownership token, and TokenFile points to an external token file with Token.ini as the default.

R1 and R2 each have one setting, GenerateNewId, a bool defaulting to false that makes the emulator create a fresh UserId on first launch. UPC has DemuxPort for the demux protocol port, defaulting to 0. Orbit has AccountId as an int defaulting to 0.

Logging lets you set LogFile which defaults to Uues.log and a LogLevel that overrides the per-emulator log level, also defaulting to info.

Not every key is read by every emulator. Each emulator only looks at the sections it cares about and ignores anything it does not recognize.

A typical config starts with a Settings block containing your user details and preferences, then a DLC block with whatever DLC IDs you want unlocked, a Network block you would uncomment and fill in if you need a custom server, and a Ticket block if you are using an external token file. Lines starting with semicolons are comments and get ignored.
