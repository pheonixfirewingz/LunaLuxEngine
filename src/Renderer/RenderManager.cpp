#include "RenderManager.h"
#include <Renderer/DirectX12/DirctX12Renderer.h>
#include <Renderer/Vulkan/VulkanRenderer.h>
#include <utils/TimeTracker.hpp>
//
// Created by luket on 08/06/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
// TODO: write documentation
namespace LunaLux
{
EngineResult RenderManager::initialise(API api)
{
    TimeTracker tracker("renderer initialise");
    switch (api)
    {
    case API::DIRECTX12:
#if __has_include(<windows.h>)
        renderer = std::make_unique<DirectX12Renderer>();
#else
        printf("LunaLuxEngine - ENGINE_ERROR: WTF why you trying to use DirectX12 on a non windows platform.\n");
        return EngineResult::ENGINE_ERROR;
#endif
        break;
    case API::VULKAN:
        renderer = std::make_unique<VulkanRenderer>();
        break;
    }
    renderable_entities = std::make_unique<BinaryTree<RenderEntity>>();

    return renderer->initialise(2);
}

EngineResult RenderManager::update()
{
    CHECK(renderer->beginFrame(), "could not start frame")
    CHECK(drawTree(renderable_entities->getRoot()), "could not render BinaryTree");
    CHECK(renderer->endFrame(), "could not start frame")
    CHECK(renderer->submitToScreen(), "could not submit to window")
    return EngineResult::SUCSESS;
}

EngineResult RenderManager::RefreshRenderWindow()
{
    return renderer->refreshRenderWindow();
}

EngineResult RenderManager::cleanUp()
{
    (void)renderable_entities.release();
    return renderer->cleanUp();
}

EngineResult RenderManager::drawTree(Component<RenderEntity>* root_entity)
{
    if(root_entity == nullptr)
        return EngineResult::ENGINE_ERROR;

    if (root_entity->left != nullptr)
        drawTree(root_entity->left);
    if (root_entity->right != nullptr)
        drawTree(root_entity->right);

    return renderer->draw(*root_entity);
}

EngineResult RenderManager::addEntity(RenderEntity entity)
{
    return EngineResult::SUCSESS;
}
EngineResult RenderManager::removeEntity(RenderEntity entity)
{
    return EngineResult::VULKAN_ERROR;
}
} // namespace LunaLux
