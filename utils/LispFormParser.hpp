/*********************************************************************************
 * File: LispFormParser.hpp
 * Description: Utility for reading Lisp Forms as Options from files
 * by BreakDS, Wed Jun  6 14:06:00 CDT 2012
 * Modification:
 * by BreakDS, Mon Jul  2 12:44:10 CDT 2012, add arithmetic support
 *********************************************************************************/

#pragma once

#include <map>
#include <vector>
#include <string>
#include "extio.hpp"

using std::vector;
using std::map;
using std::string;


class LispFormParser
{
private:
  
  static bool isSpace( const char ch )
  {
    /* whether char ch is a space */
    return '\t' == ch || ' ' == ch || 10 == ch || 13 == ch;
  }

  static bool isReturn( const char ch )
  {
    /* whether char ch is a return character */
    return 10 == ch || 13 == ch;
  }

  
  class Lisp
  {
  public:
    // Note: non-leaf lisp object only has a name
    string name;
    vector< Lisp > lst;
    Lisp()
    {
      /* constructor for empty object */
      name = "";
      lst.clear();
    }
    
    Lisp( FILE* stream, bool& indicator, LispFormParser& lfp )
    {

      name = "";
      lst.clear();


      // strip leading spaces
      char ch = static_cast<char>( getc( stream ) );
      while ( ch != EOF && isSpace( ch ) ) { 
	ch = static_cast<char>( getc( stream ) );
      }

      // remove comment lines
      if ( ';' == ch ) {
        while ( EOF != ch ) {
          if ( 10 == ch || 13 == ch ) {
            break;
          }
          ch = static_cast<char>( getc( stream ) );
        }
        indicator = true;
        return ;
      }

      if ( EOF == ch ) {
	indicator = false;
	return ;
      } else if ( '(' == ch ) {
	// Lisp Object
	bool more;
	Lisp tmp( stream, more, lfp );
	name = std::move( tmp.name );
	if ( "" == name ) {
	  Error( "LispFormParser: nil object." );
	  exit( -1 );
	}
        
	do {
	  Lisp tmp( stream, more, lfp );
	  if ( "" != tmp.name ) {
            if ( 0 == tmp.lst.size() && lfp.find( tmp.name ) ) {
              // is a defined variable
              lst.push_back( lfp[tmp.name].lst[0] );
            } else {
              lst.push_back( std::move( tmp ) );
            }
	  }
	} while ( more );

        // Evaluation if required
        if ( "/" == name ) {
          if ( 2 != lst.size() ) {
            Error( "LispFormParser: 2 operands required for / but %ld provided", lst.size() );
            exit(-1);
          }
          lst[0] /= lst[1];
          name = lst[0].name;
          lst.clear();
        } else if ( "-" == name ) {
          if ( 2 != lst.size() ) {
            Error( "LispFormParser: 2 operands required for - but %ld provided", lst.size() );
            exit(-1);
          }
          lst[0] -= lst[1];
          name = lst[0].name;
          lst.clear();
        } else if ( "+" == name ) {
          for ( int i=1, end=static_cast<int>( lst.size() ); i<end; i++ ) {
            lst[0] += lst[i];
          }
          name = lst[0].name;
          lst.clear();
        } else if ( "*" == name ) {
          for ( int i=1, end=static_cast<int>( lst.size() ); i<end; i++ ) {
            lst[0] *= lst[i];
          }
          name = lst[0].name;
          lst.clear();
        } else if ( ">>" == name ) {
          if ( 2 != lst.size() ) {
            Error( "LispFormParser: 2 operands required for >> but %ld provided", lst.size() );
            exit(-1);
          }
          lst[0] >>= lst[1];
          name = lst[0].name;
          lst.clear();
        }
	indicator = true;
      } else {
	// string object
	while ( ch != EOF && ch != ')' && (!isSpace(ch)) ) {
	  name += ch;
	  ch = static_cast<char>( getc( stream ) );
	}

	if ( EOF == ch || ')' == ch ) {
	  indicator = false;
	} else {
	  indicator = true;
	}
      }
    }

