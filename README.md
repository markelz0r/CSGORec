# About

This simple tool will automatically split traditional GO:TV into individual POVs and provide video recording of each individual player in a separate video file.

This would only work with CS:GO running on some kind of X11 system (sorry Windows users).

**This project is in its very early stage of development so if you happened to come across it - brace yourself**

# Prerequisites 

# Usage
Using this tool is a pretty straightforward process, however it is not very generic by design, so you might need to tweak some things, more specifically commands in `BashService`. To run the tool use the following command:

```
./CSGORec <tickrate> <start_tick> <end_tick>
```

This would produce 10 video files in your `~/Video/` directory with the recording for each player between ticks specified.
