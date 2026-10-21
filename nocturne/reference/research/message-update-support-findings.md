# Native Message update prerequisites and draw manager

**14 complete PS2 routines** in `src/message_update_support.c` pass **2,464 original-instruction comparisons**, covering **1,756 recognized body bytes** and all **354 main instruction addresses**. Real panel geometry callbacks, font recycling, memory-handle release, speed controls and frame/ordering dependencies execute. Full declared RAM, defined raw64 returns, Status, primitive operations, callee saves and ordered draw callback traces agree. The affected source builds with warnings treated as errors; fourteen interfaces are saved, independently reopened and merged into current exports in place.

The cases include **288 panel-offset calls** across all nine original types, including native null callback entries for types six and seven and selected panel/payload aliases. The live table at **326428** selects actual recovered geometry functions. Coordinates and depth use wrapped ADDU32; the native routine caches its inputs and callback before its ordered stores. Scrolling shifts message requests, the message panel, the speaker panel and any speaker font using the native differences between top/bottom movement.

**256 selection-group trim cases** independently check retained Y groups, repaired request tails and disjoint recycled lists: **184 requests remain** and **708 requests recycle**. The native request list follows **+24**, groups by Y at **+8**, clears display linkage at **+28**, and repairs the tail at **+2C**. Actual recycling calls `frDestroyFontRequestAfter`; no release result is substituted. Negative/wrapped group arithmetic and selections beyond the available groups retain native behavior.

**256 draw-manager cases** traverse zero to three native list records and draw **384 message instances** through the recovered frame body. The manager reads the next node after drawing its payload, then increments the wrapping global counter. The batch observes **4,488 actual draw callbacks** and **5,413,251 original instruction steps**. The pause check at **001189D0** is an actual eight-byte zero-return body, preserved as a descriptive PS2 alias rather than given speculative behavior.

| PS2 entry | Reviewed Unity role / address |
| --- | --- |
| 001CC1E8 | itfPanel.SetPositionOffset / 182666260 |
| 001CF5F0 | UnchainFontHandleUnit / 18244EFA0 |
| 001CF7A8 | ChangeFontPosition / 182447180 |
| 001CF8B8 | ChangeFontColorAll / 182447140 |
| 001CF910 | ChangeFontAlpha / 1824470F0 |
| 001CF9B0 | GetMaskedIndex / 18244A430 |
| 001CFA50 | RaiseMessageSpeedMaxAll / 18244CB20 |
| 001CFD78 | ForceSetCurCtr / 182449CB0 |
| 001CFFD0 | CalcWindow / 1824469C0 |
| 001D0518 | SlideUpDownMessage / 18244EA20 |
| 001D07F0 | SelectItemDefKey / 18244DB40 |
| 001D0880 | CalcCurCtr / 1824459E0 |
| 001D1038 | DrawManagerProc / 182448750 |

These are thirteen semantic counterparts. Native text color writes byte **+14**; alpha combines the full supplied low word with `(old & FFFFFF00)`, preserving high-bit contamination rather than silently masking to a byte. Native selection keys read signed short key/bit pairs and signed trigger bytes at **2F5830 + key**; HD instead queries the managed pad manager and adds bounds checks. Selection-mask mapping retains the original 32-step limit and ADDIU index truncation. The native cursor compares sign-extended short results, including overflow, and retains minimum alpha **32/64**, expansion **128** and steps **+8/-8**.

Window phases are **300/3000** masks. Native message alpha opens by **24** and closes by **8**; speaker alpha opens/closes by **32**, clamps to **200** and actually releases both owned handles when closed. HD changes speaker handling to immediate phase/pointer changes and applies additional option/UI behavior. These native paths are recovered from PS2 instructions, not inferred from Unity layouts. Numeric masks/offsets above are hexadecimal; fade increments and alpha thresholds are decimal.

Five new complete DDS spans resolve:

| Nocturne | DDS | Role |
| --- | --- | --- |
| 001CF5F0 | 0019D730 | Trim/recycle selected font group |
| 001CF9B0 | 0019DAF0 | Map unmasked selection index |
| 001CFD78 | 0019DED8 | Force cursor counters |
| 001189D0 | 0011E278 | Native zero-return draw pause check |
| 001D1038 | 0019F6A0 | Draw manager |

Three agreeing callee constraints support these spans. Two relocated global bases agree: **56BE60 -> 3D6EA0** for the manager and **56BBC4 -> 3D6E14** for recycled font requests. Font position, color and alpha helpers each retain two complete DDS candidates; they are deliberately unresolved. The draw-manager span does not establish DDS frame-body equivalence or runtime behavior.

At publication, the direct update graph contained 13 unrecovered bodies / 2,524 bytes. The subsequent [sound-bank/cache/path recovery](sound-bank-support-findings.md) recovers five of those routines. The [current update graph](message-update-frontier.json) also includes the actually installed resource-loader pump at002976C0 as an explicit root, exposing additional dependencies: **19 unrecovered bodies / 5,420 bytes / two indirect sites**, after the subsequent [resource-loader support recovery](resource-loader-support-findings.md) and explicit inclusion of all three installed file-event callbacks. The sound facade checks seven bank records, may submit a bank-load command, and then queues a native **90** sound command; loading and command submission still need recovery. Cache prerequisites now have separate finite external-operand comparisons. No arbitrary returning callback or sound function is substituted.

Rolling evidence: `message-update-support-validation.json`, `message-update-support-interfaces.json`, `message-update-support-abi.json`, `message-update-support-matches.json`, `message-update-support-transfer.json` and `message-update-frontier.json`. Fixtures use generated backed message/font/trigger records. Original asset-to-frame rendering, live pad sampling, IOP sound completion, scheduler/gameplay, physical PS2 execution and a matching executable remain outstanding.
