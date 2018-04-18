# include <iostream>
# include <stdio.h>
# include <stdlib.h>
# include <string>
# include <vector>
# include <ctype.h>
# include <iomanip>


using namespace std;

// ======================Data Struct==============================
enum Error_type{ UNRECOGNIZED, UNDEFINED, UNEXPECTED, ERROR };

struct Identify_Data{
  string identify_Name ;
  double identify_value ;
  bool isFloat ;
} ;

// ===============================================================

// ======================global var===============================
string gNowToken ;
string gBoolAns ;
vector<Identify_Data> gId ;
int gTestNum = 0 ;
bool gChange = false ;
bool gIsBoolOP = false ;
bool gQuit = false ;
bool gIsFloat = false ;
char gUnknowChar ;
// ===============================================================

void InitializeState() ;
// =======================use for get token=======================
string GetToken() ;
void SkipExitChar() ;
string ReadConstant() ;
string ReadIdent() ;
string ReadOPAndComment() ;
void TakeToken() ;
void ReadAfterError() ;
// =======================Judge Token============================
bool JudgeTypeSpec( string token ) ;
bool JudgeIDENT( string Token ) ;
bool JudgeNum( string Token ) ;
bool JudgeFloat( string Token ) ;
bool JudgeInt( string Token ) ;
bool JudgeConstant( string Token ) ;
// ===============================================================

// =======================Recursive===============================
void User_input() ;
void Definition() ;
void Statement() ;
void Function_definition_without_ID() ;
void Function_definition_or_declarators() ;
// ===============================================================


int main() {
  while ( !gQuit ) {
    InitializeState() ;
    try {
      User_input() ;
    } // try
    catch ( Error_type error ) {
      ReadAfterError() ;
      if ( error == UNRECOGNIZED ) {
        cout << "Unrecognized token with first char : '" << gUnknowChar << "'" << endl ;
      } // if
      else if ( error == UNDEFINED ) {
        cout << "Undefined identifier : '" << gNowToken << "'" << endl ;
      } // else if
      else if ( error == UNEXPECTED ) {
        cout << "Unexpected token : '" << gNowToken << "'" << endl ;
      } // else if
      else if ( error == ERROR ) {
        cout << "Error" << endl ;
        return 0 ;
      } // else if
    } // catch
  } // while

} // main()

string GetToken() {

  char aChar ;
  char peekChar ;
  SkipExitChar() ; // skip white space and other
  string token = "" ;
  peekChar = cin.peek() ;
  if ( isalnum( peekChar ) || peekChar == '_' || peekChar == '.'
       || peekChar == '\'' || peekChar == '"' ) {
    if ( isdigit( peekChar ) || peekChar == '.' || peekChar == '\'' || peekChar == '"' ) {
      token = ReadConstant() ;
    } // if
    else {
      token = ReadIdent() ;
    } // else

  } // if
  else if ( peekChar == '(' || peekChar == ')' || peekChar == '[' || peekChar == ']' ||
            peekChar == '{' || peekChar == '}' || peekChar == '+' || peekChar == '-' ||
            peekChar == '*' || peekChar == '/' || peekChar == '%' || peekChar == '^' ||
            peekChar == '>' || peekChar == '<' || peekChar == '!' || peekChar == '&' ||
            peekChar == '|' || peekChar == '=' || peekChar == ';' || peekChar == ',' ||
            peekChar == '?' || peekChar == ':' ) {
    token = ReadOPAndComment() ;
  } // else if
  else {
    if ( !isalnum( peekChar ) && peekChar != '_' && peekChar != '(' && peekChar != ')' &&
            peekChar != '{' && peekChar != '}' && peekChar != '+' && peekChar != '-' &&
            peekChar != '*' && peekChar != '/' && peekChar != '%' && peekChar != '^' &&
            peekChar != '>' && peekChar != '<' && peekChar != '!' && peekChar != '&' &&
            peekChar != '|' && peekChar != '=' && peekChar != ';' && peekChar != ',' &&
            peekChar != '?' && peekChar != ':' && peekChar != '[' && peekChar != ']' ) {
      gUnknowChar = peekChar ;
      throw UNRECOGNIZED ;
    } // if all possibly start

  } // else



  return token ;

} // GetToken()

