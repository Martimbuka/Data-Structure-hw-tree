#include <queue>
#include "LcRsTree.h"

namespace sd {

    void LcRsTree::clear( Node *&root ) {
        if ( root ) {
            clear( root->m_child );
            clear( root->m_sibling );
            delete root;
            root = nullptr;
        }
    }

    std::string LcRsTree::serialize() {
        std::stringstream ss;
        if ( !m_root ) {
            return "| |";
        } else {
            ss << "| " << m_root->m_value << " |\n";
        }

        std::queue< const Node * > front;
        front.push( m_root );
        front.push( nullptr );
        while ( true ) {
            const Node * current = front.front();
            front.pop();
            if ( !current ) {
                ss << "|\n";
                if ( front.empty() ) return ss.str();
                front.push( nullptr );
            } else {
                ss << "| ";
                for ( const Node * it = current->m_child ; it ; it = it->m_sibling ) {
                    ss << it->m_value << " ";
                    front.push( it );
                }
            }
        }
    }

    void LcRsTree::deserialize( std::stringstream &txt_tree ) {
        std::queue< Node * > front;
        std::string line;

        int previous_line_numbers = 0;
        int current_line_numbers = 0;
        int count_lines = 0;

        while ( std::getline( txt_tree, line ) ) { // read one line
            if ( line.empty() ) continue;

            std::stringstream ss_line( line );
            std::string token;
            int current_line_walls = 0;
            previous_line_numbers = current_line_numbers;
            current_line_numbers = 0;
            count_lines++;

            bool is_first_scope = false;
            bool is_first_line = false;

            while ( std::getline( ss_line, token, ' ' ) ) { // read one token from line (space separated)
                if ( token.empty() ) continue;

                if ( token == "|" ) {
                    ++current_line_walls;

                    if ( !is_first_scope ) {
                        is_first_scope = true;
                    } else if ( is_first_line ) {
                        is_first_line = false;
                    } else {
                        front.pop();
                    }

                } else {
                    //check if the token is a number
                    int value;
                    std::stringstream ss_token( token );
                    ss_token >> value;
                    if ( ss_token.fail() ) {
                        //std::cout << "Error: Deserialization failed (invalid token: " << token << ")" << std::endl;
                        this->clear( m_root );
                        throw std::invalid_argument( "Error: Deserialization failed (invalid token )" );
                        //return false;
                    }

                    if ( !is_first_scope ) {
                        //std::cout << "Error: Deserialization failed (scope not opened)" << std::endl;
                        this->clear( m_root );
                        throw std::invalid_argument( "Error: Deserialization failed (scope not opened)" );
                        //return false;
                    }

                    if ( !m_root && front.empty() ) { // if the tree is empty, create the root
                        m_root = new Node{ value };
                        ++current_line_numbers;
                        front.push( m_root );
                        is_first_line = true;
                        continue;
                    }

                    Node * current = front.front();

                    if ( !current ) {
                        continue;
                    } else {
                        if ( current->m_child ) {
                            Node * it = current->m_child;

                            while ( it->m_sibling ) {
                                it = it->m_sibling;
                            }

                            it->m_sibling = new Node{ value };
                            front.push( it->m_sibling );
                        } else {
                            current->m_child = new Node{ value };
                            front.push( current->m_child );
                        }

                        ++current_line_numbers;
                    }
                }
            }

            if ( current_line_walls != previous_line_numbers + 1 && count_lines != 1 ) {
                //std::cout << "Error: Deserialization failed (invalid ratio between walls and numbers)" << std::endl;
                this->clear( m_root );
                throw std::invalid_argument( "Error: Deserialization failed (invalid ratio between walls and numbers)" );
                //return false;
            }
        }

        //return true;
    }

    Node * LcRsTree::copy( Node * node ) {
        if ( !node ) {
            return nullptr;
        }

        Node * new_node = new Node{ node->m_value };
        new_node->m_sibling = copy( node->m_sibling );
        new_node->m_child = copy( node->m_child );

        return new_node;
    }

    bool LcRsTree::contains( Node * root, Node * tree ) const {
        if ( !tree ) {
            return true;
        }

        if ( !root ) {
            return false;
        }

        if ( are_identical( root, tree ) ) {
            return true;
        }

        return contains( root->m_child, tree ) || contains( root->m_sibling, tree );
    }

