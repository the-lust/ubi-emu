# Core library — has to be first, everything depends on it
add_subdirectory(Core)

# Emulator implementations
# Order doesnt really matter here but grouping them anyway
add_subdirectory(EmuR1)
add_subdirectory(EmuR2)
add_subdirectory(EmuUPC)
add_subdirectory(EmuOrbit)
add_subdirectory(EmuDbData)

# Shared DLL loader — needs Core and the emulator interfaces
add_subdirectory(Shared)

# Tools and tests — depend on everything above
add_subdirectory(Tools)
add_subdirectory(Tests)
