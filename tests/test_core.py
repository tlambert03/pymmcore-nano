import enum
import pymmcore_nano as pmn

mm = [
    "/Users/talley/Library/Application Support/pymmcore-plus/mm/Micro-Manager-80d5ac1"
]


def test_add():
    assert pmn.add(1, 2) == 3


def test_enums():
    assert pmn.DeviceType.CameraDevice == 2
    assert isinstance(pmn.DeviceType.CameraDevice, enum.IntEnum)
    assert pmn.DeviceDetectionStatus.Unimplemented == -2
    assert isinstance(pmn.DeviceDetectionStatus.Unimplemented, enum.IntEnum)

    mmc = pmn.CMMCore()
    assert mmc.getVersionInfo().startswith("MMCore version")
    assert mmc.getLoadedDevices() == ["Core"]
    mmc.setDeviceAdapterSearchPaths(mm)
    mmc.loadSystemConfiguration(mm[0] + "/MMConfig_demo.cfg")
    assert "Camera" in mmc.getLoadedDevices()

    print(mmc.getConfigState("Channel", "DAPI"))
