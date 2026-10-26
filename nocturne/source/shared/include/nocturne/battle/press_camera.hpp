// The press turn camera (original unit: nbCameraPress): at the start of a
// side's turn the side's camera shot fades its colour in over three frames,
// holds, and fades it back out by frame 10; the phase machine waits for
// frame 10 and for the camera to finish at 21 (battle/main_process.hpp).
// The first turn of an encounter skips it.
#pragma once

#include <cstdint>

namespace nocturne::nb {

void runPressCamera();          // nbCameraPressProcessRun (0x1BA6E0): a frame
void startPressCamera();        // nbCameraPressProcessInit (0x1BA7D8): from frame 0, unless skipped
bool pressCameraRunning();      // nbCameraPressProcessCheckRun (0x1BA808)
int32_t pressCameraFrame();     // nbCameraPressProcessGetFrame (0x1BA810)
void skipNextPressCamera();     // nbCameraPressProcessThrough (0x1BA818)

} // namespace nocturne::nb
