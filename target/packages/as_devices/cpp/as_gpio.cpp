/*
**    THE ARMadeus Systems
** 
**    Copyright (C) 2011  The armadeus systems team 
**    Jérémie Scheer <jeremie.scheeer@armadeus.com>
** 
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or (at your option) any later version.
** 
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Lesser General Public License for more details.
** 
** You should have received a copy of the GNU Lesser General Public
** License along with this library; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
*/

#include "as_gpio.hpp"
#include <iostream>

/** @brief Constructor: Initialize port access
 *
 * @param aPortChar character port in UPPER case
 * @param aPinNum int pin number
 */
AsGpio::AsGpio(char aPortChar, int aPinNum)
{
	mDev = as_gpio_open(aPortChar, aPinNum);
}	

AsGpio::~AsGpio()
{
	int ret;

	ret = as_gpio_close(mDev);
	if (ret < 0)
	{
		std::cout<<"AsGpio destruction error"<<std::endl;
	}
}

/** @brief  Set pin direction
 *
 * @param aDirection direction 0:input 1:output
 *
 * @return error if negative value
 */
long AsGpio::setPinDirection(int aDirection)
{
	return as_gpio_set_pin_direction(mDev, aDirection);
}

/** @brief  Get pin direction
 *
 * @return pin direction if positive or null, error if negative
 */
long AsGpio::getPinDirection() const
{
	return as_gpio_get_pin_direction(mDev);
}

/** @brief Set pin value
 *
 * @param aValue value of pin (1 or 0)
 *
 * @return error if negative
 */
long AsGpio::setPinValue(int aValue)
{
	return as_gpio_set_pin_value(mDev, aValue);
}

/** @brief Get pin value
 *
 * @return pin value if positive or null, error if negative
 */
long AsGpio::getPinValue() const
{
	return as_gpio_get_pin_value(mDev);
}

/** @brief Get pin value, blocking until interrupt occur
 *
 * @param aDelay_s waiting delay in seconds
 * @param aDelay_us waiting delay in useconds (plus delay in seconds)
 *
 * @return pin value if positive or null, read error if -1, timeout if -10
 */
long AsGpio::blockingGetPinValue(int aDelay_s, int aDelay_us) const
{
	return as_gpio_blocking_get_pin_value(mDev, aDelay_s, aDelay_us);
}
	
/** @brief Set pin irq mode
 *
 * @param aMode irq mode
 *
 * @return error if negative
 */
long AsGpio::setIrqMode(int aMode)
{
	return as_gpio_set_irq_mode(mDev, aMode);
}

/** @brief Get pin irq mode value
 *
 * @return pin mode value if positive or null, error if negative
 */
long AsGpio::getIrqMode() const
{
	return as_gpio_get_irq_mode(mDev);
}

/** @brief Get pin number value
 *
 * @return pin number, error if negative
 */
long AsGpio::getPinNum() const
{
	return as_gpio_get_pin_num(mDev);
}

/** @brief Get port letter
 *
 * @return port letter, error if negative
 */
long AsGpio::getPortLetter() const
{
	return as_gpio_get_port_letter(mDev);
}
