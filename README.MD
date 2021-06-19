# VSCode Project Template

This is a simple template for building dos programs with VSCode, Dosbox-X and Turbo C++. The main project file is `src/main.c`. Build it with `CTRL+SHIFT+B` and run it with `F9`. 

## Structure

- `.vscode/tasks.json` - The commands for building and running `main.c` and `main.exe`. Change `dosbox-x` to `dosbox` here if you use dosbox instead of `dosbox-x` instead. I hope it's also obvious how you can change `args` in tasks to adapt it to your own building habits. A helpful document is VSCode's [Variable Reference](https://code.visualstudio.com/docs/editor/variables-reference) which tells you what you need to add to e.g. reference the file opened in the current editor.
- `src/main.c` - The main file. I added some VGA commands if you want to start building from there. I am planning to follow [256 Color VGA Programming in C](http://www.brackeen.com/vga/basics.html).
- `BUILD.BAT` - The dos build batch file. Builds `src/main.c` and pauses the output. Think of it as a watered down makefile. If you want to pass it arguments from `.vscode/tasks.json` you can do so by referencing `%1` for the first argument, `%2` for the second, etc.
- `RUN.BAT` - Runs `build/MAIN.EXE` and pauses the output.

## Contacting me

Just leave an issue