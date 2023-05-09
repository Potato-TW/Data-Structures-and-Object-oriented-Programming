#include "PartII.h"

void PartII::read(std::string file) {
	std::cout << "Part II reading..." << std::endl;

	ifstream in(file);
	in >> ver >> edge;
	di_graph.resize(ver);
	be_graph.resize(ver);
	for (int i = 0; i < edge; i++) {
		int a, b, c;
		in >> a >> b >> c;
		std::pair<int, int> p(b, c);
		be_graph[a].push_back(p);
		p.second = abs(p.second);
		di_graph[a].push_back(p);
	}

	in.close();
}
void PartII::solve() {
	std::cout << "Part II solving..." << std::endl;

	dijkstra();
	distance.clear();
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>> > q;
	min_heap = q;
	bellman();
}
void PartII::write(std::string file) {
	std::cout << "Part II writing..." << std::endl;

	ofstream out(file);
	out << ans_di << endl;
	if (ans_be != INT_MAX) {
		out << ans_be << endl;
	}
	else {
		out << "Negative loop detected!" << endl;
	}
}

void PartII::dis_init() {
	for (int i = 0; i < ver; i++) {
		if (i == 0) {
			distance.push_back(0);
		}
		else {
			distance.push_back(INT_MAX);
		}
	}
}
void PartII::heap_init() {
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;

	for (int i = 0; i < distance.size(); i++) {
		std::pair<int, int> p(distance[i], i);
		q.push(p);
	}

	min_heap = q;
}
void PartII::dijkstra() {
	dis_init();
	heap_init();
	
	while (!min_heap.empty()) {
		std::pair<int, int> top = min_heap.top();
		min_heap.pop();

		for (auto it = di_graph[top.second].begin(); it != di_graph[top.second].end(); it++) {
			if (top.first + it->second < distance[it->first]) {
				distance[it->first] = top.first + it->second;
			}
		}

		heap_update();
	}

	ans_di = distance[0];
	for (int i = 0; i < distance.size(); i++) {
		if (distance[i] == INT_MAX)
			continue;

		if (distance[i] > ans_di)
			ans_di = distance[i];
	}
}
void PartII::heap_update() {
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;

	while (!min_heap.empty()) {
		std::pair<int, int> p(distance[min_heap.top().second], min_heap.top().second);
		q.push(p);
		min_heap.pop();
	}

	min_heap = q;
}
void PartII::bellman() {
	dis_init();
	for (int i = 0; i < be_graph.size() - 1; i++) {
		heap_init();

		while (!min_heap.empty()) {
			std::pair<int, int> top = min_heap.top();
			min_heap.pop();

			for (auto it = be_graph[top.second].begin(); it != be_graph[top.second].end(); it++) {
				if (top.first + it->second < distance[it->first]) {
					distance[it->first] = top.first + it->second;
				}
			}

			heap_update();
		}
	}

	heap_init();

	bool acyclic = 0;
	while (!min_heap.empty()) {
		std::pair<int, int> top = min_heap.top();
		min_heap.pop();

		for (auto it = be_graph[top.second].begin(); it != be_graph[top.second].end(); it++) {
			if (top.first + it->second < distance[it->first]) {
				acyclic = 1;
				break;
			}
		}

		if (acyclic) {
			break;
		}
	}

	if (!acyclic) {
		ans_be = distance[0];
		for (int i = 0; i < distance.size(); i++) {
			if (distance[i] == INT_MAX)
				continue;

			if (distance[i] > ans_be)
				ans_be = distance[i];
		}
	}
	else
		ans_be = INT_MAX;
}
