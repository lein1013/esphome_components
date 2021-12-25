
# Fork Notes
This is a fork of https://github.com/jplitza/esphome_components to adapt for the AS 1440. Work in progress! Current development modifications are done locally in the esphome/components folder.

The following sections are like in the original repository. 




# Components for ESPHome

These are the custom-made components that I use for [ESPHome].

To use them, simply add the following to your config file:

```yaml
external_components:
  - source: github://jplitza/esphome_components
```

[ESPHome]: https://esphome.io/

## OBIS

This component reads energy meters using the D0 according to IEC / DIN EN
62056-21 (or something like that - don't assume for a second I found or read any
standard on that protocol).

I'm successfully using it with an Easymeter Q3D, which is also what the
[example configuration](example_obis.yml) is tailored for. The baudrate and OBIS
channels for your meter might differ.

## FTC532

This component reads events from the FTC532 touch button controller found in
some cheap wall switches.

I'm successfully using it with a Teekar Curtain Switch, which is also what the
[example configuration](example_ftc532.yml) is tailored for.

# License

All components are licensed under [GPL v3](LICENSE).
