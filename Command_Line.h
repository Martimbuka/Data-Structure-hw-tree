#ifndef HOMEWORK_COMMAND_LINE_H
#define HOMEWORK_COMMAND_LINE_H

#include <iostream>
#include <fstream>
#include "Filename_Storage.h"

class Command_Line {
public:
    Command_Line() = default;

    Command_Line operator=( const Command_Line &other ) = delete;

    Command_Line( const Command_Line &other ) = delete;

    ~Command_Line() = default;

    void update() {
        while ( true ) {
            std::cout << "> ";
            std::string command;
            std::getline( std::cin, command );

            std::string command_name;
            std::string command_args;
            split_by_first_whitespace( command, command_name, command_args );

            remove_whitespaces_beggining( command_args );
            string_to_lowercase( command_name );

            try {

                if ( command_name == "exit" ) {
                    std::cout << "Successfully exited." << std::endl;
                    break;
                } else if ( command_name == "load" ) {
                    load( command_args );
                } else if ( command_name == "remove" ) {
                    remove( command_args );
                } else if ( command_name == "save" ) {
                    save( command_args );
                } else if ( command_name == "contains" ) {
                    contains( command_args );
                } else {
                    std::cout << "Unknown command: " << command_name << std::endl;
                }
            } catch ( const std::invalid_argument &e ) {
                std::cout << e.what() << std::endl;
            }

        }
    }

private:
    sd::Filename_Storage fs;

private:
    void remove_whitespaces_beggining( std::string &str ) {
        while ( str.front() == ' ' ) {
            str.erase( 0, 1 );
        }
    }

    void string_to_lowercase( std::string &str ) {
        for ( char &c: str ) {
            c = tolower( c );
        }
    }

    void split_by_first_whitespace( std::string &str, std::string &first, std::string &rest ) {
        int pos = str.find( ' ' );
        first = str.substr( 0, pos );
        str.erase( 0, pos + 1 );
        rest = str;
    }

    void load( std::string &args ) {
        std::string name;
        std::string path;
        split_by_first_whitespace( args, name, path );
        remove_whitespaces_beggining( path );

        // open file
        std::ifstream file( path );
        if ( !file.is_open() ) {
            //std::cout << "File not found" << std::endl;
            throw std::invalid_argument( "File not found" );
            //return false;
        }

        // read file
        std::string line;
        std::stringstream file_text;
        while ( std::getline( file, line ) ) {
            file_text << line << '\n';
        }
        file.close();

        sd::LcRsTree * tree = new sd::LcRsTree();

        tree->deserialize( file_text );

        fs.insert( name, * tree );

        //return true;
    }

    void save( std::string &args ) {
        std::string name;
        std::string path;

        split_by_first_whitespace( args, name, path );
        remove_whitespaces_beggining( path );

        std::ofstream file;
        file.open( path, std::ios::out );
        if ( !file ) {
            //std::cout << "Error during creating the file/opening the file" << std::endl;
            throw std::invalid_argument( "Error during creating the file/opening the file" );
            //return false;
        }

        sd::LcRsTree tree = fs.get_copy( name );
        if ( !tree.is_empty() ) {
            file << tree.serialize();
            file.close();
        } else {
            //std::cout << "Tree with this name " << name << " not found!" << std::endl;
            file.close();
            throw std::invalid_argument( "Tree with this name not found!" );
            //return false;
        }

        //return true;
    }

    bool contains( std::string &args ) {
        std::string tree_name_1;
        std::string tree_name_2;
        split_by_first_whitespace( args, tree_name_1, tree_name_2 );
        remove_whitespaces_beggining( tree_name_2 );

        const sd::LcRsTree tree_1 = fs.get_copy( tree_name_1 );
        const sd::LcRsTree tree_2 = fs.get_copy( tree_name_2 );

        if ( !tree_1.is_empty() && !tree_2.is_empty() ) {
            std::cout << std::boolalpha << tree_1.contains( tree_2 ) << std::endl;
        } else {
            std::cout << "Tree with this name " << tree_name_1 << " or " << tree_name_2
                      << " not found in the dictionary!" << std::endl;
            return false;
        }

        return true;
    }

    void remove( std::string &args ) {
        std::string tree_name_1;
        std::string tree_name_2;
        split_by_first_whitespace( args, tree_name_1, tree_name_2 );
        remove_whitespaces_beggining( tree_name_2 );

        sd::LcRsTree &tree_1 = fs.get( tree_name_1 );
        sd::LcRsTree &tree_2 = fs.get( tree_name_2 );

        if ( !tree_1.is_empty() && !tree_2.is_empty() ) {
            tree_1.remove( tree_2 );
            std::cout << tree_1.serialize() << std::endl;
        } else {
            //std::cout << "Tree with this name " << tree_name_1 << " or " << tree_name_2
            //          << " not found in the dictionary!" << std::endl;
            throw std::invalid_argument( "Tree with this name not found in the dictionary!" );
            //return false;
        }

        //return true;
    }
};


#endif //HOMEWORK_COMMAND_LINE_H
