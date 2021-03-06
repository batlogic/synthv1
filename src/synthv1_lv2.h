// synthv1_lv2.h
//
/****************************************************************************
   Copyright (C) 2012-2018, rncbc aka Rui Nuno Capela. All rights reserved.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*****************************************************************************/

#ifndef __synthv1_lv2_h
#define __synthv1_lv2_h

#include "synthv1.h"

#include "lv2.h"
#include "lv2/lv2plug.in/ns/ext/urid/urid.h"
#include "lv2/lv2plug.in/ns/ext/atom/atom.h"
#include "lv2/lv2plug.in/ns/ext/atom/forge.h"

#include "lv2/lv2plug.in/ns/ext/worker/worker.h"

#define SYNTHV1_LV2_URI "http://synthv1.sourceforge.net/lv2"
#define SYNTHV1_LV2_PREFIX SYNTHV1_LV2_URI "#"


#ifdef CONFIG_LV2_PROGRAMS
#include "lv2_programs.h"
#include <QByteArray>
#endif


//-------------------------------------------------------------------------
// synthv1_lv2 - decl.
//

class synthv1_lv2 : public synthv1
{
public:

	synthv1_lv2(double sample_rate, const LV2_Feature *const *host_features);

	~synthv1_lv2();

	enum PortIndex {

		MidiIn = 0,
		Notify,
		AudioInL,
		AudioInR,
		AudioOutL,
		AudioOutR,
		ParamBase
	};

	void connect_port(uint32_t port, void *data);

	void run(uint32_t nframes);

	void activate();
	void deactivate();

	uint32_t urid_map(const char *uri) const;

#ifdef CONFIG_LV2_PROGRAMS
	const LV2_Program_Descriptor *get_program(uint32_t index);
	void select_program(uint32_t bank, uint32_t program);
#endif

	bool worker_work(const void *data, uint32_t size);
	bool worker_response(const void *data, uint32_t size);

protected:

	void updatePreset(bool bDirty);

	bool state_changed();

private:

	LV2_URID_Map *m_urid_map;

	struct lv2_urids
	{
		LV2_URID atom_Blank;
		LV2_URID atom_Object;
		LV2_URID atom_Float;
		LV2_URID atom_Int;
		LV2_URID time_Position;
		LV2_URID time_beatsPerMinute;
		LV2_URID midi_MidiEvent;
		LV2_URID bufsz_minBlockLength;
		LV2_URID bufsz_maxBlockLength;
		LV2_URID bufsz_nominalBlockLength;
		LV2_URID state_StateChanged;

	} m_urids;

	LV2_Atom_Forge m_forge;
	LV2_Atom_Forge_Frame m_notify_frame;

	LV2_Worker_Schedule *m_schedule;

	uint32_t m_ndelta;

	LV2_Atom_Sequence *m_atom_in;
	LV2_Atom_Sequence *m_atom_out;

	float **m_ins;
	float **m_outs;

#ifdef CONFIG_LV2_PROGRAMS
	LV2_Program_Descriptor m_program;
	QByteArray m_aProgramName;
#endif
};


#endif// __synthv1_lv2_h

// end of synthv1_lv2.h

