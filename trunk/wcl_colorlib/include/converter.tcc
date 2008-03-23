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

#include "converter.hpp"
#include "plugin_tree.hpp"
#include "exception.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    // ==========================================================================
    //                              Converter
    // ==========================================================================
    template<typename T>
    Converter<T>::Converter()
      : mp_plugin_info_for_src(0),
        mp_plugin_info_for_dst(0),
        mp_plugin_for_src(0),
        mp_plugin_for_dst(0)
    {
      boost::mutex::scoped_lock lock(m_created_instance_count_mutex);
      
      ++m_created_instance_count;
    }
    
    template<typename T>
    Converter<T>::~Converter()
    {
      boost::mutex::scoped_lock lock(m_created_instance_count_mutex);
      
      assert(m_created_instance_count > 0);
      
      --m_created_instance_count;
    }
    
    template<typename T>
    void
    Converter<T>::assign_src_plugin(
      std::list<std::wstring> const &name)
    {
      if (0 == mp_plugin_tree_root)
      {
        throw DoesNotSpecifyColorSpaceConverterDatabaseException();
      }
      
      {
        if (mp_plugin_for_src != 0)
        {
          assert(mp_plugin_info_for_src != 0);
          
          mp_plugin_info_for_src->delete_func(mp_plugin_for_src);
          
          mp_plugin_for_src = 0;
          mp_plugin_info_for_src = 0;
        }
        
        mp_plugin_info_for_src = search_plugin(name);
        
        if (0 == mp_plugin_info_for_src)
        {
          throw InvalidSrcFmtException();
        }
        
        mp_plugin_for_src = mp_plugin_info_for_src->create_func(this);
        assert(mp_plugin_for_src != 0);
      }
    }
    
    template<typename T>
    void
    Converter<T>::assign_dst_plugin(
      std::list<std::wstring> const &name)
    {
      if (0 == mp_plugin_tree_root)
      {
        throw DoesNotSpecifyColorSpaceConverterDatabaseException();
      }
      
      {
        if (mp_plugin_for_dst != 0)
        {
          assert(mp_plugin_info_for_dst != 0);
          
          mp_plugin_info_for_dst->delete_func(mp_plugin_for_dst);
          
          mp_plugin_for_dst = 0;
          mp_plugin_info_for_dst = 0;
        }
        
        mp_plugin_info_for_dst = search_plugin(name);
        
        if (0 == mp_plugin_info_for_dst)
        {
          throw InvalidDstFmtException();
        }
        
        mp_plugin_for_dst = mp_plugin_info_for_dst->create_func(this);
        assert(mp_plugin_for_dst != 0);
      }
    }
    
    template<typename T>
    void
    Converter<T>::assign_src_plugin(
      PluginInfo<T> const * const info)
    {
      if (mp_plugin_for_src != 0)
      {
        assert(mp_plugin_info_for_src != 0);
        
        mp_plugin_info_for_src->delete_func(mp_plugin_for_src);
        
        mp_plugin_for_src = 0;
        mp_plugin_info_for_src = 0;
      }
      
      mp_plugin_info_for_src = info;
      
      mp_plugin_for_src = mp_plugin_info_for_src->create_func(this);
      assert(mp_plugin_for_src != 0);
    }
    
    template<typename T>
    void
    Converter<T>::assign_dst_plugin(
      PluginInfo<T> const * const info)
    {
      if (mp_plugin_for_dst != 0)
      {
        assert(mp_plugin_info_for_dst != 0);
        
        mp_plugin_info_for_dst->delete_func(mp_plugin_for_dst);
        
        mp_plugin_for_dst = 0;
        mp_plugin_info_for_dst = 0;
      }
      
      mp_plugin_info_for_dst = info;
      
      mp_plugin_for_dst = mp_plugin_info_for_dst->create_func(this);
      assert(mp_plugin_for_dst != 0);
    }
    
    template<typename T>
    void
    Converter<T>::clear_plugin_tree()
    {
      if (mp_plugin_tree_root != 0)
      {
        delete_plugin_tree(mp_plugin_tree_root);
        
        ::delete mp_plugin_tree_root;
        
        mp_plugin_tree_root = 0;
      }
    }
  
    template<typename T>
    void
    Converter<T>::clear_plugin_dll_list()
    {
      BOOST_FOREACH(HMODULE module, m_plugin_dll_list)
      {
        ::FreeLibrary(module);
      }
    }
    
    template<typename T>
    void
    Converter<T>::clear_plugin()
    {
      clear_plugin_tree();
      
      m_plugin_list.clear();
      
      clear_plugin_dll_list();
    }
    
    // ==========================================================================
    //                                Plugin Tree
    // ==========================================================================  
    template<typename T>
    void
    Converter<T>::create_plugin_tree(
      PluginTreeNode<T> * const root_node,
      std::list<PluginInfo<T> > const &plugin_list)
    {
      assert(root_node != 0);
      
      BOOST_FOREACH(PluginInfo<T> const &plugin_info, plugin_list)
      {
        wchar_t const **parent_name_list;
        uint32_t parent_name_list_size;
        
        plugin_info.get_parent_name_list_func(&parent_name_list, &parent_name_list_size);
        
        PluginTreeNode<T> *curr_parent_node = root_node;
        
        std::list<std::wstring> names;
        
        // Find and create parent group nodes.
        for (uint32_t i = 0; i < parent_name_list_size; ++i)
        {
          names.clear();
          names.push_back(parent_name_list[i]);
          
          PluginTreeNode<T> *node = curr_parent_node->search(names);
          
          if (0 == node)
          {
            node = ::new PluginTreeGroupNode<T>(curr_parent_node, parent_name_list[i]);
            
            curr_parent_node->add_child(node);
          }
          
          curr_parent_node = node;
        }
        
        names.clear();
        names.push_back(plugin_info.name_func());
        
        assert(0 == curr_parent_node->search(names));
        
        PluginTreeNode<T> * const node = ::new PluginTreeLeafNode<T>(curr_parent_node, &plugin_info);
        
        curr_parent_node->add_child(node);
      }
    }
    
    template<typename T>
    void
    Converter<T>::delete_plugin_tree(
      PluginTreeNode<T> * const root_node)
    {
      if (0 == root_node)
      {
        assert(0);
        return;
      }
      
      BOOST_FOREACH(PluginTreeNode<T> * const node, root_node->children())
      {
        delete_plugin_tree(node);
        
        ::delete node;
      }
    }
    
    template<typename T>
    void
    Converter<T>::load_plugin(std::wstring const &root_dir)
    {
      if (root_dir.compare(m_root_dir) != 0)
      {
        // Plugin root directory has been changed.
        
        // Becuase I am going to change the plugin database,
        // hence, I have to ensure there exists only one
        // converter (i.e. me) currently.
        boost::mutex::scoped_lock lock(m_created_instance_count_mutex);
      
        if (m_created_instance_count != 0)
        {
          throw LoadPluginWhenAtLeastOneConverterIsInUseException();
        }
      
        // Only me uses the converter now, so that I can
        // change the plugin database now.
        m_root_dir = root_dir;
      
        clear_plugin();
      
        boost::filesystem::wpath root_path(m_root_dir);
      
        if (false == boost::filesystem::exists(root_path))
        {
          assert(0);
          return;
        }
    
        if (false == boost::filesystem::is_directory(root_path))
        {
          assert(0);
          return;
        }
      
        // default construction yields past-the-end
        boost::filesystem::wdirectory_iterator end_itr;
        
        std::wstring desired_extension;
        
#if defined(_DEBUG)
        desired_extension.assign(L"_d.dll");
#else
        desired_extension.assign(L"_nd.dll");
#endif
      
        for (boost::filesystem::wdirectory_iterator itr(root_path);
             itr != end_itr;
             ++itr)
        {
          if (boost::filesystem::is_directory(itr->status()))
          {
            // a directory, I don't need to do anything about a
            // directory.
          }
          else
          {
            std::wstring filename = itr->path().leaf();
            
            if (0 == filename.compare(
                  filename.length() - desired_extension.length(),
                  desired_extension.length(),
                  desired_extension.c_str(),
                  0,
                  desired_extension.length()))
            {
              // I found a dll.
              HMODULE module = ::LoadLibrary(itr->path().string().c_str());
              m_plugin_dll_list.push_back(module);
              
              PluginInfo<T>::PluginCreateFunc create_func = (PluginInfo<T>::PluginCreateFunc)GetProcAddress(module, "create_plugin");
              PluginInfo<T>::PluginDeleteFunc delete_func = (PluginInfo<T>::PluginDeleteFunc)GetProcAddress(module, "delete_plugin");
              PluginInfo<T>::PluginNameFunc   name_func   = (PluginInfo<T>::PluginNameFunc)  GetProcAddress(module, "name");
              PluginInfo<T>::PluginGetParentNameListFunc get_parent_name_list_func = (PluginInfo<T>::PluginGetParentNameListFunc)GetProcAddress(module, "get_parent_name_list");
              
              if ((0 == create_func) || (0 == delete_func) || (0 == name_func) || (0 == get_parent_name_list_func))
              {
                assert(0);
                continue;
              }
              
              m_plugin_list.push_back(PluginInfo<T>(create_func,
                                                    delete_func,
                                                    name_func,
                                                    get_parent_name_list_func,
                                                    m_curr_id++));
            }
          }
        }
        
        assert(0 == mp_plugin_tree_root);
        mp_plugin_tree_root = ::new PluginTreeGroupNode<T>(0, L"root");
        
        // Create plugin tree.
        create_plugin_tree(mp_plugin_tree_root, m_plugin_list);
      }
    }
    
    template<typename T>
    PluginInfo<T> const *
    Converter<T>::search_plugin(
      std::list<std::wstring> const &name)
    {
      if (0 == mp_plugin_tree_root)
      {
        throw DoesNotSpecifyColorSpaceConverterDatabaseException();
      }
      
      PluginTreeNode<T> * const node = mp_plugin_tree_root->search(name);
      
      if (0 == node)
      {
        return 0;
      }
      else
      {
        return node->plugin_info();
      }
    }
  }
}
