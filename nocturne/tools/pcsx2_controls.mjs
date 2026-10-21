// Use from node_repl after the Computer Use skill initialization.
// Input uses PCSX2 controller macros; no guest game-state writes are performed.
export const keys = Object.freeze({
  Cross: 'F10', Circle: 'F11', Start: 'F12', Down: 'F7',
  Up: 'F13', Left: 'F14', Right: 'F15', Triangle: 'F16',
  Square: 'F17', L1: 'F18', R1: 'F19', L2: 'F20', R2: 'F21', Select: 'F22',
});

export async function tap(sky, window, button, durationMs = 100) {
  if (!(button in keys)) throw new Error('Unknown PS2 button');
  if (!Number.isInteger(durationMs) || durationMs < 50 || durationMs > 500)
    throw new Error('Use a bounded 50..500 ms controller press');
  const key = keys[button];
  await sky.press_key({ window, key });
  try {
    // Deliberate controller hold, rather than waiting for a UI transition.
    await new Promise(resolve => setTimeout(resolve, durationMs));
  } finally {
    await sky.press_key({ window, key });
  }
  return await sky.get_window_state({ window });
}
