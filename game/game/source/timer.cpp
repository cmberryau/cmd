/*==================================================================================================
 * Cpp Nintendo DS Program Source File.
 * File Name: timer.cpp
 * Date: 8th of December, 2009.
 * Author(s): Patrick Randell, Christopher Berry
 * Description: timer class, see header file.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

// header file
#include "timer.h"

// functions

void timer_c::init(){
	start_ticks = 0;
	paused_ticks = 0;
	running = false;
	paused = false;
	
	next = NULL;
	
	time.ticks = 0;
	
	time.useconds = 0;
	time.seconds = 0;
	time.minutes = 0;
	time.hours = 0;
	
	// new
	
	ms = 0;
	start_time = 0;
	end_time = 0;
	
}

void timer_c::start( time_t new_start ){
	// start the timer
	running = true;
	// unpause if paused
	paused = false;
	/* Start the timer from 0 */
	start_time = new_start;
}

bool timer_c::is_running(){
	return running;
}

void timer_c::pause(){
	// see if the timer is running and not paused
	if ((running == true) && (paused == false))
	{
		// pause timer
		paused = true;
	}
}

void timer_c::unpause(){
	// see if the timer is paused
	if (paused == true)
	{
		// unpause
		paused = false;
		
		// reset the paused ticks
		paused_ticks = 0;
	}
}

bool timer_c::is_paused(){
	return paused;
}

time_t timer_c::get_ticks(){
	// see if timer is running
	if (running == true)
	{
		// see if timer is paused
		if (paused == true)
		{
			// give the paused ticks
			return paused_ticks;
		}
		else
		{
			return time.ticks;
		}
	}
	// timer is not running at all
	return NULL;
}

void timer_c::stop(){
	// stop the timer
	running = false;
	// unpause the timer
	paused = false;
	// restart everything
	this->init();
}

void timer_c::tick(){
	if ((running == true) && (paused == false))
	{
		time.ticks++; // this is eventually just going to overflow..
		time.useconds++;
		if (time.useconds == 60)
		{
			time.useconds = 0;
			time.seconds++;
		}
		if (time.seconds == 60)
		{
			time.seconds = 0;
			time.minutes++;
		} 
		if (time.minutes == 60)
		{
			time.minutes = 0;
			time.hours++;
		}
	}

	/*

	Removed this entire section - will fix when we have actual real
	time milliseconds working
	
	Getting error when calling this locally... quick fix by passing in
	
	time_t real_time = time(NULL);
	
	*/
	
	//struct tm* new_time = gmtime((const time_t*) &unix_ticks);
	
	//time.seconds = new_time->tm_sec;
	//time.minutes = new_time->tm_min;
	//time.hours = new_time->tm_hour;
}
/**
 * Get the number of milliseconds passed since last reset (typically frame time)
 */
u64 timer_c::get_ms(){
	return ms;
}

/**
 * Resets the ms count - should be only called on vbl
 */
void timer_c::reset_ms(){
	ms=0;
}

/**
 * Increment the millisecond counter within the timer object
 */
void timer_c::incre_ms(){
	ms++;
}

timer_c_ptr timer_c::get_next(){
	return next;
}

char * timer_c::get_time_string(){ // add a param for the time detail range latter
	sprintf(time_string, "%02d:%02d:%02d:%02d", time.hours, time.minutes, time.seconds, time.useconds);
	
	return (char *) time_string;
}

time_set_t_ptr timer_c::get_time(){
	return &time;
}

// end of file
