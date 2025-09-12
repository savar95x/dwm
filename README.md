# Dynamic Window Manager
My active build of suckless's dynamic window manager.  
## Preview
<div align=center>
<img width=49% src=.assets/1.png />
<img width=49% src=.assets/2.png />
</div>
<div align=center>
<img width=49% src=.assets/3.png />
<img width=49% src=.assets/4.png />
</div>

## Installation
```bash
git clone https://github.com/savar95x/dwm savar95x-dwm/
cd savar95x-dwm/
./compiledwm
```
You would also want to install [my dwmblocks build](https://github.com/savar95/dwmblocks) for those nice looking bar modules on the top right.  
And my correspoding dotfiles including the configs and the scripts are over [here](https://github.com/savar95x/dotfiles)  

<!--[reddit post](https://www.reddit.com/r/unixporn/comments/15sh6yw/dwm_dream_of_the_endless/)  -->
## Features
### Patches
The patches that I've used are in the `patches/` directory, do take a look if you're curious  
### What I've added on my own
- single client padding  
- underline tag (the patch does not work)  
- drw_fontset_free() from original dwm/drw.c \[dunno which patch removed it and why\],
- and making alpha and titlecolor work together \[just a parallel third subarray in alphas\[\]\[3\] surprisingly fixed it\]
- wrote a toggle between tile and monocle, and replaced it with current fullscreen (independent of slemon->showbar)
- enablegaps flag for each tag, gives the illusion of each tag having a memory of it's own, where in actuality it only has this flag which we check while applying gaps on windows (or maybe just add another flag to toggle between 2 preset defaults)  
steps:  
apply pertag vanity from here https://github.com/jitessh/voidwm/commit/e8393a42f2f0f1fcbcbd61a819fd936a1245e1ed, this gives each tag their enablegaps flag  
getgaps() change calculations for !enablegaps to make it retain innergaps for outergaps, and do not change innergaps  
implement biggaps similar to enablegaps as a flag for 2 different gap settings, per tag  
also added resetgaps() func.  

the patches are in patches/  
### What I plan on adding
- patch the pango patch use variable fonts esp with battery
- modify biggaps implementation to have dynamic number of presets (more elegent)  
- make enablegaps and biggaps have the same precendece (implementation needs to be more than just flags then, we should also know which flag has been set latest, or pass it as argument)  
- add pertag gaps implementation because it is bugging me, and even tho it might be too bloated, it will allow me to set pertag gaps on the fly, and maybe even not need any flags.  
- apply restart patch  

## Launching
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
