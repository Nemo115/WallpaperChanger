gcc src/sfd.c src/main.c -o wall_hax.exe -O1 -Wall -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32