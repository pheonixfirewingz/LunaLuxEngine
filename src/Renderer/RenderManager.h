#pragma once
//
// Created by luket on 08/06/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
#include <EngineError.h>
#include <EntitySystem/Entity.h>
#include <Renderer/IRenderer.h>
#include <memory>
#include <utils/BinaryTree.hpp>
#include <utils/EngineDefines.h>

// TODO: write documentation
namespace LunaLux
{
class RenderManager
{
    typedef Entity RenderEntity;

    std::unique_ptr<IRenderer> renderer;
    std::unique_ptr<BinaryTree<RenderEntity>> renderable_entities;

    EngineResult drawTree(Component<RenderEntity>* root_entity);
  public:
    enum class API
    {
        DIRECTX12 = 0,
        VULKAN = 1
    };

    static RenderManager* the()
    {
        static auto render = new RenderManager();
        return render;
    }

    EngineResult initialise(API api);
    EngineResult RefreshRenderWindow();
    EngineResult update();
    EngineResult cleanUp();

    EngineResult addEntity(RenderEntity entity);
    EngineResult removeEntity(RenderEntity entity);
};
} // namespace LunaLux
