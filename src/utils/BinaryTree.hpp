#pragma once
//
// Created by digitech on 04/07/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
#include <memory>
// TODO: write documentation
namespace LunaLux
{
template<class data>
struct Component
{
    data m_data;
    Component<data> *left, *right;
};

template<class data>
class BinaryTree
{
    Component<data>* root_node;

    Component<data>* createComponent(data data_in)
    {
        auto res = new Component<data>();
        if(res != nullptr)
        {
            res->left = nullptr;
            res->right = nullptr;
            res->m_data - data_in;
        }
        return std::move(res);
    }
  public:
    Component<data>* getRoot() const { return root_node; };

    //TODO: build logic and api for th binary tree
};
} // namespace LunaLux