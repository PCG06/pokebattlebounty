#!/usr/bin/env python3

"""Removes Level Up and Egg Learnsets from SpeciesInfo."""

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

PATTERN = re.compile(r'^[ \t]*\.(?:levelUpLearnset|eggMoveLearnset)\s*=\s*\w+,\s*\\?\s*$\n?', flags=re.MULTILINE)


def process_file(path):
    if not os.path.exists(path):
        return

    with open(path, "r", encoding="utf-8") as f:
        text = f.read()

    new_text = PATTERN.sub("", text)

    if new_text != text:
        with open(path, "w", encoding="utf-8") as f:
            f.write(new_text)
        print(f"Removed levelUpLearnset and EggLearnset in {path}")


def main():
    for path in SPECIES_INFO_PATHS:
        process_file(path)


if __name__ == "__main__":
    main()
