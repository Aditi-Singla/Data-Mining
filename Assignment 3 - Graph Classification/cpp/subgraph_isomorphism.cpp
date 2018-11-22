#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/vf2_sub_graph_iso.hpp>
#include <boost/graph/graph_utility.hpp>

using namespace boost;
using namespace std;

int startIndex = 0;
std::unordered_map<string, int> m;

// Define edge and vertex properties
typedef property<vertex_name_t, string, property<vertex_index_t, int> > vp;
typedef property<edge_name_t, string> ep;

// Using a vecS graphs => the index maps are implicit.
typedef adjacency_list<vecS, vecS, undirectedS, vp, ep> graph_type;

typedef property_map<graph_type, vertex_name_t>::type vertex_name_map_t;
typedef property_map_equivalent<vertex_name_map_t, vertex_name_map_t> vertex_comp_t;

typedef property_map<graph_type, edge_name_t>::type edge_name_map_t;
typedef property_map_equivalent<edge_name_map_t, edge_name_map_t> edge_comp_t;

void getGraphs(vector<graph_type> &g, string infilename) {
  ifstream fin(infilename);
  string line = "";

  while(getline(fin, line)) {
    // first line has been obtained
    graph_type graph;

    // obtain num of vertices
    getline(fin, line);

    int num_vertices = stoi(line);

    for (int i = 0; i < num_vertices; ++i) {
      getline(fin, line);

      if (m.find(line) == m.end()) {
        m[line] = startIndex++;
      }

      add_vertex(vp(to_string(m[line])), graph);
    }

    // obtain num of edges
    getline(fin, line);

    int num_edges = stoi(line);

    for (int i = 0; i < num_edges; ++i) {
      getline(fin, line);
      istringstream str(line);
      string node1 = "", node2 = "", edgeLabel = "";
      str >> node1 >> node2 >> edgeLabel;
      int nodeId1 = stoi(node1);
      int nodeId2 = stoi(node2);
      add_edge(nodeId1, nodeId2, ep(edgeLabel), graph); 
    }

    g.push_back(graph);
  }

  fin.close();
}

void getFrequentGraphs(vector<graph_type> &g, string infilename) {
  ifstream fin(infilename);
  string line = "";

  while(getline(fin, line)) {
    // first line has been obtained
    graph_type graph;

    // obtain num of vertices
    while(getline(fin, line)) {
      if (line.empty()) {
        break;
      }

      if (line[0] == 'v') {
        string tag = "", index = "", label = "";
        istringstream str(line);

        str >> tag >> index >> label;
        add_vertex(vp(label), graph);
      } 
      else if (line[0] == 'e') {
        string tag = "", v1 = "", v2 = "", label = "";
        istringstream str(line);

        str >> tag >> v1 >> v2 >> label;

        int nodeId1 = stoi(v1);
        int nodeId2 = stoi(v2);
        add_edge(nodeId1, nodeId2, ep(label), graph); 
      }     
    }

    g.push_back(graph);
  }

  fin.close();
}

template<typename Graph1, typename Graph2> struct compute_matrix {
  Graph1 g_;
  Graph2 h_;
  vector<vector<int>> *mat_;
  int i_ = 0;
  int j_ = 0;

  compute_matrix(Graph1 g, Graph2 h, vector<vector<int>> *mat, int i, int j) {
    g_ = g;
    h_ = h;
    mat_ = mat;
    i_ = i;
    j_ = j;
  }

  template <typename CorrespondenceMap1To2,
          typename CorrespondenceMap2To1>
  bool operator()(CorrespondenceMap1To2 f, CorrespondenceMap2To1 g) const {
    (*mat_)[i_][j_] = 1;
  }
};

void updateMat(vector<vector<int>> &x_train, int i, int j) {
  x_train[i][j] = 1;
}

int main(int argc, char** argv) {
  string train_file(argv[1]);
  string test_file(argv[2]);
  string fsg_file(argv[3]);

  vector<graph_type> train_graphs, test_graphs, fsg;

  getGraphs(train_graphs, train_file);
  getGraphs(test_graphs, test_file);

  getFrequentGraphs(fsg, fsg_file);

  int NUM_TRAIN_SIZE = train_graphs.size();
  int NUM_FSG_SIZE = fsg.size();

  vector<vector<int>> mat(NUM_TRAIN_SIZE, vector<int> (NUM_FSG_SIZE, 0));

  for (int i = 0; i < NUM_FSG_SIZE; i++) {
    graph_type graph1 = fsg[i];

    for (int j = 0; j < NUM_TRAIN_SIZE; j++) {
      graph_type graph2 = train_graphs[j];

      vertex_comp_t vertex_comp = make_property_map_equivalent(get(vertex_name, graph1), get(vertex_name, graph2));
      edge_comp_t edge_comp = make_property_map_equivalent(get(edge_name, graph1), get(edge_name, graph2));

      // Create callback
      compute_matrix<graph_type, graph_type> callback(graph1, graph2, &mat, j, i);

      vf2_subgraph_iso(graph1, graph2, callback, vertex_order_by_mult(graph1),
                       edges_equivalent(edge_comp).vertices_equivalent(vertex_comp));
    }
  }

  return 0;
}
