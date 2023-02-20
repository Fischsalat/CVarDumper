# CVarDumper

A dll that dumps all console-variables with their description from a UnrealEngine game.

You need to change the offset to [this](https://github.com/EpicGames/UnrealEngine/blob/4.21/Engine/Source/Runtime/Core/Public/HAL/IConsoleManager.h#L714) variable in line 22 of Source.cpp to the offset for your game.

Format:
```
r.DumpingMovie
"Allows to dump each rendered frame to disk (slow fps, names MovieFrame..).
<=0:off (default), <0:remains on, >0:remains on for n frames (n is the number specified)"

DumpGPU
"Dump one frame of rendering intermediary resources to disk."
```
