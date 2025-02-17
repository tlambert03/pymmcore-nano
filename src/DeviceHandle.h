#ifndef DEVICEHANDLE_H
#define DEVICEHANDLE_H

#include "MMCore.h"
#include <string>
#include <utility>
#include <vector>

// ------------------------------------------------------------------
// PropertyHandle
// ------------------------------------------------------------------

class PropertyHandle {
  protected:
    CMMCore *core_;
    std::string device_label_;
    std::string property_name_;

  public:
    PropertyHandle(CMMCore *core, const std::string &deviceLabel,
                   const std::string &propertyName);
    virtual ~PropertyHandle();

    const std::string &getDeviceLabel() const { return device_label_; }
    const std::string &getName() const { return property_name_; }

    std::string getValue() noexcept(false);
    void setValue(const char *propValue) noexcept(false);
    void setValue(const bool propValue) noexcept(false);
    void setValue(const long propValue) noexcept(false);
    void setValue(const float propValue) noexcept(false);
    void setValue(const double propValue) noexcept(false);
    std::vector<std::string> getAllowedValues() noexcept(false);
    bool isReadOnly() noexcept(false);
    bool isPreInit() noexcept(false);
    bool isSequenceable() noexcept(false);
    bool hasLimits() noexcept(false);
    double getLowerLimit() noexcept(false);
    double getUpperLimit() noexcept(false);
    MM::PropertyType getType() noexcept(false);
    void startSequence() noexcept(false);
    void stopSequence() noexcept(false);
    long getSequenceMaxLength() noexcept(false);
    void loadSequence(std::vector<std::string> eventSequence) noexcept(false);
};

// ------------------------------------------------------------------
// DeviceHandle
// ------------------------------------------------------------------
class DeviceHandle {
  protected:
    CMMCore *core_;
    std::string label_;

  public:
    DeviceHandle(CMMCore *core, const std::string &label);
    virtual ~DeviceHandle();

    const std::string &getLabel() const { return label_; }

    MM::DeviceType getType() noexcept(false);
    std::string getLibrary() noexcept(false);
    std::string getName() noexcept(false);
    std::string getDescription() noexcept(false);
    std::vector<std::string> getPropertyNames() noexcept(false);
    PropertyHandle getPropertyObject(const std::string &propertyName) noexcept(false);
    std::vector<PropertyHandle> getPropertyObjects() noexcept(false);
    bool hasProperty(const char *propName) noexcept(false);
    bool isBusy() noexcept(false);
    void await() noexcept(false);
    double getDelayMs() noexcept(false);
    void setDelayMs(double delayMs) noexcept(false);
    bool usesDelay() noexcept(false);
};

// ------------------------------------------------------------------
// XYStageDeviceHandle
// ------------------------------------------------------------------
class XYStageDeviceHandle : public DeviceHandle {
  public:
    XYStageDeviceHandle(CMMCore *core, const std::string &label);

    // Set the absolute XY position.
    void setPosition(double x, double y);

    // Get the current XY position.
    std::pair<double, double> getPosition();

    // Move relative to the current position.
    void setRelativePosition(double dx, double dy);

    // Get individual coordinates.
    double getXPosition();
    double getYPosition();

    // Stop motion.
    void stop();

    // Home the stage.
    void home();

    // Set the origin.
    void setOriginXY();
    void setOriginX();
    void setOriginY();

    // Set the adapter origin.
    void setAdapterOriginXY(double newXUm, double newYUm);

    // Sequence operations.
    bool isSequenceable();
    void startSequence();
    void stopSequence();
    long getSequenceMaxLength();
    void loadSequence(const std::vector<double> &xSequence,
                      const std::vector<double> &ySequence);
};

class CameraDeviceHandle : public DeviceHandle {
  public:
    CameraDeviceHandle(CMMCore *core, const std::string &label);

    // Set the exposure time.
    void setExposure(double exposure);
    // Get the exposure time.
    double getExposure();
};

#endif // DEVICEHANDLE_H