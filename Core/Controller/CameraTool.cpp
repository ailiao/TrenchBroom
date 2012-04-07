/*
 Copyright (C) 2010-2012 Kristian Duske
 
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
 along with TrenchBroom.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "CameraTool.h"
#include <cstdio>

namespace TrenchBroom {
    namespace Controller {
        CameraTool::CameraTool(Model::Camera& camera) : m_camera(camera), m_orbit(false), m_invert(false), m_lookSensitivity(1 / 90.0f), m_panSensitivity(1.0f), m_moveSensitivity(6.0f) {}

        
        bool CameraTool::scrolled(ToolEvent& event) {
            if (!cameraModiferPressed(event) && !orbitModifierPressed(event)) return false;
            
            float forward = event.scrollX * m_moveSensitivity;
            float right = 0;
            float up = 0;
            m_camera.moveBy(forward, right, up);
            return true;
        }
        
        bool CameraTool::beginLeftDrag(ToolEvent& event) {
            if (!cameraModiferPressed(event) && !orbitModifierPressed(event)) return false;
            
            if (orbitModifierPressed(event)) {
                // TODO implement orbiting
            }
            return true;
        }
        
        void CameraTool::leftDrag(ToolEvent& event) {
            if (m_orbit) {
                float hAngle = -event.deltaX * m_lookSensitivity;
                float vAngle = event.deltaY * m_lookSensitivity * (m_invert ? 1 : -1);
                m_camera.orbit(m_orbitCenter, hAngle, vAngle);
            } else {
                float yawAngle = -event.deltaX * m_lookSensitivity;
                float pitchAngle = event.deltaY * m_lookSensitivity * (m_invert ? 1 : -1);
                m_camera.rotate(yawAngle, pitchAngle);
            }
        }
        
        void CameraTool::endLeftDrag(ToolEvent& event) {
            m_orbit = false;
        }
        
        bool CameraTool::beginRightDrag(ToolEvent& event) {
            return cameraModiferPressed(event) || orbitModifierPressed(event);
        }
        
        void CameraTool::rightDrag(ToolEvent& event) {
            float forward = 0;
            float right = event.deltaX * m_panSensitivity;
            float up = -event.deltaY * m_panSensitivity;
            m_camera.moveBy(forward, right, up);
        }
        
        bool CameraTool::cameraModiferPressed(ToolEvent& event) {
            return event.modifierKeys == MK_SHIFT;
        }
        
        bool CameraTool::orbitModifierPressed(ToolEvent& event) {
            return event.modifierKeys == (MK_SHIFT | MK_CMD);
        }
    }
}