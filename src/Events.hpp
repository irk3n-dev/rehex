/* Reverse Engineer's Hex Editor
 * Copyright (C) 2020 Daniel Collins <solemnwarning@solemnwarning.net>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef REHEX_EVENTS_HPP
#define REHEX_EVENTS_HPP

#include <sys/types.h>
#include <wx/event.h>
#include <wx/window.h>

#include "document.hpp"

namespace REHex
{
	class OffsetLengthEvent: public wxEvent
	{
		public:
			const off_t offset;
			const off_t length;
			
			OffsetLengthEvent(wxWindow *source, wxEventType event, off_t offset, off_t length);
			OffsetLengthEvent(wxObject *source, wxEventType event, off_t offset, off_t length);
			
			virtual wxEvent *Clone() const override;
	};
	
	typedef void (wxEvtHandler::*OffsetLengthEventFunction)(OffsetLengthEvent&);
	
	#define EVT_OFFSETLENGTH(id, type, func) \
		wx__DECLARE_EVT1(type, id, wxEVENT_HANDLER_CAST(OffsetLengthEventFunction, func))
	
	class CursorUpdateEvent: public wxEvent
	{
		public:
			const off_t cursor_pos;
			const Document::CursorState cursor_state;
			
			CursorUpdateEvent(wxWindow *source, off_t cursor_pos, Document::CursorState cursor_state);
			CursorUpdateEvent(wxObject *source, off_t cursor_pos, Document::CursorState cursor_state);
			
			virtual wxEvent *Clone() const override;
	};
	
	typedef void (wxEvtHandler::*CursorUpdateEventFunction)(CursorUpdateEvent&);
	
	#define EVT_CURSORUPDATE(id, func) \
		wx__DECLARE_EVT1(CURSOR_UPDATE, id, wxEVENT_HANDLER_CAST(CursorUpdateEventFunction, func))
	
	class DocumentTitleEvent: public wxEvent
	{
		public:
			const std::string title;
			
			DocumentTitleEvent(wxWindow *source, const std::string &title);
			DocumentTitleEvent(wxObject *source, const std::string &title);
			
			virtual wxEvent *Clone() const override;
	};
	
	typedef void (wxEvtHandler::*DocumentTitleEventFunction)(DocumentTitleEvent&);
	
	#define EVT_DOCUMENTTITLE(id, func) \
		wx__DECLARE_EVT1(DOCUMENT_TITLE_CHANGED, id, wxEVENT_HANDLER_CAST(DocumentTitleEventFunction, func))
	
	wxDECLARE_EVENT(COMMENT_LEFT_CLICK,     OffsetLengthEvent);
	wxDECLARE_EVENT(COMMENT_RIGHT_CLICK,    OffsetLengthEvent);
	wxDECLARE_EVENT(DATA_RIGHT_CLICK,       wxCommandEvent);
	
	wxDECLARE_EVENT(DATA_ERASE,        OffsetLengthEvent);
	wxDECLARE_EVENT(DATA_INSERT,       OffsetLengthEvent);
	wxDECLARE_EVENT(DATA_OVERWRITE,    OffsetLengthEvent);
	
	wxDECLARE_EVENT(CURSOR_UPDATE,    CursorUpdateEvent);
	
	wxDECLARE_EVENT(DOCUMENT_TITLE_CHANGED,  DocumentTitleEvent);
}

#endif /* !REHEX_EVENTS_HPP */
