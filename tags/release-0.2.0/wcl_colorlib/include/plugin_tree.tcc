#include "precompiled_header.hpp"

// wcl_colorlib - portable color library
// Copyright (C) <2007>  Wei Hu <wei.hu.tw@gmail.com>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include "plugin_tree.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    // ==========================================================================
    //                               Plugin Tree Node
    // ==========================================================================  
    template<typename T>
    PluginTreeNode<T>::PluginTreeNode(
      PluginTreeNode<T> * const parent)
      : mp_parent(parent)
    {
    }
    
    template<typename T>
    typename PluginTreeNode<T>::iterator
    PluginTreeNode<T>::begin()
    {
      // If this is an empty Plugin tree, then return an 'end()'
      // immediately.
      if (0 == mp_children.size())
      {
        return end();
      }
      else
      {
        iterator iter(this);
      
        iter.assign_tree_node(mp_children.front());
      
        iter.children_iter().push_back(mp_children.begin());
      
        return iter;
      }
    }
    
    template<typename T>
    typename PluginTreeNode<T>::iterator
    PluginTreeNode<T>::end()
    {
      iterator iter(this);
    
      iter.assign_tree_node(0);
    
      return iter;
    }
    
    template<typename T>
    PluginTreeNode<T> *
    PluginTreeNode<T>::search(
      std::list<std::wstring> const &names) const
    {
      std::list<std::wstring>::const_iterator names_iter = names.begin();
      
      PluginTreeNode<T> const *curr_node = this;
      
      for (;;)
      {
        bool find = false;
        
        BOOST_FOREACH(PluginTreeNode<T> * const node, curr_node->children())
        {
          if (0 == node->name().compare(*names_iter))
          {
            ++names_iter;
            
            if (names_iter == names.end())
            {
              return node;
            }
            else
            {
              curr_node = node;
              find = true;
              break;
            }
          }
        }
        
        if (false == find)
        {
          break;
        }
      }
      
      return 0;
    }
    
    // ==========================================================================
    //                            Plugin Tree Leaf Node
    // ==========================================================================  
    template<typename T>
    PluginTreeLeafNode<T>::PluginTreeLeafNode(
      PluginTreeNode<T> * const parent,
      PluginInfo<T> const * const plugin_info)
      : PluginTreeNode<T>(parent),
        mp_plugin_info(plugin_info)
    {
      assert(plugin_info != 0);
    }
    
    // ==========================================================================
    //                             Plugin Tree Iterator
    // ==========================================================================  
    
    template<typename T>
    typename PluginTreeNode<T>::iterator &
    PluginTreeNode<T>::iterator::operator++()
    {
      assert(mp_tree_node != 0);
    
#if defined(_DEBUG)
      {
        PluginTreeNode<T> const *tree_node = mp_tree_node;

        std::list<std::list<PluginTreeNode<T> *>::iterator>::reverse_iterator iter = m_children_iter.rbegin();
    
        while (tree_node != mp_init_tree_node)
        {
          if (tree_node->parent() != 0)
          {
            assert((**iter) == tree_node);
        
            assert(iter != m_children_iter.rend());
            ++iter;
        
            tree_node = tree_node->parent();
          }
          else
          {
            break;
          }
        }
      }
#endif
      
      if (true == m_return_from_children)
      {
        if (0 == m_children_iter.size())
        {
          assert(mp_init_tree_node == mp_tree_node);
          
          mp_tree_node = 0;
          m_return_from_children = false;
        }
        else
        {
          ++(m_children_iter.back());
          
          assert(mp_tree_node->parent() != 0);
          if (m_children_iter.back() == mp_tree_node->parent()->children().end())
          {
            // I have finished enumerating this parent node.
            mp_tree_node = mp_tree_node->parent();
            
            m_children_iter.pop_back();
            m_return_from_children = true;
            
            if (m_children_iter.size() != 0)
            {
              assert(mp_tree_node->parent() != 0);
            }
          }
          else
          {
            mp_tree_node = (*(m_children_iter.back()));
            m_return_from_children = false;
          }
        }
      }
      else
      {
        if (mp_tree_node->children().size() != 0)
        {
          // This is a group node.
          
          // If there is at least a child, then I will enumerate
          // to this child node.
          m_children_iter.push_back(mp_tree_node->children().begin());
          
          mp_tree_node = (*(m_children_iter.back()));
          
          m_return_from_children = false;
        }
        else
        {
          // This is a leaf node
        
          // If the init node is a leaf node, then the first
          // operator++() will result in an end situation.
          if (mp_init_tree_node == mp_tree_node)
          {
            assert(0 == m_children_iter.size());
          
            mp_tree_node = 0;
            m_return_from_children = false;
          }
          else
          {
            // enumerate to its sibling node.
          
            assert(mp_tree_node->parent() != 0);
            assert(m_children_iter.size() != 0);
            assert(m_children_iter.back() != mp_tree_node->parent()->children().end());
          
            ++(m_children_iter.back());
          
            if (m_children_iter.back() == mp_tree_node->parent()->children().end())
            {
              // I have finished enumerating this parent node.
              mp_tree_node = mp_tree_node->parent();
            
              m_children_iter.pop_back();
              m_return_from_children = true;
              
              if (m_children_iter.size() != 0)
              {
                assert(mp_tree_node->parent() != 0);
              }
            }
            else
            {
              mp_tree_node = (*(m_children_iter.back()));
            
              m_return_from_children = false;
            }
          }
        }
      }
      
      return (*this);
    }
    
    // ==========================================================================
    //                            Plugin Tree Group Node
    // ==========================================================================  
    template<typename T>
    PluginTreeGroupNode<T>::PluginTreeGroupNode(
      PluginTreeNode<T> * const parent,
      wchar_t const * const name)
      : PluginTreeNode<T>(parent),
        m_name(name)
    {
      assert(name != 0);
    }
    
    template<typename T>
    std::wstring
    PluginTreeGroupNode<T>::name() const
    {
      assert(m_name.size() != 0);
    
      return m_name;
    }
  }
}
