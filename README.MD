# ALSA Sound Control

## Compile

`make` to compile. 

This will create a statically linked library file  `libsoundctrl.so` in `bin/` as well as `/usr/lib/`

## API

1. Get system volume range (in dB):
	
	`get_range(int *min, int *max)`

2. Get current system volume level 

	`get_volume()`

3. Set system volume:

	`set_volume(int dB_value)`

## Use

### The library can be PInvoked (C# example)

```C#
[DllImport("libsoundctrl.so", EntryPoint = "set_volume", CallingConvention = CallingConvention.Cdecl)]
static extern void set_volume(int dB_value);

[DllImport("libsoundctrl.so", EntryPoint = "get_volume", CallingConvention = CallingConvention.Cdecl)]
static extern int get_volume();

[DllImport("libsoundctrl.so", EntryPoint = "get_range", CallingConvention = CallingConvention.Cdecl)]
static extern int get_range(ref int min, ref int max);
```
