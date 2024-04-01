# CharToClipboard

## How to set icon in C

1. Create a .rc file, for instance, program.rc with the following content:

`IDI_ICON_1 ICON "myicon.ico"`

The IDI_ICON_1 is an arbitrary ID that you can use in your application via a #define statement. But just for the application icon, you don't need to do anything.

2. Compile your source file(s) to generate objects/lib (will create main.obj):

`cl -c main.c`

3. Generate the resource file (will create the file program.res):

`rc program.rc`

4. Link your objects with the resource file:

`link main.obj program.res -out:program.exe`

The program should now appear with the icon.
