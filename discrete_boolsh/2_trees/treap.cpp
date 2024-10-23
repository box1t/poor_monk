

std::pair<Node*, Node*> split(Node* tree, const std::string& key) {
    if (tree == nullptr) {
        return {nullptr, nullptr};
    }

    if (tree->key == key) {
        Node* t1 = tree->left;
        Node* t2 = tree->right;
        delete tree;
        return {t1, t2};
    } else if (tree->key < key) {
        auto pr = split(tree->right, key);
        tree->right = pr.first;
        return {tree, pr.second};
    } else {
        auto pr = split(tree->left, key);
        tree->left = pr.second;
        return {pr.first, tree};
    }
}


Node* merge(Node* t1, Node* t2) {
    if (!t1 && !t2) {
        return nullptr;
    } else if (t1 && !t2) {
        return t1;
    } else if (!t1 && t2) {
        return t2;
    }

    if (t1->priority >= t2->priority) {
        t1->right = merge(t1->right, t2);
        return t1;
    } else {
        t2->left = merge(t2->left, t1);
        return t2;
    }
}