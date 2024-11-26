from pathlib import Path
import sys
import re

THROW_CMMERROR_RE = re.compile(r"throw\s*\(CMMError\)")


def patch_file(file_path: str) -> None:
    content = Path(file_path).read_text(encoding="utf-8")

    # Replace 'throw (CMMError)' with 'noexcept(false)'
    patched_content = THROW_CMMERROR_RE.sub("noexcept(false)", content)

    Path(file_path).write_text(patched_content, encoding="utf-8")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python patch_throw_to_noexcept.py <file_path>")
        sys.exit(1)
    patch_file(sys.argv[1])
