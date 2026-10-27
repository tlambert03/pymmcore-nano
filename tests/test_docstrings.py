from __future__ import annotations

import re

import pymmcore_nano as pmn


def test_cmmcore_docstrings() -> None:
    """MMCore.cpp docs are attached, and their Args match the python signature."""
    sigs = [
        (sig, doc)
        for name in dir(pmn.CMMCore)
        for sig, doc, _ in getattr(getattr(pmn.CMMCore, name), "__nb_signature__", ())
    ]
    documented = [(sig, doc) for sig, doc in sigs if doc]
    # a drop here may mean binding arg names drifted from MMCore.h, or that a
    # non-autodoc method (e.g. def_prop_ro) was chained into the CMMCore binding
    assert len(documented) > 0.95 * len(sigs)
    for sig, doc in documented:
        assert not re.search(r"^\s*[@\\]\w+", doc, re.M), f"doxygen tag left in {sig}"
        args = re.search(r"^Args:\n((?:    .*\n?)+)", doc, re.M)
        for arg in re.findall(r"^    (\w+):", args[1] if args else "", re.M):
            assert re.search(rf"\b{arg}\s*[:=]", sig), f"{arg!r} not in {sig}"
