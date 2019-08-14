/*
 * \brief  Linker configuration
 * \author Norman Feske
 * \date   2019-08-13
 */

/*
 * Copyright (C) 2019 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__CONFIG_H_
#define _INCLUDE__CONFIG_H_

namespace Linker { class Config; }


class Linker::Config : Noncopyable
{
	private:

		Attached_rom_dataspace _config_rom;

		Xml_node const _config { _config_rom.xml() };

		Bind const _bind = _config.attribute_value("ld_bind_now", false)
		                 ? BIND_NOW : BIND_LAZY;

		bool const _verbose = _config.attribute_value("ld_verbose", false);

	public:

		Config(Env &env) : _config_rom(env, "config") { }

		Bind bind()    const { return _bind; }
		bool verbose() const { return _verbose; }

		typedef String<100> Rom_name;

		/**
		 * Call fn for each library specified in the configuration
		 *
		 * The functor 'fn' is called with 'Rom_name', 'Keep' as arguments.
		 */
		template <typename FN>
		void for_each_library(FN const &fn) const
		{
			_config.with_sub_node("ld", [&] (Xml_node ld) {

				ld.for_each_sub_node("library", [&] (Xml_node lib) {

					Rom_name const rom = lib.attribute_value("rom", Rom_name());

					Keep const keep = lib.attribute_value("keep", false)
					                ? DONT_KEEP : KEEP;

					fn(rom, keep);
				});
			});
		}
};

#endif /* _INCLUDE__CONFIG_H_ */