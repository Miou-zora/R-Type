#pragma once

#include <chrono>
#include <functional>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>

#include "NetworkMessage.hpp"

namespace rtype::network {
class IntervalTimer {
public:
    /**
     * @brief Construct a new Interval Timer object
     * @param io boost::asio::io_context& The io context to use
     * @param callback std::function<void()> The callback to call on each interval
     * @param interval_ms int The interval in milliseconds
     */
    IntervalTimer(boost::asio::io_context& io, std::function<void()> callback, std::chrono::microseconds intervalNs)
        : m_io(io)
        , m_callback(callback)
        , m_intervalNs(intervalNs)
        , m_timer(io)
    {
    }

    /**
     * @brief Start the timer
     */
    void start()
    {
        m_lastTime = std::chrono::high_resolution_clock::now();
        m_timer.expires_from_now(std::chrono::microseconds(0));
        m_timer.async_wait(boost::bind(&IntervalTimer::onTimer, this, boost::asio::placeholders::error));
    }

private:
    /**
     * @brief Run newt action after the interval
     * @param error boost::system::error_code& The error code
     * @return void
     */
    void startAfter(std::chrono::microseconds time)
    {
        m_timer.expires_from_now(time);
        m_timer.async_wait(boost::bind(&IntervalTimer::onTimer, this, boost::asio::placeholders::error));
    }

    /**
     * @brief Callback called on each interval. This is a wrapper to handle boost::asio error codes
     */
    void onTimer(const boost::system::error_code& error)
    {
        if (!error) {

            m_lastTime = std::chrono::high_resolution_clock::now();
            m_callback();
            auto now = std::chrono::high_resolution_clock::now();
            auto elapsed = now - m_lastTime;
            auto remaining = m_intervalNs - elapsed;
            if (remaining.count() < 0) {
                std::cerr << "IntervalTimer error: can't keep up ! (last tick was too long, diff=" << remaining.count() << "ns)" << std::endl;
                remaining = std::chrono::microseconds(0);
            }
            startAfter(std::chrono::duration_cast<std::chrono::microseconds>(remaining));
        } else {
            std::cerr << "IntervalTimer error: " << error.message() << std::endl;
        }
    }

    boost::asio::io_context& m_io;
    std::function<void()> m_callback;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTime;
    std::chrono::microseconds m_intervalNs;
    boost::asio::steady_timer m_timer;
};
}
