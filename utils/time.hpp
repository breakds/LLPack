#ifndef LLPACK_TIME_HPP
#define LLPACK_TIME_HPP

#include <sys/time.h>
#define TIMER_CLEAR(tvp) \
  ((tvp)->tv_sec = (tvp)->tv_usec = 0)

/*
 * Warning: The following one is not thread-safe
 * Do not use it in multi-threaded programs
 */
namespace timer {
  timeval t0, t1;

  // This is not a very accurate timer
  inline void tic() {
    gettimeofday( &t0, NULL );
  }
  inline time_t toc() {
    gettimeofday( &t1, NULL );
    return t1.tv_sec - t0.tv_sec;
  }
  inline double utoc() {
    gettimeofday( &t1, NULL );
    return static_cast<double>(t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec) * 1e-6;
  }
}

/*
 * This is the thread-safe version
 */
class TimeInterval {
private:
  timeval t0, t1;
public:
  TimeInterval() {
    TIMER_CLEAR( &t0 );
    TIMER_CLEAR( &t1 );
  }
  inline void tic() {
    gettimeofday( &t0, NULL );
  }
  inline time_t toc() {
    gettimeofday( &t1, NULL );
    return t1.tv_sec - t0.tv_sec;
  }
  inline double utoc() {
    gettimeofday( &t1, NULL );
    return static_cast<double>(t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec) * 1e-6;
  }
};

#endif