string ReadConstant() {
  char aChar ;
  char peekChar ;
  string token ;
  token.clear() ;

  peekChar = cin.peek() ;

  if ( peekChar == '.' ) {
    aChar = cin.get() ; // read '.'
    token = token + aChar ;
    peekChar = cin.peek() ;
    while ( isdigit( peekChar ) ) {
      aChar = cin.get() ;
      token = token + aChar ;
      peekChar = cin.peek() ;
    } // while
  } // if
  else if ( isdigit( peekChar ) ) {
    while ( isdigit( peekChar ) ) {
      aChar = cin.get() ;
      token = token + aChar ;
      peekChar = cin.peek() ;
    } // while

    if ( peekChar == '.' ) {
      aChar = cin.get() ; // read '.'
      token = token + aChar ;
      peekChar = cin.peek() ;
      while ( isdigit( peekChar ) ) {
        aChar = cin.get() ;
        token = token + aChar ;
        peekChar = cin.peek() ;
      } // while
    } // if

  } // else if
  else if ( peekChar == '\'' ) {
    aChar = cin.get() ; // read '
    token = token + aChar ;
    peekChar = cin.peek() ;
    while ( peekChar != '\'' ) {
      aChar = cin.get() ;
      token = token + aChar ;
      peekChar = cin.peek() ;
    } // while

    aChar = cin.get() ; // read '
    token = token + aChar ;
  }  // else if
  else if ( peekChar == '"' ) {
    aChar = cin.get() ; // read "
    token = token + aChar ;
    peekChar = cin.peek() ;
    while ( peekChar != '"' ) {
      aChar = cin.get() ;
      token = token + aChar ;
      peekChar = cin.peek() ;
    } // while

    aChar = cin.get() ; // read '
    token = token + aChar ;
  }  // else if

  return token ;
} // ReadConstant()

string ReadIdent() {
  char aChar ;
  char peekChar ;
  string token ;
  token.clear() ;

  peekChar = cin.peek() ;
  while ( isalnum( peekChar ) || peekChar == '_' ) {
    aChar = cin.get() ;
    token = token + aChar ;
    peekChar = cin.peek() ;
  } // while

  return token ;
} // ReadIdent()

string ReadOPAndComment() {
  char peekChar ;
  char aChar ;
  string token ;
  token.clear() ;
  peekChar = cin.peek() ;

  if ( peekChar == '(' || peekChar == ')' || peekChar == '[' || peekChar == ']' ||
       peekChar == '{' || peekChar == '}' || peekChar == ';' || peekChar == ',' ||
       peekChar == '?' || peekChar == ':' ) {
    aChar = cin.get() ;
    token = token + aChar ;
  } // if
  else if ( peekChar == '+' || peekChar == '-' || peekChar == '*' ||
            peekChar == '/' || peekChar == '%' || peekChar == '^' ) {
    aChar = cin.get() ;
    token = token + aChar ;
    peekChar = cin.peek() ;
    if ( aChar == '+' || aChar == '-' ) {

      if ( peekChar == '=' ) {
        aChar = cin.get() ;
        token = token + aChar ;
      } // if += -+
      else if ( aChar == '+' && peekChar == '+' ) {
        aChar = cin.get() ;
        token = token + aChar ;
      } // else if ++
      else if ( aChar == '-' && peekChar == '-' ) {
        aChar = cin.get() ;
        token = token + aChar ;
      } // else if --

    } // if
    else if ( aChar == '*' || aChar == '/' || aChar == '%' || aChar == '^' ) {

      if ( peekChar == '=' ) {
        aChar = cin.get() ;
        token = token + aChar ;
      } // if
      else if ( aChar == '/' && peekChar == '/' ) {
        char comment[500] ;
        cin.getline( comment , 500 ) ;
        token = GetToken() ;
      } // else if comment

    } // else if
  } // else if
  else if ( peekChar == '>' || peekChar == '<' || peekChar == '=' || peekChar == '!' ) {
    aChar = cin.get() ;
    token = token + aChar ;
    peekChar = cin.peek() ;
    if ( peekChar == '=' ) {
      aChar = cin.get() ;
      token = token + aChar ;
    } // if >= <= ==
    else if ( aChar == '>' && peekChar == '>' ) {
      aChar = cin.get() ;
      token = token + aChar ;
    } // else if >>
    else if ( aChar == '<' && peekChar == '<' ) {
      aChar = cin.get() ;
      token = token + aChar ;
    } // else if <<

  } // else if
  else if ( peekChar == '&' || peekChar == '|' ) {
    aChar = cin.get() ;
    token = token + aChar ;
    peekChar = cin.peek() ;
    if ( aChar == '&' && peekChar == '&' ) {
      aChar = cin.get() ;
      token = token + aChar ;
    } // if
    else if ( aChar == '|' && peekChar == '|' ) {
      aChar = cin.get() ;
      token = token + aChar ;
    } // else if

  } // else if

  return token ;
} // ReadOPAndComment()

void ReadAfterError() {
  char aChar ;
  aChar = cin.peek() ;
  while ( aChar != '\n' ) {
    aChar = cin.get() ;
    aChar = cin.peek() ;
  } // while
} // ReadAfterError()

void InitializeToken() {
  gNowToken.clear() ;
} // InitializeToken()

void InitializeState() {
  gNowToken.clear() ;
  gBoolAns.clear() ;
  gIsFloat = false ;
  gQuit = false ;
  gIsBoolOP = false ;
  gChange = false ;
  gUnknowChar = '\0' ;
} // InitializeState()

void TakeToken() {
  gNowToken.clear() ;
} // TakeToken()

void SkipExitChar() {
  char aChar ;
  char exitChar ;
  aChar = cin.peek() ;

  if ( aChar != ' ' && aChar != '\n' && aChar != '\0' && aChar != '\t' ) {
    return ;
  } // if
  else {

    while ( aChar == ' ' || aChar == '\n' || aChar == '\0' || aChar == '\t' ) {
      exitChar = cin.get() ;
      aChar = cin.peek() ;
    } // while

  } // else

} // SkipExitChar()

