#!/usr/bin/env python3

# Adds event learnset to specified Pokémon
 
import re
import os

species_info_paths = [
    "src/data/pokemon/species_info.h",
    "src/data/pokemon/species_info/gen_1_families.h",
    "src/data/pokemon/species_info/gen_2_families.h",
    "src/data/pokemon/species_info/gen_3_families.h",
    "src/data/pokemon/species_info/gen_4_families.h",
    "src/data/pokemon/species_info/gen_5_families.h",
    "src/data/pokemon/species_info/gen_6_families.h",
    "src/data/pokemon/species_info/gen_7_families.h",
    "src/data/pokemon/species_info/gen_8_families.h",
    "src/data/pokemon/species_info/gen_9_families.h",
]

event_learnsets_path = "src/data/pokemon/event_learnsets.h"

with open(event_learnsets_path, "r", encoding="utf-8") as f:
    event_data = f.read()

species_with_events = set(re.findall(r"s([A-Za-z0-9_]+)EventLearnset", event_data))

normal_entry_start_re = re.compile(r"\s*\[SPECIES_[A-Z0-9_]+\]\s*=\s*{")
normal_entry_end_re = re.compile(r"^\s*},\s*$", re.MULTILINE)

macro_re = re.compile(
    r'(#define\s+[A-Z0-9_]+_SPECIES_INFO[^\n]*\\\n(?:.*?\\\n)*?.*?[^\\\n]\n)',
    re.DOTALL
)

def insert_eventlearnset_in_text(entry_text, species):
    if f".eventLearnset = s{species}EventLearnset" in entry_text:
        return entry_text

    egg_re = re.compile(r'(\.eggMoveLearnset\s*=\s*s' + re.escape(species) + r'EggMoveLearnset\s*,)')
    teach_re = re.compile(r'(\.teachableLearnset\s*=\s*s' + re.escape(species) + r'TeachableLearnset\s*,)')

    if egg_re.search(entry_text):
        entry_text = egg_re.sub(lambda m: m.group(1) + f"\n        .eventLearnset = s{species}EventLearnset,", entry_text, 1)
    elif teach_re.search(entry_text):
        entry_text = teach_re.sub(lambda m: m.group(1) + f"\n        .eventLearnset = s{species}EventLearnset,", entry_text, 1)
    else:
        pos = entry_text.rfind("},")
        if pos != -1:
            entry_text = entry_text[:pos] + f"\n        .eventLearnset = s{species}EventLearnset," + entry_text[pos:]
        else:
            entry_text += f"\n        .eventLearnset = s{species}EventLearnset,"
    return entry_text

def process_normal_entries(content):
    output = []
    pos = 0
    while True:
        m_start = normal_entry_start_re.search(content, pos)
        if not m_start:
            output.append(content[pos:])
            break

        start_index = m_start.start()
        output.append(content[pos:start_index])

        m_end = normal_entry_end_re.search(content, m_start.end())
        if not m_end:
            output.append(content[m_start.start():])
            break

        end_index = m_end.end()
        entry_text = content[start_index:end_index]

        species_match = re.search(r"\.teachableLearnset\s*=\s*s([A-Za-z0-9_]+)TeachableLearnset", entry_text)
        if species_match:
            species = species_match.group(1)
            if species in species_with_events:
                entry_text = insert_eventlearnset_in_text(entry_text, species)

        output.append(entry_text)
        pos = end_index

    return "".join(output)

def insert_eventlearnset_in_macro(macro_text, species):
    if f".eventLearnset = s{species}EventLearnset" in macro_text:
        return macro_text

    egg_re = re.compile(r'(\.eggMoveLearnset\s*=\s*s' + re.escape(species) + r'EggMoveLearnset\s*,\s*\\?)')
    teach_re = re.compile(r'(\.teachableLearnset\s*=\s*s' + re.escape(species) + r'TeachableLearnset\s*,\s*\\?)')

    def build_event_line(match):
        original_line = match.group(1)
        # Count the total length of the original line (including backslash if present)
        line_length = len(original_line.rstrip())
        # Create the new line with same spacing
        new_line = f".eventLearnset = s{species}EventLearnset,"
        # Calculate needed padding to match original line length
        padding = max(0, line_length - len(new_line) - 2)
        new_line = "        " + new_line + (" " * padding) + " \\"
        return original_line + "\n" + new_line

    if egg_re.search(macro_text):
        macro_text = egg_re.sub(build_event_line, macro_text, 1)
    else:
        macro_text = teach_re.sub(build_event_line, macro_text, 1)

    return macro_text

def process_macros(content):
    def replacer(m):
        macro_text = m.group(1)

        species_match = re.search(r"\.teachableLearnset\s*=\s*s([A-Za-z0-9_]+)TeachableLearnset", macro_text)
        if not species_match:
            return macro_text

        species = species_match.group(1)
        if species not in species_with_events:
            return macro_text

        return insert_eventlearnset_in_macro(macro_text, species)

    return macro_re.sub(replacer, content)

def main():
    for path in species_info_paths:
        if not os.path.exists(path):
            continue

        with open(path, "r", encoding="utf-8") as f:
            content = f.read()

        content = process_normal_entries(content)
        content = process_macros(content)

        with open(path, "w", encoding="utf-8") as f:
            f.write(content)

if __name__ == "__main__":
    main()
