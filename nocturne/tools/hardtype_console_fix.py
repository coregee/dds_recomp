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
- Fusion's inheritance tables (fclKeisyoSkillLevel, 3-byte rows) are read
  with halfword loads at odd addresses: in cmbGetKeisyoSkillLevel's loop
  (0x222BC0, which Hardtype's own code also jumps to) and in
  cmbGetMutationSkill (0x223580). Each becomes an LWR/LWL pair and a mask,
  the same value; both fit in place (the first function's loop takes its
  padding, its head staying put; the second drops a divide-by-zero trap
  for its divisor, the constant 0xE3).
- SetCommList's Beckon Call check (0x25CFFC) reads the halfword 4 past a
  register left by the skill list, which can hold the RNG's state word:
  any address. It now reads only main RAM (or its uncached mirrors at
  0x20000000 and 0x30000000) and takes anything else as 0, which is what
  PCSX2 reads where nothing is mapped (a few unlikely addresses, the
  scratchpad among them, read 0 here and something else there). Only
  whether it is 0 matters. The check runs in 11 words after SetCommList's
  return (unreachable) and the 7 after nbRunAi's at 0x2FE544.

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

AT, V0, V1, A1, A3, S0, S2, S3, S4, S6 = 1, 2, 3, 5, 7, 16, 18, 19, 20, 22   # registers


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


def lbu(rt, offset, base):
    return load(0x24, rt, offset, base)


def immediate(op, rt, rs, value):
    return op << 26 | rs << 21 | rt << 16 | value & 0xFFFF


def addiu(rt, rs, value): return immediate(0x09, rt, rs, value)
def andi(rt, rs, value): return immediate(0x0C, rt, rs, value)
def ori(rt, rs, value): return immediate(0x0D, rt, rs, value)
def lui(rt, value): return immediate(0x0F, rt, 0, value)


def special(rd, rs, rt, function, sa=0):
    return rs << 21 | rt << 16 | rd << 11 | sa << 6 | function


def srl(rd, rt, sa): return special(rd, 0, rt, 0x02, sa)
def srlv(rd, rt, rs): return special(rd, rs, rt, 0x06)
def movn(rd, rs, rt): return special(rd, rs, rt, 0x0B)
def and_(rd, rs, rt): return special(rd, rs, rt, 0x24)
def or_(rd, rs, rt): return special(rd, rs, rt, 0x25)


def branch(op, rs, rt, at, target):
    return op << 26 | rs << 21 | rt << 16 | ((target - at - 4) >> 2) & 0xFFFF


def beq(rs, rt, at, target): return branch(0x04, rs, rt, at, target)
def bne(rs, rt, at, target): return branch(0x05, rs, rt, at, target)
def bnel(rs, rt, at, target): return branch(0x15, rs, rt, at, target)


JR_RA = 0x03E00008


NOP = 0
CONDITIONS = 0x002FDEE0   # nbAiAiChk's loads
CHECK_TABLE = 0x002FE534  # nbRunAi's load
LEVEL = 0x00222BC0        # cmbGetKeisyoSkillLevel's loop
BECKON = 0x0025D1AC       # Beckon Call's check, then BECKON_END
BECKON_END = 0x002FE544

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

    # cmbGetKeisyoSkillLevel: row by row (a1 counts on from what the caller
    # left), the skill's halfword at any address
    (LEVEL + 0x00, 0x94620000, lwr(V0, 0x0, V1)),           # lhu v0,0x0(v1)
    (LEVEL + 0x04, 0x54440004, lwl(V0, 0x3, V1)),           # bnel v0,a0,0x222BD8
    (LEVEL + 0x08, 0x24A50001, andi(V0, V0, 0xFFFF)),       # addiu a1,a1,0x1
    (LEVEL + 0x0C, JR_RA, bnel(V0, 4, LEVEL + 0x0C, LEVEL + 0x1C)),   # jr ra
    (LEVEL + 0x10, 0x90620002, addiu(A1, A1, 1)),           # lbu v0,0x2(v1)
    (LEVEL + 0x14, NOP, JR_RA),
    (LEVEL + 0x18, 0x2CA2012E, lbu(V0, 0x2, V1)),           # sltiu v0,a1,0x12e
    (LEVEL + 0x1C, NOP, 0x2CA2012E),                        # sltiu v0,a1,0x12e
    (LEVEL + 0x20, 0x1440FFF7, bne(V0, 0, LEVEL + 0x20, LEVEL)),   # bne v0,zero,0x222BC0
    (LEVEL + 0x24, 0x24630003, 0x24630003),                 # addiu v1,v1,0x3
    (LEVEL + 0x28, JR_RA, JR_RA),
    (LEVEL + 0x2C, 0x24020001, 0x24020001),                 # addiu v0,zero,0x1

    # cmbGetMutationSkill: a random row's halfword (the trap for a zero
    # divisor goes: it is the constant 0xE3)
    (0x00223564, 0x52800001, 0x0054001B),          # beql s4,zero,... -> divu v0,s4
    (0x00223568, 0x000001CD, 0x00001810),          # break             -> mfhi v1
    (0x0022356C, 0x0054001B, 0x00031040),          # divu v0,s4        -> sll v0,v1,1
    (0x00223570, 0x00001810, 0x00621821),          # mfhi v1           -> addu v1,v1,v0
    (0x00223574, 0x00031040, 0x00761821),          # sll v0,v1,1       -> addu v1,v1,s6
    (0x00223578, 0x00621821, lwr(S0, 0x0, V1)),    # addu v1,v1,v0
    (0x0022357C, 0x00761821, lwl(S0, 0x3, V1)),    # addu v1,v1,s6
    (0x00223580, 0x94700000, andi(S0, S0, 0xFFFF)),   # lhu s0,0x0(v1)

    # SetCommList: Beckon Call's halfword, from main RAM only
    (0x0025CFF8, 0x24160002, j(BECKON)),           # addiu s6,zero,0x2 ...
    (0x0025CFFC, 0x94E20004, 0x24160002),          # ... into the delay slot (was lhu v0,0x4(a3))
    (BECKON + 0x00, 0, addiu(AT, A3, 4)),          # the address
    (BECKON + 0x04, 0, srl(V1, AT, 28)),
    (BECKON + 0x08, 0, ori(V0, 0, 0xD)),           # segments 0, 2 and 3: main RAM ...
    (BECKON + 0x0C, 0, srlv(V0, V0, V1)),
    (BECKON + 0x10, 0, andi(V0, V0, 1)),
    (BECKON + 0x14, 0, lui(V1, 0x0E00)),           # ... in their first 32 MB
    (BECKON + 0x18, 0, and_(V1, AT, V1)),
    (BECKON + 0x1C, 0, movn(V0, 0, V1)),
    (BECKON + 0x20, 0, lui(V1, 0x01FF)),
    (BECKON + 0x24, 0, j(BECKON_END)),
    (BECKON + 0x28, 0, ori(V1, V1, 0xFFFF)),
    (BECKON_END + 0x00, 0, beq(V0, 0, BECKON_END, BECKON_END + 0x14)),   # elsewhere: 0
    (BECKON_END + 0x04, 0, and_(AT, AT, V1)),
    (BECKON_END + 0x08, 0, lbu(V0, 0x0, AT)),      # its two bytes, nonzero if either is
    (BECKON_END + 0x0C, 0, lbu(AT, 0x1, AT)),
    (BECKON_END + 0x10, 0, or_(V0, V0, AT)),
    (BECKON_END + 0x14, 0, j(0x0025D000)),         # bne v0,zero,... as before
    (BECKON_END + 0x18, 0, NOP),
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
    print("patched %d words" % sum(1 for _, original, patched in PATCHES if original != patched))


if __name__ == "__main__":
    main()