    bool LcRsTree::are_identical( Node * root_1, Node * root_2 ) const {
        if ( getSize( root_1 ) < getSize( root_2 ) ) {
            return false;
        }

        if ( !root_1 && !root_2 ) {
            return true;
        }

        if ( !root_1 || !root_2 ) {
            return false;
        }

        if ( root_1->m_value != root_2->m_value ) {
            return false;
        }

        if ( !root_2->m_child ) {
            return true;
        }


        std::queue< Node * > t1;
        std::queue< Node * > t2;
        t1.push( root_1 );
        t2.push( root_2 );

        unsigned size_children = 0;
        while ( !t2.empty() ) {
            Node * parent1 = t1.front();
            Node * parent2 = t2.front();

            unsigned num_of_children_parent2 = getNumChildren( parent2 );

            if ( size_children == num_of_children_parent2 ) {
                t1.pop();
                t2.pop();
                size_children = 0;
                continue;
            }

            if ( parent2->m_child && parent1->m_child ) {
                if ( queue_contains( t2, parent2->m_child ) ) {
                    Node * it = parent2->m_child->m_sibling;

                    while ( queue_contains( t2, it ) ) {
                        it = it->m_sibling;
                    }

                    if ( it ) {
                        t2.push( it );
                        ++size_children;

                        Node * parent1_it = parent1->m_child;
                        if ( parent1_it->m_value == it->m_value ) {
                            t1.push( parent1_it );
                        } else {
                            while ( parent1_it->m_sibling && parent1_it->m_sibling->m_value != it->m_value ) {
                                parent1_it = parent1_it->m_sibling;
                            }

                            if ( !parent1_it->m_sibling ) {
                                return false;
                            }

                            t1.push( parent1_it->m_sibling );
                        }
                    }

                } else {
                    t2.push( parent2->m_child );
                    ++size_children;

                    if ( parent1->m_child->m_value != parent2->m_child->m_value ) {
                        Node * it = parent1->m_child;

                        while ( it && it->m_sibling->m_value != parent2->m_child->m_value ) {
                            it = it->m_sibling;
                        }

                        if ( it->m_sibling->m_value != parent2->m_child->m_value ) {
                            return false;
                        }

                        t1.push( it->m_sibling );
                    } else {
                        t1.push( parent1->m_child );
                    }
                }
            } else if ( parent2->m_child && !parent1->m_child ) {
                return false;
            }
        }

        return true;
    }

    void LcRsTree::remove( Node *&first, Node * second, Node *&parent_first ) {
        //Post-order traversal
        if ( !first ) {
            return;
        }

        if ( first->m_child ) {
            remove( first->m_child, second, first );
        }

        if ( first->m_sibling ) {
            remove( first->m_sibling, second, parent_first );
        }

        if ( are_identical( first, second ) ) {
            Node * copy_first_sibling = first->m_sibling;

            if ( first->m_sibling ) {
                first->m_sibling = nullptr;
            }

            int sum_first_tree = getSum( first );
            int sum_second_tree = getSum( second );
            int remainder = sum_first_tree - sum_second_tree;
            unsigned size_first = getSize( first );
            unsigned size_second = getSize( second );

            first->m_sibling = copy_first_sibling;

            Node * sibling;
            Node * copy_first = first;
            if ( first->m_sibling ) {
                sibling = first->m_sibling;
                first->m_sibling = nullptr;

                if ( parent_first->m_child == first ) {
                    parent_first->m_child = nullptr;
                    parent_first->m_child = sibling;
                    clear( copy_first );
                } else {
                    Node * it = parent_first->m_child;
                    while ( it->m_sibling != first ) {
                        it = it->m_sibling;
                    }
                    clear( first );
                    it->m_sibling = nullptr;
                    it->m_sibling = sibling;

                }

            } else {
                sibling = nullptr;
                clear( first );
            }

            Node * temp = nullptr;

            if ( !is_child_of( parent_first, remainder ) ) {
                if ( size_first != size_second ) {
                    if ( !second->m_child && !second->m_sibling && remainder == second->m_value ) {
                    } else {
                        temp = new Node{ remainder, sibling };
                    }
                }
            }

            if ( sibling ) {
                if ( parent_first->m_child->m_value == sibling->m_value ) {
                    if ( temp ) {
                        parent_first->m_child = temp;
                    } else {
                        parent_first->m_child = sibling;
                    }
                } else {
                    Node * it = parent_first->m_child;
                    while ( it->m_sibling->m_value != sibling->m_value ) {
                        it = it->m_sibling;
                    }

                    if ( temp ) {
                        it->m_sibling = temp;
                    } else {
                        it->m_sibling = sibling;
                    }
                }
            } else if ( parent_first && parent_first->m_child ) {
                Node * it = parent_first->m_child;
                while ( it->m_sibling ) {
                    it = it->m_sibling;
                }
                it->m_sibling = temp;
            } else {
                if ( parent_first ) {
                    parent_first->m_child = temp;
                } else {
                    first = temp;
                }

            }

        }

    }

    bool LcRsTree::is_child_of( Node * root, const int &value ) const {
        if ( !root ) {
            return false;
        }

        if ( root->m_child ) {
            if ( root->m_child->m_value == value ) {
                return true;
            }

            Node * it = root->m_child;
            while ( it->m_sibling ) {
                if ( it->m_sibling->m_value == value ) {
                    return true;
                }
                it = it->m_sibling;
            }
        }

        return false;
    }

    unsigned LcRsTree::getSize( Node * root ) const {
        if ( !root ) {
            return 0;
        }

        return 1 + getSize( root->m_child ) + getSize( root->m_sibling );
    }

    int LcRsTree::getSum( Node * root ) const {
        if ( !root ) {
            return 0;
        }

        return root->m_value + getSum( root->m_child ) + getSum( root->m_sibling );
    }

    unsigned LcRsTree::getNumChildren( Node * root ) const {
        if ( !root ) {
            return 0;
        }

        unsigned num_of_children = 0;
        Node * it = root->m_child;
        while ( it ) {
            ++num_of_children;
            it = it->m_sibling;
        }

        return num_of_children;
    }

}
