#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

#include "MMCore.h"
#include "MMEventCallback.h"

namespace nb = nanobind;

using namespace nb::literals;

NB_MODULE(_pymmcore_nano, m) {
  // define module level attributes
  m.attr("DEVICE_INTERFACE_VERSION") = DEVICE_INTERFACE_VERSION;

  /////////////////// Enums ///////////////////

  nb::enum_<MM::DeviceType>(m, "DeviceType", nb::is_arithmetic())
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

  nb::enum_<MM::DeviceDetectionStatus>(m, "DeviceDetectionStatus", nb::is_arithmetic())
      .value("Misconfigured", MM::DeviceDetectionStatus::Misconfigured)
      .value("Unimplemented", MM::DeviceDetectionStatus::Unimplemented)
      .value("CanNotCommunicate", MM::DeviceDetectionStatus::CanNotCommunicate)
      .value("CanCommunicate", MM::DeviceDetectionStatus::CanCommunicate);

  nb::enum_<MM::PropertyType>(m, "PropertyType", nb::is_arithmetic())
      .value("Undef", MM::PropertyType::Undef)
      .value("String", MM::PropertyType::String)
      .value("Float", MM::PropertyType::Float)
      .value("Integer", MM::PropertyType::Integer);

  nb::enum_<MM::FocusDirection>(m, "FocusDirection", nb::is_arithmetic())
      .value("FocusDirectionUnknown", MM::FocusDirection::FocusDirectionUnknown)
      .value("FocusDirectionTowardSample", MM::FocusDirection::FocusDirectionTowardSample)
      .value("FocusDirectionAwayFromSample", MM::FocusDirection::FocusDirectionAwayFromSample);

  nb::enum_<MM::PortType>(m, "PortType", nb::is_arithmetic())
      .value("InvalidPort", MM::PortType::InvalidPort)
      .value("SerialPort", MM::PortType::SerialPort)
      .value("USBPort", MM::PortType::USBPort)
      .value("HIDPort", MM::PortType::HIDPort);

  nb::enum_<DeviceInitializationState>(m, "DeviceInitializationState", nb::is_arithmetic())
      .value("CoreIdle", DeviceInitializationState::Uninitialized)
      .value("CoreBusy", DeviceInitializationState::InitializedSuccessfully)
      .value("CoreError", DeviceInitializationState::InitializationFailed);

  //////////////////// Supporting classes ////////////////////

  nb::class_<Configuration>(m, "Configuration")
      .def(nb::init<>())  // Assuming it has a default constructor
      // Add any methods or properties for Configuration here
      ;

  nb::class_<MMEventCallback>(m, "MMEventCallback")
      .def(nb::init<>())  // Assuming it has a default constructor
      // Add any methods or properties for MMEventCallback here
      ;
  //////////////////// MMCore ////////////////////

  nb::class_<CMMCore>(m, "CMMCore")
      .def(nb::init<>())

      .def("loadSystemConfiguration", &CMMCore::loadSystemConfiguration, "fileName"_a)
      .def("saveSystemConfiguration", &CMMCore::saveSystemConfiguration, "fileName"_a)
      .def_static("enableFeature", &CMMCore::enableFeature, "name"_a, "enable"_a)
      .def_static("isFeatureEnabled", &CMMCore::isFeatureEnabled, "name"_a)
      .def("loadDevice", &CMMCore::loadDevice, "label"_a, "moduleName"_a, "deviceName"_a)
      .def("unloadDevice", &CMMCore::unloadDevice, "label"_a)
      .def("unloadAllDevices", &CMMCore::unloadAllDevices)
      .def("initializeAllDevices", &CMMCore::initializeAllDevices)
      .def("initializeDevice", &CMMCore::initializeDevice, "label"_a)
      .def("getDeviceInitializationState", &CMMCore::getDeviceInitializationState, "label"_a)
      .def("reset", &CMMCore::reset)
      .def("unloadLibrary", &CMMCore::unloadLibrary, "moduleName"_a)
      .def("updateCoreProperties", &CMMCore::updateCoreProperties)
      .def("getCoreErrorText", &CMMCore::getCoreErrorText, "code"_a)
      .def("getVersionInfo", &CMMCore::getVersionInfo)
      .def("getAPIVersionInfo", &CMMCore::getAPIVersionInfo)
      .def("getSystemState", &CMMCore::getSystemState)
      .def("setSystemState", &CMMCore::setSystemState, "conf"_a)
      .def("getConfigState", &CMMCore::getConfigState, "group"_a, "config"_a)
      .def("getConfigGroupState", nb::overload_cast<const char*>(&CMMCore::getConfigGroupState),
           "group"_a)
      .def("saveSystemState", &CMMCore::saveSystemState, "fileName"_a)
      .def("loadSystemState", &CMMCore::loadSystemState, "fileName"_a)
      .def("registerCallback", &CMMCore::registerCallback, "cb"_a)
      .def("setPrimaryLogFile", &CMMCore::setPrimaryLogFile, "filename"_a, "truncate"_a = false)
      .def("getPrimaryLogFile", &CMMCore::getPrimaryLogFile)
      .def("logMessage", nb::overload_cast<const char*>(&CMMCore::logMessage), "msg"_a)
      .def("logMessage", nb::overload_cast<const char*, bool>(&CMMCore::logMessage), "msg"_a,
           "debugOnly"_a)

      .def("enableDebugLog", &CMMCore::enableDebugLog, "enable"_a)
      .def("debugLogEnabled", &CMMCore::debugLogEnabled)
      .def("enableStderrLog", &CMMCore::enableStderrLog, "enable"_a)
      .def("stderrLogEnabled", &CMMCore::stderrLogEnabled)
      .def("startSecondaryLogFile", &CMMCore::startSecondaryLogFile, "filename"_a, "enableDebug"_a,
           "truncate"_a = true, "synchronous"_a = false)
      .def("stopSecondaryLogFile", &CMMCore::stopSecondaryLogFile, "handle"_a)

      .def("getDeviceAdapterSearchPaths", &CMMCore::getDeviceAdapterSearchPaths)
      .def("setDeviceAdapterSearchPaths", &CMMCore::setDeviceAdapterSearchPaths, "paths"_a)
      .def("getDeviceAdapterNames", &CMMCore::getDeviceAdapterNames)
      .def("getAvailableDevices", &CMMCore::getAvailableDevices, "library"_a)
      .def("getAvailableDeviceDescriptions", &CMMCore::getAvailableDeviceDescriptions, "library"_a)
      .def("getAvailableDeviceTypes", &CMMCore::getAvailableDeviceTypes, "library"_a)
      .def("getLoadedDevices", &CMMCore::getLoadedDevices)
      .def("getLoadedDevicesOfType", &CMMCore::getLoadedDevicesOfType, "devType"_a)
      .def("getDeviceType", &CMMCore::getDeviceType, "label"_a)
      .def("getDeviceLibrary", &CMMCore::getDeviceLibrary, "label"_a)
      .def("getDeviceName", nb::overload_cast<const char*>(&CMMCore::getDeviceName), "label"_a)
      .def("getDeviceDescription", &CMMCore::getDeviceDescription, "label"_a)
      .def("getDevicePropertyNames", &CMMCore::getDevicePropertyNames, "label"_a)
      .def("hasProperty", &CMMCore::hasProperty, "label"_a, "propName"_a)
      .def("getProperty", &CMMCore::getProperty, "label"_a, "propName"_a)
      .def("setProperty",
           nb::overload_cast<const char*, const char*, const char*>(&CMMCore::setProperty),
           "label"_a, "propName"_a, "propValue"_a)
      .def("setProperty", nb::overload_cast<const char*, const char*, bool>(&CMMCore::setProperty),
           "label"_a, "propName"_a, "propValue"_a)
      .def("setProperty", nb::overload_cast<const char*, const char*, long>(&CMMCore::setProperty),
           "label"_a, "propName"_a, "propValue"_a)
      .def("setProperty",
           nb::overload_cast<const char*, const char*, float>(&CMMCore::setProperty), "label"_a,
           "propName"_a, "propValue"_a)
      .def("getAllowedPropertyValues", &CMMCore::getAllowedPropertyValues, "label"_a, "propName"_a)
      .def("isPropertyReadOnly", &CMMCore::isPropertyReadOnly, "label"_a, "propName"_a)
      .def("isPropertyPreInit", &CMMCore::isPropertyPreInit, "label"_a, "propName"_a)
      .def("isPropertySequenceable", &CMMCore::isPropertySequenceable, "label"_a, "propName"_a)
      .def("hasPropertyLimits", &CMMCore::hasPropertyLimits, "label"_a, "propName"_a)
      .def("getPropertyLowerLimit", &CMMCore::getPropertyLowerLimit, "label"_a, "propName"_a)
      .def("getPropertyUpperLimit", &CMMCore::getPropertyUpperLimit, "label"_a, "propName"_a)
      .def("getPropertyType", &CMMCore::getPropertyType, "label"_a, "propName"_a)
      .def("startPropertySequence", &CMMCore::startPropertySequence, "label"_a, "propName"_a)
      .def("stopPropertySequence", &CMMCore::stopPropertySequence, "label"_a, "propName"_a)
      .def("getPropertySequenceMaxLength", &CMMCore::getPropertySequenceMaxLength, "label"_a,
           "propName"_a)
      .def("loadPropertySequence", &CMMCore::loadPropertySequence, "label"_a, "propName"_a,
           "eventSequence"_a)
      .def("deviceBusy", &CMMCore::deviceBusy, "label"_a)
      .def("waitForDevice", nb::overload_cast<const char*>(&CMMCore::waitForDevice), "label"_a)
      .def("waitForConfig", &CMMCore::waitForConfig, "group"_a, "configName"_a)
      .def("systemBusy", &CMMCore::systemBusy)
      .def("waitForSystem", &CMMCore::waitForSystem)
      .def("deviceTypeBusy", &CMMCore::deviceTypeBusy, "devType"_a)
      .def("waitForDeviceType", &CMMCore::waitForDeviceType, "devType"_a)
      .def("getDeviceDelayMs", &CMMCore::getDeviceDelayMs, "label"_a)
      .def("setDeviceDelayMs", &CMMCore::setDeviceDelayMs, "label"_a, "delayMs"_a)
      .def("usesDeviceDelay", &CMMCore::usesDeviceDelay, "label"_a)
      .def("setTimeoutMs", &CMMCore::setTimeoutMs, "timeoutMs"_a)
      .def("getTimeoutMs", &CMMCore::getTimeoutMs)
      .def("sleep", &CMMCore::sleep, "intervalMs"_a)

      //  Configuration getSystemStateCache() const;
      //  void updateSystemStateCache();
      //  std::string getPropertyFromCache(const char* deviceLabel,
      //        const char* propName) const noexcept(false);
      //  std::string getCurrentConfigFromCache(const char* groupName) noexcept(false);
      //  Configuration getConfigGroupStateFromCache(const char* group) noexcept(false);
      //  ///@}

      //  /** \name Configuration groups. */
      //  ///@{
      //  void defineConfig(const char* groupName, const char* configName) noexcept(false);
      //  void defineConfig(const char* groupName, const char* configName,
      //        const char* deviceLabel, const char* propName,
      //        const char* value) noexcept(false);
      //  void defineConfigGroup(const char* groupName) noexcept(false);
      //  void deleteConfigGroup(const char* groupName) noexcept(false);
      //  void renameConfigGroup(const char* oldGroupName,
      //        const char* newGroupName) noexcept(false);
      //  bool isGroupDefined(const char* groupName);
      //  bool isConfigDefined(const char* groupName, const char* configName);
      //  void setConfig(const char* groupName, const char* configName) noexcept(false);
      //  void deleteConfig(const char* groupName, const char* configName) noexcept(false);
      //  void deleteConfig(const char* groupName, const char* configName,
      //        const char* deviceLabel, const char* propName) noexcept(false);
      //  void renameConfig(const char* groupName, const char* oldConfigName,
      //        const char* newConfigName) noexcept(false);
      //  std::vector<std::string> getAvailableConfigGroups() const;
      //  std::vector<std::string> getAvailableConfigs(const char* configGroup) const;
      //  std::string getCurrentConfig(const char* groupName) noexcept(false);
      //  Configuration getConfigData(const char* configGroup,
      //        const char* configName) noexcept(false);
      //  ///@}

      .def("getCameraDevice", &CMMCore::getCameraDevice)
      .def("getShutterDevice", &CMMCore::getShutterDevice)
      .def("getFocusDevice", &CMMCore::getFocusDevice)
      .def("getXYStageDevice", &CMMCore::getXYStageDevice)
      .def("getAutoFocusDevice", &CMMCore::getAutoFocusDevice)
      .def("getImageProcessorDevice", &CMMCore::getImageProcessorDevice)
      .def("getSLMDevice", &CMMCore::getSLMDevice)
      .def("getGalvoDevice", &CMMCore::getGalvoDevice)
      .def("getChannelGroup", &CMMCore::getChannelGroup)
      .def("setCameraDevice", &CMMCore::setCameraDevice, "cameraLabel"_a)
      .def("setShutterDevice", &CMMCore::setShutterDevice, "shutterLabel"_a)
      .def("setFocusDevice", &CMMCore::setFocusDevice, "focusLabel"_a)
      .def("setXYStageDevice", &CMMCore::setXYStageDevice, "xyStageLabel"_a)
      .def("setAutoFocusDevice", &CMMCore::setAutoFocusDevice, "focusLabel"_a)
      .def("setImageProcessorDevice", &CMMCore::setImageProcessorDevice, "procLabel"_a)
      .def("setSLMDevice", &CMMCore::setSLMDevice, "slmLabel"_a)
      .def("setGalvoDevice", &CMMCore::setGalvoDevice, "galvoLabel"_a)
      .def("setChannelGroup", &CMMCore::setChannelGroup, "channelGroup"_a)

      .def("getSystemStateCache", &CMMCore::getSystemStateCache)
      .def("updateSystemStateCache", &CMMCore::updateSystemStateCache)
      .def("getPropertyFromCache", &CMMCore::getPropertyFromCache, "deviceLabel"_a, "propName"_a)
      .def("getCurrentConfigFromCache", &CMMCore::getCurrentConfigFromCache, "groupName"_a)
      .def("getConfigGroupStateFromCache", &CMMCore::getConfigGroupStateFromCache, "group"_a)

      .def("defineConfig", nb::overload_cast<const char*, const char*>(&CMMCore::defineConfig),
           "groupName"_a, "configName"_a)
      .def("defineConfig",
           nb::overload_cast<const char*, const char*, const char*, const char*, const char*>(
               &CMMCore::defineConfig),
           "groupName"_a, "configName"_a, "deviceLabel"_a, "propName"_a, "value"_a)
      .def("defineConfigGroup", &CMMCore::defineConfigGroup, "groupName"_a)
      .def("deleteConfigGroup", &CMMCore::deleteConfigGroup, "groupName"_a)
      .def("renameConfigGroup", &CMMCore::renameConfigGroup, "oldGroupName"_a, "newGroupName"_a)
      .def("isGroupDefined", &CMMCore::isGroupDefined, "groupName"_a)
      .def("isConfigDefined", &CMMCore::isConfigDefined, "groupName"_a, "configName"_a)
      .def("setConfig", &CMMCore::setConfig, "groupName"_a, "configName"_a)

      .def("deleteConfig", nb::overload_cast<const char*, const char*>(&CMMCore::deleteConfig),
           "groupName"_a, "configName"_a)
      .def("deleteConfig",
           nb::overload_cast<const char*, const char*, const char*, const char*>(
               &CMMCore::deleteConfig),
           "groupName"_a, "configName"_a, "deviceLabel"_a, "propName"_a)

      .def("renameConfig", &CMMCore::renameConfig, "groupName"_a, "oldConfigName"_a,
           "newConfigName"_a)
      .def("getAvailableConfigGroups", &CMMCore::getAvailableConfigGroups)
      .def("getAvailableConfigs", &CMMCore::getAvailableConfigs, "configGroup"_a)
      .def("getCurrentConfig", &CMMCore::getCurrentConfig, "groupName"_a)
      .def("getConfigData", &CMMCore::getConfigData, "configGroup"_a, "configName"_a)

      .def("getCurrentPixelSizeConfig", nb::overload_cast<>(&CMMCore::getCurrentPixelSizeConfig))
      .def("getCurrentPixelSizeConfig",
           nb::overload_cast<bool>(&CMMCore::getCurrentPixelSizeConfig), "cached"_a)
      .def("getPixelSizeUm", nb::overload_cast<>(&CMMCore::getPixelSizeUm))
      .def("getPixelSizeUm", nb::overload_cast<bool>(&CMMCore::getPixelSizeUm), "cached"_a)
      .def("getPixelSizeUmByID", &CMMCore::getPixelSizeUmByID, "resolutionID"_a)
      .def("getPixelSizeAffine", nb::overload_cast<>(&CMMCore::getPixelSizeAffine))
      .def("getPixelSizeAffine", nb::overload_cast<bool>(&CMMCore::getPixelSizeAffine), "cached"_a)
      .def("getPixelSizeAffineByID", &CMMCore::getPixelSizeAffineByID, "resolutionID"_a)
      .def("getMagnificationFactor", &CMMCore::getMagnificationFactor)
      .def("setPixelSizeUm", &CMMCore::setPixelSizeUm, "resolutionID"_a, "pixSize"_a)
      .def("setPixelSizeAffine", &CMMCore::setPixelSizeAffine, "resolutionID"_a, "affine"_a)
      .def("definePixelSizeConfig",
           nb::overload_cast<const char*, const char*, const char*, const char*>(
               &CMMCore::definePixelSizeConfig),
           "resolutionID"_a, "deviceLabel"_a, "propName"_a, "value"_a)
      .def("definePixelSizeConfig",
           nb::overload_cast<const char*>(&CMMCore::definePixelSizeConfig), "resolutionID"_a)
      .def("getAvailablePixelSizeConfigs", &CMMCore::getAvailablePixelSizeConfigs)
      .def("isPixelSizeConfigDefined", &CMMCore::isPixelSizeConfigDefined, "resolutionID"_a)
      .def("setPixelSizeConfig", &CMMCore::setPixelSizeConfig, "resolutionID"_a)
      .def("renamePixelSizeConfig", &CMMCore::renamePixelSizeConfig, "oldConfigName"_a,
           "newConfigName"_a)
      .def("deletePixelSizeConfig", &CMMCore::deletePixelSizeConfig, "configName"_a)
      .def("getPixelSizeConfigData", &CMMCore::getPixelSizeConfigData, "configName"_a)

      //
      ;

  m.doc() = "This is a \"hello world\" example with nanobind";
  m.def("add", [](int a, int b) { return a + b; }, "a"_a, "b"_a);
}