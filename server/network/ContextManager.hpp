#pragma once

#include <chrono>
#include <functional>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>

namespace rtype::network {
class ContextManager {
public:
    /**
     * @brief Get the instance of the singleton
     * @return ContextManager&
     */
    static ContextManager& getInstance()
    {
        static ContextManager instance;
        return instance;
    }

    /**
     * @brief Get the context object
     * @param name Name of the context
     * @return boost::asio::io_context&
     */
    boost::asio::io_context& getContext(const std::string& name)
    {
        if (m_contexts.find(name) == m_contexts.end())
            m_contexts[name] = std::make_shared<boost::asio::io_context>();
        return *m_contexts[name];
    }

    /**
     * @brief Run all contexts
     * @return void
     */
    void runAllContexts()
    {
        for (auto& context : m_contexts) {
            m_threads[context.first] = boost::thread(boost::bind(&boost::asio::io_context::run, context.second));
        }
    }

    /**
     * @brief Join all contexts
     */
    void joinAllContexts()
    {
        for (auto& thread : m_threads) {
            thread.second.join();
        }
    }

private:
    ContextManager() = default;
    ~ContextManager() = default;

    std::unordered_map<std::string, std::shared_ptr<boost::asio::io_context>> m_contexts;
    std::unordered_map<std::string, boost::thread> m_threads;
};
}
