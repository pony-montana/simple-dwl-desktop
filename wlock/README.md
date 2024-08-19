# wlock

wlock is a itty-bitty simple screenlocker for Wayland compositors that support
the `ext-session-lock-v1` protocol.

Excerpt from the protocol specifying the behavior:
> The client is responsible for performing authentication and informing the
> compositor when the session should be unlocked. If the client dies while
> the session is locked the session remains locked, possibly permanently
> depending on compositor policy.

## Building

To build wlock first ensure that you have the following dependencies:

* pkg-config
* wayland
* wayland-protocols
* xkbcommon

After installing the dependencies, you may build and install wlock:
```
make
make install
```

## Usage

Run `wlock`.

See the wlock usage (`wlock -h`) for more details.

## Credits

- [swaylock](https://github.com/swaywm/swaylock)
- [waylock](https://codeberg.org/ifreund/waylock)
