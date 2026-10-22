"""Check that long-running CMMCore methods release the GIL."""

from __future__ import annotations

import itertools
import sys
import threading
import time
from typing import TYPE_CHECKING

import pytest

if TYPE_CHECKING:
    from collections.abc import Callable
    from pathlib import Path

    import pymmcore_nano as pmn


def _releases_gil(
    func: Callable[[], object],
    setup: Callable[[], object] | None = None,
    attempts: int = 20,
) -> bool:
    """Return True if another Python thread got to run while `func` was executing.

    The switch interval is raised so that the interpreter never forces a thread
    switch on its own: the spinner thread below can only run if `func` releases
    the GIL.  (So this can't pass by accident, but it could fail if the spinner
    keeps losing the race to re-acquire the GIL... hence the `attempts`.)
    """
    ticks = 0
    done = threading.Event()

    def spin() -> None:
        nonlocal ticks
        while not done.is_set():
            ticks += 1
            time.sleep(1e-4)

    old_interval = sys.getswitchinterval()
    sys.setswitchinterval(100)
    thread = threading.Thread(target=spin, daemon=True)
    thread.start()
    try:
        for _ in range(attempts):
            if setup is not None:
                setup()
            # busy-wait (holding the GIL) so the spinner is done sleeping
            # and is blocked waiting for the GIL when `func` is called
            deadline = time.perf_counter() + 0.002
            while time.perf_counter() < deadline:
                pass
            before = ticks
            func()
            if ticks > before:
                return True
        return False
    finally:
        done.set()
        thread.join()
        sys.setswitchinterval(old_interval)


def test_load_system_configuration_releases_gil(
    core: pmn.CMMCore, demo_config: Path
) -> None:
    assert _releases_gil(lambda: core.loadSystemConfiguration(demo_config))


def test_unload_all_devices_releases_gil(core: pmn.CMMCore, demo_config: Path) -> None:
    assert _releases_gil(
        core.unloadAllDevices,
        setup=lambda: core.loadSystemConfiguration(demo_config),
    )


def test_set_primary_log_file_releases_gil(core: pmn.CMMCore, tmp_path: Path) -> None:
    # use a new file each time (re-setting the current file is a quick no-op)
    n = itertools.count()
    try:
        assert _releases_gil(
            lambda: core.setPrimaryLogFile(tmp_path / f"primary{next(n)}.log")
        )
    finally:
        core.setPrimaryLogFile("")


def test_start_secondary_log_file_releases_gil(
    core: pmn.CMMCore, tmp_path: Path
) -> None:
    handles: list[int] = []
    try:
        assert _releases_gil(
            lambda: handles.append(
                core.startSecondaryLogFile(tmp_path / "secondary.log", False)
            )
        )
    finally:
        for handle in handles:
            core.stopSecondaryLogFile(handle)


@pytest.mark.parametrize("attempt", range(3))
def test_snap_image_releases_gil(demo_core: pmn.CMMCore, attempt: int) -> None:
    # control: snapImage has always released the GIL
    assert _releases_gil(demo_core.snapImage)