    Lisp( Lisp&& other ) 
    {
      /* Move Constructor */
      lst = std::move( other.lst );
      name = std::move( other.name );
    }

    
    Lisp( const Lisp& other )
    {
      lst = other.lst;
      name = other.name;
    }


    Lisp& operator=( const Lisp& other ) 
    {
      /* Move Constructor */
      if ( this != &other ) {
        lst = other.lst;
        name = other.name;
      }
      return *this;
    }


    Lisp& operator=( Lisp&& other ) 
    {
      /* Move Constructor */
      if ( this != &other ) {
        lst = std::move( other.lst );
        name = std::move( other.name );
      }
      return *this;
    }


    void operator-=( const Lisp& operand )
    {
      if ( 0 != lst.size() || 0 != operand.lst.size() ) {
        Error( "LispFormParser: invalid operands." );
        exit( -1 );
      }
      // Check whether it is floating or integer
      bool isInt0 = string::npos == name.find( '.' );
      bool isInt1 = string::npos == operand.name.find( '.' );
      char tmp[224];

      if ( isInt0 && isInt1 ) {
        sprintf( tmp, "%d", atoi( name.c_str() ) - atoi( operand.name.c_str() ) );
        name = tmp;
      } else {
        sprintf( tmp, "%.20lf", atof( name.c_str() ) - atof( operand.name.c_str() ) );
        name = tmp;
      }
    }

    void operator+=( const Lisp& operand )
    {
      if ( 0 != lst.size() || 0 != operand.lst.size() ) {
        Error( "LispFormParser: invalid operands." );
        exit( -1 );
      }
      // Check whether it is floating or integer
      bool isInt0 = string::npos == name.find( '.' );
      bool isInt1 = string::npos == operand.name.find( '.' );
      char tmp[224];

      if ( isInt0 && isInt1 ) {
        sprintf( tmp, "%d", atoi( name.c_str() ) + atoi( operand.name.c_str() ) );
        name = tmp;
      } else {
        sprintf( tmp, "%.20lf", atof( name.c_str() ) + atof( operand.name.c_str() ) );
        name = tmp;
      }
    }

    
    void operator*=( const Lisp& operand )
    {
      if ( 0 != lst.size() || 0 != operand.lst.size() ) {
        Error( "LispFormParser: invalid operands." );
        exit( -1 );
      }
      // Check whether it is floating or integer
      bool isInt0 = string::npos == name.find( '.' );
      bool isInt1 = string::npos == operand.name.find( '.' );
      char tmp[224];

      if ( isInt0 && isInt1 ) {
        sprintf( tmp, "%d", atoi( name.c_str() ) * atoi( operand.name.c_str() ) );
        name = tmp;
      } else {
        sprintf( tmp, "%.20lf", atof( name.c_str() ) * atof( operand.name.c_str() ) );
        name = tmp;
      }
    }

    void operator/=( const Lisp& operand )
    {
      if ( 0 != lst.size() || 0 != operand.lst.size() ) {
        Error( "LispFormParser: invalid operands." );
        exit( -1 );
      }
      // Check whether it is floating or integer
      char tmp[224];
      sprintf( tmp, "%.20lf", atof( name.c_str() ) / atof( operand.name.c_str() ) );
      name = tmp;
    }


    void operator>>=( const Lisp& operand )
    {
      if ( 0 != lst.size() || 0 != operand.lst.size() ) {
        Error( "LispFormParser: invalid operands." );
        exit( -1 );
      }
      // Check whether it is floating or integer
      bool isInt0 = string::npos == name.find( '.' );
      bool isInt1 = string::npos == operand.name.find( '.' );
      char tmp[224];

      if ( isInt0 && isInt1 ) {
        sprintf( tmp, "%d", atoi( name.c_str() ) >> atoi( operand.name.c_str() ) );
        name = tmp;
      } else {
        Error( "LispFormParser: Both operands for >> have to be integer." );
        exit( -1 );
      }
    }

    
    
    
    const Lisp& operator[]( const string& query ) const
    {
      for ( auto& item : lst ) {
        if ( query == item.name ) {
          return item;
        }
      }
      // Exception: Not Found
      Error( "LispFormParser: item \"%s\" not found.", query.c_str() );
      printf( "at %s:%d", __FILE__, __LINE__ );
      exit(-1);
    }

