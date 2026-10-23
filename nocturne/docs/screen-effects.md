# Screen effects: blurs, filters, lights and fog

Events change how the whole screen looks with a handful of FlowScript
commands (`scrCommonCommand`): blurs and colour filters, the scene's light and
fog colours, the screen quake and the camera's field of view. The commands
only set state; the kernel (`dds3KernelDraw`) fades it in over frames and the
effect library (`effEvent`) draws it.

Source: `source/src/script/commands.cpp` (the commands),
`source/src/kernel/draw.cpp` (the kernel's state), `source/src/effect/event.cpp`
(the effects' switches and settings). Records and names follow the HD
remaster (`dds3Effect_*_t`, `dds3KernelDraw`, `effEvent`).

## The six event effects

| Effect | Commands | Kernel | Library |
|---|---|---|---|
| whole-screen blur | `BLUR2_*` | `dds3*Blur2*` | `Eve_Blur*` |
| whole-screen filter | `FILTER2_*` | `dds3*Filter2*` | `Eve_Filter*` |
| partial multi-blur | `MUL_BLUR_*` | `dds3*MultiBlur*` | `Eve_PartialMultiBlur*` |
| partial multi-filter | `MFILTER_*` | `dds3*MFilter*` | `Eve_PartialMultiFilter*` |
| distortion blur | `DIST_BLUR_*` | `dds3*DistBlur*` | `Eve_DistortionBlur*` |
| ripple blur | `RIP_BLUR_*` | `dds3*RipBlur*` | `Eve_RippleBlur*` |

Each effect has the same six commands:

- `*_PARA`, `*_RGBA(r, g, b, a)`, `*_AREA` set the **target** settings
  (rotation and scale, colour, the masked area and its centre, the number
  and spacing of strips or ripples);
- `*_ON(frames)` / `*_OFF(frames)` fade the effect in or out: its alpha
  goes from 0 to the target's (or back) over that many frames, or at once
  for 0;
- `*_SWAP(frames)` moves from the settings drawn now to the target.

A fade is recorded in a bit of `dds3DrawFlag` and a small record
`{now, max, abase, atarget, swapnow, swapmax}`; `dds3BlurUpdate` advances it
each frame (not rewritten yet). `BLUR_ALLOFF` and `FILTER_ALLOFF` turn every
blur or both filters off at once.

Blend modes (the GS alpha setting): 0 normal (0x44), 1 additive (0x48),
2 subtractive (0x42); the filters also take 3, the screen inverted (0x06).

Quirks kept:

- The distortion and ripple blurs apply their target settings when fading
  in, and are switched off until the fade turns them on; the others wait.
- The multi-blur's `OFF` re-applies its target settings first.
- More than 100 distortion strips or 40 ripples are cut down and counted
  (`distblurovercnt`, `ripblurovercnt`).

`BLUR(frames, alpha, scale)` is the older screen blur (the last frame drawn
over the next), on while either value is non-zero.

## Light, ambient, fog

- `SCENE_LIGHT_RGB(frames, r, g, b)` sets light 0's colour,
  `SCENE_AMBIENT` the ambient light, `SCENE_FOG_RGB` the fog's colour: at
  once, or as a fade between two colours packed as the GS takes them
  (0xAABBGGRR; lights and ambient at half intensity, x128, fog x255).
- `SCENE_FOG_PARA(frames, max, near, min, far)` takes ints (read as
  unsigned) for the fog's distances; `SOFTEN_BIAS(frames, soften, bias)` the
  models' softening.
- `SCENE_LIGHT_DIR(frames, x, y, z)` points light 0 (refused when all three
  are within 0.01 of 0). A fade keeps the start direction and the rotation
  to the end as a quaternion (`dds3RotationArc`): none for nearly the same
  direction (dot >= 0.9999), half a turn about an axis at right angles for
  nearly opposite ones, otherwise about the cross product by way of the
  half-way vector. The VU0 code passes these vectors in registers; the
  rewrite does the same arithmetic lane by lane.

## The camera and the pad

- `SET_FOVY(degrees)` converts to radians and then accepts the angle only
  strictly between 5 and 180 — a check written for degrees — so ordinary
  angles are refused (with a debug warning compiled out of the game).
- `QUAKE_ON(frames, range)` shakes the view (0 frames: until `QUAKE_OFF`);
  the vertical range is `range` tenths, the horizontal 0.4 of it.
- `PAD_TRIG(button)` / `PAD_PRESS(button)` read the pad; `PAD_ACT(mode,
  power, frames)` vibrates it.
