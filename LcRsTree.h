#ifndef _LCRSTREE_H
#define _LCRSTREE_H

#include <iostream>
#include <sstream>
#include <queue>

namespace sd {

    class LcRsTree;

    class Node {
        explicit Node( const int &value, Node * sibling = nullptr, Node * child = nullptr )
                : m_value{ value },
                  m_sibling{ sibling },
                  m_child{ child } {}

        int m_value;
        Node * m_sibling;
        Node * m_child;

        friend class LcRsTree;
    };

    class LcRsTree {
    public:
        LcRsTree() : m_root{ nullptr } {}

        explicit LcRsTree( const int &value ) : m_root{ new Node{ value } } {}

        LcRsTree( const LcRsTree &other ) : m_root{ copy( other.m_root ) } {}

        ~LcRsTree() { clear( m_root ); }

        Node * getRoot() const { return m_root; }

        bool contains( const LcRsTree &tree ) const {
            if ( this->getSize( m_root ) < tree.getSize( tree.getRoot() ) ) {
                return false;
            }
            return contains( m_root, tree.getRoot() );
        }

        void remove( const LcRsTree &tree ) { remove( m_root, tree.getRoot(), m_root ); }

        std::string serialize();

        void deserialize( std::stringstream &txt_tree );

        LcRsTree &operator=( const LcRsTree &tree ) {
            if ( this == & tree ) {
                return * this;
            }
            clear( this->m_root );
            this->m_root = copy( tree.m_root );
            return * this;
        }

        bool is_empty() const { return m_root == nullptr; }

    private:
        Node * m_root;

    private:
        Node * copy( Node * node );

        void clear( Node *&root );

        int getSum( Node * root ) const;

        unsigned getSize( Node * root ) const;

        bool is_child_of( Node * root, const int &value ) const;

        static bool queue_contains( std::queue< Node * > queue, Node * node ) {
            while ( !queue.empty() ) {
                if ( queue.front() == node ) {
                    return true;
                }
                queue.pop();
            }
            return false;
        }

        unsigned getNumChildren( Node * root ) const;

        bool contains( Node * root, Node * tree ) const;

        bool are_identical( Node * root_1, Node * root_2 ) const;

        void remove( Node *&first, Node * second, Node *&parent_first );
    };
}// namespace sd
#endif