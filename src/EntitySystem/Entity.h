#pragma once
//
// Created by digitech on 04/07/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
#include <EntitySystem/Component.h>
#include <utils/BinaryTree.hpp>
// TODO: write documentation
namespace LunaLux
{
class Entity
{
  protected:
    uint64_t entity_id = 0;
  public:
    BinaryTree<EntityComponent> components{};
    [[nodiscard]] bool equl(Entity entity_in) const
    {
        return entity_id == entity_in.entity_id;
    };
};
} // namespace LunaLux