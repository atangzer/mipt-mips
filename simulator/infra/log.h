/**
 * log.h - Header of log class
 * includes 2 methods to show warrnings and errors
 * @author Pavel Kryukov
 * Copyright 2017 MIPT-MIPS team
 */

#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <ostream>

class LogOstream
{
public:
    explicit LogOstream(std::ostream& _out) : stream(_out) { }

    void enable() noexcept  { is_enabled = true;  }
    void disable() noexcept { is_enabled = false; }
    bool enabled() const noexcept { return is_enabled; }

    LogOstream& operator<<(std::ostream& (*F)(std::ostream&)) {
        if ( is_enabled)
            F(stream);
        return *this;
    }

    template<typename T>
    LogOstream& operator<<(const T& v) {
        if ( is_enabled)
            stream << v;

        return *this;
    }

    template<size_t N> // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays, modernize-avoid-c-arrays, hicpp-avoid-c-arrays)
    LogOstream& operator<<(const char (&array)[N]) {
        return *this << static_cast<const char*>( array);
    }

private:
    bool is_enabled = false;
    std::ostream& stream;
};

class Log
{
public:
    mutable LogOstream sout;
    mutable LogOstream serr;

    Log() : sout( std::cout), serr( std::cerr) { }

    // Rule of five
    virtual ~Log() = default;
    Log( const Log&) = delete;
    Log( Log&&) = delete;
    Log& operator=( const Log&) = delete;
    Log& operator=( Log&&) = delete;
};

#endif /* LOG_H */

