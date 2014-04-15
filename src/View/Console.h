/*
 Copyright (C) 2010-2014 Kristian Duske
 
 This file is part of TrenchBroom.
 
 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __TrenchBroom__Console__
#define __TrenchBroom__Console__

#include "StringUtils.h"
#include "Notifier.h"
#include "Logger.h"

#include <wx/textctrl.h>

class wxSimplebook;
class wxString;

namespace TrenchBroom {
    namespace View {
        class Console : public wxTextCtrl, public Logger {
        public:
            Notifier2<LogLevel, const wxString&> logNotifier;
        public:
            Console(wxWindow* parent, wxSimplebook* extraBook);
        private:
            void doLog(LogLevel level, const String& message);
            void doLog(LogLevel level, const wxString& message);
            void logToDebugOut(LogLevel level, const wxString& message);
            void logToConsole(LogLevel level, const wxString& message);
        };
    }
}

#endif /* defined(__TrenchBroom__Console__) */
