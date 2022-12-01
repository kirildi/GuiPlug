# GuiPlug

Musical instrument and fx plugin maker

## Directories and files

- **dependencies** - dependencies like skia, vst3 and others;
- **(hidden)buildir** - default Meson build directory;
- **GLFW** - header files for the GLFW backends library;
- **imgui** - The Dear Imgui GUI library;
- **imgui/backends** - put imgui backend impl here;
- **imgui/renderers** - put imgui renderer impl here;
- **include** - the project headers(.h);
- **lib** - additional libs;
- **(hidden)release** - project production dir(you can name it whatever you want);
- **resources** - fonts, images used in the project;
- **src** - the project definitions files (.cpp);
- **main.cpp** - main project file;
- **meson.build** - Meson build system configuration file;
- **nlohmann** - JSON library;
- **portable-file-dialogs.h** - lib for operating system dialogs;
- **libglfw3.a, libglfwdll.a** - precompiled static libs used for the GLFW

_Quote: lib contains glfw3.dll, which is required by the .exe. For now you can copy it from here while developing_

## VS Code configs (windows)

### tasks.json

For VS code build task add this in tasks.json:

```
{
      "type": "meson",
      "target": "a",
      "mode": "build",
      "problemMatcher": [ "$meson-gcc" ],
      "group": {
      "kind": "build",
      "isDefault": true
      },
      "label": "Meson: Build a"
},
```

### launch.json

```
{
      "version": "0.2.0",
      "configurations": [
            {
                  "name": "g++.exe - Build and debug active file",
                  "type": "cppdbg",
                  "request": "launch",
                  //"program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
                  "program": "${workspaceFolder}\\release\\a.exe",
                  "args": [],
                  "stopAtEntry": false,
                  "cwd": "${fileDirname}",
                  "environment": [],
                  "externalConsole": false,
                  "MIMode": "gdb",
                  "miDebuggerPath": "C:\\msys64\\mingw64\\bin\\gdb.exe",
                  "setupCommands": [
                        {
                              "description": "Enable pretty-printing for gdb",
                              "text": "-enable-pretty-printing",
                              "ignoreFailures": true
                        }
                  ]
            }
      ]
}
```

### c_cpp_properties.json

```
{
    "configurations": [
        {
            "name": "GCC",
            "includePath": [
                "${workspaceFolder}/**",
                "${workspaceFolder}/imgui/",
                "${workspaceFolder}/imgui/backends/",
                "${workspaceFolder}/imgui/renderers/",
                "${workspaceFolder}/lib/",
                "${workspaceFolder}/dependencies/",
                "${workspaceFolder}/dependencies/skia/include/",
                "${workspaceFolder}/dependencies/skia/include/core/",
                "${workspaceFolder}/dependencies/skia/include/effects/",
                "${workspaceFolder}/dependencies/skia/include/gpu/",
                "${workspaceFolder}/dependencies/skia/include/private/",
                "${workspaceFolder}/dependencies/skia/include/config/",
                "${workspaceFolder}/dependencies/skia/src/",
                "${workspaceFolder}/dependencies/skia/src/image/",
                "${workspaceFolder}/dependencies/skia/src/core/",
                "${workspaceFolder}/dependencies/skia/src/gpu/",
                "${workspaceFolder}/include/",
                "${workspaceFolder}/include/fonts/",
                "${workspaceFolder}/resources/fonts/",
                "${workspaceFolder}/src/"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "windowsSdkVersion": "10.0.19041.0",
            "compilerPath": "C:\\msys64\\mingw64\\bin\\g++.exe",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "windows-gcc-x64",
            "compileCommands": "${workspaceFolder}/builddir/compile_commands.json"
        }
    ],
    "version": 4
}
```
