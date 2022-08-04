#ifndef HOMEWORK_FILENAME_STORAGE_H
#define HOMEWORK_FILENAME_STORAGE_H

#include <string>
#include <iostream>
#include "LcRsTree.h"

namespace sd {

    class TrieNode {
        static const int CHARACTER_SIZE = 128;

        explicit TrieNode( const char &data, const bool is_end_of_word = false )
                : m_data{ data }, m_is_end_of_word{ is_end_of_word } {
            for ( TrieNode *&child: m_children ) {
                child = nullptr;
            }
        }

        char m_data;
        bool m_is_end_of_word;
        TrieNode * m_children[CHARACTER_SIZE];
        sd::LcRsTree m_tree;

        friend class Filename_Storage;
    };

    class Filename_Storage {
    public:
        Filename_Storage() : m_root{ new TrieNode{ '\0' } } {}

        ~Filename_Storage() { clear( m_root ); }

        bool insert( const std::string &filename, const sd::LcRsTree &tree ) {
            return insert( m_root, filename, tree );
        }

        sd::LcRsTree get_copy( const std::string &filename ) const {
            return get_copy( m_root, filename );
        }

        sd::LcRsTree &get( const std::string &filename ) {
            return get( m_root, filename );
        }

    private:
        TrieNode * m_root;

    private:
        void clear( TrieNode * node );

        sd::LcRsTree get_copy( TrieNode * root, const std::string &filename ) const;

        sd::LcRsTree &get( TrieNode * root, const std::string &filename );

        bool insert( TrieNode *&root, const std::string &filename, const sd::LcRsTree &tree );

    };

} // sd

#endif //HOMEWORK_FILENAME_STORAGE_H
