// The script VM as the legacy C and the fake world see it: the rewrite's
// (script/vm.hpp), on the work at FW_SCRIPT.
#include <cstring>

#include "harness.hpp"
#include "nocturne/script/vm.hpp"

using namespace nocturne;

extern "C" {
uint64_t scrGetData(void) { return scr::scrGetData(); }
uint64_t scrGetIntPara(uint64_t index) { return static_cast<uint64_t>(static_cast<int64_t>(scr::scrGetIntPara(static_cast<int32_t>(index)))); }
void scrSetIntReturnValue(uint64_t value) { scr::scrSetIntReturnValue(static_cast<int32_t>(value)); }
uint64_t scrGetMessageHandle(void) { return static_cast<uint64_t>(static_cast<int64_t>(scr::scrGetMessageHandle())); }
}

namespace difftest {

namespace {

constexpr int32_t kArguments = 8;

scr::ProcessWork& work() { return at<scr::ProcessWork>(FW_SCRIPT); }

} // namespace

void scriptWork(int32_t messageHandle)
{
    scr::ProcessWork& w = work();
    std::memset(&w, 0, sizeof w);
    w.SP = kArguments;
    for (int i = 0; i < scr::kStackSize; ++i)
        w.StackType[i] = scr::kInt;
    w.MesHandle = messageHandle;
    w.data = FW_ACTION;
    at<uint32_t>(0x00551c78) = FW_SCRIPT;   // the running COMM's work
}

// Argument i is the i-th entry below the top of the stack.
void scriptParam(int32_t index, int32_t value) { work().StackData[kArguments - 1 - index] = static_cast<uint32_t>(value); }

int32_t& scriptMessageHandle() { return work().MesHandle; }

} // namespace difftest
