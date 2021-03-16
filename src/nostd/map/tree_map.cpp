// #include "tree_map.hpp"
// #include <iostream>

// using namespace std;
// using namespace Nostd;


// template<typename K, typename V>
// TreeNode<K,V>::TreeNode(K key, V value){
//     this->key = key;
//     this->value = value;
// }

// template<typename K, typename V>
// Tree<K,V>::Tree(){
// }

// template<typename K, typename V>
// void Tree<K,V>::add(K key, V value){
//     TreeNode<K,V>* p = nullptr;
//     TreeNode<K,V>* t = this->root;
//     while(t != nullptr){
//         p = t;
//         if(key <= t->key)
//             t = t->left;
//         else
//             t = t->right;
//     }
//     if(p == nullptr) this->root = new TreeNode<K,V>(key, value);
//     else if(key <= p->key) p->left = new TreeNode<K,V>(key, value);
//     else p->right = new TreeNode<K,V>(key, value);
// }

// template<typename K, typename V>
// TreeMap<K,V>::TreeMap(){
//     this->tree = new Tree();
// }

// template<typename K, typename V>
// void TreeMap<K,V>::add(K key, V value){
//     this->tree->add(key, value);
// }

// //     struct B {
// //         int a;
// //         char b;
// //     };
// //     struct A
// //     {
// //         B b;
// //     };

// // void print_tree(TreeNode<A, int>* t){
// //     // in order
// //     if(t == nullptr){
// //         cout << "end" << endl;
// //         return;
// //     }
// //     cout << t -> key << endl;
// //     print_tree(t->left);
// //     print_tree(t->right);
// // }


// // int main(){
    
// //     Tree<A, int>* t = new Tree<A, int>();
// //     t->add({{0,'v'}}, 3);
// //     t->add({{4,'2'}}, 3);
// //     t->add({{6,'f'}}, 3);
// //     print_tree(t->root);
// //     return 0;
// // }
