# Dynamic Window Manager
My active build of suckless' dynamic window manager.  
## preview
<div align=center>
<img width=49% src=.assets/sky.png />
<img width=49% src=.assets/sky2.png />
</div>

### install these as well
[dwmblocks](https://github.com/savar95x/dwmblocks) - the statusbar  
[dotfiles](https://github.com/savar95x/dotfiles) - my configs

<!--[reddit post](https://www.reddit.com/r/unixporn/comments/15sh6yw/dwm_dream_of_the_endless/)  -->
## patches
The patches that I've used are in the `patches/` directory, do take a look if you're curious  
### what i've added on my own
- single client padding  
- underline tag (the patch does not work)  
- drw_fontset_free() from original dwm/drw.c \[dunno which patch removed it and why\],
- and making alpha and titlecolor work together \[just a parallel third subarray in alphas\[\]\[3\] surprisingly fixed it\]

the patches are in patches/  
### what i plan on adding
- write a function that applies gaps in real time and bind them to 2-3 presets  
- apply restart patch  
- per tag vanitygaps  

## installation
Clone this repo and run `compiledwm`
```bash
git clone https://github.com/savar95x/dwm
cd dwm
./compiledwm
```  
This should make and install dwm.  

## launching
I use startx from the console. Just make a file in the home of your user `.xinitrc` and add the following stuff
```bash
#!/bin/sh
export XAUTHORITY="$HOME/.local/run/x11/xauth"
setsid -f $HOME/.config/dwm/autostart.sh &
export MYMENU="dmenu"
exec dbus-launch dwm
```  
And make this file `~/.xinitrc` executable  
```bash
$ chmod +x ~/.xinitrc
```  
Now whenever you run `startx` from the linux console, it should run the `~/.xinitrc` file.  

### Thanks
[lukesmith](https://lukesmith.xyz) for his chad way of living
