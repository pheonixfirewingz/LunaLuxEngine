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
    BinaryTree<EntityComponent> components;
};
} // namespace LunaLux