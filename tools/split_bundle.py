#!/usr/bin/env python3
"""
Split codegen/code_bundle.txt into real files under code/inc and code/src.

Bundle format:
###### FILE: <relative_path> ######
<content>
###### END FILE ######
"""

from __future__ import annotations
import os
import sys
from pathlib import Path

START_PREFIX = "###### FILE: "
START_SUFFIX = " ######"
END_MARKER = "###### END FILE ######"

ALLOWED_PREFIXES = ("code/inc/", "code/src/")
ALLOWED_EXTS = (".h", ".c")


def fail(msg: str) -> None:
    print(f"ERROR: {msg}", file=sys.stderr)
    sys.exit(1)


def parse_bundle(bundle_text: str) -> list[tuple[str, str]]:
    lines = bundle_text.splitlines(keepends=True)
    i = 0
    out: list[tuple[str, str]] = []
    seen = set()

    while i < len(lines):
        line = lines[i].rstrip("\n")
        if not line.strip():
            i += 1
            continue

        if not (line.startswith(START_PREFIX) and line.endswith(START_SUFFIX)):
            fail(f"Invalid start marker at line {i+1}: {line!r}")

        rel_path = line[len(START_PREFIX):-len(START_SUFFIX)].strip()
        if not rel_path:
            fail(f"Empty path at line {i+1}")

        if not rel_path.startswith(ALLOWED_PREFIXES):
            fail(f"Disallowed path '{rel_path}' (must start with code/inc/ or code/src/)")

        if not rel_path.endswith(ALLOWED_EXTS):
            fail(f"Disallowed extension '{rel_path}' (must end with .h or .c)")

        if rel_path in seen:
            fail(f"Duplicate file path in bundle: {rel_path}")
        seen.add(rel_path)

        i += 1
        content_lines: list[str] = []
        while i < len(lines):
            if lines[i].rstrip("\n") == END_MARKER:
                break
            content_lines.append(lines[i])
            i += 1

        if i >= len(lines) or lines[i].rstrip("\n") != END_MARKER:
            fail(f"Missing END marker for '{rel_path}'")

        content = "".join(content_lines)
        if content.strip() == "":
            fail(f"Empty content for '{rel_path}'")

        out.append((rel_path, content))
        i += 1  # skip END marker

    if not out:
        fail("Bundle contains no files.")
    return out


def write_files(repo_root: Path, entries: list[tuple[str, str]]) -> None:
    for rel_path, content in entries:
        abs_path = repo_root / rel_path
        abs_path.parent.mkdir(parents=True, exist_ok=True)

        # Write exactly; use LF in bundle; OS will keep bytes as provided.
        abs_path.write_text(content, encoding="utf-8", newline="\n")


def main() -> None:
    repo_root = Path(os.environ.get("GITHUB_WORKSPACE", os.getcwd())).resolve()
    bundle_path = repo_root / "codegen" / "code_bundle.txt"

    if not bundle_path.exists():
        fail(f"Bundle file not found: {bundle_path}")

    bundle_text = bundle_path.read_text(encoding="utf-8")
    entries = parse_bundle(bundle_text)
    write_files(repo_root, entries)

    print(f"OK: wrote {len(entries)} files from bundle.")
    for p, _ in entries[:20]:
        print(f"- {p}")


if __name__ == "__main__":
    main()
