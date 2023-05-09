#include "PartI.h"

void PartI::read(std::string file) {
    std::cout << "Part I reading..." << std::endl;

    ifstream in(file);
    in >> ver >> edge;
    graph.resize(ver);
    rev_graph.resize(ver);
    finish.resize(ver);
    for (int i = 0; i < edge; i++) {
        int a, b, c;
        in >> a >> b >> c;
        
        pair<int, int> p(b, c);
        graph[a].push_back(p);
        pair<int, int> rp(a, c);
        rev_graph[b].push_back(rp);
        
        finish[a][b] = c;
    }

    in.close();
}
void PartI::solve() {
    std::cout << "Part I solving..." << std::endl;

    iscylic = isThereACycle();
    if (iscylic) {
        kosoraju();
    }
    else {
        topologicalSort();
    }
}
void PartI::write(std::string file) {
    std::cout << "Part I writing..." << std::endl;

    if (iscylic) {
        for (int i = 0; i < scc.size(); i++) {
            if (scc[i].empty())  continue;
            //bubble sort
            map<int, int>temp;
            for (int j = 0; j < scc[i].size(); j++) {
                temp[scc[i][j]]++;
            }
            take.push_back(temp);
        }

        for (int i = 0; i < take.size(); i++) {
            for (int j = i + 1; j < take.size(); j++) {
                if (take[i].begin()->first > take[j].begin()->first) {
                    map<int, int>  temp = take[i];
                    take[i] = take[j];
                    take[j] = temp;
                }
            }
        }

        vector<vector<pair<int, int>>> ans(ver);
        for (int i = 0; i < take.size(); i++) {
            vector<pair<int, int>> v; //tar wei

            for (int j = i + 1; j < take.size(); j++) {
                find(v, i, j);
            }

            if (!v.empty())
                ans[i] = v;
        }
        for (int i = take.size() - 1; i >= 0; i--) {
            vector<pair<int, int>> v; //tar wei

            for (int j = i - 1; j >= 0; j--) {
                find(v, i, j);
            }

            if (!v.empty())
                ans[i] = v;
        }

        int scc_ver = take.size(),
            scc_edge = 0;
        for (int i = 0; i < ans.size(); i++) {
            if (!ans[i].empty()) {
                scc_edge += ans[i].size();
            }
        }

        ofstream out(file);
        out << scc_ver << " " << scc_edge << endl;
        for (int i = 0; i < scc_ver; i++) {
            if (!ans[i].empty())
                for (int j = 0; j < ans[i].size(); j++)
                    out << i << " " << ans[i][j].first << " " << ans[i][j].second << endl;
        }
        out.close();
    }
    else {
        ofstream out(file);
        while (!topo_order.empty()) {
            out << topo_order.top() << " ";
            topo_order.pop();
        }
        out.close();
    }
}
void PartI::find(vector<pair<int, int>>& v, int i, int j) {
    int weight = 0;
    map<int, int> from = take[i],
                    to = take[j];

    for (auto t_from = from.begin(); t_from != from.end(); t_from++) {
        for (auto t_to = to.begin(); t_to != to.end(); t_to++) {
            if (finish[t_from->first].find(t_to->first) != finish[t_from->first].end()) {
                weight += finish[t_from->first][t_to->first];
            }
        }
    }
    if (weight != 0) {
        pair<int, int> p(j, weight);
        v.push_back(p);
    }
}

bool PartI::isThereACycle()
{
    for(int k=0;k<ver;k++)
    {
        vector<int> a(ver, 0);
        a[k] = 1;
        vector<int>first, cycle;
        cycle.push_back(k);
        vector<vector<int>>second;

        for (auto it = graph[k].begin(); it != graph[k].end(); it++) {
            first.push_back(it->first);
        }

        if (!first.empty())
        {
            second.push_back(first);
            while (!second.empty())
            {
                while ((second.back()).empty())
                {
                    second.pop_back();
                    a[cycle.back()] = 0;
                    cycle.pop_back();
                    if (second.empty())
                        break;
                }
                if (second.empty())
                    break;
                int last = (second.back()).back();
                (second.back()).pop_back();
                a[last] = 1;
                cycle.push_back(last);
                vector<int>third;

                for (auto it = graph[last].begin(); it != graph[last].end(); it++) {
                    if (a[it->first])  return 1;
                    third.push_back(it->first);
                }


                if (!third.empty())
                    second.push_back(third);
                else
                {
                    a[last] = 0;
                    cycle.pop_back();
                }
            }
        }
    }

    return false;
}
void PartI::rec(int a, bool* visit){
    visit[a] = 1;

    for (auto it = to_graph[a].begin(); it != to_graph[a].end(); it++)
        if (!visit[it->first])
            rec(it->first, visit);

    topo_order.push(a);
}
void PartI::topologicalSort(){
    priority_queue<pair<int, int>> pq;
    to_graph.resize(ver);
    
    for (int i = 0; i < graph.size(); i++) {
        for (auto it = graph[i].begin(); it != graph[i].end(); it++) {
            pq.push(*it);
        }
        while (!pq.empty()) {
            to_graph[i].push_back(pq.top());
            pq.pop();
        }
    }

    bool* visit = new bool[ver];
    for (int i = 0; i < ver; i++)
        visit[i] = 0;

    for (int i = ver - 1; i >= 0; i--)
        if (!visit[i])
            rec(i, visit);
}
void PartI::showTopo() {
    stack<int> stack = topo_order;
    while (!stack.empty()) {
        cout << stack.top() << " ";
        stack.pop();
    }
    cout << endl;
}

void PartI::kosoraju() {
    for (int i = 0; i <= ver; i++) {
        visit.push_back(0);
    }

    for (int i = 1; i < ver; i++) {
        if (!visit[i]) first_dfs(i);
    }

    visit.clear();
    scc.resize(ver);
    for (int i = 0; i <= ver; i++) {
        visit.push_back(0);
        //scc.push_back(0);
    }


    for (int i = path.size() - 1; i >= 0; i--) { 
        if (!visit[path[i]]) {
            second_dfs(path[i], path[i]);
        }
    }

}
void PartI::first_dfs(int r) {
    if (visit[r]) 
        return;

    visit[r] = 1;

    for (auto it = graph[r].begin(); it != graph[r].end(); it++) {
        first_dfs(it->first);
    }

    path.push_back(r); 
}
void PartI::second_dfs(int r, int anc) {
    if (visit[r])
        return;

    visit[r] = 1;
    scc[anc].push_back(r);
    for (auto it = rev_graph[r].begin(); it != rev_graph[r].end(); it++) {
        second_dfs(it->first, anc);
    }

}
void PartI::showKoso() {
    for (int i = 0; i < ver; i++) {
        if (!scc[i].empty()) {
            for (int j = 0; j < scc[i].size(); j++) {
                cout << "scc[" << i << "]=" << scc[i][j] << endl;
            }
        }
    }
    cout << endl;
}

