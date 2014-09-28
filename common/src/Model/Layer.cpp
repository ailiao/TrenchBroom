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

#include "Layer.h"

#include "Model/NodeVisitor.h"

namespace TrenchBroom {
    namespace Model {
        Layer::Layer(const String& name) :
        m_name(name),
        m_hidden(false),
        m_locked(false) {}
        
        const String& Layer::name() const {
            return m_name;
        }
        
        void Layer::setName(const String& name) {
            m_name = name;
        }

        bool Layer::hidden() const {
            return m_hidden;
        }
        
        void Layer::setHidden(const bool hidden) {
            m_hidden = hidden;
        }

        bool Layer::locked() const {
            return m_locked;
        }
        
        void Layer::setLocked(const bool locked) {
            m_locked = locked;
        }

        Node* Layer::doClone(const BBox3& worldBounds) const {
            Layer* layer = new Layer(m_name);
            layer->addChildren(clone(worldBounds, children()));
            return layer;
        }

        class CanAddChildToLayer : public ConstNodeVisitor, public NodeQuery<bool> {
        private:
            void doVisit(const World* world)   { setResult(false); }
            void doVisit(const Layer* layer)   { setResult(false); }
            void doVisit(const Group* group)   { setResult(true); }
            void doVisit(const Entity* entity) { setResult(true); }
            void doVisit(const Brush* brush)   { setResult(true); }
        };

        bool Layer::doCanAddChild(const Node* child) const {
            CanAddChildToLayer visitor;
            child->accept(visitor);
            return visitor.result();
        }
        
        bool Layer::doCanRemoveChild(const Node* child) const {
            return true;
        }
        
        bool Layer::doSelectable() const {
            return false;
        }

        void Layer::doAccept(NodeVisitor& visitor) {
            visitor.visit(this);
        }
        
        void Layer::doAccept(ConstNodeVisitor& visitor) const {
            visitor.visit(this);
        }
    }
}
