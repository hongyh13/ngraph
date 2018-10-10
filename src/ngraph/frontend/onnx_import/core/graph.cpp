//*****************************************************************************
// Copyright 2017-2018 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//*****************************************************************************

#include "graph.hpp"
#include "node.hpp"

namespace ngraph
{
    namespace onnx_import
    {
        namespace detail
        {
            std::string to_string(const std::vector<std::string>& vector)
            {
                std::string result;
                for (std::size_t i{0}; i < vector.size(); ++i)
                {
                    result += (i != 0 ? ", " : "") + vector.at(i);
                }
                return result;
            }
        }

        Graph::Graph(const onnx::GraphProto& graph_proto, const OperatorSet& opset)
            : m_graph_proto{&graph_proto}
            , m_opset{&opset}
        {
            for (const auto& tensor : m_graph_proto->initializer())
            {
                if (tensor.has_name())
                {
                    m_initializers.emplace(tensor.name(), Tensor{tensor});
                }
            }

            // Process all ONNX graph inputs, convert them to nGraph nodes and store in cache
            for (const auto& input : m_graph_proto->input())
            {
                m_inputs.emplace_back(input);
                m_ng_node_cache[input.name()] =
                    m_inputs.back().get_ng_node(m_parameters, m_initializers);
            }

            for (const auto& output : m_graph_proto->output())
            {
                m_outputs.emplace_back(output);
            }

            // Verify that ONNX graph contains only nodes of available operator types
            std::vector<std::string> unknown_operator_types;
            for (const auto& node_ptoro : m_graph_proto->node())
            {
                auto it{m_opset->find(node_ptoro.op_type())};
                if (it == std::end(*m_opset))
                {
                    unknown_operator_types.push_back(node_ptoro.op_type());
                }
            }

            NGRAPH_ASSERT(unknown_operator_types.empty())
                << "unknown operators: " << detail::to_string(unknown_operator_types);

            // Process ONNX graph nodes, convert to nGraph nodes
            for (const auto& node_proto : m_graph_proto->node())
            {
                m_nodes.emplace_back(node_proto, this);
                const Node& node{m_nodes.back()};
                NodeVector ng_nodes{node.get_ng_nodes()};
                for (int i = 0; i < ng_nodes.size(); i++)
                {
                    m_ng_node_cache[node.output(i)] = ng_nodes[i];
                }
            }
        }

    } // namespace onnx_import

} // namespace ngraph
