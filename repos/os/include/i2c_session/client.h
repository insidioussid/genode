/*
 * \brief  I2C session client implementation
 * \author Jean-Adrien Domage <jean-adrien.domage@gapfruit.com>
 * \date   2021-02-25
 */

/*
 * Copyright (C) 2013-2021 Genode Labs GmbH
 * Copyright (C) 2021 gapfruit AG
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__I2C_SESSION__CLIENT_H_
#define _INCLUDE__I2C_SESSION__CLIENT_H_

#include <base/rpc_client.h>
#include <i2c_session/capability.h>

namespace I2c { struct Session_client; }


struct I2c::Session_client : Rpc_client<I2c::Session>
{
	explicit Session_client(I2c::Session_capability session)
	:
		Rpc_client<I2c::Session>(session)
	{ }

	void write_8bits(uint8_t byte) override
	{
		call<Rpc_write_8bits>(byte);
	}

	uint8_t read_8bits() override
	{
		return call<Rpc_read_8bits>();
	}

	void write_16bits(uint16_t word) override
	{
		call<Rpc_write_16bits>(word);
	}

	uint16_t read_16bits() override
	{
		return call<Rpc_read_16bits>();
	}
};

#endif /* _INCLUDE__I2C_SESSION__CLIENT_H_ */
