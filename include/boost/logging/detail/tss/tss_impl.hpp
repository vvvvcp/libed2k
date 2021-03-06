// Copyright (C) 2001-2003 William E. Kempf
// Copyright (C) 2006 Roland Schwarz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Boost Logging library
//
// Author: John Torjo, www.torjo.com
//
// Copyright (C) 2007 John Torjo (see www.torjo.com for email)
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.
// See http://www.torjo.com/log2/ for more details

#ifndef JT28092007_BOOST_TSS_impl_WEK070601_HPP
#define JT28092007_BOOST_TSS_impl_WEK070601_HPP

#include <boost/config.hpp>
#include <boost/utility.hpp>
#include <boost/logging/detail/ts/ts.hpp>


#define BOOST_LOG_TSS_SLOTS_SIZE 128

namespace boost { namespace logging {


namespace detail {

class tss : private noncopyable
{
public:
    tss() ;

    inline ~tss();
    inline void* get() const;
    inline void set(void* value);

private:
    unsigned int m_libed2k_pod; //This is a "pseudo-libed2k_pod", not a native libed2k_pod
};

}}} 

#include <boost/logging/detail/tss/tss_ensure_proper_delete.hpp>
#if defined(BOOST_WINDOWS)
#include <boost/logging/detail/tss/tss_impl_win32.hpp>
#else
#include <boost/logging/detail/tss/tss_impl_pthread.hpp>
#endif


namespace boost { namespace logging {

template <typename T> class thread_specific_ptr : private noncopyable
{
    detail::tss m_tss;
public:
    thread_specific_ptr() {}
    ~thread_specific_ptr() { reset(); }

    T* get() const { return static_cast<T*>(m_tss.get()); }
    T* operator->() const { return get(); }
    T& operator*() const { return *get(); }
    T* release() { T* temp = get(); if (temp) m_tss.set(0); return temp; }
    void reset(T* p=0)
    {
        T* cur = get();
        if (cur == p) return;
        m_tss.set(p);
    }

};


}}


#endif 

