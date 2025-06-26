#pragma once

#include <ctime>
#include <variant>
#include <print>
#include <format>
#include <string>

struct TimeCounter
{
    std::variant<std::clock_t, double> clk;

    void begin() {
        clk = std::clock();
    }

    void end() {
        std::clock_t end = std::clock();
        clk = static_cast<double>(end - std::get<std::clock_t>(clk)) / CLOCKS_PER_SEC;
    }
};

template<>
struct std::formatter<TimeCounter> : std::formatter<std::string>
{
    auto format (TimeCounter tc, format_context& ctx) const
    {
        return formatter<string>::format(
            std::format("{:.3f}", std::get<double>(tc.clk)), ctx);
    };
};