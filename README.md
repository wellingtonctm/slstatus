# slstatus (customized)

This is a customized version of [slstatus](https://tools.suckless.org/slstatus/) — a minimal status monitor for window managers like `dwm`. This fork introduces a custom component called `songs`, and currently includes the `slstatus-signals-1.0` patch for dynamic signal-based updates.

## ✨ Features

- All standard `slstatus` modules (CPU, RAM, battery, date, etc.)
- [slstatus-signals-1.0](https://tools.suckless.org/slstatus/patches/signals/) patch applied  
- **Custom `songs` module** to show the currently playing song from a custom Bash-based media app  
- Configurable via C (`config.h`)  
- Lightweight, fast, no dependencies beyond standard libc

---

## 🎵 Custom `songs` Module

The `songs` component displays the currently playing song, using a homegrown media control script ([yt-cli](https://github.com/wellingtonctm/yt-cli)) that:

- Writes the current song title to `~/.config/yt-cli/song.info`  
- Stores the media process PID in `~/.config/yt-cli/song.pid`  
- Listens for commands on a UNIX socket `~/.config/yt-cli/song.socket` to check pause status via MPV-like JSON IPC

### Output Format:
- If playing: `Song Title`  
- If paused: [`Song Title`] (bracketed)

It integrates into the status bar just like other modules:
```c
{ songs, "%s ", NULL, 0, 1 },
```

You can trigger real-time updates via:
```sh
kill -RTMIN+1 \$(pidof slstatus)
```

---

## 🧩 Configuration

Here’s an excerpt from `config.h`:

```c
static const struct arg args[] = {
    { songs,        "%s ",     NULL,    0,  1  },
    { cpu_perc,     "%s%% ",   NULL,    3, -1 },
    { ram_perc,     "%s%% ",   NULL,    3, -1 },
    { battery_perc, "%s%% ",   "BAT0",  60, -1 },
    { datetime,     "%s",      "%T",    1, -1 },
};
```

- `interval` is set to 1000 ms  
- Signal `1` updates the `songs` module on demand

---

## 📦 Building

```sh
git clone https://github.com/wellingtonctm/slstatus.git
cd slstatus
sudo make clean install
```

Edit and recompile after changing `config.h`:
```sh
make clean install
```

---

## 📝 License

This project is licensed under the **MIT/X Consortium License**, in the same spirit as the original [suckless slstatus](https://tools.suckless.org/slstatus/). See the [LICENSE](LICENSE) file for details.

---

## 🙏 Credits

- Original project: [suckless.org/slstatus](https://tools.suckless.org/slstatus/)  
- Patch used: [slstatus-signals-1.0](https://tools.suckless.org/slstatus/patches/signals/)

---

## 🔧 Optional: Hook into dwm

If you're using `dwm`, you can start `slstatus` in your `.xinitrc` or `autostart.sh`:

```sh
slstatus &
```
