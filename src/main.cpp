#include "ApplicationConfig.hpp"
//

#include <cmake_git_version/version.hpp>
#include <kvasir/Util/StaticVector.hpp>

using namespace sc::literals;

using LedMetric = uc_log::Metric<int, "Led"_sc, "ON/OFF"_sc, "Global"_sc>;

int main() {
    UC_LOG_D("{}", CMakeGitVersion::FullVersion);

    auto next = Clock::time_point{};
    bool on   = false;

    while(true) {
        auto const now = Clock::now();
        if(now > next) {
            next += std::chrono::milliseconds{500};
            if(on) {
                apply(clear(HW::Pin::led{}));
                UC_LOG_D("Led: {}", LedMetric{on});
            } else {
                apply(set(HW::Pin::led{}));
                UC_LOG_D("Led: {}", LedMetric{on});
            }
            on = !on;

            if(USB::acm_connected) {
                std::string_view sv = "Hello World\n";
                USB::send(std::as_bytes(std::span{sv}));
            }
        }

        StackProtector::handler();
    }
}

KVASIR_START(Startup)
