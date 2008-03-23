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

#ifndef __wcl_colorlib_converter_hpp__
#define __wcl_colorlib_converter_hpp__

#include "export.hpp"
#include "plugin_tree.hpp"
#include "plugin_info.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    enum PluginType
    {
      PLUGIN_TYPE_SRC,
      PLUGIN_TYPE_DST
    };
    typedef enum PluginType PluginType;
    
    template<typename T>
    class Converter
    {
    private:
      
      /** @name static member: all Converter<T> objects
       * share the same database.
       */
      //@{
      WCL_COLORLIB_EXPORT static boost::mutex m_created_instance_count_mutex;
      WCL_COLORLIB_EXPORT static uint32_t m_created_instance_count;
      
      WCL_COLORLIB_EXPORT static std::wstring m_root_dir;
      
      WCL_COLORLIB_EXPORT static std::list<HMODULE> m_plugin_dll_list;
      WCL_COLORLIB_EXPORT static std::list<PluginInfo<T> > m_plugin_list;
      WCL_COLORLIB_EXPORT static PluginTreeNode<T> *mp_plugin_tree_root;
      
      WCL_COLORLIB_EXPORT static uint32_t m_curr_id;
      //@}
      
      /** @name static
       */
      //@{
      static void clear_plugin_tree();
      static void clear_plugin_dll_list();
      
      static void clear_plugin();
      
      static void ensure_no_converter_instance(boost::mutex::scoped_lock &lock);
      
      static void create_plugin_tree(
        PluginTreeNode<T> * const root_node,
        std::list<PluginInfo<T> > const &plugin_list);
    
      static void delete_plugin_tree(
        PluginTreeNode<T> * const root_node);
      
      static uint32_t find_new_id();
      //@}
      
      template<PluginType T, typename S> friend struct ConverterPluginTypeTraits;
      
    protected:
      
      PluginInfo<T> const *mp_plugin_info_for_src;
      PluginInfo<T> const *mp_plugin_info_for_dst;
      
      T *mp_plugin_for_src;
      T *mp_plugin_for_dst;
      
      /** @name life cycle
       */
      //@{
      Converter();
      virtual ~Converter();
      //@}
      
    public:
      
      /** @name Setting
       */
      //@{
      void assign_src_plugin(std::list<std::wstring> const &name);
      void assign_dst_plugin(std::list<std::wstring> const &name);
      
      void assign_src_plugin(PluginInfo<T> const * const info);
      void assign_dst_plugin(PluginInfo<T> const * const info);
      //@}
      
      /** @name Querying
       */
      //@{
      T *get_src_plugin() const
      { return mp_plugin_for_src; }
      
      T *get_dst_plugin() const
      { return mp_plugin_for_dst; }
      
      PluginInfo<T> const *get_src_plugin_info() const
      { return mp_plugin_info_for_src; }
      
      PluginInfo<T> const *get_dst_plugin_info() const
      { return mp_plugin_info_for_dst; }
      //@}
      
      /** @name static
       */
      //@{
      // I can change the plugin root directory of a
      // 'Converter' during runtime.
      static void load_plugin(std::wstring const &root_dir);
      
      static PluginTreeNode<T> *get_plugin_tree_root()
      { return mp_plugin_tree_root; }
      
      static std::wstring const &get_plugin_root_dir()
      { return m_root_dir; }
      
      // Plugin will use this function to find the plugin
      // ID.
      static PluginInfo<T> const *search_plugin(std::list<std::wstring> const &name);
      //@}
    };
        
    template<PluginType T, typename S> struct ConverterPluginTypeTraits;
    
    template<typename S>
    struct ConverterPluginTypeTraits<PLUGIN_TYPE_SRC, S>
    {
      static S *get_plugin(Converter<S> * const converter)
      {
        return converter->mp_plugin_for_src;
      }
      
      static PluginInfo<S> const *get_plugin_info(Converter<S> * const converter)
      {
        return converter->mp_plugin_info_for_src;
      }
      
      static S *get_the_other_plugin(Converter<S> * const converter)
      {
        return converter->mp_plugin_for_dst;
      }
      
      static PluginInfo<S> const *get_the_other_plugin_info(Converter<S> * const converter)
      {
        return converter->mp_plugin_info_for_dst;
      }
    };
    
    template<typename S>
    struct ConverterPluginTypeTraits<PLUGIN_TYPE_DST, S>
    {
      static S *get_plugin(Converter<S> * const converter)
      {
        return converter->mp_plugin_for_dst;
      }
      
      static PluginInfo<S> const *get_plugin_info(Converter<S> * const converter)
      {
        return converter->mp_plugin_info_for_dst;
      }
      
      static S *get_the_other_plugin(Converter<S> * const converter)
      {
        return converter->mp_plugin_for_src;
      }
      
      static PluginInfo<S> const *get_the_other_plugin_info(Converter<S> * const converter)
      {
        return converter->mp_plugin_info_for_src;
      }
    };
    
    typedef bool (*progress_stage_name_cb_func_t)(void *user_data, wchar_t const * const name);
    typedef bool (*progress_percentage_cb_func_t)(void *user_data, double_t const percentage);
  }
}

#include "converter.tcc"

#endif
