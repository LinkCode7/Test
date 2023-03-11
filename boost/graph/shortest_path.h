#pragma once
#ifdef TEST_BOOST_RTREE
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/adjacency_list.hpp>

// create a typedef for the Graph type
typedef std::pair<int, int> Edge;
typedef boost::property<boost::edge_weight_t, int> EdgeWeightProperty; // 边的权重

// directedS,bidirectionalS
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property, EdgeWeightProperty> Graph_t;

typedef boost::graph_traits<Graph_t>::vertex_descriptor vertex_descriptor;

typedef boost::property_map<Graph_t, boost::vertex_index_t>::type IndexMap;
typedef boost::graph_traits<Graph_t>::vertex_iterator vertex_iter;

namespace BoostGraph
{
	void Test();
	void Test2();


	void TestVertex(Graph_t& graph);
	void TestEdge(Graph_t& graph);

	// 遍历所有顶点得out-edges
	void TestVertexAdjacent(Graph_t& graph);

	void TestGraphProperty(Graph_t& graph);

	void TestVisitor(Graph_t& graph);

	template <class Graph>
	struct exercise_vertex_out
	{
		Graph& m_graph;

		exercise_vertex_out(Graph& g_) : m_graph(g_) {}

		typedef typename boost::graph_traits<Graph_t>::vertex_descriptor Vertex;
		void operator()(const Vertex& v) const
		{
			typedef boost::graph_traits<Graph_t> GraphTraits;
			typename boost::property_map<Graph_t, boost::vertex_index_t>::type indexMap = get(boost::vertex_index, m_graph);

			std::cout << "out-edges: ";
			typename GraphTraits::out_edge_iterator out_i, out_end;
			typename GraphTraits::edge_descriptor e;
			for (tie(out_i, out_end) = out_edges(v, m_graph); out_i != out_end; ++out_i)
			{
				e = *out_i;
				Vertex src = source(e, m_graph), targ = target(e, m_graph);
				std::cout << "(" << indexMap[src] << "," << indexMap[targ] << ") ";
			}
			std::cout << std::endl;
		}
	};


	template <class Graph>
	struct exercise_vertex_in
	{
		Graph& m_graph;

		exercise_vertex_in(Graph& g_) : m_graph(g_) {}

		typedef typename boost::graph_traits<Graph_t>::vertex_descriptor Vertex;
		void operator()(const Vertex& v) const
		{
			std::cout << "in-edges: ";

			typedef typename boost::graph_traits<Graph> GraphTraits;
			typename GraphTraits::in_edge_iterator in_i, in_end;

			typename boost::property_map<Graph_t, boost::vertex_index_t>::type indexMap = get(boost::vertex_index, m_graph);
			typename GraphTraits::edge_descriptor e;

			for (tie(in_i, in_end) = in_edges(v, m_graph); in_i != in_end; ++in_i)
			{
				e = *in_i;
				Vertex src = source(e, m_graph), targ = target(e, m_graph);
				std::cout << "(" << indexMap[src] << "," << indexMap[targ] << ") ";
			}
			std::cout << std::endl;
		}
	};

	template <class Graph>
	struct exercise_vertex_adjacent_vertices
	{
		Graph& m_graph;

		exercise_vertex_adjacent_vertices(Graph& g_) : m_graph(g_) {}

		typedef typename boost::graph_traits<Graph_t>::vertex_descriptor Vertex;
		void operator()(const Vertex& v) const
		{
			typename boost::property_map<Graph_t, boost::vertex_index_t>::type indexMap = get(boost::vertex_index, m_graph);

			std::cout << "adjacent vertices: ";
			typename boost::graph_traits<Graph>::adjacency_iterator ai;
			typename boost::graph_traits<Graph>::adjacency_iterator ai_end;
			for (tie(ai, ai_end) = adjacent_vertices(v, m_graph); ai != ai_end; ++ai)
			{
				std::cout << indexMap[*ai] << " ";
			}
			std::cout << std::endl;
		}
	};


	/*
	*
	*/
	template <class PredecessorMap>
	class record_predecessors : public boost::dijkstra_visitor<>
	{
	public:
		record_predecessors(PredecessorMap p) : m_predecessor(p) { }

		template <class Edge, class Graph>
		void edge_relaxed(Edge e, Graph& g)
		{
			// set the parent of the target(e) to source(e)
			put(m_predecessor, target(e, g), source(e, g));
		}
	protected:
		PredecessorMap m_predecessor;
	};

	template <class PredecessorMap>
	record_predecessors<PredecessorMap> make_predecessor_recorder(PredecessorMap p)
	{
		return record_predecessors<PredecessorMap>(p);
	}

} // namespace BoostGraph

#endif // TEST_BOOST_RTREE
