#include "Filename_Storage.h"

namespace sd {

    void Filename_Storage::clear( TrieNode * node ) {
        if ( !node ) {
            return;
        }

        for ( TrieNode *&child: node->m_children ) {
            clear( child );
        }

        delete node;
        node = nullptr;

    }

    sd::LcRsTree
    Filename_Storage::get_copy( TrieNode * current, const std::string &filename ) const { // returns a copy of the tree
        if ( !current ) {
            return sd::LcRsTree{};
        }

        for ( const char &c: filename ) {
            int index = static_cast<int>(c);
            current = current->m_children[index];

            if ( !current ) {
                return sd::LcRsTree{};
            }
        }

        if ( current->m_is_end_of_word ) {
            // create a copy of the tree
            return sd::LcRsTree{ current->m_tree };
        }

        return sd::LcRsTree{};
    }

    bool Filename_Storage::insert( TrieNode *&root, const std::string &filename, const sd::LcRsTree &tree ) {
        TrieNode * temp = root;
        for ( const char &c: filename ) {
            int index = static_cast<int>(c);
            if ( temp->m_children[index] == nullptr ) {
                temp->m_children[index] = new TrieNode{ c };
            }

            temp = temp->m_children[index];
        }

        temp->m_is_end_of_word = true;
        temp->m_tree = tree;
        return true;
    }

    sd::LcRsTree &Filename_Storage::get( TrieNode * root, const std::string &filename ) {
        if ( !root ) {
            return m_root->m_tree;
        }

        for ( const char &c: filename ) {
            int index = static_cast<int>(c);
            root = root->m_children[index];

            if ( !root ) {
                return m_root->m_tree;
            }
        }

        if ( root->m_is_end_of_word ) {
            return root->m_tree;
        }

        return m_root->m_tree;
    }

} // sd