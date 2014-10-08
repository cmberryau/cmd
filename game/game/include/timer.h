/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: timer.h
 * Date: 10th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry
 * Description: timer calss, simple game timer.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef TIMER_H
#define TIMER_H

// libraries

#include <nds.h>
#include <stdio.h>
#include <time.h>

// defines
#define TIME_STRING_LENGTH 64

// this struct holds a single time instance. to preform time checks, make a pointer of these 
// structs localy, then call the get_time function to get the current time of the timer, 
typedef struct
{
	int ticks;
	int useconds;
	int seconds;
	int minutes;
	int hours;
} time_set_t;

typedef time_set_t * time_set_t_ptr;

// timer class

class timer_c
{
	private:
		unsigned int ms;	// system ms

		int start_ticks;	// start time		
		int paused_ticks;	// ticks from when the timer was paused
		
		bool running;	// timer is running
		bool paused;	// timer is paused
		
		timer_c * next; // can point to another timer for lists
		
		time_set_t time; // time the timer is holding

		char time_string[TIME_STRING_LENGTH]; // String used to store the time
	
		time_t start_time;	// time started
		time_t end_time;	// time finished

	public:
		void init();					// setup variables
		void start( time_t new_start ); // start the timer
		void pause();					// pause the timer
		void unpause();					// unpause the timer
		void stop();					// stop the timer

		time_t get_ticks();		// get the ticks passed
		void tick();			// make time pass

		bool is_running();		// check to see if the timer is running
		bool is_paused();		// check to see if the timer is paused

		void incre_ms();	// increment the ms		
		void reset_ms();	// reset the ms count
		u64 get_ms();		// get the ms since timer start

		timer_c * get_next();	// get the next timer if in a list
		
		char * get_time_string();	// get a formated string of the timer
		time_set_t_ptr get_time();	// returns pointer to this timer's time values.
};

// pointer
typedef timer_c * timer_c_ptr;

#endif

// end of file
