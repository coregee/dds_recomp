"""Patches Hardtype 1.5.1's executable so its AI no longer freezes a PS2.

    python tools/hardtype_console_fix.py <Hardtype SLUS_209.11> <output>

On a console the EE raises an address error for a misaligned halfword,
word or doubleword access. PCSX2 lets it through, so Hardtype plays there
but freezes on hardware before an AI unit acts (docs/hardtype.md, "On a
console"). The patch changes code only, so the game plays exactly as
Hardtype does on PCSX2:

- 0x2FDD3C (nbAiAiChk's new prologue): `sw zero,0x190(s0)` runs before
  s0 holds the AI work, so it stores to nbRunAi's check counter + 0x190
  (0x191: misaligned, in the kernel's low memory). On PCSX2 it hits nothing
  the game reads; it becomes a nop.
- Hardtype's AI records (datDevilAI) are often only 2-aligned, and three
  places read words from them. Each such load becomes an LWR/LWL pair,
  which reads the same word at any alignment:
  - nbAiAiChk (0x2867E4): a check's three conditions, through 8 words at
    0x2FDEE0;
  - nbRunAi (0x287D38): a check's table, through 4 words at 0x2FE534.
  Both spots are unused space in Hardtype's code area, after an
  unconditional jump, and nothing refers to them.
- nbRunAiSub (0x287C10): an action's two halfwords at +4 and +6 are read
  with two halfword loads instead of one word split in two (in place).

The records themselves can't simply be realigned. Eight bosses' records
have no action tables (Kin-Ki, Sui-Ki, Fuu-Ki, Aciel, Futomimi, Koumoku,
Zouchou, Thor 2), and their scripts call AI(), which reads the bytes after
the record as the table: moving records would change what they do.

It refuses any executable but Hardtype 1.5.1's. It contains no game data.
"""
import hashlib
import struct
import sys

HARDTYPE_SHA256 = "a61a6696a275e04f11296cd026e67836091313ff66329eac85d114202342bc6e"

S2, S3, S4, A1, V1 = 18, 19, 20, 5, 3   # registers


def j(target):
    return 2 << 26 | target >> 2


def load(op, rt, offset, base):
    return op << 26 | base << 21 | rt << 16 | offset & 0xFFFF


def lwr(rt, offset, base):
    return load(0x26, rt, offset, base)


def lwl(rt, offset, base):
    return load(0x22, rt, offset, base)


def lhu(rt, offset, base):
    return load(0x25, rt, offset, base)


NOP = 0
CONDITIONS = 0x002FDEE0   # nbAiAiChk's loads
CHECK_TABLE = 0x002FE534  # nbRunAi's load

# (address, original word, patched word)
PATCHES = [
    (0x002FDD3C, 0xAE000190, NOP),                 # sw zero,0x190(s0)

    (0x002867E4, 0x8CB20000, j(CONDITIONS)),       # lw s2,0x0(a1)
    (0x002867E8, 0x8CB30004, NOP),                 # lw s3,0x4(a1) (the delay slot)
    (0x002867EC, 0x8CB40008, NOP),                 # lw s4,0x8(a1)
    (CONDITIONS + 0x00, 0, lwr(S2, 0x0, A1)),
    (CONDITIONS + 0x04, 0, lwl(S2, 0x3, A1)),
    (CONDITIONS + 0x08, 0, lwr(S3, 0x4, A1)),
    (CONDITIONS + 0x0C, 0, lwl(S3, 0x7, A1)),
    (CONDITIONS + 0x10, 0, lwr(S4, 0x8, A1)),
    (CONDITIONS + 0x14, 0, lwl(S4, 0xB, A1)),
    (CONDITIONS + 0x18, 0, j(0x002867F0)),
    (CONDITIONS + 0x1C, 0, NOP),

    # lw s3,0xc(v1); the lui after it (also a branch target) stays as the
    # jump's delay slot
    (0x00287D38, 0x8C73000C, j(CHECK_TABLE)),
    (CHECK_TABLE + 0x0, 0, lwr(S3, 0xC, V1)),
    (CHECK_TABLE + 0x4, 0, lwl(S3, 0xF, V1)),
    (CHECK_TABLE + 0x8, 0, j(0x00287D40)),
    (CHECK_TABLE + 0xC, 0, NOP),

    (0x00287C10, 0x8CA50004, lhu(6, 0x4, A1)),     # lw a1,0x4(a1)     -> lhu a2,0x4(a1)
    (0x00287C14, 0x30A6FFFF, lhu(A1, 0x6, A1)),    # andi a2,a1,0xffff -> lhu a1,0x6(a1)
    (0x00287C1C, 0x00052C02, NOP),                 # srl a1,a1,16 (the delay slot)
]


def file_offset(data, address):
    phoff = struct.unpack_from("<I", data, 0x1C)[0]
    for i in range(struct.unpack_from("<H", data, 0x2C)[0]):
        kind, offset, vaddr, _, filesz, _, _, _ = struct.unpack_from("<8I", data, phoff + 32 * i)
        if kind == 1 and vaddr <= address and address + 4 <= vaddr + filesz:
            return offset + address - vaddr
    raise SystemExit("0x%08X is outside the executable's loaded data" % address)


def patch(data):
    """The patched executable (bytes), from Hardtype 1.5.1's."""
    if hashlib.sha256(data).hexdigest() != HARDTYPE_SHA256:
        raise SystemExit("not Hardtype 1.5.1's SLUS_209.11 (or already patched)")
    out = bytearray(data)
    for address, original, patched in PATCHES:
        at = file_offset(data, address)
        if struct.unpack_from("<I", data, at)[0] != original:
            raise SystemExit("unexpected word at 0x%08X" % address)
        struct.pack_into("<I", out, at, patched)
    return bytes(out)


def main():
    if len(sys.argv) != 3:
        raise SystemExit(__doc__)
    out = patch(open(sys.argv[1], "rb").read())
    open(sys.argv[2], "wb").write(out)
    print("patched %d words" % len(PATCHES))


if __name__ == "__main__":
    main()
