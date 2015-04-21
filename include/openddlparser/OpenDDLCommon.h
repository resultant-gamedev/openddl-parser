/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014-2015 Kim Kulling

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-----------------------------------------------------------------------------------------------*/
#pragma once
#ifndef OPENDDLPARSER_OPENDDLPARSERCOMMON_H_INC
#define OPENDDLPARSER_OPENDDLPARSERCOMMON_H_INC

#include <cstddef>
#include <vector>

#include <string.h>

#ifdef _MSC_VER
#   define TAG_DLL_EXPORT __declspec(dllexport)
#   define TAG_DLL_IMPORT __declspec(dllimport )
#   ifdef OPENDDLPARSER_BUILD
#       define DLL_ODDLPARSER_EXPORT TAG_DLL_EXPORT
#   else
#       define DLL_ODDLPARSER_EXPORT TAG_DLL_IMPORT
#   endif // OPENDDLPARSER_BUILD
#   pragma warning( disable : 4251 )
#else
#   define DLL_ODDLPARSER_EXPORT
#endif // _WIN32

#define BEGIN_ODDLPARSER_NS namespace ODDLParser {
#define END_ODDLPARSER_NS   } // namespace ODDLParser
#define USE_ODDLPARSER_NS   using namespace ODDLParser;

BEGIN_ODDLPARSER_NS

#ifndef OPENDDL_NO_USE_CPP11
#   define ddl_nullptr nullptr
#else
#   define ddl_nullptr NULL
#endif // OPENDDL_NO_USE_CPP11

class DDLNode;
class Value;

struct Name;
struct Identifier;
struct Reference;
struct Property;
struct DataArrayList;

typedef char           int8;
typedef short          int16;
typedef int            int32;
typedef long           int64;
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef unsigned long  uint64;

enum NameType {
    GlobalName,
    LocalName
};

struct Identifier {
    size_t m_len;
    char *m_buffer;

    Identifier( size_t len, char buffer[] )
        : m_len( len )
        , m_buffer( buffer ) {
        // empty
    }

    bool operator == ( const Identifier &rhs ) const {
        if( rhs.m_len != m_len ) {
            return false;
        }

        for( size_t i = 0; i < m_len; ++i ) {
            if( m_buffer[ i ] != rhs.m_buffer[ i ] ) {
                return false;
            }
        }

        return true;
    }

private:
    Identifier( const Identifier & );
    Identifier &operator = ( const Identifier & );
};

struct Name {
    NameType    m_type;
    Identifier *m_id;

    Name( NameType type, Identifier *id )
        : m_type( type )
        , m_id( id ) {
        // empty
    }

private:
    Name( const Name & );
    Name &operator = ( const Name& );
};

struct Reference {
    size_t   m_numRefs;
    Name   **m_referencedName;

    Reference()
    : m_numRefs( 0 )
    , m_referencedName( ddl_nullptr ) {
        // empty
    }
     
    Reference( size_t numrefs, Name **names )
    : m_numRefs( numrefs )
    , m_referencedName( ddl_nullptr ) {
        m_referencedName = new Name *[ numrefs ];
        for( size_t i = 0; i < numrefs; i++ ) {
            Name *name = new Name( names[ i ]->m_type, names[ i ]->m_id );
            m_referencedName[ i ] = name;
        }
    }

private:
    Reference( const Reference & );
    Reference &operator = ( const Reference & );
};

struct Property {
    Identifier *m_key;
    Value *m_value;
    Reference *m_ref;
    Property *m_next;

    Property( Identifier *id )
        : m_key( id )
        , m_value( ddl_nullptr )
        , m_ref( ddl_nullptr )
        , m_next( ddl_nullptr ) {
        // empty
    }

private:
    Property( const Property & );
    Property &operator = ( const Property & );
};

struct DataArrayList {
    size_t m_numItems;
    Value *m_dataList;
    DataArrayList *m_next;

    DataArrayList()
        : m_numItems( 0 )
        , m_dataList( ddl_nullptr )
        , m_next( ddl_nullptr ) {
        // empty
    }

private:
    DataArrayList( const DataArrayList & ); 
    DataArrayList &operator = ( const DataArrayList & );

};

struct Context {
    DDLNode *m_root;

    Context()
        : m_root( ddl_nullptr ) {
        // empty
    }

private:
    Context( const Context & );
    Context &operator = ( const Context & );
};

END_ODDLPARSER_NS

#endif // OPENDDLPARSER_OPENDDLPARSERCOMMON_H_INC

