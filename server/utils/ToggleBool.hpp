#pragma once

namespace rtype::utils {
class ToggleBool {
public:
    /**
     * @brief Construct a new Toggle Bool object
     * @param value Initial value
     */
    ToggleBool(bool value = false)
        : m_value(value)
    {
    }
    /**
     * @brief Destroy the Toggle Bool object
     */
    ~ToggleBool() = default;

    /**
     * @brief Copy constructor
     * @param other ToggleBool const& Other ToggleBool to copy
     */
    ToggleBool(const ToggleBool& other)
        : m_value(other.m_value)
    {
    }

    /**
     * @brief Copy assignment operator
     * @param other ToggleBool const& Other ToggleBool to copy
     */
    ToggleBool& operator=(bool value)
    {
        m_value = value;
        return *this;
    }

    /**
     * @brief Copy assignment operator
     * @param other ToggleBool const& Other ToggleBool to copy
     */
    ToggleBool& operator=(const ToggleBool& other)
    {
        m_value = other.m_value;
        return *this;
    }

    /**
     * @brief Move constructor
     * @param other ToggleBool&& Other ToggleBool to move
     */
    ToggleBool(ToggleBool&& other)
        : m_value(other.m_value)
    {
    }

    /**
     * @brief Move assignment operator
     * @param other ToggleBool&& Other ToggleBool to move
     */
    ToggleBool& operator=(ToggleBool&& other)
    {
        m_value = other.m_value;
        return *this;
    }

    /**
     * @brief Toggle the value
     * @return void
     */
    void toggle()
    {
        m_value = true;
    }

    /**
     * @brief Get the value and reset it to false
     * @return bool
     */
    bool get()
    {
        bool returnVal = m_value;
        m_value = false;
        return returnVal;
    }

private:
    bool m_value;
};
}