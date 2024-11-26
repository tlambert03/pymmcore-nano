import pymmcore_nano as pmn


def test_add():
    assert pmn.add(1, 2) == 3


def test_enums():
    assert pmn.DeviceType.CameraDevice.value == 2

    core = pmn.CMMCore()
    assert core.getVersionInfo().startswith("MMCore version")
