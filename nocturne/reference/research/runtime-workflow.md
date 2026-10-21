# Nocturne runtime integration

Installed on 2026-10-13; latest runtime check 2026-10-20 on this Windows PC. This adds live emulator checks to the
existing recovered-host/original-instruction validation; it does not change the
compiled recovery totals or establish hardware PS2 behavior.

Parallel work follows [the recovery workflow](../AGENTS.md#parallel-recovery):
workers investigate distinct code areas in place, with explicit file ownership.
PCSX2 and the working Ghidra project each have one owner at a time; other workers
continue from retained exports, original bytes, Unity and community sources.
The coordinator reviews results before changing shared mappings or recovery
counts. Parallelism does not require project copies or checkpoints.

## Tools and responsibilities

- Existing Ghidra MCP: the working R5900 program and persistent annotations.
- Existing PCSX2 MCP: guest EE/IOP debugging, memory, registers, pause/resume,
  and breakpoint observations. DebugServer is loopback port 21512; PINE is 28011.
- REA 6.4.0: supplementary evidence, native PC artifacts, function dossiers,
  callers/references, and reconstruction obligations where its providers support
  the target. Installed from the official npm package `rea-agents`.
- Computer Use: the selected Windows game window, screen observations and input.
  Read its installed skill before use. Do not infer game results from a host
  command returning successfully.

REA is registered in `C:\Users\coreg\.codex\config.toml`, with Ghidra 12.1.2
and the existing JDK 21 configured. Its matching skill is installed under
`C:\Users\coreg\.agents\skills\reverse-engineer-anything`. No installer
backups were made. Its MCP tools are available in this chat: the live session
query on 2026-10-14 confirms version 6.4.0, 170 tools and an available Windows
Ghidra provider. CLI operations also work.

Checks: `rea-readiness.json` passes the selected client/provider/skill checks;
`rea-mcp-smoke.json` records an actual stdio handshake and 170 tools, with a
successful target-free session query. `rea-nocturne-pc-smoke.json` records a real
Ghidra inspection of the installed `smt3hd.exe` launcher: 381 procedures and 278
defined strings. This is not a test of the entire 383 MB GameAssembly DLL.

### REA limits that matter here

The Windows Ghidra adapter admits PE targets only. Opening the actual
`SLUS_209.11` ELF returns `target_format_unsupported`, recorded in
`rea-ps2-support-check.json`. Its separate MIPS lane is bounded to MIPS32r2/o32,
and does not establish R5900/VU support. Do not force a generic MIPS processor
profile onto the PS2 program or confuse PCSX2 host x64 addresses with guest EE
addresses. REA native UI capture/scenarios require macOS/Mach-O; process PTY
capture supports Linux/macOS. Neither is the Windows controller solution.

Use our existing Ghidra MCP/PS2 processor extension for the guest executable.
REA's function evidence and obligation-ledger approach can inform our workflow,
but existing original-instruction comparisons remain authoritative for recovered
C. Community research remains an independent source of leads.

## Launch and headless behavior

From the repository root:

```powershell
& nocturne\tooling\launch_pcsx2.ps1 -Mode Interactive
& nocturne\tooling\launch_pcsx2.ps1 -Mode Hidden
```

Only one emulator instance may run at a time. The launcher refuses to disturb an
existing instance. It uses the installed custom `PCSX2 d75a0ad` executable and
the original Nocturne ISO. Slot 1 is `NocturneResearch.ps2`; the DDS card remains
available as `Card01.ps2`. Existing SDL controller bindings remain present.

Hidden mode uses supported `-nogui` plus a hidden Windows process window. Both
DebugServer and PINE connected, identified `SLUS-20911`, and execution advanced
without a visible window. This still uses a Windows rendering surface and D3D12.
It is not a display-server-free emulator. `QT_QPA_PLATFORM=offscreen` failed to
create the D3D12 swap chain, including with Null renderer selected. No offscreen
mode is offered by the launcher. Hidden-mode input and screenshots are not
verified; use Interactive for the screen/input evidence loop.

A fresh hidden-mode test connected both interfaces and observed original BIOS
WaitSema/SignalSema calls during normal Nocturne boot. Both returned semaphore
ID 13 and also changed V1. The [runtime observation](runtime-kernel-semaphore-observation.json)
records the registers, exact loaded leaf bytes, BIOS identity and cleanup.
All four owned breakpoints were removed and the owned emulator process exited.
This verifies hidden-mode debugging; it does not verify hidden controller input
or screenshot capture.

The [cache startup observation](runtime-cache-startup-observation.json) also
catches the original `FlushCache(0)` call and the subsequent guest DMAC loads.
`observe_pcsx2_cache_startup.py` owns a fresh hidden process, connects when its
debug listener appears, and pauses before installing its exact probes. In this
build `StartPaused=true` initializes the VM but leaves the debug listener
unavailable. Normal launch plus immediate connection catches early startup;
the installed setting has been restored to `StartPaused=false`. Each probe is
removed individually and the owned process is verified exited. This workflow
does not write guest registers or memory, use a savestate, or supply a device
response to the original/C comparison.

The [DMAC startup observation](runtime-dmac-startup-observation.json) extends
that hidden boot through the actual `AddDmacHandler(5, 2DE330, 0)` call. Six
observations include its return and the loaded kernel wrapper. The observed
return changes several argument/scratch registers and HI/LO in addition to
V0/V1; this is evidence for the next external ABI investigation, not a supplied
response in the original/C device tests. All owned probes were removed and
the owned process exited.

The [SIF kernel follow-through](runtime-sif-kernel-startup-observation.json)
adds twelve observations through registration, `EnableDmac(5)` and the first
`SifGetReg(80000000)`. Named linked-list/counter records were read before and
after registration; their unique footprint is 56 bytes per state. The SIF
software table entry at `8001E080` was read separately before and after GetReg.
These are bounded input/state observations, not a kernel RAM snapshot or an
emulated response. The [independent runtime review](battle-action-skill/sif-kernel-runtime-independent-review.json)
checks exact loaded BIOS words and all displayed register categories. K0,
Count and EPC changes remain distinct from the chosen flat-RAM test world.
All probes were removed and the owned emulator exited.

The subsequent [original/C worker comparison](battle-action-skill/worker-sif-kernel-C-validation.json)
uses these bounded pre-registration words as external inputs and computes
services 120/18 rather than replaying observed returns. Four fresh original
paths and the 553-unit C module agree through registration and stop before
service 22. This is a separate instruction/C comparison, not a claim that the
entire modeled kernel/device state was observed live. Its QWC 0 input is chosen
synthetic state. The [next original/C comparison](battle-action-skill/worker-sif-ready-C-validation.json)
extends four fresh paths through computed22/122 and coherent flat-RAM cache
handling to the unprovided119 boundary. It matches all declared banks/RAM/stacks,
including the actual native command packet and descriptor. The cache world
records effects in order without claiming physical cache-line or timing fidelity.
The [static119 study](battle-action-skill/sif-setdma119-static-study.json) identifies
channel6/ring inputs and a full128-bit V0 clobber. A fresh
[119 observation](runtime-sif-setdma119-observation.json) now captures the actual
before-syscall, after-syscall and after-leaf states. All335 loaded words match
the installed BIOS, and the leaf/caller match selected original ELF bytes.
The actual descriptor/source32 and164B of BEFORE-selected ring state are read;
no MMIO values, guest writes, savestates or full RAM copies are used. V0low701
and its payload-derived upper64 confirm why the next model needs a full128-bit
effect. Available six-category register captures remain distinct from the
comparison's304-bank contract. All owned probes were removed and the process
exited. Channel6 device evolution and transfer completion remain unverified.
The [independent review](battle-action-skill/sif-setdma119-runtime-independent-review.json)
passes 670 checks. This boot used SP `01FFEC80`; the comparison worker uses
`00C43D40`. Matching caller/descriptor evidence does not establish the same
thread or complete external state. Ring index 6 and return `701` remain specific
to this observation.

This custom build does not accept the newer `-gamecfg` or `-datapath` arguments.
An unsupported flag prevented startup before the debug endpoints appeared.
The runtime configuration is maintained in the installed portable INI in place.
No savestate is saved on shutdown, and no checkpoints or project copies are used.

The [alarm installer observation](runtime-alarm-installer-observation.json)
confirms a fresh hidden boot executes Nocturne's patch installation. At the
original guest load, Timer3 MODE was `0x83`; its bit `0x100` was clear. After
the six-entry installation loop, the complete 1,856-byte patch at `80076000`,
40-byte callback trampoline at `00082000`, and all eight changed syscall slots
match the original ELF. SetSyscall is selector `0x74` (116 decimal), correcting
an earlier static label of 114. Selector 252 points to `80076440`.
`observe_pcsx2_alarm_installer.py` reads code and table entries, with MODE taken
from the genuine guest LW result. It removes its owned probes and confirms its
owned process exits. This observes installation; alarm registration, timer
evolution, interrupt callbacks and SleepThread completion remain separate work.

The [registration implementation](battle-alarm-registration-C-validation.json)
now matches 512 original-instruction worlds and 768 connected calls in both C
builds. That comparison uses explicit timer inputs with HBLNK edges held fixed;
it does not deliver interrupts or callbacks. All 168 source instructions execute.
The [separate live probe](runtime-alarm-registration-observation.json) did not
reach the selected `DelayThread` syscall (`002DBC24`, RA `002A8558`) within its
30-second observation window. It captured no registration boundary. Debug
status remained alive and execution advanced; the final sampled PC was
`00081FC0`. The probe removed its breakpoint and confirmed its owned process
exited. This pending live check must not be confused with the earlier verified
installer observation or the original-instruction/C comparison.

## Controller automation

Ordinary automation key taps can fall entirely between guest controller polls.
`configure_pcsx2_runtime.py` adds separate keyboard bindings and PCSX2 toggle
macros. Repeated INI keys represent alternatives; ` & ` represents a chord and
must not combine a physical controller with a keyboard alternative.
Run that configuration script only while PCSX2 is closed. It was already applied
for this installation; ordinary launches need only the launcher.

`tooling/pcsx2_controls.mjs` supplies a bounded controller tap: toggle the macro
on, hold for 100 ms, toggle it off in a finally block, then capture fresh state.
Use a returned, uniquely selected Nocturne window; inspect the screenshot before
the next decision. Activate and reobserve if capture shows an occluding window.

```javascript
// In node_repl, after the Computer Use skill's sky initialization and window selection:
globalThis.padControls = await import('file:///C:/Projects/dds_recomp/nocturne/tooling/pcsx2_controls.mjs');
globalThis.state = await padControls.tap(sky, pcsxWindow, 'Cross');
globalThis.pcsxWindow = state.window;
```

| Button | Macro key |
| --- | --- |
| Cross / Circle / Start | F10 / F11 / F12 |
| Down / Up / Left / Right | F7 / F13 / F14 / F15 |
| Triangle / Square | F16 / F17 |
| L1 / R1 / L2 / R2 | F18 / F19 / F20 / F21 |
| Select | F22 |

Do not mix manual toggle presses with the paired helper: an already-held macro
would invert the intended edges. A newly launched emulator starts unheld.
After input interruption or a failed release, reobserve before resuming; a new
launch resets controller state. This implementation requires the Windows desktop
and uses Computer Use. It is not frame-exact input or an added PCSX2 MCP tool.

## Imported save

Source: [Ichiny's GameFAQs save, 2009-02-06](https://gamefaqs.gamespot.com/ps2/582958-shin-megami-tensei-nocturne/saves/18609),
listed as final save, complete compendium, Hard mode and ultimate boss unlocked.
The downloaded ZIP contains `BASLUS-209112D646473332D31.PSV`.

`import_psv_folder_card.py` validates the PSV table/payload bounds and North
American Nocturne directory, extracts the three original files, and refuses to
replace an existing card. Format layout was checked against
[bucanero/ps2save-extract](https://github.com/bucanero/ps2save-extract/blob/main/include/ps2mc.h).
It does not authenticate the PS3 PSV signature. Original bytes and hashes are
recorded in `nocturne-save-import.json`.

The first blank-card template had a zero-byte superblock and was unformatted;
PCSX2 ignored its files. Corrected using only the existing formatted card's
8192-byte format metadata, without copying its DDS saves. PCSX2 now indexes the
Nocturne directory normally. The importer now rejects an unformatted template.

Observed in the game: file 2, FuFu, level 94, Hard, cycle 2, time 198:46,
Tower of Kagutsuchi 3-D. The author's compendium/boss claims require separate
in-game checks before being treated as verified research fixtures.

The file was actually loaded and the 666F map and field scene were observed.
Square opens the party menu; Triangle opens the map. Bounded Start, Cross,
Down, Up, Triangle, Circle and Square inputs were verified. Other configured
buttons remain untested. The party menu shows FuFu HP 714 / MP 261 / level 94,
with Daisoujou, Metatron and Beelzebub in the active party.

A temporary probe hit the original `ps2LibmSinFloat` at `0x002CF5D0` in this
loaded scene. `f12` was `0xBFC8DBA9` (-1.569203495979309); `ra` was `0x002B6004`.
The caller's `JAL` at `0x002B5FFC` targets that entry. Its first 32 loaded bytes,
and the ELF entry's first 32 bytes, match the original ELF. This confirms a
live call/probe route; it does not establish the sine return or certify the
recovered function from this one observation. The probe was removed and the
breakpoint list returned to empty. `runtime-integration-check.json` contains the
small register/instruction report. No full RAM snapshot or savestate was made.

## Evidence loop for volatile findings

1. Establish the exact ELF/ISO region and current game identity; compare selected
   loaded instructions with the original ELF rather than relying only on a title.
2. Inspect existing breakpoints and watchpoints. Add only the probe needed for the
   hypothesis; do not clear unrelated debugging state.
3. Observe the screen, perform one bounded controller action, and inspect the
   resulting state. Use the built-in pause/debugger to collect the relevant
   arguments, registers, memory and caller at the original function.
4. Compare the native observation with recovered C, Unity and community leads.
   Distinguish live emulator evidence from static matches, synthetic P-code
   fixtures, downloaded-save modifications and physical hardware behavior.
5. Remove only probes added for this test. Release every input. Save concise
   findings and one current report, without savestate/project checkpoints.

Sources: [REA installation](https://github.com/morluto/rea/blob/main/docs/installation.md),
[REA native guide](https://rea.tools/guides/native/),
[PCSX2 CLI](https://pcsx2.net/docs/advanced/cli/),
[PCSX2-MCP](https://github.com/hkmodd/PCSX2-MCP).


<!-- natural-alarm-delivery-current -->
The [natural alarm observation](runtime-alarm-delivery-observation.json) and [independent review](runtime-alarm-delivery-independent-review.json) record one actual registration, IRQ, dynamic CD callback and negative8 return across11 boundaries. The owned hidden process exited with all owned probes removed. Kernel RAM reads use KSEG0; debug low-address zero results do not prove initialized kernel data. The idleID0/priority128/code match is observed; this earlier probe left `FFFFFD80` unread, resolved by the newer wired-alias observation below. This is one callback path, not SleepThread2A8508 completion, scheduler equivalence, IOP completion or unperturbed hardware timing.
<!-- /natural-alarm-delivery-current -->


<!-- native-idle-context-current -->
The [idle-context observation](runtime-idle-context-observation.json) reads the original bootstrap TLB table, actualTCB0, interrupt scratch and both640B aliases at one natural IRQ pause. The [review](runtime-idle-context-review.json) checks raw receipts and original BIOS bytes: `FFFFFD80` translates to physical `0007FD80`; the frames agree, the nonzero savedFCSR matches actual idleFCSR, and full128 savedSP matches the interruptedSP. Current handlerSP is separately observed at `FFFFFFFF80015C30`; it is not the interruptedSP. No guestTLBR, register/RAM writes, debugger MMIO, injected ticks or savestates. Owned probes were removed and the process exited. This establishes this installed BIOS/emulator mapping, not general TLB correctness or physical hardware timing.
<!-- /native-idle-context-current -->


<!-- RPC-semaphore-live-current -->
The [live RPC observation](runtime-RPC-semaphore-observation.json) and [review](runtime-RPC-semaphore-review.json) corroborate five actual boot boundaries: worker entry, CreateSema before/after, constructor return and the first empty-queue Sleep entry. The installed BIOS allocates semaphore 23 (allocated count 23 to 24); RPC thread 12 publishes it at `552140`. Its actual stack packet at `5937B0` passes attr `00593860`, retained from the saved initial FP; the BIOS copies that word into record `8001C2E0` before subsequent stack frames overwrite the packet. The observed queue `5937E0` has server `593800`, callback `2C2338` and buffer `593F40`, with no pending request. All original caller bytes and the loaded 132-byte kernel handler match the pinned ELF/BIOS. This probe stops before Sleep executes; actual park/parent restoration remains established by the separate 168-world instruction comparison. It supplies no IOP request or scheduler reply. 37 review checks pass; all five owned probes and the owned hidden process are removed, with configuration unchanged. Native command drain, nonempty RPC callbacks and actual IOP bank loading remain the next work. Canonical recovery remains 2,746/9,062 functions and 556 source units.
<!-- /RPC-semaphore-live-current -->


<!-- live-SIF-dispatch-current -->
The [current SIF dispatch observation](runtime-SIF-dispatch-observation.json) and [review](runtime-SIF-dispatch-review.json) follow five natural-boot boundaries from RPC-worker startup through actual DMAC dispatcher80001798, game receive2DE330, its real callback return and kernel80000574. The initialized target, full512B adapter code,272B IRQ body,104B kernel user bridge and SDK81FE0 prefix match original BIOS carriers; the complete296B game receive matches the ELF. A nonzero64B bind request for SID54524E53 is read through both2059B9C0 and its physical alias; only its low size byte clears during consumption. Scheduler globals remain unchanged for this request. No guest writes, device reply, savestate or debugger MMIO reads occur.42 checks pass, owned probes are removed and the owned hidden process exits. This does not establish a newly submitted RPC roundtrip or live blocked-client restoration.
<!-- /live-SIF-dispatch-current -->


<!-- live-loadfile-roundtrip-current -->
The [cold loadfile observation](runtime-loadfile-roundtrip-observation.json) and [review](runtime-loadfile-roundtrip-review.json) now prove eight natural-boot boundaries through new BindRpc and FF version CallRpc replies and initializer return. Initial flag52C358 is−1; the real bind fills client59EC00 server/buffer fields, the real version reply supplies2500 at59EA00, and original partial-word instructions copy it to client+28 before returning0 with flag0. The first filename is IRX/SIO2MAN.IRX, preceding the sound loader.33 checks bind complete loaded caller/client/response code and raw client/version/packet receipts. Actual recorded reads cover that original code, module filename, loadfile flag/client/version buffers and response packets; this supersedes the raw observer's inherited generic read-scope prose. No debugger MMIO, guest writes, supplied reply or savestate is used. Owned probes are removed and the owned hidden process exits. Module-load and heap-service returns remain separate work.
<!-- /live-loadfile-roundtrip-current -->


<!-- live-custom-module-current -->
The [SDFSDMAN observation](runtime-custom-module-observation.json) and [36-check review](runtime-custom-module-review.json) follow seven natural boundaries: custom loader entry, handle acquire entry/return, private MCallRpc entry, private end handler, RPC return and loader return. Original sound bootstrap calls `2A98A8` with RA `2C13C4`. Actual raw data is128-byte aligned; received reply supplies module ID36 and secondary0. The response restores the client mutex, clears request packet busy/serial and pointer, and returns with the original stack. The acquired handle is retained. No packet/register/memory writes, savestate or configuration change is used; owned probes are removed and the hidden process exits. This is genuine observed IOP completion, separate from the finite C/original continuation corpus, and does not establish complete sound initialization or a recovered C IOP service.
<!-- /live-custom-module-current -->


<!-- live-IOP-heap-current -->
The [heap observation](runtime-IOP-heap-observation.json) and [32-check review](runtime-IOP-heap-review.json) establish ten genuine boundaries through service80000003 Bind, actual response, initializer return to2C15C0, first sound allocation entry, CallRpc, actual allocation response and native return. Request59E8C0 contains4000; reply59E880 receives observed000E7C00, then native2E2B98 returns it to2C0EA8 with the original SP. Bound server and buffer pointers come from the received bind packet. All six complete loaded caller/client bodies match the original ELF. No guest writes, supplied packet/state, savestate, configuration edit or debugger MMIO occurs; owned probes are removed and hidden process exits. This observed address is never supplied as a fixed C allocation result. Finite continuation inputs and newly submitted EE requests remain separate proofs; C IOP allocation and full sound root remain incomplete.
<!-- /live-IOP-heap-current -->


<!-- live-whole-sound-root-current -->
The [whole sound observation](runtime-sound-setup-observation.json) and [28-check review](runtime-sound-setup-review.json) establish15 actual boundaries from original2C1578 through allocator diagnostics, channels, bank table, status-mirror allocation/DMA/command and native root return. All1440 table bytes are reconstructed from observed call inputs and actual allocation-result registers, with channel overlap and retained padding preserved. The tested invocation has four banks/19520 aligned bytes. Status-mirror descriptor/source/destination/size, actual command parameters, mode reset and original caller/SP/callee-save values agree. Six complete loaded original sound bodies are checked against the ELF. No guest/register writes, supplied reply, savestate, configuration change or debugger MMIO is used. Owned probes are individually removed, execution resumed and owned hidden process exited. This proves actual original initialization on the installed emulator/BIOS only. It does not establish the pending C formatter/console/mirror path, bank asset residency, audible output, all inputs or physical timing.
<!-- /live-whole-sound-root-current -->


<!-- live-console-registration-current -->
The [console observation](runtime-console-observation.json) and [25-check review](runtime-console-review.json) follow seven actual boundaries from original console init through Open packet, kernel command124, special BIOS entry8001123C, actual return and initializer return. The normal124 table slot points80001564 but is bypassed. The128-byte loaded special-handler prefix matches the installed BIOS. Real registration returns observed port5, and original init stores it, constructs TX/RX/ring pointers and returns1 with the original SP. Caller initialized flag remains0 until its later publication. All four complete loaded game bodies match the ELF. No guest/register writes, supplied replies, savestates or configuration edits occur; probes are removed, execution resumed and owned hidden process exited. This is one actual registration, separate from the96-world C/original comparison stopping at special entry. Full BIOS124 closure, send completion and whole C sound-root return remain pending.
<!-- /live-console-registration-current -->


<!-- live-deci2-save-current -->
The [BIOS124 save observation](runtime-deci2-save-observation.json) and [87-check review](runtime-deci2-save-review.json) record13 real boundaries through full register save, rd24/25 reads, native port Open, restore and original console return. The loaded wrapper/context/port bodies match the installed BIOS. All32 saved GPR128 values and31 restored nonresult values agree; V0 low64 receives actual5. rd24 demonstrably preserves a nonzero full128 destination; rd25 produces observed control0 while preserving upper64. Before/after port tables independently select first-free5 and retain all other records/padding. Saved580-byte frame changes only the returned V0 low64 slot. The first attempt missed a kernel return because a32-bit SP constant was compared with a sign-extended64-bit kernel SP; that owned process/probes were removed before the corrected current run. No guest writes, supplied service state, savestates or INI edits occur. Current owned probes/process are removed and execution resumed. This is one installed-build observation, not enabled performance timing, hardware debug semantics, full C console send or executable completion.
<!-- /live-deci2-save-current -->


<!-- live-deci2-send-current -->
The [DECI2 send observation](runtime-deci2-send-observation.json) and [24-check review](runtime-deci2-send-review.json) follow five actual boundaries: console initializer entry, first later console BIOS send, its native return, writer continuation and writer caller return. Loaded240-byte send body matches the installed BIOS. Observed port5/destination48 and both routes0 produce actual−10, propagated through original wrappers; ConsoleWrite returns−1 with SP restored and busy0. All request/list bytes and the unused notification pool descriptor remain unchanged. The complete native TX header/pending length agree. The first attempt expected immediate draining, but the sampled call was ordinary console output with an unavailable route and skipped that branch; its owned probes/process were removed before the corrected current capture. No guest writes, supplied reply, savestate, debugger MMIO or INI edit occurs. Actual host DECI2 text logging is outside this capture, and active-route completion/full C sound-root execution remain pending.
<!-- /live-deci2-send-current -->


<!-- iop-memory-service-current -->
The original IOP memory service is now identified and its **762-word SYSMEM module** recovered in [C](../src/iop_sysmem_native.c). The [original/C comparison](iop-sysmem-C-validation.json) matches **1,776 stateful original calls and3,552 strict C calls** across24 worlds, exercising745 words. Checks compare all32 GPR,HI/LO,nextPC,instruction counts and complete256KiB RAM digests after every API or real callback transfer. The C owner carries explicit R3000 delayed loads; the original stream has no immediate load-use hazards or loads in branch delay slots. The [581-check review](iop-sysmem-results-review.json) also corroborates all762 relocated loaded words and one real sound allocation: module830, FILEIO4B730, request4000, actual resultE7C00. Both C compiler profiles reproduce all32 actual GPR,HI/LO,four complete control tables/1024 bytes and256B caller stack with explicit module-global adaptation and one saved internal JAL-link relocation. Query execution on that metadata is offline. The [service study](iop-memory-service-study.json) decodes the fifteen pending EE calls as **12 allocation requests and3 QueryMaxFreeMemSize requests**. Retail FILEIO dispatches opcodes1..9; modern community FILEIO covers1..3. Original SYSMEM1.1 lacks modern internal interrupt wrappers, so retail FILEIO owns intrman17/18 exclusion. FILEIO/SIFCMD server execution, IOP scheduling/transport and full C sound-root completion remain pending. Canonical recovery stays **2,746/9,062 functions across556 source units**; these platform modules add no EE identity credit.
<!-- /iop-memory-service-current -->


<!-- iop-heap-service-current -->
The [received heap-service comparison](iop-heap-service-C-validation.json) joins **1,111 loaded words**, adding331 original FILEIO/INTRMANI words and18 observed loader-bound import words to the allocator. **1,398 original calls match2,796 strict C calls** across18 stateful worlds, including the exact payloads of all15 pending EE requests. All32 GPR,HI/LO,nextPC,instruction counts,complete2MiB RAM digests and ICTRL read/write state agree. 835 total words and276/349 newly joined words are exercised. Original file loading, unknown-opcode stdio and service-thread startup reach three real unowned import boundaries; no result is supplied. The standard Ghidra decoder exposes writes to register zero in IRX import delay slots; the original executor now source-checks and discards exactly those writes as required by R3000 before the next instruction, rather than normalizing outputs. The [6,207-check review](iop-heap-service-results-review.json) also reproduces **six actual IOP boundaries** in both C profiles: heap dispatch, interrupt suspend, guest ICTRL load, allocator, interrupt resume and handler return. Every boundary matches all32 GPR andHI/LO; the complete observed four heap tables/1024 bytes,512B caller stack,request/reply and module globals match with the actual relocated instruction profile, without stack-link or address adaptation. INTRMANI is the observed interrupt variant: its genuine guest LW supplies the saved ICTRL value; no debugger MMIO read is used. The bus model carries read-to-clear/write values and has no interrupt timing or pending-IRQ delivery owner. The [SIFCMD study](iop-sifcmd-server-study.json) matches96 actual caller bytes at base1C330 and identifies `ExecRequest1730`, returning from FILEIO at1DA9C, plus its packet pool,SendCmd/DMA and server queue/sleep dependencies. **No full EE RPC roundtrip is newly completed**: received-handler tests and live reply construction do not replace transport or scheduling. The15 EE waits and two DECI2 callback/two Poll dependencies remain open. Canonical recovery stays2,746/9,062 functions across556 source units.
<!-- /iop-heap-service-current -->


<!-- iop-rpc-reply-current -->
The [SIFCMD comparison](iop-rpc-reply-C-validation.json) adds **467 original words across11 complete reply,packet,send and queue bodies**, plus8 observed import words, joining1,586 loaded words. **147 original calls/prefixes match294 strict C executions across82 worlds**. Sixty received heap-reply prefixes cover all15 pending payloads through both reply/direct-DMA modes and indexed/rotating packet pools. The corpus exercises222/475 new loaded words; queue lifecycle,unowned BREAK/exception paths and other unvisited cases remain open. The [8,779-check review](iop-rpc-reply-results-review.json) independently derives70 DMA descriptor sets,client/CID fields,packed command lengths,packet-pool selection/counters and allocator/query answers. Both C builds reproduce **six actual IOP boundaries through the real SIFMAN entry**, matching all32 GPR andHI/LO,the768B caller stack,4KiB packet pools,heap metadata,request/reply and outgoing descriptors. The [ten-boundary live trace](runtime-iop-rpc-reply-observation.json) also observes a real DMA ID,ExecRequest return and the correct first EE return. The EE breakpoint is armed before request execution and the observer handles either CPU pausing; the first allocation is correlated by its real caller/SP. An initial probe armed that breakpoint too late and captured the following allocation; the cross-check detected it and the rolling observation was replaced after owned cleanup. No later DMA ID or EE result is supplied to C. The [DMA study](iop-sifman-DMA-study.json) identifies **216 original SIFMAN words** for tag construction,batch submission and wrappers. Original export7 is SetDma at860; export8 is DmaStat, and export32 is the callback-preserving SetDmaIntr wrapper at884. SIFMAN CPU/ring/MMIO request recovery is completed in the current section below;autonomous transfer/completion,IOP scheduling and the15 EE completions remain pending. Canonical recovery stays2,746/9,062 functions across556 source units.
<!-- /iop-rpc-reply-current -->


<!-- iop-sifman-current -->
The [SIFMAN comparison](iop-sifman-C-validation.json) recovers **all216 original tag-builder,batch and SetDma/SetDmaIntr words**:648 original calls match1,296 strict C executions across360 initialized worlds;every selected instruction is exercised. The [22,746-check review](iop-sifman-results-review.json) independently checks full1,600B ring/callback state,DMA tag rounding/flags/address masks,capacity rejection,generation wrap,double buffers,native callback queuing and exact MMIO accesses. Per compiler it checks7,776 tags,240 queued callbacks,168 rejects,384 busy batches including native warm initialization,and96 pending starts. The combined1,802-word C path reproduces **ten actual IOP boundaries from received RPC through SetDma return**, plus five isolated SIFMAN boundaries,matching all32 GPR/HI/LO,the768B stack and1,600B SIFMAN state. The DMA ID is computed from the real generation/queued/count;no observed ID or EE reply is supplied to C. The [13-boundary observation](runtime-sifman-DMA-observation.json) confirms DMA9 is **SIF0,IOP-to-EE**,correcting the earlier SIF1 label. Guest loads corroborate CHCR and the pre-write MSFLAG observable value;the debugger byte view of EE F240 is not authoritative raw state. The isolated SIFMAN CPU test leaves the start request pending. The current SIF0 transport section below reproduces the subsequent FIFO transfer and IOP completion register effects;guest IRQ/scheduler integration remains open. Canonical recovery remains2,746/9,062 functions across556 source units.
<!-- /iop-sifman-current -->


<!-- sif0-transport-current -->
The [SIF0 device comparison](sif0-transport-C-validation.json) matches **976 operations per compiler across256 worlds**,using the actual pinned PCSX2 `Sif0.cpp` and `Sif.h` as the reference. Tests compare the entire128-word FIFO,junk state,registers,ordered completion requests and full RAM digests,including delayed EE startup,buffer wrap,early IOP stop,TIE-disabled waits and completion order. The [connected review](sif0-transport-results-review.json) passes22,837 checks. The original1,802-word native received-RPC path now **computes all80 EE output bytes**,including12 junk-padding bytes,and matches11 actual IOP boundaries,all32 GPR/HI/LO,the768B stack,1,600B ring state and the final IOP DMA register values. No observed DMA ID or EE reply bytes are supplied. The copy schedules completion separately;the due IOP event clears CHCR and publishes an IRQ request. Original ICTRL still excludes guest interrupt dispatch at the chosen API boundary,and EE completion remains pending. Ready EE CHAIN/TIE/QWC0 and an empty FIFO are declared inputs because bytewise EE DMA debugger reads return unsupported zeros. Instruction clock profiles1/2/4 are finite integration tests,not observed hardware timing. A further [17-boundary live trace](runtime-sifman-IRQ-observation.json) catches the original **94-word SIFMAN interrupt handler**,its genuine CHCR load and natural return1. It has zero global/queued callbacks and zero queued DMA in this observation. The [next-owner study](sif0-completion-study.json) identifies callback/restart paths without supplying their results. The current SIFMAN IRQ section below recovers that handler. Native controller/exception dispatch and joining computed EE completion to the EE IRQ/RPC/scheduler path remain necessary for full C RPC and sound-root completion. Canonical recovery remains2,746/9,062 functions across556 source units.
<!-- /sif0-transport-current -->


<!-- iop-sifman-IRQ-current -->
The [SIFMAN IRQ comparison](iop-sifman-IRQ-C-validation.json) recovers **all94 original ISR words plus the original exported2-word return callback**. Across432 source-initialized worlds,4,980 original initialization/ISR calls match9,960 strict C executions;all96 new words are exercised. Per compiler,696 ISR calls include528 native returns and168 genuine unknown-callback transfers. Callback/tag arrays are built by original DMA APIs. Returning callback tests use the actual exported JR RA/NOP;no callback result is injected. The [31,767-check independent review](iop-sifman-IRQ-results-review.json) derives complete1,600B callback/ring state,2,760 returning callbacks,168 queued restarts,120 busy returns and240 empty-queue returns per compiler,including generation wrap and ordered MMIO. Both C builds reproduce **three actual IRQ boundaries through native return1**,matching all32 GPR/HI/LO,the1,600B state,256B interrupt stack and DMA9 registers through the shared bus. The observed ISR entry bank remains an input;native CPU exception/controller entry and restoration are separate work. Ghidra names/comments were saved in the existing project. A new [20-boundary trace](runtime-iop-DMA-dispatch-observation.json) and [dispatcher study](iop-DMA-dispatch-study.json) identify **261 original INTRMANI dispatcher/guard words**,genuine DICR1/DICR2 loads,slot5D0 targeting this ISR,flag26 acknowledgment and the natural dispatcher return. The current DMA dispatcher section below recovers that dispatcher. General exception/scheduler and pending EE IRQ/RPC integration remain necessary for full C RPC and sound-root completion. Canonical recovery remains2,746/9,062 functions across556 source units.
<!-- /iop-sifman-IRQ-current -->


<!-- iop-DMA-dispatch-current -->
The [INTRMANI comparison](iop-DMA-dispatch-C-validation.json) recovers **261 original DMA dispatcher/guard words plus a real2-word return-zero callback**. Across961 worlds,961 original cases match1,922 strict C executions;all263 selected words execute. Per compiler there are820 native returns,140 true unknown-callback transfers andone bounded busy-poll prefix. Original handlers execute to produce callback results. The busy prefix holds the real master-enable bit set;it is not given a fabricated ready value. The [17,831-check review](iop-DMA-dispatch-results-review.json) also compares522 controller operations against actual compiled pinned PCSX2 DICR write/publication bodies. C now **computes DICR2 and ISTAT interrupt publication from the real pre-start state**,then executes native INTRMANI/SIFMAN dispatch through six actual CPU boundaries and return1. Both builds match all32 GPR/HI/LO,the256B dispatcher stack,112B callback table and1,600B SIFMAN state. The80 computed EE transfer bytes remain intact. The [21-boundary trace](runtime-iop-DMA-publication-observation.json) retains the raw debugger-immediate load observation. Full-bank comparison uses the next genuine point,after the R3000 pending load commits;no register normalization or injection is used. The initial process-exit check raced asynchronous shutdown;an exact-PID follow-through verified absence without rerunning the probe or creating another process. The original cleanup result is retained. A [24-boundary context trace](runtime-iop-IRQ-context-observation.json) and [next-owner study](iop-IRQ-context-study.json) now bind **301 general IRQ instructions plus10 stack-check instructions**,the actual152B saved frame,and natural JR/RFE resumption. One padding word is excluded from the instruction count. The context section below now recovers save/restore and same-thread syscall return. Hardware exception entry,switched-thread scheduling and pending EE IRQ/RPC integration remain open. Canonical recovery remains2,746/9,062 functions across556 source units.
<!-- /iop-DMA-dispatch-current -->


<!-- iop-context-current -->
The [interrupt-context comparison](iop-IRQ-context-C-validation.json) recovers **331 original words**:301 general IRQ instructions,10 stack checks,13 THREADMAN preemption instructions and7 priority-return instructions. Across896 original cases, both C builds match all CPU/RAM and declared device effects. Each build executes616 real RFE returns, including256 priority returns;280 cases retain real unowned transfers. The [21,368-check independent review](iop-IRQ-context-results-review.json) also compares552 CP0 operations with compiled pinned PCSX2 source. Both builds reproduce11 full actual GPR/HI/LO banks through IRQ save, DMA/SIFMAN dispatch, the native predicate and RFE return. One pre-JR point is explicitly qualified for a pending SP load. The debugger exposes no IOP CP0 bank, so computed Status is not described as live observed. The [syscall/context comparison](iop-thread-context-C-validation.json) adds **227 original words**:the184-instruction context callback,29-instruction syscall frame builder,9-instruction add64 helper and5-instruction list predicate.576 original cases match1,152 C executions. Per compiler, native code builds512 complete152-byte syscall frames;32 same-thread cases execute the original F0FF restore/RFE path,64 add64 cases check carry/wrap,and16 cases emit the original byte-wide debug-port request. No return frame or callback result is supplied. The [11,215-check review](iop-thread-context-results-review.json) independently checks every frame field and untouched slot, saved_regs ownership, return ABI, counters and genuine dependency transfers. Together the suites exercise all331 earlier context words;169/227 new words execute,with58 remaining behind timer/diagnostic dependencies. The ready-queue section below now recovers the timer reader and ready selection,with deletion still stopping at real imports. Full switched-frame restoration,hardware exception entry and EE IRQ/RPC/sound-root completion remain open. Canonical recovery remains2,746/9,062 functions across556 source units.
<!-- /iop-context-current -->


<!-- iop-ready-queue-current -->
The [ready-queue comparison](iop-ready-queue-C-validation.json) adds **299 original instructions**:294 THREADMAN queue/scheduler/deletion instructions and the5-instruction bound TIMEMANI reader.817 worlds contain3,073 original calls and bounded prefixes,all matching6,146 C executions across two compiler profiles.260 new instructions execute;39 remain behind genuine diagnostic/deletion imports. The [independent review](iop-ready-queue-results-review.json) passes763,570 checks,covering all128 priorities,1/2/3-node linked queues,bitmap clearing,priority selection,timer wrap,64-bit run clocks and counter wrap. Each compiler executes105 switched callback prefixes and39 retained callbacks. The selected TCB saved_regs pointer is a declared input;tests stop at the actual callback return before dereferencing that selected frame. This establishes callback behavior,not a complete thread switch. The [natural runtime capture](runtime-iop-thread-switch-observation.json) observes ready selection retaining current priority40 ahead of the strongest ready priority41. Both C builds reproduce175 native instructions,all32 GPR/HI/LO,1,236B globals,96B TCB,152B frame and128 observed stack bytes. These are bounded reads;the full nested stack is not claimed. The first observer ended after assuming a timer call where selection retained current;its branch handling was corrected before the successful rolling capture. The actual callback slot binds TIMEMANI+6AC at loaded84DC;128 loaded bytes match the relocated original module. Its5 instructions read **BF8014A0**. This callback did not invoke the timer,so no live counter return is claimed. Unit cases supply an explicit peripheral BEFORE value to the original LW;autonomous clock/IRQ timing remains open. The original trailing-zero helper loops on zero,where modern ps2sdk returns32. A33-instruction zero case preserves the original loop;readyq_highest tests for nonzero before calling it. The [next-owner study](iop-ready-queue-study.json) identifies55 original frame-initializer instructions and40 start-helper instructions,linked from thbase export6 StartThread. The native thread-start section below now recovers that constructor/start/vector/RFE chain. Sleep/wakeup lifecycle and repeated RPC delivery are next. Canonical recovery remains2,746/9,062 functions across556 source units;the full executable remains incomplete.
<!-- /iop-ready-queue-current -->


<!-- iop-thread-start-current -->
The [native thread-start comparison](iop-thread-start-C-validation.json) selects **180 original instructions**,adding164 unique loaded words and reusing16 existing INTRMANI instructions. All180 execute.232 original/CPU-primitive cases match464 strict C runs. Each build executes72 preempting starts into a child frame built by the original constructor,144 nonpreempting starts and8 complete same-thread syscall returns. The recovered path now runs **constructor → start → syscall → installed exception vector → syscall dispatch → outgoing frame save → context callback/timer → original RFE → child entry**. It supplies neither a selected frame nor a syscall result. The [7,384-check independent review](iop-thread-start-results-review.json) checks complete frame ownership,ready-list order,register restoration,exception scratch and timer accounting. Actual pinned PCSX2 psxSYSCALL/psxException bodies match480 C primitive cases,including delay-slot EPC/BD and BEV selection. Ghidra original execution uses this separately checked CPU primitive and a source-checked hardwired-zero correction for loader ordinal words. The [nine-observation live capture](runtime-iop-thread-start-observation.json) catches a genuinely preempting start. Both builds reproduce347 native instructions across8 complete IOP GPR/HI/LO banks,1,236B globals,two96B TCBs,512B stack,32B exception scratch and both152B frame outputs. Root CP0 Status401 is inferred from the known exception-stack profile;the debugger exposes no live IOP CP0 bank. The actual guest timer LW supplies the peripheral sample;there is no timer-function return hook or autonomous timing claim. One4B dormant predecessor write lies outside captured live memory. The original EXCEPMAN template matches the installed vector after its native LW offset fixup8F5A0000→8F5A0440;the vector executes at80000080 and accesses physical table440. Its unpatched module-relative Ghidra pseudocode has indirect-flow warnings;execution proof uses the actual installed original bytes. The [next-owner study](iop-thread-start-study.json) binds thbase exports24/25/26 SleepThread,WakeupThread andiWakeupThread to183 original instructions and lists their native dependencies. The sleep/wakeup section below now recovers those lifecycle paths and joins the native empty RPC server loop. Incoming packet delivery and native EE IRQ/RPC completion remain open. Canonical recovery remains2,746/9,062 functions across556 source units;the full executable remains incomplete.
<!-- /iop-thread-start-current -->


<!-- iop-sleep-wake-current -->
The [sleep/wakeup comparison](iop-sleep-wake-C-validation.json) adds **216 original instructions**:183 lifecycle instructions,31 stack-check instructions and2 observed SIFCMD import words.288 worlds contain368 original calls and prefixes,matching736 C executions across two builds.206 instructions execute;10 stack-diagnostic instructions remain behind a genuine unowned import. Each build completes12 stateful native cycles:construct B/C frames,park A/B,preempt C to wake A,then restore B from its saved SleepThread call. CPU,RAM,CP0,queues and counters persist across calls.24 sleeping callers resume at their own saved return addresses. The [30,440-check review](iop-sleep-wake-results-review.json) independently checks list order,wait/ready transitions,u16 counter wrap,handle/state errors and signed168-byte stack threshold. The recovered lifecycle now joins the existing native **SIFCMD SetRpcQueue/GetNextRequest/RpcLoop** code. Two cases initialize an empty RPC queue with original code,park its server through the observed SleepThread import,and wake it back to the real next-request entry. No ready frame or wakeup result is supplied. These remain empty-queue prefixes rather than complete EE roundtrips. The [live capture](runtime-iop-sleep-observation.json) binds the actual caller to SIFCMD RpcLoop and records a genuine zero-count sleep. Both builds match515 native instructions,six complete GPR/HI/LO banks andone pre-JR bank qualified for pendingSP. They also match1,236B globals,two112B TCBs,1,024B stack,32B scratch and the native outgoing152B frame;the selected existing frame is observed BEFORE. One4B sleep-tail write is outside the capture. Final memory is recorded **before JR/RFE**. An idle-loop breakpoint allowed later context switches before observation,and the installed step command uses a temporaryPC+4 breakpoint that does not reliably step this branch/delay slot. The2-instruction original JR/RFE continuation is computed and covered by original-instruction tests;it is not described as a live post-RFE observation. CP0 remains source-inferred rather than directly displayed. The [next-owner study](iop-sleep-wake-study.json) identifies54 original SIFCMD incoming-call queue instructions and their iWakeupThread import. Joining that received-packet wakeup to this native server loop is next. Canonical recovery remains2,746/9,062 functions across556 source units;the full executable remains incomplete.
<!-- /iop-sleep-wake-current -->


<!-- iop-rpc-receive-current -->
The [incoming RPC callback](iop-rpc-receive-C-validation.json) adds **56 original instructions**:54 packet-to-server queue instructions and2 observed iWakeupThread import words. All56 execute.256 worlds contain284 original calls,matching568 strict C calls across debug and optimized builds. Four coherent sequences per build initialize a queue and two server descriptors with native SetRpcQueue/RegisterRpc,enqueue two explicit received packets,then consume both FIFO entries and the empty queue through native GetNextRequest. The [independent review](iop-rpc-receive-results-review.json) performs5,009 checks of eight exact copied fields,empty/nonempty queues,preserved descriptor.next,negative thread/activity wake gates,context/handle/state errors,ready queues andu16 wake-count wrap. No wakeup result,ready frame,scheduler return or hardware delivery is supplied. The [actual capture](runtime-iop-rpc-receive-observation.json) records the callback on its real interrupt stack,wakes the existing waiting server,and returns to the SIFCMD dispatcher. Both builds exactly match four full GPR/HI/LO banks and64B packet,72B descriptor,24B queue,1,236B THREADMAN globals,112B TCB,512B stack andthree8B list neighbors across153 instructions. No pending-load qualification or CP0/timer/ICTRL input is needed for this callback. All owned probes were removed and the owned emulator exited. The [next-owner study](iop-rpc-receive-study.json) identifies the76-word SIF1 command dispatcher atSIFCMD+6AC..7DC and the actual callback return at+7C8. It clears the packet-size byte before copying to its stack,explaining the observed zero byte. RPC number is packet+20 and send_size is packet+24:the captured operation is1 with4 request bytes. An earlier report mislabeled the operation as send_size;the recovered instructions already used the right offsets. Preserve differences from modern ps2sdk,including the original optional callback check and lack of a pre-copy command-id clear. Next recover its real rearm import/handler tables/raw packet and enclosing IRQ return. Hardware arrival,service execution,EE RPC completion and full executable recovery remain incomplete. Canonical recovery remains2,746/9,062 functions across556 source units;isolated SDK owners add no canonical identity credit.
<!-- /iop-rpc-receive-current -->


<!-- iop-sif1-dispatch-current -->
The [SIF1 dispatcher/rearm comparison](iop-sif1-dispatch-C-validation.json) adds **99 original instructions**:76 SIFCMD command-dispatch instructions,21 SIFMAN DMA10 rearm instructions and2 observed loader-binding words.322 worlds contain342 original calls,matching684 strict C calls across debug and optimized builds.98 instructions execute;the remaining sign-correction word is unreachable after an unsigned-byte size plus3. The [8,888-check review](iop-sif1-dispatch-results-review.json) independently checks complete2MiB RAM for generic packet-copy cases,signed user/system table bounds,optional original callbacks and genuine unowned transfers. Original short packets retain a stale temporary command id;113..116-byte inputs overwrite savedS0 and117+ overwrite savedRA. These malformed lengths are explicit unit domains,not asserted game traffic.28 cases per build join the recovered RPC queue/wake path;four native queue/register/dispatch/re-dispatch/consume cycles show that clearing size prevents duplicate delivery while both IRQ calls still rearm. The [actual capture](runtime-iop-sif1-dispatch-observation.json) follows a genuine64-byte RPC packet from dispatcher entry through its actual SIFMAN ordinal6 binding,rearm,queue/wakeup callback,and return to INTRMANI DMA dispatch at4A1C. Both builds match seven full GPR/HI/LO banks,44B context,128B raw packet and128B copied stack span,72B server,24B queue,1,236B globals,112B TCB,768B stack andthree8B list neighbors across340 instructions. SBUS input comes from the real guestLW. DMA10 receives orderedCHCR0,BCR.SH20,CHCR41000300 CPU writes and a pending start;autonomous transfer/completion is not supplied. All owned probes were removed and the emulator exited. The [next-join study](iop-sif1-dispatch-study.json) identifies the already-recovered INTRMANI DMA/general IRQ continuation. The worker is READY while current TCB remains unchanged at ISR return. Next capture its existing152B frame plus the current TCB/priority BEFORE following the real scheduler decision and RPC service/reply. Immediate preemption,full EE roundtrips and whole-program completion remain unproved. Canonical recovery stays2,746/9,062 functions across556 source units;isolated SDK owners add no canonical identity credit.
<!-- /iop-sif1-dispatch-current -->


<!-- iop-rpc-handoff-current -->
The [IRQ/current-thread composition](iop-rpc-handoff-C-validation.json) now matches **781 original instructions** from real SIF1 dispatch through DMA/general IRQ,preemption predicate,queue scheduler,frame restore,JR/RFE,and13 original caller instructions to the actual BindRpc continuation. Both strict C builds match original P-code and the complete declared2MiB RAM/device world. Actual proof covers captured spans and **15 full GPR/HI/LO banks**,plus one pendingA2 and one pendingSP qualification;raw registers are never normalized. The post-RFE ordinary caller endpoint is observed and matched. The scheduler correctly retains priority40 current while the received-request worker atpriority96 remains READY. Existing worker/current frames are observed BEFORE. The callback performs no timer read because current does not change. Timer and callback-return breakpoints are armed together,so a later unrelated switch cannot be mislabeled as this IRQ result. The [live trace](runtime-iop-rpc-handoff-observation.json) then observes the current SIFCMD BindRpc call reaching genuine thevent ordinal10 WaitEventFlag atTHREADMAN+33C0 withbits1,mode0,NULL result pointer. That wait is observed at entry;its block-or-return decision is not supplied. The [next-owner study](iop-rpc-handoff-study.json) identifies201 original words:BindRpc92,event-bit pool53,and packet pool56. Recover these and the event wait/clear transitions before following real scheduling to RPC service/reply. The [shared RPC layout review](iop-rpc-layout-review.json) adds portable32-bit guest-address C types in `src/iop_rpc_layout.h`.44 offset/size assertions independently parsed from the pinned SDK header compile successfully and match original copy/service-consumer instructions. **Correction:** packet+20 is RPC operation1;packet+24 is send_size4. The full observed payload is00400000,requesting0x4000 heap bytes. Earlier reports mislabeled operation1 as a byte count;the recovered instruction code and original/C outcomes were already correct and have been revalidated. This composition adds no new instruction or canonical identity credit. Available original IOP source remains3,553 unique loaded words;canonical executable recovery remains2,746/9,062 functions across556 source units. Worker execution,full EE RPC roundtrips,sound root and the full executable remain incomplete.
<!-- /iop-rpc-handoff-current -->


<!-- iop-bind-current -->
The [BindRpc/event comparison](iop-bind-C-validation.json) adds **363 original instructions**:201 BindRpc/packet/event-bit pool words,158 native Wait/ClearEventFlag words and4 observed loader-binding words. All363 execute.220 worlds contain317 original calls,matching634 strict C calls across debug and optimized builds. The original SIFMAN216 dependency is explicitly included in this original-instruction comparison;it adds no duplicate recovery credit. The [2,969-check review](iop-bind-results-review.json) independently checks first-free event/packet ownership,pid wrap,allocation and send failures,async pending packets,context/handle/multiplicity/mode errors,AND/OR/clear behavior and exact list/TCB state.25 cases per build construct a real B frame with original code and reach it through native WaitEventFlag/BindRpc,thread_leave,SYS,scheduler andRFE. They stop at B entry;no wait result or resumed frame is supplied. Native busy batches produce queued tags;no DMA completion or remote binder response is invented. The [actual bind capture](runtime-iop-bind-observation.json) enters the priority40 caller after its EE reply is already present. Both builds match247 original instructions,eight complete GPR/HI/LO banks,40B client,56B table,2,048B packet pool,512B stack,64B event neighborhood,1,236B globals and112B TCB. Wait findsbit1 ready,Clear consumes it,bit release frees slot0,and the caller receives0 without a context switch or timer read. This is actual BEFORE reply state,not a supplied function return or new whole EE roundtrip. Original WaitEventFlag stores **mode** inTCB+2C;the pinned modern reference stores **bits** there. Original stored handle ids are also masked to6 bits. These differences are preserved. Current Ghidra inventory now contains29 THREADMAN functions;exact prior inventory hashes were reconstructed to verify the two additions and seven SIFCMD name changes. Only inventory/dependent metadata receipts were refreshed;old behavioral test results were unchanged and were not rerun by that refresh. The [next-owner study](iop-bind-study.json) uniquely matches64 relocated caller bytes to original **SDFSDMAN.IRX atCCB30**,connecting actual RPC server54524E53 to the existing EE sound/file-service study. A [separate live trace](runtime-iop-sound-wait-observation.json) observes the caller's next WaitSema through actual thsemap ordinal8 atTHREADMAN+3C34. It blocks with wait_type3 and enters the native syscall/scheduler path. An existing priority41 thread/frame is observed BEFORE selection;the ready96 heap RPC worker still does not run. The semaphore section below now recovers the four native APIs and observed import;the full sound worker remains next. Available original IOP source is3,916 unique loaded words. Canonical executable recovery remains2,746/9,062 functions across556 source units. The semaphore section below supersedes the earlier WaitSema C frontier;worker service/reply,full EE roundtrips,sound-root completion and the full executable remain incomplete.
<!-- /iop-bind-current -->


<!-- iop-sema-current -->
The [semaphore comparison](iop-sema-C-validation.json) recovers **244 original SignalSema/iSignalSema/WaitSema/PollSema words plus2 observed SDFSDMAN loader-binding words**. All246 execute.321 worlds contain435 original calls,matching870 strict C executions. Each build executes12 stateful wait/signal sequences and90 native syscall/RFE returns. Original constructors build runnable frames;WaitSema builds outgoing frames;SignalSema resumes the saved callers. No wait result or resumed frame is supplied. The [4,542-check review](iop-sema-results-review.json) independently checks signed count/max comparisons,errors and six-bit handle ids,30 FIFO/stable signed-priority insertions,and4 IRQ wakes that publish ready bits and write savedV0 without switching. The original wait_event points to the semaphore object base,whereas modern PS2SDK points to an inner event. The existing actual sound wait matches107 C instructions,one complete stable GPR/HI/LO bank,112B TCB,1,236B THREADMAN globals and64B semaphore neighborhood through the pre-SYSCALL boundary. **I_CTRL=1 is declared for this replay;it was not independently measured immediately before this particular WaitSema.** This is a qualified prefix replay,not a newly observed full scheduler return. The [next-owner study](iop-sema-study.json) corrects the SDFSDMAN function extent to **314 original words at3FD4..44BC**,including the shutdown branch into its six-word return epilogue at44A4. Its193 command-table entries select30 distinct targets. The50-word command0 queue producer copies16..256 bytes into128-byte slots;lengths above128 overlap the next slot. Its overflow handling preserves count while advancing the read index. These are original-instruction findings requiring full source/runtime validation,not clamped replacement behavior. Recover the complete sound worker,queue producer and actual import bindings next;then connect resumed command processing and the ready96 heap worker to original EE reply/sound-root completion. The SDF worker section below now compiles the314-word body;whole-worker behavior remains incomplete. Available original IOP source is4,162 unique loaded words. Canonical recovery remains2,746/9,062 functions across556 source units;the full executable remains incomplete.
<!-- /iop-sema-current -->


<!-- iop-sdf-worker-current -->
The [SDF worker comparison](iop-sdf-worker-C-validation.json) compiles **590 selected original words**:the complete314-word worker body,50-word command producer,129-word command0 initializer,57 SYSCLIB memcpy/word-copy instructions and40 observed import-binding words.588 words are newly unique.818 original cases match1,636 strict C executions. **354 selected words execute;236 remain unvisited behind initialization and genuine handler/driver dependencies.** The worker body being compiled does not establish complete worker behavior. The [7,548-check review](iop-sdf-worker-results-review.json) independently checks273 copy cases,242 queue cases,16 IRQ waiter wakes,284 worker prefixes covering all256 opcode values,and separate initializer/shutdown/ACK boundaries per build. Original aligned copying loads four words before writing each16-byte group;unaligned copying is forward bytewise. Queue tests retain16..256-byte copies into128-byte slots. At slot255,raw oversized inputs overwrite queue metadata before counter operations;those operations read the copied bytes. This is tested raw-input behavior,not observed corruption in normal gameplay. Packet pointers are word-aligned as actual SIF delivery;Ghidra P-code does not model unaligned LW AddressError. The [actual capture](runtime-sdf-dispatch-observation.json) records38 boundaries and all67 SDFSDMAN import bindings. A real48-byte command copy is followed by native iSignalSema ready publication and natural worker resumption into command0. Both C builds reproduce196 producer instructions,five complete GPR/HI/LO banks and2,188B bounded output state. A separate replay from the actual resumed caller reproduces25 worker instructions and the complete dispatch bank at4188,selecting4190. **The scheduler interval between those replay roots is not replayed.** The semaphore handle cell input uses the earlier observed WaitSema A0,checked against later iSignalSema A0;the cell itself was not independently captured. No guest memory/register writes,savestates or RAM copies were made,and owned probes/process were removed. The [next-owner study](iop-sdf-worker-study.json) identifies the genuine next command0 dependency:original **SDFSDMAN+1158,60 words**,which begins with LIBSD ordinal4 at actualB809C and configures both sound cores. Recover that driver path and original thread initialization,then bridge actual IRQ scheduling and complete the EE reply/sound-root flow. Available original IOP source is4,750 unique loaded words. Canonical recovery remains2,746/9,062 functions across556 source units;full executable recovery remains incomplete.
<!-- /iop-sdf-worker-current -->


<!-- iop-libsd-current -->
The [LIBSD comparison](iop-libsd-C-validation.json) adds **1,519 selected original instructions**,1,517 newly unique:LIBSD initialization/configuration,Nocturne's60-word two-core caller,original INTRMANI registration/release/enable/disable APIs,and SYSCLIB clear routines with actual loader bindings.672 original cases match1,344 strict C runs. **1,284 selected words execute;235 remain unvisited.** Tests use an explicit SPU2/six-IOP-register value profile and the existing INTC/DICR primitives. This is not an SPU2 audio,RAM,DMA,status-transition or timing implementation. The [38,841-check review](iop-libsd-results-review.json) checks packed selector/core/voice address formulas,the bit7 stride distinction0x400→0x28,MULT/HI/LO effects,24-bit switch writes,SPU address masking and EEA's high-only store,core attribute masks,callback pair ownership,IRQ mode/error/gate behavior and native bzero. Global volume selectors keep their SDK bit7 flag;selectors outside the mapped register window are not treated as supported device operations. The [live initialization capture](runtime-libsd-init-observation.json) observes62 boundaries,including native DPCR1/DPCR2/core-status/DICR/INTC/gate reads,real SdInit return0 and the actual Nocturne setup return. Both C builds replay **8,522 instructions through the real CreateEventFlag entry**,matching19 complete GPR/HI/LO banks,3,920B SDK globals,512B callback table and1,024B stack. One additional bank retains a source pending A0 load versus the debugger's immediate A0 display;it is qualified without normalization. Peripheral inputs come from genuine native reads;there are no debugger MMIO reads or supplied event/driver results. Observed full Init/setup returns are future evidence,not replayed C returns. Owned probes/process were removed without guest writes,savestates or RAM copies. The [next-owner study](iop-libsd-study.json) corrects the synchronization-object role:the driver imports **thevent ordinal4**,creating two event flags with descriptor[attr2,option0,initial_bits1]. The original40-byte object stores tag7F03 at8,id atA,wait head14,option1C,bits20 and initial_bits24;handle identity uses the low6 id bits. Its64-word constructor calls the24-word tagged allocator atTHREADMAN+6720,then the heaplib and memset imports. Recover these native objects and Set/iSetEventFlag next,then complete Init and SetEffectAttr at actualB476C. The latter is LIBSD ordinal23,as used by the actual Nocturne caller. Available original IOP source is6,267 unique loaded words. Canonical recovery remains2,746/9,062 functions across556 source units. Full sound initialization,SPU2-dependent behavior,the native scheduler bridge,original EE reply/sound-root completion and full executable recovery remain incomplete.
<!-- /iop-libsd-current -->


<!-- iop-event-heap-current -->
The [heap/event comparison](iop-event-heap-C-validation.json) adds **762 original instructions**,all newly unique:original HEAPLIB management,CreateEventFlag,SetEventFlag,iSetEventFlag,the tagged allocator and observed loader bindings. **295 original worlds / 1,350 calls match both C builds** (2,700 C calls);742 selected instructions execute and20 remain unvisited. Real heap initialization,growth,allocation,free/coalescing and deletion compute their results. Twelve connected wait/set sequences use native constructors and SYS/scheduler/RFE to resume original blocked callers. The [independent semantic review](iop-event-heap-independent-review.json) checks heap and event ownership. The [actual-runtime review](iop-event-heap-runtime-review.json) passes95,718 assertions:both C builds reproduce two observed event allocations and **22,511 instructions through the full SdInit return0**,matching captured registers and bounded SDK globals,THREADMAN state,IRQ table,stack,objects and heap metadata. Each build checks396 full register banks including standalone allocations;one raw pending-A0 bank remains qualified. The replay uses176 genuine SPU2 LHU samples as external register inputs;one status halfword changes from0 to80. This is not an autonomous SPU2 audio,DMA or timing model. No allocation or function return is supplied. The [live capture](runtime-event-heap-observation.json) contains426 bounded observations,with owned probes/process removed and no guest writes,savestates or RAM copies. The [ownership study](iop-event-heap-study.json) records40-byte native event objects and8-byte heap blocks. Original loader import-header metadata is excluded from code identity checks. Available IOP source is7,029 unique loaded instructions;canonical recovery stays **2,746/9,062 functions across556 source units**. Parallel workers now investigate distinct code areas with explicit file ownership and one owner per shared Ghidra/PCSX2 session. Next targets include original LIBSD effects and uncovered script-process lifecycle commands. Full SDF setup,the native scheduler bridge,EE sound completion and full executable recovery remain open.
<!-- /iop-event-heap-current -->


<!-- parallel-recovery-current -->
Current compiled recovery is **3,089/9,065 recognized PS2 functions (34.076%)**, **701 C source units**, and **561,944 recognized body bytes**. Seven Magatama entry functions add 1,020 bytes. Their 376 original worlds and752 strict staged executions pass; the actual701 main passes376 new worlds plus10,336 affected file/menu preservation cases. Two explicit host memory ports route the real guest address space; all game C/H implementations and697 other parent objects are unchanged.

The tests retain real allocator/file-queue publication,3,200 RNG draws,160 sound calls and928 native SYS/ERET pairs. Four Unity roles are authenticated; three native roles remain descriptive. Three ordinary PCs are unvisited, with their source-cold conditions recorded. Queued callback2144A0, full menu process shutdown and physical resource completion remain separate work.

The latest broad regression remains **413 functions /462,684 cases on its actual699-unit build**. Parallel recovery continues in menu process/resource callbacks, model attachment, and battle-result shutdown/field return. See the [workstream index](parallel-recovery-workstreams.json) and [entry admission](magatama-entry-admission.json).
<!-- /parallel-recovery-current -->


<!-- sif-control-current -->
The [current SIF/MC comparison](sdk-memory-card-client-comparison.json) passes **262 original worlds /524 strict C executions /1,248,712 instructions**, with every modeled raw bank,RAM span,cache line and MMIO event compared. It now owns installed BIOS selectors18/22/120/121/122 and their414-word selected closure;221 control words and286 of320 existing SIF support words are observed. There are236 native returns,22 other boundaries andfour genuine200,000-instruction waits. Source-owned handler/free lists,current register state and real command scratch pass197,024 independent BEFORE checks. Two partial-startup peer buffers remain explicit incoming state; no IOP readiness,clock,DMA completion or live-game behavior is supplied. The26 client APIs remain staged with **zero new identity credit**. See [scope and limits](sif-control-connected-progress.json).
<!-- /sif-control-current -->