    const Lisp& operator[]( const int ind ) const
    {
      if ( ind >= 0 && ind < static_cast<int>( lst.size() ) ) {
        return lst[ind];
      }
      // Exception: out of range
      Error( "LispFormParser: [%d] out of range.", ind );
      exit(-1);
    }
    
    const char* c_str() const
    {
      if ( 1 == lst.size() ) {
        return lst[0].name.c_str();
      } else if ( 0 == lst.size() ) {
        return name.c_str();
      }
      // Exception: out of range
      Error( "LispFormParser: possibly accessing a composite form." );
      exit(-1);
    }

    int toInt() const
    {
      /* explicit conversion to int */
      if ( 1 == lst.size() ) {
        return atoi( lst[0].name.c_str() );
      } else if ( 0 == lst.size() ) {
        return atoi( name.c_str() );
      }
      // Exception: out of range
      Error( "LispFormParser: possibly accessing a composite form." );
      exit(-1);
    }

    operator int () const
    {
      if ( 1 == lst.size() ) {
        return atoi( lst[0].name.c_str() );
      } else if ( 0 == lst.size() ) {
        return atoi( name.c_str() );
      }
      // Exception: out of range
      Error( "LispFormParser: not an int; possibly accessing a coposite form." );
      exit( -1 );
    }

    operator const string& () const
    {
      /* implicit conversion to string */
      if ( 1 == lst.size() ) {
        return lst[0].name;
      } else if ( 0 == lst.size() ) {
        return name;
      }
      // Exception: out of range
      Error( "LispFormParser: not a string; possibly accessing a composite form." );
      exit(-1);
    }

    double toDouble() const
    {
      /* explicit conversion to double */
      if ( 1 == lst.size() ) {
        return atof( lst[0].name.c_str() );
      } else if ( 0 == lst.size() ) {
        return atof( name.c_str() );
      }
      // Exception: out of range
      Error( "LispFormParser: possibly accessing a composite form." );
      exit(-1);
    }

    bool atom() const
    {
      if ( 1 == lst.size() ) {
        return true;
      }
      return false;
    }

    int length() const
    {
      return static_cast<int>( lst.size() );
    }

    int size() const
    {
      return static_cast<int>( lst.size() );
    }


    void Summary( int indent=0 ) const
    {
      for ( int i=0; i<indent; i++ ) {
        printf( " " );
      }
      if ( 0 == lst.size() ) {
        printf( "%s\n", name.c_str() );
      } else if ( 1 == lst.size() && 0 == lst[0].lst.size() ) {
        printf( "%s: %s\n", name.c_str(), lst[0].name.c_str() );
      } else if ( lst.size() < 10 ) {
        printf( "%s:\n", name.c_str() );
        for ( auto& item : lst ) {
          item.Summary( indent + 4 );
        }
      } else {
        printf( "%s: list [%ld items]\n", name.c_str(), lst.size() );
      }
    }
  };
  
  map< string, Lisp > options;
  bool loaded;
public:

  LispFormParser()
  {
    loaded = false;
    options.clear();
  }
  
  void parse( const string& filename )
  {
    WITH_OPEN( in, filename.c_str(), "r" );
    loaded = true;
    bool more = false;
    do {
      Lisp tmp( in, more, *this );
      if ( "" != tmp.name ) {
        if ( "include" == tmp.name ) {
          parse( tmp[0].name );
        } else {
          options[tmp.name] = std::move( tmp );
        }
      } 
    } while ( more );
    END_WITH( in );
  }

  void Summary() const
  {
    for ( auto p=options.begin(); p!=options.end(); p++ ) {
      p->second.Summary();
    }
  }


  bool find( const string& query ) const
  {
    if ( !loaded ) {
      Error( "LispFormParser: please load a file first." );
      exit( -1 );
    }
    auto p = options.find( query );
    if ( options.end() != p ) {
      return true;
    }
    return false;
  }
  
  const Lisp& operator[]( const string& query ) const
  {
    auto p = options.find( query );
    if ( options.end() != p ) {
      return p->second;
    }
    // Exception: Not Found
    Error( "LispFormParser: item \"%s\" not found.", query.c_str() );
    exit(-1);
  }
  
};
