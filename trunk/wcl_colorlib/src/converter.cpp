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

#include "converter.hpp"
#include "color_space_converter_plugin.hpp"
#include "subsampling_converter_plugin.hpp"

namespace Wcl
{
  namespace Colorlib
  {
    template<> uint32_t Converter<ColorSpaceConverterPlugin>::m_created_instance_count = 0;
    template<> boost::mutex Converter<ColorSpaceConverterPlugin>::m_created_instance_count_mutex;
    template<> std::wstring Converter<ColorSpaceConverterPlugin>::m_root_dir;
    template<> std::list<HMODULE> Converter<ColorSpaceConverterPlugin>::m_plugin_dll_list;
    template<> std::list<PluginInfo<ColorSpaceConverterPlugin> > Converter<ColorSpaceConverterPlugin>::m_plugin_list;
    template<> PluginTreeNode<ColorSpaceConverterPlugin> *Converter<ColorSpaceConverterPlugin>::mp_plugin_tree_root = 0;
    template<> uint32_t Converter<ColorSpaceConverterPlugin>::m_curr_id = 0;
    
    template<> uint32_t Converter<SubSamplingConverterPlugin>::m_created_instance_count = 0;
    template<> boost::mutex Converter<SubSamplingConverterPlugin>::m_created_instance_count_mutex;
    template<> std::wstring Converter<SubSamplingConverterPlugin>::m_root_dir;
    template<> std::list<HMODULE> Converter<SubSamplingConverterPlugin>::m_plugin_dll_list;
    template<> std::list<PluginInfo<SubSamplingConverterPlugin> > Converter<SubSamplingConverterPlugin>::m_plugin_list;
    template<> PluginTreeNode<SubSamplingConverterPlugin> *Converter<SubSamplingConverterPlugin>::mp_plugin_tree_root = 0;
    template<> uint32_t Converter<SubSamplingConverterPlugin>::m_curr_id = 0;
  }
}
