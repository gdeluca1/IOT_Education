#ifndef _ULTRASONIC_SENSOR_H
#define _ULTRASONIC_SENSOR_H
#include "Sensor.h"
#include "hcsr04/hcsr04.h"
#include <iostream>
#include <exception>
#include <mraa.hpp>
//#include <hcsr04.h>
#include <functional>
#include <stdexcept>
#include <boost/thread/thread.hpp>
#include <boost/chrono/chrono.hpp>
using std::cout;
using std::endl;
using std::runtime_error;
class UltrasonicSensor: public Sensor{

public:

/* Start static members */

	//This function is used to manage the static upm objects.
	//TODO: Eliminate this and bind upm::HCSR04 objects to a callback, eliminating static objects and callbacks
	static HCSR04 * get_hcsr04(int trig_pin, int echo_pin)
	{
		return new HCSR04::HCSR04(trig_pin, echo_pin);
	}

/* End static members, start public instance members */

	UltrasonicSensor(int trig_pin, int echo_pin, int id) : Sensor(id, "distance")
	{
		this->m_ultrasonicSensor = get_hcsr04(trig_pin, echo_pin);
		this->m_echo_pin = echo_pin;
		this->m_trig_pin = trig_pin;
	}

	~UltrasonicSensor()
	{
		//currently, this is a reference to a static member.
		//this works even for that case.  Again, the static member setup is certainly not ideal.
		delete this->m_ultrasonicSensor;
	}
	/*
	Routine Description:
	Read from the ultrasonic sensor and return the value
	*/
//we will try to read from the ultrasonic sensor NUM_ATTEMPTS times, each time giving it TIMEOUT_MS seconds to respond
/*
   In the case where the sensor fails to 
 */
//25 attempts might be generous, but we can lower this to around 5 or so if we need to.
#define NUM_ATTEMPTS 25
//Intel's upm GroveUltrasonic Sensor uses a timeout of 25 ms, so we will do that as well.
#define TIMEOUT_MS 25

	float
	value()
	{
		return this->m_ultrasonicSensor->getDistance(CM);
	}

protected:
	int m_echo_pin, m_trig_pin;
	HCSR04 * m_ultrasonicSensor;

private:

};

#endif

