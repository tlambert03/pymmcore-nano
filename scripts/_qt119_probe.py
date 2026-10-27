"""Reproduce micro-manager/pymmcore#119: import Qt (which adds its Qt/bin, containing
msvcp140.dll, to the DLL search path) *before* pymmcore, then construct CMMCore."""
import subprocess
import sys

CASES = {
    "pymmcore after PyQt5 (QApplication)": (
        "from PyQt5.QtWidgets import QApplication; app = QApplication([]); "
        "import {m}; c = {m}.CMMCore(); print('ok', {m}.__version__)"
    ),
    "pymmcore after PyQt6 (QApplication)": (
        "from PyQt6.QtWidgets import QApplication; app = QApplication([]); "
        "import {m}; c = {m}.CMMCore(); print('ok', {m}.__version__)"
    ),
    "issue 119 script (add_dll_directory PyQt5/Qt5/bin)": (
        "import os, PyQt5; d = os.path.join(os.path.dirname(PyQt5.__file__), 'Qt5', 'bin'); "
        "print('dll dir', d, os.path.exists(os.path.join(d, 'msvcp140.dll'))); os.add_dll_directory(d); "
        "import {m}; c = {m}.CMMCore(); print('ok', {m}.__version__)"
    ),
    "PyQt5 first, then load DemoCamera + snap (adapters use the *system* runtime)": (
        "from PyQt5.QtWidgets import QApplication; app = QApplication([]); "
        "import {m}; from mm_test_adapters import device_adapter_path; c = {m}.CMMCore(); "
        "c.setDeviceAdapterSearchPaths([str(device_adapter_path())]); "
        "c.loadDevice('Camera', 'DemoCamera', 'DCam'); c.initializeAllDevices(); c.setCameraDevice('Camera'); "
        "c.snapImage(); print('ok snap', c.getImage().shape); c.unloadAllDevices()"
    ),
    "PyQt6 first, then load DemoCamera + snap": (
        "from PyQt6.QtWidgets import QApplication; app = QApplication([]); "
        "import {m}; from mm_test_adapters import device_adapter_path; c = {m}.CMMCore(); "
        "c.setDeviceAdapterSearchPaths([str(device_adapter_path())]); "
        "c.loadDevice('Camera', 'DemoCamera', 'DCam'); c.initializeAllDevices(); c.setCameraDevice('Camera'); "
        "c.snapImage(); print('ok snap', c.getImage().shape); c.unloadAllDevices()"
    ),
    "ctypes-preload system runtimes (pymmcore-gui style), then PyQt5, then DemoCamera + snap": (
        "import ctypes, contextlib; "
        "[contextlib.suppress(OSError).__enter__() or ctypes.WinDLL(d) for d in ('concrt140','msvcp140','msvcp140_1','msvcp140_2','vcruntime140','vcruntime140_1')]; "
        "from PyQt5.QtWidgets import QApplication; app = QApplication([]); "
        "import {m}; from mm_test_adapters import device_adapter_path; c = {m}.CMMCore(); "
        "c.setDeviceAdapterSearchPaths([str(device_adapter_path())]); "
        "c.loadDevice('Camera', 'DemoCamera', 'DCam'); c.initializeAllDevices(); c.setCameraDevice('Camera'); "
        "c.snapImage(); print('ok snap', c.getImage().shape); c.unloadAllDevices()"
    ),
    "pymmcore BEFORE PyQt5 (control)": (
        "import {m}; c = {m}.CMMCore(); from PyQt5.QtWidgets import QApplication; "
        "app = QApplication([]); print('ok', {m}.__version__)"
    ),
}

mod = sys.argv[1]
failed = 0
for name, code in CASES.items():
    r = subprocess.run([sys.executable, "-c", code.format(m=mod)], capture_output=True, text=True)
    status = "PASS" if r.returncode == 0 else f"FAIL (exit {r.returncode:#x})"
    print(f"[{mod}] {name}: {status}")
    print("   ", (r.stdout.strip() or r.stderr.strip())[-300:].replace("\n", "\n    "))
    failed += r.returncode != 0
print(f"[{mod}] {failed} of {len(CASES)} cases failed")
