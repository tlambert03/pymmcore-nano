import enum
from pathlib import Path
import pymmcore_nano as pmn

root = Path.home() / "Library/Application Support/pymmcore-plus/mm"
mm = next(root.glob("Micro-Manager-*"), None)
paths = [str(mm)] if mm else []


def test_enums():
    assert pmn.DeviceType.CameraDevice == 2
    assert isinstance(pmn.DeviceType.CameraDevice, enum.IntEnum)
    assert pmn.DeviceDetectionStatus.Unimplemented == -2
    assert isinstance(pmn.DeviceDetectionStatus.Unimplemented, enum.IntEnum)

    mmc = pmn.CMMCore()
    assert mmc.getVersionInfo().startswith("MMCore version")
    assert mmc.getLoadedDevices() == ["Core"]
    mmc.setDeviceAdapterSearchPaths(paths)

    if mm:
        mmc.loadSystemConfiguration(mm / "MMConfig_demo.cfg")
        assert "Camera" in mmc.getLoadedDevices()
        cfg = mmc.getConfigState("Channel", "DAPI")
        assert isinstance(cfg, pmn.Configuration)
