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

#ifndef __wcl_colorlib_plugin_tree_hpp__
#define __wcl_colorlib_plugin_tree_hpp__

#include "wcl_types.hpp"
#include "export.hpp"
#include "plugin_info.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    template<typename T>
    class PluginTreeNode
    {
    private:
      
      PluginTreeNode<T> * const mp_parent;
      std::list<PluginTreeNode<T> *> mp_children;
      
      // PluginTreeNode should not be copied.
      PluginTreeNode &operator=(PluginTreeNode const &);
      
    protected:
      
      PluginTreeNode(PluginTreeNode<T> * const parent);
      
    public:
      
      virtual ~PluginTreeNode() {}
      
      virtual std::wstring name() const = 0;
      virtual PluginInfo<T> const *plugin_info() const = 0;
      
      void add_child(PluginTreeNode<T> * const node)
      {
        assert(node != 0);
      
        mp_children.push_back(node);
      }
    
      std::list<PluginTreeNode<T> *> const &children() const
      {
        return mp_children;
      }
    
      std::list<PluginTreeNode<T> *> &children()
      {
        return mp_children;
      }
      
      PluginTreeNode<T> *parent() const
      { return mp_parent; }
      
      PluginTreeNode<T> *search(std::list<std::wstring> const &name) const;
      
      // The following API is for iterating a Plugin tree.
      class iterator : public std::iterator<std::input_iterator_tag, PluginTreeNode<T> *>
      {
      private:
        
        PluginTreeNode<T> *mp_init_tree_node;
        bool m_return_from_children;
        
        // Setting this field to 0 indicates the end of
        // enumeration.
        PluginTreeNode<T> *mp_tree_node;
      
        std::list<typename std::list<PluginTreeNode<T> *>::iterator> m_children_iter;
      
      public:
      
        // Constructor
        iterator(
          PluginTreeNode<T> * const tree_node = 0)
          : mp_init_tree_node(tree_node),
            m_return_from_children(false)
        { }
      
        // Copy constructor
        iterator(iterator const &iter)
          : mp_init_tree_node(iter.init_tree_node()),
            m_return_from_children(iter.return_from_children()),
            mp_tree_node(iter.tree_node()),
            m_children_iter(iter.children_iter())
        { }
      
        std::list<typename std::list<PluginTreeNode<T> *>::iterator> const &children_iter() const
        { return m_children_iter; }
      
        std::list<typename std::list<PluginTreeNode<T> *>::iterator> &children_iter()
        { return m_children_iter; }

        PluginTreeNode<T> *init_tree_node() const
        { return mp_init_tree_node; }
      
        bool return_from_children() const
        { return m_return_from_children; }
      
        PluginTreeNode<T> *tree_node() const
        { return mp_tree_node; }
      
        void assign_tree_node(PluginTreeNode<T> * const tree_node)
        { mp_tree_node = tree_node; }
        
        void skip_to_the_next_sibling()
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
        
        bool operator==(iterator const &iter) const
        {
          // Compare 2 iterator with different initial node is
          // meaningless.
          assert(mp_init_tree_node == iter.mp_init_tree_node);
        
          if (mp_tree_node == iter.mp_tree_node)
          {
            return true;
          }
          else
          {
            return false;
          }
        }
        
        bool operator!=(iterator const &iter) const
        {
          return !(*this == iter);
        }
      
        PluginTreeNode<T> const *operator*()
        {
          return mp_tree_node;
        }
        
        iterator &operator++();
      };
      typedef class iterator iterator;
      
      iterator begin();
      iterator end();
    };
    
    template<typename T>
    class PluginTreeLeafNode : public PluginTreeNode<T>
    {
    private:
      
      PluginInfo<T> const *mp_plugin_info;
      
    public:
      
      PluginTreeLeafNode(PluginTreeNode<T> * const parent, PluginInfo<T> const * const plugin_info);
      
      virtual std::wstring name() const
      {
        return mp_plugin_info->name_func();
      }
      
      virtual PluginInfo<T> const *plugin_info() const
      { return mp_plugin_info; }
    };
    
    template<typename T>
    class PluginTreeGroupNode : public PluginTreeNode<T>
    {
    private:
      
      std::wstring m_name;
      
    public:
      
      PluginTreeGroupNode(PluginTreeNode<T> * const parent, wchar_t const * const name);
      
      virtual std::wstring name() const;
      
      virtual PluginInfo<T> const *plugin_info() const
      { return 0; }
    };
  }
}

#include "plugin_tree.tcc"

#endif
