#!/usr/bin/env python3

"""Adds Event Learnsets to SpeciesInfo"""

import os
import re

SPECIES_INFO_PATHS = [
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


with open("src/data/pokemon/event_learnsets.h", "r", encoding="utf-8") as f:
    EVENT_SPECIES = set(re.findall(r"s(\w+)EventLearnset", f.read()))


INSERT_PATTERN = re.compile(r'^([ \t]*)\.teachableLearnset(\s*)=(\s*)s(\w+)TeachableLearnset,([ \t]*\\?)\s*$', flags=re.MULTILINE,)
STALE_PATTERN = re.compile(r'^[ \t]*\.eventLearnset\s*=\s*s(\w+)EventLearnset,[ \t]*\\?[ \t]*\n?', flags=re.MULTILINE)


def strip_stale(match):
    species = match.group(1)
    if species in EVENT_SPECIES:
        return match.group(0)
    return ""


def insert_repl(match):
    indent, pre_eq, post_eq, species, suffix = match.groups()

    if species not in EVENT_SPECIES:
        return match.group(0)

    padded_pre_eq = pre_eq + (" " * 8)
    event_line = f"{indent}.eventLearnset{padded_pre_eq}={post_eq}s{species}EventLearnset,{suffix}"

    newline = match.string.find("\n", match.end())
    if newline != -1:
        next_line = match.string[newline + 1:].split("\n", 1)[0]
        if ".eventLearnset" in next_line and f"s{species}EventLearnset" in next_line:
            return match.group(0)

    return match.group(0) + "\n" + event_line


def process_file(path):
    if not os.path.exists(path):
        return

    with open(path, "r", encoding="utf-8") as f:
        original = f.read()

    text = STALE_PATTERN.sub(strip_stale, original)
    new_text = INSERT_PATTERN.sub(insert_repl, text)

    if new_text != original:
        with open(path, "w", encoding="utf-8") as f:
            f.write(new_text)
    else:
        os.utime(path, None)


def main():
    for path in SPECIES_INFO_PATHS:
        process_file(path)


if __name__ == "__main__":
    main()
