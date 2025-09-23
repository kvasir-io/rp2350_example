#pragma once
#include "HWConfig.hpp"
///

#include "kvasir/Util/StaticString.hpp"

#include <cmake_git_version/version.hpp>
#include <kvasir/Util/FaultHandler.hpp>
#include <kvasir/Util/StackProtector.hpp>

using Clock          = HW::SystickClock;
using StackProtector = Kvasir::StackProtector<>;
using FaultHandler   = Kvasir::Fault::Handler<HW::Fault_CleanUpAction>;

struct USBConfig {
    static constexpr auto ManufacturerString = "Dominic";
    static constexpr auto ProductString      = CMakeGitVersion::Project::Name;
    static constexpr auto SerialNumberString = []() {
        Kvasir::StaticString<16> s{"test"};
        return s;
    };

    static constexpr auto ProductVersionBCD = 0x0100;
    static constexpr auto VendorID          = 0x2e8a;
    static constexpr auto ProductID         = 0x000a;
};

using USB = Kvasir::USB::USB_CDC_ACM<Clock, USBConfig>;

using Startup = Kvasir::Startup::Startup<HW::ClockSettings,
                                         Clock,
                                         HW::ComBackend,
                                         FaultHandler,
                                         StackProtector,
                                         USB,
                                         HW::PinConfig>;
