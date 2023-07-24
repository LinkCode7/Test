#include "shortest_path.h"

#ifdef TEST_BOOST_RTREE
    #pragma warning(disable : 4267)

using namespace boost;
using namespace std;

void boost_graph()
{
    using namespace BoostGraph;

    // Test2();

    enum
    {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H
    };

    // 数组创建图
    Edge edge_array[] = {Edge(A, B), Edge(B, C), Edge(B, D), Edge(D, E), Edge(D, F), Edge(E, F), Edge(C, F)};
    int  weights[]    = {6, 3, 3, 4, 2, 4, 9};

    int num_nodes = 6;
    // 创建图的顶点不能用负数
    Graph_t graph(edge_array, edge_array + sizeof(edge_array) / sizeof(Edge), weights, num_nodes);

    TestVertex(graph);
    TestEdge(graph);
    TestVertexAdjacent(graph);

    TestGraphProperty(graph);
    TestVisitor(graph);
}

namespace BoostGraph
{
void Test()
{
    enum
    {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H
    };

    // 创建图
    Graph_t newGraph;
    add_edge(A, B, 6, newGraph);
    add_edge(C, D, 3, newGraph);

    add_edge(A, C, 3, newGraph);

    // 起点、终点
    int iBeginPos = A, iEndPos = C;

    size_t size = num_vertices(newGraph);

    vector<vertex_descriptor> vecParent(size);
    // std::vector<Graph::edge_descriptor> q(size);
    vector<int> vecDistance(size);

    vertex_descriptor startVertex = vertex(iBeginPos, newGraph); // s

    cout << "A -> F最短路径Test\n" << endl;

    dijkstra_shortest_paths(newGraph, startVertex,
                            predecessor_map(boost::make_iterator_property_map(vecParent.begin(), get(boost::vertex_index, newGraph)))
                                .distance_map(boost::make_iterator_property_map(vecDistance.begin(), get(boost::vertex_index, newGraph))));

    cout << "各顶点到A的最短距离及其父节点\n" << endl;

    graph_traits<Graph_t>::vertex_iterator vi, vend;
    for (boost::tie(vi, vend) = vertices(newGraph); vi != vend; ++vi)
    {
        string strVertex   = to_string(*vi);
        string strDistance = to_string(vecDistance[*vi]);
        string strParent   = to_string(vecParent[*vi]);
    }

    // A->F 从终止点到起始点的路径
    vector<int> vecPath;
    int         t = iEndPos;
    for (; t != iBeginPos; t = vecParent[t])
    {
        vecPath.push_back(t);
    }
    vecPath.push_back(iBeginPos);

    // 反转路线 从起始点到出发点
    reverse(vecPath.begin(), vecPath.end());

    // 输出路径
    for (size_t i = 0; i < vecPath.size(); ++i)
    {
        cout << vecPath[i] << "->";
    }
    cout << endl;
}

void Test2()
{
    enum
    {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H
    };

    #define CREATE_GRAPH_BY_ARRAY
    #ifdef CREATE_GRAPH_BY_ARRAY
    // 数组创建图
    Edge edge_array[] = {Edge(A, B), Edge(B, C), Edge(B, D), Edge(D, E), Edge(D, F), Edge(E, F), Edge(C, F)};
    int  weights[]    = {6, 3, 3, 4, 2, 4, 9};

    int     num_nodes = 6;
    Graph_t newGraph(edge_array, edge_array + sizeof(edge_array) / sizeof(Edge), weights, num_nodes); // 创建图的顶点不能用负数

    // add_edge(A, B, 6, newGraph);
    add_edge(G, H, 1, newGraph);
    int iTestt = A;
    #else
    Graph newGraph;
    add_edge(A, B, 6, newGraph);
    add_edge(B, C, 3, newGraph);
    add_edge(B, D, 3, newGraph);
    add_edge(D, E, 4, newGraph);
    add_edge(D, F, 2, newGraph);
    add_edge(E, F, 4, newGraph);
    add_edge(C, F, 9, newGraph);
    #endif

    // 起点、终点
    int iBeginPos = A, iEndPos = H;

    size_t                    size = num_vertices(newGraph);
    vector<vertex_descriptor> vecParent(size);
    // std::vector<Graph::edge_descriptor> q(size);
    vector<int> vecDistance(size);

    vertex_descriptor startVertex = vertex(iBeginPos, newGraph); // s

    cout << "A -> F最短路径Test" << endl;

    dijkstra_shortest_paths(newGraph, startVertex,
                            predecessor_map(boost::make_iterator_property_map(vecParent.begin(), get(boost::vertex_index, newGraph)))
                                .distance_map(boost::make_iterator_property_map(vecDistance.begin(), get(boost::vertex_index, newGraph))));

    cout << "各顶点到A的最短距离及其父节点" << endl;

    graph_traits<Graph_t>::vertex_iterator vi, vend;
    for (boost::tie(vi, vend) = vertices(newGraph); vi != vend; ++vi)
    {
        string strVertex   = to_string(*vi);
        string strDistance = to_string(vecDistance[*vi]);
        string strParent   = to_string(vecParent[*vi]);
    }

    // A->F 从终止点到起始点的路径
    vector<int> vecPath;
    int         t = iEndPos;
    for (; t != iBeginPos; t = vecParent[t])
    {
        vecPath.push_back(t);
    }
    vecPath.push_back(iBeginPos);

    // 反转路线 从起始点到出发点
    reverse(vecPath.begin(), vecPath.end());

    // 输出路径
    for (size_t i = 0; i < vecPath.size(); ++i)
    {
        cout << vecPath[i] << "->";
    }

    cout << endl;

    // 输出结果：
    // A -> F最短路径Test
    //各顶点到A的最短距离及其父节点
    // distance(0) = 0, parent(0) = 0
    // distance(1) = 6, parent(1) = 0
    // distance(2) = 9, parent(2) = 1
    // distance(3) = 9, parent(3) = 1
    // distance(4) = 13, parent(4) = 3
    // distance(5) = 11, parent(5) = 3
    // 0->1->3->5
}

void TestVertex(Graph_t& graph)
{
    int iVertexCount = 0;

    IndexMap indexMap = get(vertex_index, graph);

    std::pair<vertex_iter, vertex_iter> vp = vertices(graph);
    for (; vp.first != vp.second; ++vp.first)
    {
        cout << indexMap[*(vp.first)] << endl;

        ++iVertexCount;
    }

    return;
}

void TestEdge(Graph_t& graph)
{
    IndexMap indexMap = get(vertex_index, graph);

    std::cout << "edges(g) = ";

    graph_traits<Graph_t>::edge_iterator ei, ei_end;

    for (tie(ei, ei_end) = edges(graph); ei != ei_end; ++ei)
    {
        std::cout << "(" << indexMap[source(*ei, graph)] << "," << indexMap[target(*ei, graph)] << ") ";
    }

    std::cout << std::endl;
    return;
}

// 遍历所有顶点得in/out-edges
void TestVertexAdjacent(Graph_t& graph)
{
    std::pair<vertex_iter, vertex_iter> vp = vertices(graph);

    // out-edges
    std::for_each(vp.first, vp.second, exercise_vertex_out<Graph_t>(graph));

    // in-edges:Graph_t第三个参数必须是bidirectionalS
    // std::for_each(vp.first, vp.second, exercise_vertex_in<Graph_t>(graph));

    // adjacent vertices
    std::for_each(vp.first, vp.second, exercise_vertex_adjacent_vertices<Graph_t>(graph));
}

void TestGraphProperty(Graph_t& graph)
{
    typedef adjacency_list<listS, vecS, directedS, no_property, property<edge_weight_t, int> > Graph;
    typedef graph_traits<Graph>::vertex_descriptor                                             Vertex;
    typedef std::pair<int, int>                                                                Pair;

    #ifdef USE_NEW_GRAPH
    const int num_nodes = 5;
    Pair      edges[]   = {Pair(0, 2), Pair(1, 1), Pair(1, 3), Pair(1, 4), Pair(2, 1), Pair(2, 3), Pair(3, 4), Pair(4, 0), Pair(4, 1)};

    int   weights[] = {1, 2, 1, 2, 7, 3, 1, 1, 1};
    Graph graph(edges, edges + sizeof(edges) / sizeof(Pair), weights, num_nodes);
    #endif // USE_NEW_GRAPH

    // vector for storing distance property
    std::vector<int> vecDistance(num_vertices(graph));
    // get the first vertex
    Vertex startVertex = *(vertices(graph).first);
    // invoke variant 2 of Dijkstra's algorithm
    dijkstra_shortest_paths(graph, startVertex, distance_map(&vecDistance[0]));

    IndexMap indexMap = get(vertex_index, graph);

    std::cout << dec << "\n\ndistances from start vertex:" << std::endl;

    std::pair<vertex_iter, vertex_iter> vp = vertices(graph);
    vertex_iter                         vi = vp.first;
    for (; vi != vp.second; ++vi)
    {
        std::cout << "distance(" << indexMap(*vi) << ") = " << vecDistance[*vi] << std::endl;
    }

    std::cout << std::endl;
}

void TestVisitor(Graph_t& graph)
{
    using std::cout;
    using std::endl;
    using std::vector;

    typedef adjacency_list<listS, vecS, directedS, no_property, property<edge_weight_t, int> > Graph;
    typedef graph_traits<Graph>::vertex_descriptor                                             Vertex;

    #ifdef USE_NEW_GRAPH
    const int num_nodes = 5;
    Pair      edges[]   = {Pair(0, 2), Pair(1, 1), Pair(1, 3), Pair(1, 4), Pair(2, 1), Pair(2, 3), Pair(3, 4), Pair(4, 0), Pair(4, 1)};

    int   weights[] = {1, 2, 1, 2, 7, 3, 1, 1, 1};
    Graph graph(edges, edges + sizeof(edges) / sizeof(Pair), weights, num_nodes);
    #endif // USE_NEW_GRAPH

    std::vector<int> vecDistance(num_vertices(graph));

    Vertex startVertex = *(vertices(graph).first);

    // the predecessor 数组
    vector<Vertex> pre(num_vertices(graph));
    dijkstra_shortest_paths(graph, startVertex, distance_map(&vecDistance[0]).visitor(make_predecessor_recorder(&pre[0])));

    cout << dec << "\n\nparents in the tree of shortest paths:" << endl;

    std::pair<vertex_iter, vertex_iter> vp = vertices(graph);
    vertex_iter                         vi = vp.first;
    for (; vi != vp.second; ++vi)
    {
        if (pre[*vi] == Vertex())
            cout << "parent(" << *vi << ") = no parent" << endl;
        else
            cout << "parent(" << *vi << ") = " << pre[*vi] << endl;
    }

    cout << endl;
}

} // namespace BoostGraph

#endif // TEST_BOOST_RTREE

// 参考：CSDN博主IceCreHaker BGL使用dijkstra计算图的最短路径
// https://blog.csdn.net/starelegant/article/details/78357146

// 较好的Boost Graph说明
// CSDN		https://blog.csdn.net/kevin_ysu/article/details/7558271
// 博客园	https://www.cnblogs.com/forgood/archive/2013/10/22/3382228.html

// https://blog.csdn.net/zhangweilong219/article/details/78995295

// 20200423
// https://blog.csdn.net/u011630575/article/details/80837629