bool JudgeIDENT( string Token ) {
  int length = Token.length() ;
  int correct = 0 ;

  if ( Token == "int" || Token == "float" || Token == "char" ||
       Token == "bool" || Token == "string" || Token == "void" ||
       Token == "if" || Token == "else" || Token == "while" ||
       Token == "do" || Token == "return" || Token == "true" || Token == "false" ) {
    return false ;
  } // if

  if ( isalpha( Token.at( 0 ) ) || Token.at( 0 ) == '_' ) {
    correct++ ;
  } // if a~z||A~Z|| _

  for ( int i = 1 ; i < length ; i++ ) {
    if ( isalnum( Token.at( i ) ) || Token.at( i ) == '_' ) {
      correct++ ;
    } // if  a~z || A~Z || 0~9 || _
  } // for

  if ( correct == length ) return true ;

  return false ;

} // JudgeIDENT()

bool JudgeNum( string Token ) {
  if ( JudgeFloat( Token ) || JudgeInt( Token ) ) {
    return true ;
  } // if

  return false ;
} // JudgeNum()

bool JudgeInt( string Token ) {
  int length = Token.length() ;
  int correct = 0 ;
  for ( int i = 0 ; i < length ; i++ ) {
    if ( Token.at( i ) >= '0' && Token.at( i ) <= '9' ) {
      correct++ ;
    } // if  0~9
  } // for

  if ( correct == length ) return true ;

  return false ;
} // JudgeInt()

bool JudgeFloat( string Token ) {
  int length = Token.length() ;
  int correct = 0 ;
  bool find_point = false ;

  if ( Token == "." ) {
    return false ;
  } // if just one point '.'

  for ( int i = 0 ; i < length ; i++ ) {
    if ( Token.at( i ) >= '0' && Token.at( i ) <= '9' ) {
      correct++ ;
    } // if  0~9
    else if ( Token.at( i ) == '.' && !find_point ) {
      correct++ ;
      find_point = true ;
    } // else if judge 123.111 && .2 && 2. should take care
  } // for

  if ( correct == length && find_point ) return true ;

  return false ;
} // JudgeFloat()

bool JudgeTypeSpec( string Token ) {

  if ( Token == "int" || Token == "float" || Token == "char" ||
       Token == "bool" || Token == "string" ) {
    return true ;
  } // if

} // JudgeTypeSpec()

bool JudgeConstant( string Token ) {
  char first_char = Token[0] ;
  char last_char = Token[ ( Token.length() - 1 ) ] ;

  if ( JudgeNum( Token ) ) {
    return true ;
  } // if
  else if ( ( first_char == '\'' && last_char == '\'' ) || ( first_char == '"' && last_char == '"' ) ) {
    return true ;
  } // else if 'aaa' "aaa"
  else if ( Token == "true" || Token == "false" ) {
    return true ;
  } // else if
  else {
    return false ;
  } // else

  return false ;

} // JudgeConstant()

bool JudgeStatment( string Token ) {
  if ( Token == ";" || Token == "return" || Token == "if" || Token == "while" ||
       Token == "do" || Token == "{" || Token == "++" || Token == "--" ||
       JudgeIDENT( Token ) || Token == "+" || Token == "-" || Token == "!" ||
       JudgeConstant( Token ) ) {
    return true ;
  } // if

  return false ;

} // JudgeStatment()

void User_input() {
  if ( gNowToken.empty() ) {
    gNowToken = GetToken() ;
  } // if

  if ( gNowToken == "void" || JudgeTypeSpec( gNowToken ) ) {
    Definition() ;
  } // if
  else if ( JudgeStatment( gNowToken ) ) {
    Statement() ;
  } // else if
  else {

  } // else
} // User_input()

void Definition() {
  string type_spec = gNowToken ;
  string id_name ;
  TakeToken() ; // take void || type_spec

  if ( type_spec == "void" ) {
    if ( gNowToken.empty() ) {
      gNowToken = GetToken() ; // get IDENT
    } // if

    if ( JudgeIDENT( gNowToken ) ) {
      id_name = gNowToken ;
    } // if
    else {
      throw UNEXPECTED ;
    } // else

    Function_definition_without_ID() ;
  } // if
  else if ( JudgeTypeSpec( type_spec ) ){
    if ( gNowToken.empty() ) {
      gNowToken = GetToken() ; // get IDENT
    } // if

    if ( JudgeIDENT( gNowToken ) ) {
      id_name = gNowToken ;
    } // if
    else {
      throw UNEXPECTED ;
    } // else

    Function_definition_or_declarators() ;
  } // else if
  else {
    throw UNEXPECTED ;
  } // else

} // Definition()

void Statement() {
} // Statement()

void Function_definition_without_ID() {
  cout << "IS DEF" ;
} // Function_definition_without_ID()

void Function_definition_or_declarators() {
  cout << "IS DEF" ;
} // Function_definition_or_declarators()
