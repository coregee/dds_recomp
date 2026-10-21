"""Configure the installed custom emulator for Nocturne research in place."""
from pathlib import Path
import re

config = Path(r'C:\Games\Emulators\PCSX2-MCP\inis\PCSX2.ini')
text = config.read_text(encoding='utf-8')

def set_value(section, key, value):
    global text
    pattern = r'(?m)^\[' + re.escape(section) + r'\]\s*\n(?P<body>.*?)(?=^\[|\Z)'
    match = re.search(pattern, text, flags=re.S)
    if match is None:
        text += f'\n[{section}]\n{key} = {value}\n'
        return
    body = match['body']
    setting = r'(?m)^' + re.escape(key) + r'\s*=.*$'
    if re.search(setting, body):
        body = re.sub(setting, f'{key} = {value}', body)
    else:
        body += f'{key} = {value}\n'
    text = text[:match.start('body')] + body + text[match.end('body'):]

set_value('MemoryCards', 'Slot1_Filename', 'NocturneResearch.ps2')
set_value('MemoryCards', 'Slot1_Enable', 'true')
set_value('EmuCore', 'EnablePINE', 'true')
set_value('EmuCore', 'SaveStateOnShutdown', 'false')
for button, key in dict(Up='Up', Down='Down', Left='Left', Right='Right',
                        Cross='J', Circle='K', Square='U', Triangle='I',
                        Start='Return', Select='Backspace', L1='Q', R1='E',
                        L2='1', R2='3').items():
    # Preserve the existing physical controller binding alongside the keyboard.
    match = re.search(r'(?ms)^\[Pad1\]\s*\n(.*?)(?=^\[|\Z)', text)
    current = re.findall(r'(?m)^' + button + r'\s*=\s*(.*)$', match[1])
    binding = 'Keyboard/' + key
    # SimpleIni string lists use repeated keys. " & " means a chord, requiring
    # both devices; it is not an alternative binding separator.
    bindings = []
    for entry in current:
        if entry.strip().endswith(' & ' + binding):
            entry = entry.strip()[:-len(' & ' + binding)]
        if entry.strip() and entry.strip() not in bindings:
            bindings.append(entry.strip())
    if binding not in bindings:
        bindings.append(binding)
    body = re.sub(r'(?m)^' + button + r'\s*=.*\n?', '', match[1])
    body += ''.join(f'{button} = {entry}\n' for entry in bindings)
    text = text[:match.start(1)] + body + text[match.end(1):]
for index, (button, key) in enumerate((('Cross', 'F10'), ('Circle', 'F11'),
                                     ('Start', 'F12'), ('Down', 'F7'),
                                     ('Up', 'F13'), ('Left', 'F14'),
                                     ('Right', 'F15'), ('Triangle', 'F16'),
                                     ('Square', 'F17'), ('L1', 'F18'),
                                     ('R1', 'F19'), ('L2', 'F20'),
                                     ('R2', 'F21'), ('Select', 'F22')), 1):
    set_value('Pad1', f'Macro{index}', 'Keyboard/' + key)
    set_value('Pad1', f'Macro{index}Binds', button)
    set_value('Pad1', f'Macro{index}Toggle', 'true')
    set_value('Pad1', f'Macro{index}Frequency', '0')
config.write_text(text, encoding='utf-8')
print('Nocturne research card selected; keyboard bindings added alongside SDL.')
