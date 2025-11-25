A small programme to maintain a playlist, with functionality of adding/removing and inserting songs.

Example:
We have 

playlist.txt
Bad Guy – Billie Eilish 👽
Bohemian Rhapsody - Queen 🎤
Billie Jean – Michael Jackson 🕺
Rolling in the Deep – Adele 🌊
Smells Like Teen Spirit – Nirvana 🤘

We run the programme, instructing to insert "Tarkan – Şımarık 💋" at 4th place
Then we get:

playlist-out.txt
Bad Guy – Billie Eilish 👽
Bohemian Rhapsody - Queen 🎤
Billie Jean – Michael Jackson 🕺
Tarkan – Şımarık 💋
Rolling in the Deep – Adele 🌊


## Compile and run
To compile quick and dirty with clang (I'm using C23 and llvm 21.6) just

```bash
#for macOs/Linux
clang -std=c2x -g -Iinclude -o main src/main.c src/singly_linked_list.c
```
or
```bash
#for Windows (I think this is how)
clang -std=c2x -g -Iinclude -o main.exe src\main.c src\singly_linked_list.c
```

And then run
```bash
#for macOs/Linux
./main
```
Or
```cmd
#for Windows (I think this is how)
main.exe
```
