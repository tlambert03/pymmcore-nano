#include "DeviceHandle.h"

// ------------------------------------------------------------------
// PropertyHandle
// ------------------------------------------------------------------
PropertyHandle::PropertyHandle(CMMCore *core, const std::string &deviceLabel,
                               const std::string &propertyName)
    : core_(core), device_label_(deviceLabel), property_name_(propertyName) {}

PropertyHandle::~PropertyHandle() {}

std::string PropertyHandle::getValue() {
    return core_->getProperty(device_label_.c_str(), property_name_.c_str());
}

void PropertyHandle::setValue(const char *propValue) {
    core_->setProperty(device_label_.c_str(), property_name_.c_str(), propValue);
}

void PropertyHandle::setValue(const bool propValue) {
    core_->setProperty(device_label_.c_str(), property_name_.c_str(), propValue);
}

void PropertyHandle::setValue(const long propValue) {
    core_->setProperty(device_label_.c_str(), property_name_.c_str(), propValue);
}

void PropertyHandle::setValue(const float propValue) {
    core_->setProperty(device_label_.c_str(), property_name_.c_str(), propValue);
}

void PropertyHandle::setValue(const double propValue) {
    core_->setProperty(device_label_.c_str(), property_name_.c_str(), propValue);
}

std::vector<std::string> PropertyHandle::getAllowedValues() {
    return core_->getAllowedPropertyValues(device_label_.c_str(), property_name_.c_str());
}

bool PropertyHandle::isReadOnly() {
    return core_->isPropertyReadOnly(device_label_.c_str(), property_name_.c_str());
}

bool PropertyHandle::isPreInit() {
    return core_->isPropertyPreInit(device_label_.c_str(), property_name_.c_str());
}

bool PropertyHandle::isSequenceable() {
    return core_->isPropertySequenceable(device_label_.c_str(), property_name_.c_str());
}

bool PropertyHandle::hasLimits() {
    return core_->hasPropertyLimits(device_label_.c_str(), property_name_.c_str());
}

double PropertyHandle::getLowerLimit() {
    return core_->getPropertyLowerLimit(device_label_.c_str(), property_name_.c_str());
}

double PropertyHandle::getUpperLimit() {
    return core_->getPropertyUpperLimit(device_label_.c_str(), property_name_.c_str());
}

MM::PropertyType PropertyHandle::getType() {
    return core_->getPropertyType(device_label_.c_str(), property_name_.c_str());
}

void PropertyHandle::startSequence() {
    core_->startPropertySequence(device_label_.c_str(), property_name_.c_str());
}

void PropertyHandle::stopSequence() {
    core_->stopPropertySequence(device_label_.c_str(), property_name_.c_str());
}

long PropertyHandle::getSequenceMaxLength() {
    return core_->getPropertySequenceMaxLength(device_label_.c_str(), property_name_.c_str());
}

void PropertyHandle::loadSequence(std::vector<std::string> eventSequence) {
    core_->loadPropertySequence(device_label_.c_str(), property_name_.c_str(), eventSequence);
}

// ------------------------------------------------------------------
// DeviceHandle
// ------------------------------------------------------------------
DeviceHandle::DeviceHandle(CMMCore *core, const std::string &label)
    : core_(core), label_(label) {}

DeviceHandle::~DeviceHandle() {}

MM::DeviceType DeviceHandle::getType() { return core_->getDeviceType(label_.c_str()); }

std::string DeviceHandle::getLibrary() { return core_->getDeviceLibrary(label_.c_str()); }

std::string DeviceHandle::getName() { return core_->getDeviceName(label_.c_str()); }

std::string DeviceHandle::getDescription() {
    return core_->getDeviceDescription(label_.c_str());
}

std::vector<std::string> DeviceHandle::getPropertyNames() {
    return core_->getDevicePropertyNames(label_.c_str());
}

bool DeviceHandle::hasProperty(const char *propName) {
    return core_->hasProperty(label_.c_str(), propName);
}

PropertyHandle DeviceHandle::getPropertyObject(const std::string &propertyName) {
    return PropertyHandle(core_, label_, propertyName);
}

std::vector<PropertyHandle> DeviceHandle::getPropertyObjects() {
    std::vector<PropertyHandle> properties;
    for (const auto &propertyName : core_->getDevicePropertyNames(label_.c_str())) {
        properties.push_back(PropertyHandle(core_, label_, propertyName));
    }
    return properties;
}

bool DeviceHandle::isBusy() { return core_->deviceBusy(label_.c_str()); }

void DeviceHandle::await() { core_->waitForDevice(label_.c_str()); }

double DeviceHandle::getDelayMs() { return core_->getDeviceDelayMs(label_.c_str()); }

void DeviceHandle::setDelayMs(double delayMs) {
    core_->setDeviceDelayMs(label_.c_str(), delayMs);
}

bool DeviceHandle::usesDelay() { return core_->usesDeviceDelay(label_.c_str()); }

// ------------------------------------------------------------------
// XYStageDeviceHandle
// ------------------------------------------------------------------
XYStageDeviceHandle::XYStageDeviceHandle(CMMCore *core, const std::string &label)
    : DeviceHandle(core, label) {}

void XYStageDeviceHandle::setPosition(double x, double y) {
    core_->setXYPosition(label_.c_str(), x, y);
}

std::pair<double, double> XYStageDeviceHandle::getPosition() {
    double x, y;
    core_->getXYPosition(label_.c_str(), x, y);
    return {x, y};
}

void XYStageDeviceHandle::setRelativePosition(double dx, double dy) {
    core_->setRelativeXYPosition(label_.c_str(), dx, dy);
}

double XYStageDeviceHandle::getXPosition() { return core_->getXPosition(label_.c_str()); }

double XYStageDeviceHandle::getYPosition() { return core_->getYPosition(label_.c_str()); }

void XYStageDeviceHandle::stop() { core_->stop(label_.c_str()); }

void XYStageDeviceHandle::home() { core_->home(label_.c_str()); }

void XYStageDeviceHandle::setOriginXY() { core_->setOriginXY(label_.c_str()); }

void XYStageDeviceHandle::setOriginX() { core_->setOriginX(label_.c_str()); }

void XYStageDeviceHandle::setOriginY() { core_->setOriginY(label_.c_str()); }

void XYStageDeviceHandle::setAdapterOriginXY(double newXUm, double newYUm) {
    core_->setAdapterOriginXY(label_.c_str(), newXUm, newYUm);
}

bool XYStageDeviceHandle::isSequenceable() {
    return core_->isXYStageSequenceable(label_.c_str());
}

void XYStageDeviceHandle::startSequence() { core_->startXYStageSequence(label_.c_str()); }

void XYStageDeviceHandle::stopSequence() { core_->stopXYStageSequence(label_.c_str()); }

long XYStageDeviceHandle::getSequenceMaxLength() {
    return core_->getXYStageSequenceMaxLength(label_.c_str());
}

void XYStageDeviceHandle::loadSequence(const std::vector<double> &xSequence,
                                       const std::vector<double> &ySequence) {
    core_->loadXYStageSequence(label_.c_str(), xSequence, ySequence);
}

// ------------------------------------------------------------------
// CameraDeviceHandle
// ------------------------------------------------------------------

CameraDeviceHandle::CameraDeviceHandle(CMMCore *core, const std::string &label)
    : DeviceHandle(core, label) {}

void CameraDeviceHandle::setExposure(double exposure) {
    core_->setExposure(label_.c_str(), exposure);
}

double CameraDeviceHandle::getExposure() { return core_->getExposure(label_.c_str()); }

// ------------------------------------------------------------------
