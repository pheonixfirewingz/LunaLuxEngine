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
    Component<data>* left,* right;

    explicit Component(data data_in)
    {
        m_data = data_in;
        left = nullptr;
        right = nullptr;
    }
};

template<class data>
class BinaryTree
{
    Component<data>* root_node,* current_selected_node;
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
    void select(Component<data>* node)
    {
        if(current_selected_node != node)
            current_selected_node = node;
    }

    void insert(Component<data>* node)
    {
        if(root_node == nullptr)
        {
            current_selected_node = (root_node = node);
            return;
        }

        if(current_selected_node->right != nullptr)
        {
            current_selected_node->right = node;
            return;
        }

        if(current_selected_node->left != nullptr)
        {
            current_selected_node->left = node;
            return;
        }

        //idk what to do if both are already assigned
    }

    void remove(Component<data> node)
    {
        if(current_selected_node->right->m_data.equl(node.m_data))
        {
            current_selected_node->right = Component<data>(node.right);
            return;
        }

        if(current_selected_node->left->m_data.equl(node.m_data))
        {
            current_selected_node->left = Component<data>(node.left);
            return;
        }
    }

    //WARNING: this is experimental idk if works
    BinaryTree<data> createSubTree(Component<data>& node)
    {
        BinaryTree<data> tree = new BinaryTree<data>();
        tree.insert(node);
        return std::move(tree);
    }
};
} // namespace LunaLux