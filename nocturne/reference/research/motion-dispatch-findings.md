# Motion dispatch and boundary findings

The original node generator at `002b3b20` selects the upper 16 bits of A1 and reads category table `00529448`. Three observed category entries are `002b43a8`, `002b4c88` and `002b5998`, followed by a zero word. Each dispatcher selects the lower 16 bits and indexes its own table at `00529458`, `005294e8` or `00529600`. These observations establish the two selector stages, not a universal limit on valid types. The HD node generator lead instead indexes its managed generator array with the lower 16 bits. Its type encoding must not be copied into the PS2 front end.

Seven entry or boundary candidates were absent from the preceding 8,938-function index. `002b43a8` begins four bytes before the existing `002b43ac` function, with an ANDI instruction that supplies the selector; it requires a boundary repair rather than an additional overlapping function. The other two category dispatchers and four small callbacks are also supported by table words and decoded original spans. `002b4118` is an eight-byte return-delay-slot pointer store; the next existing function begins at `002b4120` and is separate. The seven supported repairs have now been applied to the 261-function checkpoint. Five associated C leaf implementations pass the combined203,804-case regression. See `motion-callback-findings.md`; the original candidate evidence is retained here.

The five observed model generator tables resolve the motion engine's indirect offsets: offset 0 destroys, offset 4 assigns the cut pointer, offset 8 seeks, offset C initializes blend state and offset 10 seeks with blending. The offset 4 callback is `002b4118` throughout these tables. Offset C selects three raw 16-byte copy callbacks (`002b4c28`, `002b4c48`, `002b4c68`) or the remaining visible-node callback. The three copy callbacks read the raw model-node address at node+C, load model fields at 60/50/70, then store the complete 16-byte value at node+10. No floating arithmetic is involved.

The HD position/rotation/scale initialization leads (`1825ebce0`, `1825ebd80`, `1825ebe20`) instead read the managed node backup at30/38 and write the referenced model fields at98/88/A8. Their static copy direction is reversed. The name is useful context, but it cannot establish equivalent PS2 behavior. Native source hashes and exact original bytes are retained in the JSON reports.

| Minor observed | Generator | Vtable | Set cut | Init blend |
|---|---|---|---|---|
|0|002b4428|00529470|002b4118|002b4c28|
|1|002b45b8|00529488|002b4118|002b4c48|
|2|002b47b8|005294a0|002b4118|002b4c68|
|3|002b4948|005294b8|002b4118|002b4c48|
|4|002b4af8|005294d0|002b4118|002b4c08|

The supported entries and five full-width callbacks are now saved and validated; next follow their allocator and seek/blend dependencies. The comparison draft is separately pinned in `model-compare-findings.md`. The original investigation preceded promotion; current checkpoint totals are recorded in `motion-callback-findings.md`.
