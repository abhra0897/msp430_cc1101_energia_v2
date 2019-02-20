#ifndef MACROS_h
#define MACROS_h

/******************************************************************************/
/* General utility macros                                                     */
/******************************************************************************/
// the following macro will stringize the passed parameter
// Example: STRINGIZE( hello ) ==> "hello"
#define STRINGIZE( s ) STRINGIZE_X( s )
#define STRINGIZE_X( s ) #s

// the following macro will concatenate to parameters into a single parameter
// or identifier
// Example: CONCATENATE( GOOD, BYE ) ==> GOODBYE
#define CONCATENATE( a, b ) CONCATENATE_X( a, b )
#define CONCATENATE_X( a, b ) a ## b

// the following macro will concatenate two items infixed with the middle item
// Eample: INFIX( ANOTHER, _, TOKEN ) ==> ANOTHER_TOKEN
#define INFIX( a, i, b ) CONCATENATE( CONCATENATE( a, i ), b )

// Alternate size INFIXs
#define INFIX4( a, b, c, d) CONCATENATE( INFIX( a, b, c), d)
#define INFIX5( a, b, c, d, e) INFIX (INFIX( a, b, c), d, e)

// Easier to put lines of code in a macro
#define st(x)      do { x } while (__LINE__ == -1)

// Bit value
#define BV(n)      (1 << (n))

// Software delay (clock cycles)
//#define delay(x) st(for(uint16_t __indx=0;__indx<(uint16_t)x*1000;__indx++);)

#endif
