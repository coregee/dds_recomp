"""A small disassembler for the R5900 (EE) instructions the game uses most,
for comparing versions' code (tools/version_diff.py). Instructions it
doesn't know print as words."""

REGS = ['zero', 'at', 'v0', 'v1', 'a0', 'a1', 'a2', 'a3', 't0', 't1', 't2', 't3', 't4', 't5', 't6', 't7',
        's0', 's1', 's2', 's3', 's4', 's5', 's6', 's7', 't8', 't9', 'k0', 'k1', 'gp', 'sp', 's8', 'ra']

I_TYPE = {0x08: 'addi', 0x09: 'addiu', 0x0a: 'slti', 0x0b: 'sltiu', 0x0c: 'andi', 0x0d: 'ori', 0x0e: 'xori',
          0x18: 'daddi', 0x19: 'daddiu'}
MEMORY = {0x1a: 'ldl', 0x1b: 'ldr', 0x1e: 'lq', 0x1f: 'sq', 0x20: 'lb', 0x21: 'lh', 0x22: 'lwl', 0x23: 'lw',
          0x24: 'lbu', 0x25: 'lhu', 0x26: 'lwr', 0x27: 'lwu', 0x28: 'sb', 0x29: 'sh', 0x2a: 'swl', 0x2b: 'sw',
          0x2c: 'sdl', 0x2d: 'sdr', 0x2e: 'swr', 0x37: 'ld', 0x3f: 'sd'}
FLOAT_MEMORY = {0x31: 'lwc1', 0x39: 'swc1'}
BRANCH = {0x04: 'beq', 0x05: 'bne', 0x06: 'blez', 0x07: 'bgtz', 0x14: 'beql', 0x15: 'bnel', 0x16: 'blezl', 0x17: 'bgtzl'}
SPECIAL = {0x00: 'sll', 0x02: 'srl', 0x03: 'sra', 0x04: 'sllv', 0x06: 'srlv', 0x07: 'srav', 0x08: 'jr', 0x09: 'jalr',
           0x0a: 'movz', 0x0b: 'movn', 0x0c: 'syscall', 0x0d: 'break', 0x0f: 'sync', 0x10: 'mfhi', 0x12: 'mflo',
           0x14: 'dsllv', 0x16: 'dsrlv', 0x17: 'dsrav', 0x18: 'mult', 0x19: 'multu', 0x1a: 'div', 0x1b: 'divu',
           0x20: 'add', 0x21: 'addu', 0x22: 'sub', 0x23: 'subu', 0x24: 'and', 0x25: 'or', 0x26: 'xor', 0x27: 'nor',
           0x2a: 'slt', 0x2b: 'sltu', 0x2d: 'daddu', 0x2f: 'dsubu', 0x38: 'dsll', 0x3a: 'dsrl', 0x3b: 'dsra',
           0x3c: 'dsll32', 0x3e: 'dsrl32', 0x3f: 'dsra32'}
REGIMM = {0x00: 'bltz', 0x01: 'bgez', 0x02: 'bltzl', 0x03: 'bgezl'}
FLOAT_S = {0x00: 'add.s', 0x01: 'sub.s', 0x02: 'mul.s', 0x03: 'div.s', 0x05: 'abs.s', 0x06: 'mov.s', 0x07: 'neg.s',
           0x18: 'adda.s', 0x1c: 'madd.s', 0x24: 'cvt.w.s', 0x32: 'c.eq.s', 0x34: 'c.lt.s', 0x36: 'c.le.s'}


def disassemble(word, address):
    op = word >> 26
    rs, rt, rd = (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    sa, funct = (word >> 6) & 31, word & 63
    imm = word & 0xffff
    simm = imm - 0x10000 if imm & 0x8000 else imm
    target = address + 4 + 4 * simm
    if word == 0:
        return 'nop'
    if op == 0:
        name = SPECIAL.get(funct)
        if name is None:
            return '.word 0x%08x' % word
        if funct in (0x00, 0x02, 0x03, 0x38, 0x3a, 0x3b, 0x3c, 0x3e, 0x3f):
            return '%s %s,%s,%d' % (name, REGS[rd], REGS[rt], sa)
        if funct in (0x04, 0x06, 0x07, 0x14, 0x16, 0x17):
            return '%s %s,%s,%s' % (name, REGS[rd], REGS[rt], REGS[rs])
        if funct == 0x08:
            return 'jr %s' % REGS[rs]
        if funct == 0x09:
            return 'jalr %s' % REGS[rs]
        if funct in (0x10, 0x12):
            return '%s %s' % (name, REGS[rd])
        if funct in (0x18, 0x19, 0x1a, 0x1b):
            return '%s %s,%s' % (name, REGS[rs], REGS[rt])
        if funct in (0x0c, 0x0d, 0x0f):
            return name
        return '%s %s,%s,%s' % (name, REGS[rd], REGS[rs], REGS[rt])
    if op == 1:
        name = REGIMM.get(rt)
        return '%s %s,0x%x' % (name, REGS[rs], target) if name else '.word 0x%08x' % word
    if op in (2, 3):
        return '%s 0x%x' % ('j' if op == 2 else 'jal', (address & 0xf0000000) | ((word & 0x3ffffff) << 2))
    if op in BRANCH:
        if op in (0x06, 0x07, 0x16, 0x17):
            return '%s %s,0x%x' % (BRANCH[op], REGS[rs], target)
        return '%s %s,%s,0x%x' % (BRANCH[op], REGS[rs], REGS[rt], target)
    if op == 0x0f:
        return 'lui %s,0x%x' % (REGS[rt], imm)
    if op in I_TYPE:
        value = imm if op in (0x0c, 0x0d, 0x0e) else simm
        return '%s %s,%s,%s' % (I_TYPE[op], REGS[rt], REGS[rs], hex(value) if value >= 0 else '-' + hex(-value))
    if op in MEMORY:
        return '%s %s,%s(%s)' % (MEMORY[op], REGS[rt], hex(simm) if simm >= 0 else '-' + hex(-simm), REGS[rs])
    if op in FLOAT_MEMORY:
        return '%s f%d,%s(%s)' % (FLOAT_MEMORY[op], rt, hex(simm) if simm >= 0 else '-' + hex(-simm), REGS[rs])
    if op == 0x11:
        fmt = rs
        if fmt == 0x00:
            return 'mfc1 %s,f%d' % (REGS[rt], rd)
        if fmt == 0x04:
            return 'mtc1 %s,f%d' % (REGS[rt], rd)
        if fmt == 0x08:
            return 'bc1%s 0x%x' % (('f', 't', 'fl', 'tl')[rt & 3], target)
        if fmt == 0x10:
            name = FLOAT_S.get(funct)
            fs, ft, fd = rd, rt, sa
            if name and funct in (0x05, 0x06, 0x07, 0x24):
                return '%s f%d,f%d' % (name, fd, fs)
            if name and funct >= 0x30:
                return '%s f%d,f%d' % (name, fs, ft)
            if name:
                return '%s f%d,f%d,f%d' % (name, fd, fs, ft)
        if fmt == 0x14 and funct == 0x20:
            return 'cvt.s.w f%d,f%d' % (sa, rd)
    return '.word 0x%08x' % word
