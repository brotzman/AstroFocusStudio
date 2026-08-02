#!/usr/bin/env python3
"""Create a Microsoft .res file containing all images from an .ico plus one group icon (ID 101)."""
import struct
import sys
from pathlib import Path

def pad4(data: bytes) -> bytes:
    return data + b"\0" * ((-len(data)) & 3)

def ordinal(value: int) -> bytes:
    return struct.pack("<HH", 0xFFFF, value)

def record(resource_type: int, name: int, data: bytes, language: int = 0x0407) -> bytes:
    variable = ordinal(resource_type) + ordinal(name)
    header = pad4(struct.pack("<II", len(data), 0) + variable)
    header += struct.pack("<IHHII", 0, 0x1030, language, 0, 0)
    header = struct.pack("<II", len(data), len(header)) + header[8:]
    return pad4(header) + pad4(data)

def null_record() -> bytes:
    result = struct.pack("<II", 0, 32) + ordinal(0) + ordinal(0)
    result = pad4(result) + struct.pack("<IHHII", 0, 0, 0, 0, 0)
    if len(result) != 32:
        raise AssertionError("invalid null resource header")
    return result

def generate(ico_path: Path, output_path: Path, group_id: int = 101) -> None:
    source = ico_path.read_bytes()
    reserved, icon_type, count = struct.unpack_from("<HHH", source, 0)
    if reserved != 0 or icon_type != 1 or count < 1:
        raise ValueError(f"{ico_path} is not a valid Windows icon")
    entries = []
    for index in range(count):
        entry = struct.unpack_from("<BBBBHHII", source, 6 + index * 16)
        if entry[7] + entry[6] > len(source):
            raise ValueError("icon image points outside the file")
        entries.append(entry)
    output = bytearray(null_record())
    for resource_id, entry in enumerate(entries, 1):
        output += record(3, resource_id, source[entry[7] : entry[7] + entry[6]])
    group = bytearray(struct.pack("<HHH", 0, 1, count))
    for resource_id, entry in enumerate(entries, 1):
        group += struct.pack("<BBBBHHIH", *entry[:7], resource_id)
    output += record(14, group_id, bytes(group))
    output_path.write_bytes(output)

if __name__ == "__main__":
    if len(sys.argv) not in (3, 4):
        raise SystemExit("usage: generate_icon_res.py icon.ico app.res [group_id]")
    generate(Path(sys.argv[1]), Path(sys.argv[2]), int(sys.argv[3]) if len(sys.argv) == 4 else 101)
