#include <nanobind/nanobind.h>

#include "MMCore.h"

namespace nb = nanobind;

using namespace nb::literals;

NB_MODULE(_pymmcore_nano, m) {
  // define module level attributes
  m.attr("DEVICE_INTERFACE_VERSION") = DEVICE_INTERFACE_VERSION;

  /////////////////// Enums ///////////////////

  nb::enum_<MM::DeviceType>(m, "DeviceType")
      .value("UnknownType", MM::DeviceType::UnknownType)
      .value("AnyType", MM::DeviceType::AnyType)
      .value("CameraDevice", MM::DeviceType::CameraDevice)
      .value("ShutterDevice", MM::DeviceType::ShutterDevice)
      .value("StateDevice", MM::DeviceType::StateDevice)
      .value("StageDevice", MM::DeviceType::StageDevice)
      .value("XYStageDevice", MM::DeviceType::XYStageDevice)
      .value("SerialDevice", MM::DeviceType::SerialDevice)
      .value("GenericDevice", MM::DeviceType::GenericDevice)
      .value("AutoFocusDevice", MM::DeviceType::AutoFocusDevice)
      .value("CoreDevice", MM::DeviceType::CoreDevice)
      .value("ImageProcessorDevice", MM::DeviceType::ImageProcessorDevice)
      .value("SignalIODevice", MM::DeviceType::SignalIODevice)
      .value("MagnifierDevice", MM::DeviceType::MagnifierDevice)
      .value("SLMDevice", MM::DeviceType::SLMDevice)
      .value("HubDevice", MM::DeviceType::HubDevice)
      .value("GalvoDevice", MM::DeviceType::GalvoDevice);

  nb::enum_<MM::DeviceDetectionStatus>(m, "DeviceDetectionStatus")
      .value("Misconfigured", MM::DeviceDetectionStatus::Misconfigured)
      .value("Unimplemented", MM::DeviceDetectionStatus::Unimplemented)
      .value("CanNotCommunicate", MM::DeviceDetectionStatus::CanNotCommunicate)
      .value("CanCommunicate", MM::DeviceDetectionStatus::CanCommunicate);

  nb::enum_<MM::PropertyType>(m, "PropertyType")
      .value("Undef", MM::PropertyType::Undef)
      .value("String", MM::PropertyType::String)
      .value("Float", MM::PropertyType::Float)
      .value("Integer", MM::PropertyType::Integer);

  nb::enum_<MM::FocusDirection>(m, "FocusDirection")
      .value("FocusDirectionUnknown", MM::FocusDirection::FocusDirectionUnknown)
      .value("FocusDirectionTowardSample", MM::FocusDirection::FocusDirectionTowardSample)
      .value("FocusDirectionAwayFromSample", MM::FocusDirection::FocusDirectionAwayFromSample);

  nb::enum_<MM::PortType>(m, "PortType")
      .value("InvalidPort", MM::PortType::InvalidPort)
      .value("SerialPort", MM::PortType::SerialPort)
      .value("USBPort", MM::PortType::USBPort)
      .value("HIDPort", MM::PortType::HIDPort);

  //////////////////// MMCore ////////////////////

  nb::class_<CMMCore>(m, "CMMCore")
      .def("getVersionInfo", &CMMCore::getVersionInfo)
      .def("getAPIVersion", &CMMCore::getAPIVersionInfo);

  m.doc() = "This is a \"hello world\" example with nanobind";
  m.def("add", [](int a, int b) { return a + b; }, "a"_a, "b"_a);
}