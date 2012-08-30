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

#ifndef __TrenchBroom__MapRenderer__
#define __TrenchBroom__MapRenderer__

#include "Model/BrushTypes.h"
#include "Model/EntityTypes.h"
#include "Model/FaceTypes.h"
#include "Model/Texture.h"
#include "Utility/Color.h"
#include "Utility/GLee.h"

#include <map>
#include <vector>

namespace TrenchBroom {
    namespace Model {
        class Map;
    }
    
    namespace Renderer {
        class RenderContext;
        class Vbo;
        class VboBlock;
        
        class MapRenderer {
        private:
            class CompareTexturesById {
            public:
                inline bool operator() (const Model::Texture* left, const Model::Texture* right) const {
                    return left->uniqueId() < right->uniqueId();
                }
            };
            
            class EdgeRenderInfo {
            public:
                GLuint offset;
                GLuint vertexCount;
                EdgeRenderInfo() : offset(0), vertexCount(0) {};
                EdgeRenderInfo(GLuint offset, GLuint vertexCount) : offset(offset), vertexCount(vertexCount) {}
            };
            
            class TexturedTriangleRenderInfo {
            public:
                Model::Texture* texture;
                GLuint offset;
                GLuint vertexCount;
                TexturedTriangleRenderInfo(Model::Texture* texture, GLuint offset, GLuint vertexCount) : texture(texture), offset(offset), vertexCount(vertexCount) {}
            };
            
            /*
            class CachedEntityRenderer {
            public:
                EntityRenderer* renderer;
                String classname;
                CachedEntityRenderer() : renderer(NULL), classname("") {}
                CachedEntityRenderer(EntityRenderer* renderer, const std::string& classname) : renderer(renderer), classname(classname) {}
            };
            */
            
            typedef std::vector<GLuint> IndexBuffer;
            typedef std::map<Model::Texture*, Model::FaceList, CompareTexturesById> FacesByTexture;
            typedef std::vector<TexturedTriangleRenderInfo> FaceRenderInfos;
            //typedef std::map<Model::Entity*, CachedEntityRenderer> EntityRenderers;

            // level geometry rendering
            Vbo* m_faceVbo;
            VboBlock* m_faceBlock;
            VboBlock* m_selectedFaceBlock;
            Vbo* m_edgeVbo;
            VboBlock* m_edgeBlock;
            VboBlock* m_selectedEdgeBlock;
            FaceRenderInfos m_faceRenderInfos;
            FaceRenderInfos m_selectedFaceRenderInfos;
            EdgeRenderInfo m_edgeRenderInfo;
            EdgeRenderInfo m_selectedEdgeRenderInfo;
            
            // entity bounds rendering
            Vbo* m_entityBoundsVbo;
            VboBlock* m_entityBoundsBlock;
            VboBlock* m_selectedEntityBoundsBlock;
            EdgeRenderInfo m_entityBoundsRenderInfo;
            EdgeRenderInfo m_selectedEntityBoundsRenderInfo;
            
            /*
            // entity model rendering
            EntityRendererManager* m_entityRendererManager;
            EntityRenderers m_entityRenderers;
            EntityRenderers m_selectedEntityRenderers;
            bool m_entityRendererCacheValid;
             
            // classnames
            TextRenderer<Model::Entity*>* m_classnameRenderer;
            TextRenderer<Model::Entity*>* m_selectedClassnameRenderer;
            
            // selection guides
            SizeGuideFigure* m_sizeGuideFigure;
            
            // figures
            Vbo* m_figureVbo;
            std::vector<Figure*> m_figures;
            */
             
            // state
            bool m_entityDataValid;
            bool m_selectedEntityDataValid;
            bool m_geometryDataValid;
            bool m_selectedGeometryDataValid;
            
            /*
            GridRenderer* m_gridRenderer;
            FontManager& m_fontManager;
             */

            Model::Texture* m_dummyTexture;
            Model::Map& m_map;
            
            void writeFaceData(RenderContext& context, FacesByTexture& facesByTexture, FaceRenderInfos& renderInfos, VboBlock& block);
            void writeEdgeData(RenderContext& context, Model::BrushList& brushes, Model::FaceList& faces, EdgeRenderInfo& renderInfo, VboBlock& block);
            void rebuildGeometryData(RenderContext& context);
            void writeEntityBounds(RenderContext& context, const Model::EntityList& entities, EdgeRenderInfo& renderInfo, VboBlock& block);
            void rebuildEntityData(RenderContext& context);
            /*
            bool reloadEntityModel(const Model::Entity& entity, CachedEntityRenderer& cachedRenderer);
            void reloadEntityModels(RenderContext& context, EntityRenderers& renderers);
            void reloadEntityModels(RenderContext& context);
             */
            
            void validate(RenderContext& context);

            void renderEntityBounds(RenderContext& context, const EdgeRenderInfo& renderInfo, const Color* color);
//            void renderEntityModels(RenderContext& context, EntityRenderers& entities);
            void renderEdges(RenderContext& context, const EdgeRenderInfo& renderInfo, const Color* color);
            void renderFaces(RenderContext& context, bool textured, bool selected, const FaceRenderInfos& renderInfos);
            void renderFigures(RenderContext& context);
        public:
            MapRenderer(Model::Map& map);
            ~MapRenderer();
            
            void addEntities(const Model::EntityList& entities);
            void loadMap();
            void clearMap();

            void render(RenderContext& context);
        };
    }
}

#endif /* defined(__TrenchBroom__MapRenderer__) */