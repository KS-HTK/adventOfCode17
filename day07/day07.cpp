//
// Created by hkoertge on 22.02.2024.
//

#include "day07.h"
#include "../util.h"
#include <map>
#include <utility>

Node::Node(const string& name, int weight, vector<string> c_list) {
    this->name = name;
    this->weight = weight;
    this->c_list = std::move(c_list);
    has_parents = false;
}

void Node::setHasParent() {
    has_parents = true;
}
int Node::getTotalWeight() {
    int total = weight;
    for (Node* n: children) {
        total += n->getTotalWeight();
    }
    return total;
}
string Node::as_string() {
    if (children.empty()) {
        return (name + "(" + to_string(weight) + ")");
    }
    return (name + "(" + to_string(weight) + ") -> " + this->name_list());
}
string Node::name_list() {
    string out;
    for (Node* n: children) {
        out += n->name;
        out += ", ";
    }
    out.pop_back();
    out.pop_back();
    return out;
}

map<string, Node> nmap;
string root;

string Day07::part_1(string input) {
    vector<string> lines = splitString(input, "\n");
    lines.pop_back();
    for (const string& line: lines) {
        vector<string> words = splitString(line, " ");
        string name = words.front();
        words.erase(words.begin());
        int weight = stoi(words.front().substr(1, words.front().size() - 2));
        if (words.size() == 1) {
            words.erase(words.begin());
        }
        else {
            words.erase(words.begin(), words.begin() + 2);
            for (string & word : words) {
                if (word.back() == ',') {
                    word = word.substr(0, word.size() - 1);
                }
            }
        }
        Node node = Node(name, weight, words);
        nmap[name] = node;
    }
    for (auto& p: nmap) {
        for (string& c: p.second.c_list) {
            nmap[c].setHasParent();
            p.second.children.push_back(&nmap[c]);
        }
        //cout << p.second.as_string() << endl;
    }
    for (auto& p: nmap) {
        if (!p.second.has_parents) {
            root = p.second.name;
            return root;
        }
    }

    return "No Parentless Node found";
}

int findImbalanceWeight(Node* node, int expected) {
    if (node->children.empty()) {
        return -1; // Leaf node, no imbalance
    }

    // Check if all children have the same total weight
    int targetWeight = node->children[0]->getTotalWeight();
    for (size_t i = 1; i < node->children.size(); i++) {
        if (node->children[i]->getTotalWeight() != targetWeight) {
            // Imbalance found, recursively check the imbalanced child
            return findImbalanceWeight(node->children[i], targetWeight);
        }
    }
    // All children have the same total weight, so the imbalance is in this node
    // Calculate the weight adjustment needed to balance the tower
    int totalWeight = node->getTotalWeight();
    int imbalance = expected - totalWeight;
    return node->weight + imbalance;
}

string Day07::part_2(string input) {
    // Find the weight needed to balance the tower
    int imbalanceWeight = findImbalanceWeight(&nmap[root], -1);
    return to_string(imbalanceWeight);
}